<?php
// $Id: notifications.cron.inc,v 1.6.2.6.2.20.2.8 2009/10/05 17:51:13 jareyero Exp $
/**
 * Notifications module. Queue processing.
 * 
 * Callbacks for queue processing. They may be implemented by other modules
 *    _load_user()
 *    _user_allowed()
 *    _process_send()
 * 
 * @ TO DO: Support different languages for message localization
 */

// Number of users to process for each step
define('NOTIFICATIONS_STEP_ROWS', 1000);
define('NOTIFICATIONS_STEP_USERS', 1000);

// Minimum amount of seconds the process will need for clean-up tasks
// Just to make sure that after exhausting cron assigned time we'll have a few spare seconds for some cleanup
define('NOTIFICATIONS_TIME_MARGIN', 5);

/**
 * Function to be called on cron by the main notifications_cron
 * 
 * It will call each subscription_process for each interval a number of times
 * 
 * This should send out messages starting with immediate delivery. We send first immediate delivery
 * because the other ones can be added up for each period. 
 * Assumption: The bigger the interval, the longer delay it may admit (?) I.e. sending hourly email 
 * after 1 hour 15 mins may be ok if the system is overloaded.
 */
function notifications_process_run($cron = TRUE) {  
  notifications_log('Starting notifications process');
  notifications_process('start');
  // There may be special time adjustments for cron
  if ($cron) {
    notifications_process('cron');
  }
  $stop = FALSE;
  $send_intervals = _notifications_send_intervals();
  unset($send_intervals[-1]);
  if ($max_sqid = notifications_process_prepare()) {
    foreach ($send_intervals as $interval => $name) {
      notifications_log('Processing queue', array('send interval' => $name));
      while (notifications_process_queue($interval, $max_sqid)) {
        $stop = !notifications_process('check');
      }
      if ($stop) {
        notifications_log('Process stopped, reached processing limits');
        break;
      } else {
        notifications_log('Process finished', array('send interval' => $name));
      }
    }
  } else {
    notifications_log('No rows in queue');
  }
}

/**
 * Prepare subscriptions queue
 * 
 * This is intended to avoid race conditions where new rows are added while the process is running
 * 
 * @return
 *   Max $sqid that will be processed this cron
 */
function notifications_process_prepare() {
  // Clean up expired logs from queue if logging enabled
  if ($keep = variable_get('notifications_log', 0)) {
    db_query("DELETE FROM {notifications_queue} WHERE cron = 0 AND sent < %d", time() - $keep);
  }
  // Clean up event table
  notifications_event_clean();
  // This will get the latest notification in queue so we don't mess with new ones being created during cron run
  // It will also prevent clashes with the immediate sending feature
  return db_result(db_query("SELECT max(sqid) FROM {notifications_queue}"));
}

/**
 * Clean up event table
 * 
 * @param $update
 *   Update event counter
 */
function notifications_event_clean($update = FALSE) {
  // This expiretime will prevent some race condition that occurs when the event is saved but the subs queue not yet populated  
  $expiretime = time() - 60; 
  if ($update) {
    // Update event counter, which keeps the number of notifications pending for each event
    db_query("UPDATE {notifications_event} e SET counter = (SELECT COUNT(*) FROM {notifications_queue} q WHERE q.eid = e.eid ) WHERE e.created < %d", $expiretime);
  }
  db_query("DELETE FROM {notifications_event} WHERE counter = 0 AND created < %d", $expiretime);
  // Delete events with no pending notifications. As events are created sequentially, we use this fact to speed up the query
  db_query("DELETE FROM {notifications_event} WHERE created < %d AND eid < (SELECT MIN(eid) FROM {notifications_queue})", $expiretime); 
}

/**
 * Controls and checks limits for queue processing
 * It can be used by other modules to add their own limits here, like number of sms sent, etc...
 * @param $op
 *   'start' => Start the counters
 *   'cron' => Special time adjustment for cron operations
 *   'init' => Start a new counter with $value limit
 *   'option' => Sets /gets options
 *      - debug
 *      - output Enables output for admin page
 * @return
 *   TRUE if we are yet under the processing limits
 */
function notifications_process($op = 'check', $name = NULL, $value = NULL) {
  static $limit = array(), $options = array();
  static $current = array('message' => 0, 'step' => 0);

  switch ($op) {
    case 'start':
      $defaults = variable_get('notifications_process_limit', array('time' => 0, 'message' => 0, 'row' => 0, 'percent' => 0));
      foreach ($defaults as $name => $value) {
        if ($value && !isset($limit[$name])) {
          $limit[$name] = $value;
        }
      }
      break;
    case 'cron':
      // Calculate time limit. We get the smaller of all these times in seconds
      // There's an issue with poormanscron not setting the cron semaphore so it will default to current time
      $timelimit = array();
      $cronstart = variable_get('cron_semaphore', time());
      
      // Max execution time may be zero meaning no limit, then no limits based on this
      if ($maxtime = ini_get('max_execution_time')) {
        $timelimit[] =  $cronstart + $maxtime - NOTIFICATIONS_TIME_MARGIN;
        if (!empty($limit['percent'])) {
          $timelimit[] = time() + $maxtime * $limit['percent'] / 100;
          unset($limit['percent']);
        }
      }
      // This is an absolute limit, applies always if set
      if (!empty($limit['time'])) {
        $timelimit[] = time() + $limit['time'];
      }
      if ($timelimit) {
        $limit['time'] = min($timelimit);
      }
      break;

      break;
    case 'init':
      $current[$name] = 0;
      $limit[$name] = $value;
      break;
    case 'count':
      $value =  $value ? $value : 1;
      isset($current[$name]) ? ($current[$name] += $value) : $current[$name] = $value;
      break;
    case 'option':
      if (isset($value)) {
        $options[$name] = $value;
      }
      return isset($options[$name]) ? $options[$name] : FALSE;
  }
  
  $current['time'] = time();
  
  // Check all limits till we find a false one
  foreach ($limit as $name => $value) {
    if ($value && !empty($current[$name]) && $current[$name] >= $value) {
      watchdog('notifications', 'Reached processing limit on queue processing: %name = %value', array('%name' => $name, '%value' => $value));
      return FALSE;
    }
  }
  return TRUE;
}

/**
 * Process rows given query conditions
 * 
 * This is used by the immediate sending feature
 * @see notifications_queue_query()
 * 
 * @param $conditions
 *   Array of query conditions
 * @param $limit
 *   Optional, limit the number of rows to process
 * @param $update
 *   Optional, update queue rows and event counter after processing
 */
function notifications_process_rows($conditions, $limit = 0, $update = TRUE) {
  notifications_log('Processing queue rows', $conditions);
  $account = $destination = NULL;
  $subscriptions = $events = $processed = array();
  $send_method = $send_interval = $module = NULL;
  $test = notifications_process('option', 'test');
  $count = 0;

  // Build query and fetch rows from queue
  $query = notifications_queue_query($conditions);
  $sql = "SELECT * FROM {notifications_queue} ";
  $sql .= " WHERE ". implode(' AND ', $query['where']);
  $sql .= " ORDER BY module, uid, destination, send_method, send_interval";
  if ($limit) {
    $result = db_query_range($sql, $query['args'], 0, $limit);
  }
  else {
    $result = db_query($sql, $query['args']);
  }

  // Group rows by user, send_method, send_interval before composing and sending
  // This loop has to run a final time after all rows have been fetched
  while (($queue = db_fetch_object($result)) || $processed) {
    if (!$account || !$queue || ($queue->module != $module) || ($queue->uid != $account->uid) || ($queue->destination != $destination) || $queue->send_method != $send_method || $queue->send_interval != $send_interval) {
      // New user or sending method or destination, send if not the first row and reset
      if ($account && $events && $subscriptions) {        
        $messages = notifications_callback($module, 'process_compose', $account, $events, $subscriptions, $send_method, $send_interval);
        notifications_log('Composed messages', array('number' => count($messages), 'send_method' => $send_method));
        // Note that we pass the testing parameter to notifications_process_send
        notifications_callback($module, 'process_send', $account, $messages, $send_method, $test);
        if (!$test) {          
          notifications_update_sent($account, $send_method, $send_interval, time());
        }
      }
      if ($processed && $update) {
        notifications_queue_done(array('sqid' => $processed));        
      }
      $subscriptions = $events = $processed = array();
      
      // Keep track of parameters that will trigger a sending when changing
      if ($queue) {
        $send_method = $queue->send_method;
        $send_interval = $queue->send_interval;
        $destination = $queue->destination;
        $module = $queue->module;
        // Users may be handled by a different module implementing the _load_user callback. 
        // I.e. for anonymous users it may load the name from somewhere
        $account = notifications_callback($module, 'load_user', $queue->uid, $destination, $send_method);
      }
    }
    // For every row in queue, compile everyting that will be available for sending
    if ($queue) {
      $count++;
      $processed[] = $queue->sqid;
      // Load event, check it exists and check the user has access to the event objects
      if ($event = notifications_load_event($queue->eid)) {
        notifications_event_tracker('count', $event);
        notifications_log('Processing queued', array('queue sqid' => $queue->sqid , 'event' => $queue->eid, 'type' => $event->type, 'action' => $event->action, 'send method' =>$send_method));
        if (notifications_user_allowed('event', $account, $event)) {
          // This will take care of duplicated events
          $events[$queue->eid] = $event;
          // We keep track also of subscriptions originating this event
          $subscriptions[$queue->eid][] = $queue->sid;          
        } else {
          notifications_log('Access denied for event', array('account' => $user->uid, 'event' => $queue->eid));
        }      
      } else {
        notifications_log('Cannot load event', array('eid' => $queue->eid, 'queue sid' => $queue->sid));
      }
    }
  }
  if ($update) {
    notifications_event_tracker('update');
  }
  // Return number of rows processed
  return $count;
}

/**
 * Process subscriptions queue
 * 
 * The subscriptions queue has the following fields
 * sqid, uid, eid, sid, digest
 * 
 * This function should be able of splitting the whole processing in several steps.
 * It will be called multiple times for each send interval
 * 
 * Messages will be processed for each send interval, send_method, user
 * 
 * @param $send_interval
 *   Send interval to process
 * @param $max_sqid
 *   Max queue id to process
 * @return Number of rows processed
 * 
 * @ TODO Review time conditions
 * @ TODO Per module queue processing
 */
function notifications_process_queue($send_interval, $max_sqid) {
  notifications_log('Starting queue processing', array('send interval' => $send_interval, 'max squid' => $max_sqid));
  $test = notifications_process('option', 'test');
  // Count processed rows
  $count = 0;
  // This is the time from which stored rows will be sent
  $timelimit = time() - $send_interval;

  // Get users to process messages for, with this time interval and ordered by squid
  // Order by last sent for this send interval
  // Note: If we get the users with more messages pending first this may save some time
  $sql = "SELECT q.uid, q.destination, q.module, q.send_method, count(*) AS count_rows FROM {notifications_queue} q ";
  $sql .= " LEFT JOIN {notifications_sent} su ON q.uid = su.uid AND q.send_interval = su.send_interval AND q.send_method = su.send_method ";
  $sql .= " WHERE q.cron = 1 AND q.send_interval = '%d' AND q.sqid <= %d";
  $sql .= " AND (su.uid IS NULL OR su.sent < %d) ";
  // Note: the group by su.sent seems to be needed by pgsql
  $sql .= " GROUP BY q.uid, q.destination, q.module, q.send_method, su.sent ORDER BY su.sent";
  $result = db_query_range($sql, $send_interval, $max_sqid, $timelimit, 0, NOTIFICATIONS_STEP_USERS);

  // We create a bach for each user, destination method and handle it to notifications_process_rows()
  while (($queue = db_fetch_object($result)) && notifications_process('check')) {
    notifications_log('Queue processing', array('user' => $queue->uid , 'rows' => $queue->count_rows, 'send method' => $queue->send_method));
    $module = $queue->module;
    $events = $subscriptions = $processed = array();    

    // Process all rows for this user. With some hard limit to prevent process lock ups.
    // In case we have too many rows, we go updating step by step
    if ($queue->count_rows > NOTIFICATIONS_STEP_ROWS) {
      $limit = NOTIFICATIONS_STEP_ROWS;
      $update = TRUE;
    }
    else {
      $limit = $queue->count_rows;
      $update = FALSE;
    }
    $batch = array(
      'uid' => $queue->uid, 'destination' => $queue->destination, 'module' => $queue->module,
      'send_method' => $queue->send_method, 'send_interval' => $send_interval, 
      'cron' => 1, 'max_sqid' => $max_sqid,
    );
    // These rows may be processed by a different module
    $processed = notifications_callback($queue->module, 'process_rows', $batch, $limit, $update);
    $count += $processed;

    if ($processed && !$test && !$update) {
      notifications_queue_done($batch);      
    }
  }

  // If not doing a test run, update event counter and return count
  // If doing a test run, return 0 so we don't go through this again
  if (!$test) {
    notifications_event_tracker('update');
    return $count;
  }
  else {
    return 0;
  }
}

/**
 * Keep track of events and update event counter with processed rows eids
 * 
 * @param $op
 *   count, reset, update
 * @param $event
 *   event object to track
 */
function notifications_event_tracker($op, $event = NULL) {
  static $events = array();
  
  switch ($op) {
    case 'count':
      $events[$event->eid] = array_key_exists($event->eid, $events) ? $events[$event->eid] + 1 : 1;
      break;
    case 'delete':
      // Delete event and all related rows. For events no longer available, deleted nodes, comments, etc..
      foreach (array('notifications_queue', 'notifications_event') as $table) {
        db_query('DELETE FROM {' . $table . '} WHERE eid = %d', $event->eid);
      }
      if (array_key_exists($event->eid, $events)) {
        unset($events[$event->eid]);
      }
      break;
    case 'update':
      foreach ($events as $eid => $count) {
        db_query('UPDATE {notifications_event} SET counter = counter - %d WHERE eid = %d', $count, $eid);
      }
      // Intentional no break (update will also reset)
    case 'reset':
      $events = array();
  }  
}

/**
 * Update user last time sent for each sending method / interval
 */
function notifications_update_sent($account, $method, $interval, $time) {
  db_query("UPDATE {notifications_sent} SET sent = %d WHERE uid = %d AND send_interval = '%d' AND send_method = '%s'", $time, $account->uid, $interval, $method);
  if (!db_affected_rows()) {
    db_query("INSERT INTO {notifications_sent}(uid, send_interval, send_method, sent) VALUES(%d, '%d', '%s', %d)", $account->uid, $interval, $method, $time);
  }
}

/**
 * Message composition.
 * 
 * Processes everything, included templating and digestion and sends message/s.
 * 
 * Adds some more information into $message['notifications'] that may be used by other modules
 *
 * @param $account
 *   User account to send the notification to
 * @param $events
 *   Array of loaded event objects to be processed
 * @param $subscriptions
 *   Array of arrays of subscription ids (sids) for each event(eid)
 * 
 * @return array()
 *   Array of messages ready for sending out
 */
function notifications_process_compose($account, $events, $subscriptions, $send_method, $send_interval, $module = 'notifications') {
  notifications_log('Processing for sending', array('method' => $send_method, 'interval' => $send_interval, 'module' => $module, 'events' => count($events)));
  // Digest if send_interval > 0 (not immediate sending)
  if ($digest = notifications_digest_method($send_interval)) {
     $function = $digest['digest callback'];
     // It can be digested in more than one message by some other digest plug-in
     $messages = $function($account, $events, $subscriptions, $send_interval, $send_method, $module);
  }
  else {
    $sender_option = variable_get('notifications_sender', 0);
    foreach ($events as $event) {
      $message = notifications_process_message($account, $event, $subscriptions[$event->eid], $send_method);
      // We pass on the full information so it can be used by modules implementing some of the hooks
      $message['notifications'] = array('events' => array($event), 'subscriptions' => $subscriptions);
      // Optional sender, if chosen will be the user account who produced the event
      // It will be up to the sending method modules what to do with this information.
      if ($sender_option) {
        $sender = notifications_load_user($event->uid);
        $message['sender_name'] = $sender->name;
        if ($sender_option == 2) {
          $message['sender_account'] = $sender;
        }
      }
      $messages[] = $message;
    }
  }
  return $messages;
}

/**
 * Send array of messages through messaging module
 * 
 * @param $account
 *   User account to send to, may be an anonymous user account with destination
 * @param $messages
 *   Array of messages prepared for sending
 * @param $test
 *   Optional just test composition and formating but do not send
 */
function notifications_process_send($account, $messages, $send_method, $test = FALSE) {  
  foreach ($messages as $message) {
    notifications_process('count', 'send');
    notifications_debug('Sending out notification', array('method' => $send_method, 'message' => $message));
    notifications_message_send($account, $message, $send_method, $test);
  }
  return $messages;
}

/**
 * Creates a single message for a single event
 * 
 * @param $account
 *   Destination user account
 * @param $event
 *   Event object which caused this notification
 * @param $subscriptions
 *   Array of subscription ids
 * 
 * @return
 *   Message array 
 */
function notifications_process_message($account, $event, $subscriptions, $send_method) {
  $info = notifications_event_text($event);

  // Create message. Do all this in one replacemente
  $text = array(
    'subject' => notifications_message_part('event', 'subject', $send_method, $event),
    'header' => notifications_message_part('event' , 'header', $send_method, $event),
    'event'  => notifications_message_part('event', 'main', $send_method, $event),
    'footer' => notifications_message_part('event', 'footer', $send_method, $event),
  );

  // We pass only the first subscription, which is at least something
  // @ TODO Handle nicely the case where there are more than one subscription
  if ($sid = array_shift($subscriptions)) {
    $subscription = notifications_load_subscription($sid);
  }
  else {
    $subscription = NULL;
  }
  $objects = array('user' => $account, 'event' => $event, 'subscription' => $subscription);
  $objects = array_merge($objects, $event->objects);
  $text = messaging_text_replace($text, $objects);

  // Get subject out of text and build the message array
  $subject = $text['subject'];
  unset($text['subject']);
  return array('subject' => $subject, 'body' => $text);
}

/**** Retrieving and replacing text parts, interfacing with tokens and messaging module ****/

/**
 * Get message part
 * 
 * It searches for optional message group keys for options defaulting to $type
 * 1. $module-$type-[$event->type]-[$event->action]
 * 2. $module-$type-[$event->type]
 * 3. $module-$type
 * 
 * @param $type
 *   Message type to send, either 'event' or 'digest'
 * @param $key
 *   Id of message part, ie 'header'
 * @param $method
 *   Method by which message will be sent. Normally 'mail'
 * @param $param
 *   Event data if we have a single event (type = event), none if we are digesting multiple events (type = digest)
 * @param $module
 *   Module name to be prefixed to the template name. If different than notifications we first try
 *   with that module but if not found, try again with 'notifications'
 * 
 * @return
 *   Part of the message with tokens for replacement.
 */
function notifications_message_part($type, $key, $method, $param = NULL, $module = 'notifications') {
  // If event passed check for predefined text or get optional keys from event
  if ($type == 'event' && is_object($param)) {
    if (isset($param->text[$key])) {
      return $param->text[$key];  
    } else {
      $options = array($param->type, $param->action);
    }
  } elseif ($method == 'test') {
    // Little trick for this to be testable
    return "$type $key [type-name] [title] [site-name]";
  } else {
    $options = is_array($param) ? $param : array();
  }  
  // Buid an array for searching templates, here's where the template fallback happens
  // I.e. $keyparts = array('notifications, 'event', 'node', 'update'),  will search for:
  // - notifications-event-node-update
  // - notifications-event-node
  // - notifications-event
  // - notifications
  $search = $keyparts = array_merge(array($module, $type), $options);
  while ($keyparts) {
    $groupkey = implode('-', $keyparts);
     if ($text = messaging_message_part($groupkey, $key, $method)) {
      $output = $text == MESSAGING_EMPTY ? '' : $text;
      break;
    }
    // If no text trim out latest part of the key and retry
    array_pop($keyparts);
  }
  // If we don't have a template and the module is not notifications, give it another try
  if (isset($output)) {
    // We found something, return it
    return $output;
  }
  elseif ($module != 'notifications') {
    // Found nothing, different module, retry with notifications templates
    return notifications_message_part($type, $key, $method, $param, 'notifications');
  }
  else {
    // Failed to get message part, return information about the template not found, will help debugging
    return "[UNDEFINED module = $module, key = $key, type = $type, method = $method, search = ". implode(',', $search) .']';
  }
}

/**
 * Message sending, pass the message to Messaging back end
 * 
 * @param $account
 *   User account to send the message to
 * @param $message
 *   Message array, will be converted to object
 * @param $send_method
 *   Send method
 * @param $test
 *   Optional, set to TRUE if doing a test run (messages not to be actually sent)
 * 
 * @return boolean
 *   TRUE if sending was successfull
 */
function notifications_message_send($account, $message, $send_method, $test = FALSE) {
  notifications_debug('Preparing user notification for messaging', array('message' => $message, 'account' => $account));
  $message = (object)$message;
  $message->type = 'notifications';
  $message->test = $test;
  notifications_process('count', 'message');
  messaging_message_send_user($account, $message, $send_method);
}

/**
 * Get texts for event
 * 
 * @ TODO Support for configurable texts
 */
function notifications_event_text($event) {
  $info = notifications_event_types($event->type, $event->action);
  return $info;
}

/**
 * Get users with static caching for existing users
 * 
 * If not uid passed it will return an anonymous fake user (with destination, send_method)
 * We need to pass the send method to produce the right tokens later
 * 
 * This provides some API support for user-less subscriptions, i.e. when we've got just
 * an email address but no user associated. The idea is that these fake users will be properly 
 * handled by messaging module
 * 
 * @todo Possibly all this should be handled by messaging layer
 * 
 * @param $uid
 *   Uid of the user account to load, none to use anonymous user
 * @param $destination
 *   Messaging destination (mail, sms number, etc..), just for anonymous users
 * @param $send_method
 *   Messaging send method key (mail, sms, xmpp, etc..), just for anonymous users
 */
function notifications_load_user($uid, $destination = NULL, $send_method = NULL) {
  if ($uid) {
    return messaging_load_user($uid);
  }
  else {
    $account = drupal_anonymous_user();
    $account->destination = $destination;
    $account->send_method = $send_method;
    return $account;
  }
}

/**
 * Get events with static caching. Handle event deletion if not available anymore
 */
function notifications_load_event($id) {
  static $cache = array();

  if (!array_key_exists($id, $cache)) {
    $event = db_fetch_object(db_query("SELECT * FROM {notifications_event} WHERE eid = %d", $id));
    $event->params = unserialize($event->params);
    // Load aditional objects for the event
    $event->objects = array();
    notifications_module_invoke('event load', $event);
    // Check event status, it may need deletion if objects are not available
    if (!empty($event->delete)) {
      notifications_event_tracker('delete', $event);
      $event = NULL;
    }
    $cache[$id] = $event;
  }

  return $cache[$id];
}

/**
 * Mark queue rows as done
 * 
 * Either log, if logging enabled, or delete
 */
function notifications_queue_done($params) {
  if (variable_get('notifications_log', 0)) {
    notifications_queue_update($params, array('cron' => 0, 'sent' => time()));
  } else {
    notifications_queue_delete($params);
  }
}

/**
 * Update queue rows with defined values
 * 
 * @arg $params
 *   Parameters to select the queue rows for updating. Array of field => value pairs
 * @arg $update
 *   Fields values to update. Array of field => value pairs
 */
function notifications_queue_update($params, $updates) {
  
  $values =  _messaging_query_conditions('notifications_queue', $updates);
  $where = notifications_queue_query($params);
  $args = array_merge($values['args'], $where['args']);

  return db_query('UPDATE {notifications_queue} SET ' . implode(', ', $values['conditions']) . ' WHERE ' . implode(' AND ', $where['where']), $args);
}

/**
 * Delete rows from subscriptions queue
 * 
 * @see notifications_queue_query()
 * 
 * Note: Handle with care if no params may delete all rows
 */
function notifications_queue_delete($params) {
  $query = notifications_queue_query($params);
  db_query("DELETE FROM {notifications_queue} WHERE ". implode(' AND ', $query['where']), $query['args']);
}

/**
 * Build query conditions for queue queries
 * 
 * @param $params
 *   Array of parameters, field => value form
 *   Special parameters
 *     'max_squid' => max squid to delete
 *     'rows' => array of squid values to delte
 * @return
 *   Array with 'where' and 'args' elements. Each of them is an array
 */
function notifications_queue_query($params) {
  $where = $args = array();
  
  // Special condition max_sqid
  if (isset($params['max_sqid'])) {
    $where[] = "sqid <= %d";
    $args[] = $params['max_sqid'];
    unset ($params['max_sqid']);
  }
  // User generic query builder for the rest of fields
  $values =  _messaging_query_conditions('notifications_queue', $params);  
  $where = array_merge($where, $values['conditions']);
  $args = array_merge($args, $values['args']);
 
  return array('where' => $where, 'args' => $args);
}

/** Digest functions **/

/**
 * Get digest information for an event.
 * 
 * From the event definition (notifications('event types')) we find out 
 * - which event object we'll use for digesting
 * - which field of that object to use for indexing
 * 
 * I.e. for event type = 'node', event action = 'update'
 *  'digest' => ('node', 'nid')
 */
function nofitications_digest_event_info($event, $module = 'notifications') {
  $info = notifications_event_types($event->type, $event->action);
  if (!empty($info['digest'])) {
    $type = $info['digest'][0];
    $field = $info['digest'][1];
    // Check object and values, the object may be the event itself
    if ($type == 'event') {
      $object = $event;
    }
    else {
      $object = !empty($event->objects[$type]) ? $event->objects[$type] : NULL;
    }
  }
  else {
    // No digest info for this event /action so we use event and action itselves.
    $type = $event->type;
    $field = $event->action;
    $object = NULL;
  }
  $value = $object && isset($object->$field) ? $object->$field : 0;
  return array('type' => $type, 'field' => $field, 'value' => $value, 'object' => $object, 'module' => $module);  
}

/**
 * Digest multiple events in a single message, short format.
 * 
 * @return array with messages ready to be sent
 */
function notifications_process_digest_short($account, $events, $subscriptions, $send_interval, $send_method, $module = 'notifications') {
  // Compile list of events for each object
  $list = array();
  // Build up the digested list with text replacement
  // We need text replacement for each line because it depends on different objects
  foreach ($events as $event) {
    notifications_log('Digesting short format', array('event' => $event));
    $sid = is_array($subscriptions[$event->eid]) ? array_shift($subscriptions[$event->eid]) : 0;
    $subscription = $sid ? notifications_load_subscription($sid) : NULL;
    $objects = $event->objects + array('user' => $account, 'subscription' => $subscription);
    // $info = notifications_event_types($event->type, $event->action);
    $digest = nofitications_digest_event_info($event);
    $digest_type = $digest['type'];
    $digest_value = $digest['value'];

    if (!isset($list[$digest_type][$digest_value]['group'])) {
      $group = array(      
        'title' => notifications_digest_group($digest, 'title', $send_method),
        'footer' => notifications_digest_group($digest, 'closing', $send_method),
      );
      // The objects passed here for tokens will be the ones from the first event only
      $list[$digest_type][$digest_value]['group'] = messaging_text_replace($group, $objects);
      notifications_log('Digesting object', array('type' => $digest_type, 'value' => $digest_value));
    }
    // Check duplicate notifications for the same event so we do some deduping
    if (!isset($list[$digest_type][$digest_value]['line'][$event->eid])) {
      $line = notifications_digest_line($event, $send_method, $objects);
      $objects['event'] = $event; 
      $list[$digest_type][$digest_value]['line'][$event->eid] = messaging_text_replace($line, $objects);
    }
  }
  // Create message. Do all this in one replacement, then strip out the subject
  $text['subject'] = notifications_message_part('digest', 'subject', $send_method, NULL, $module);
  $text['header'] = notifications_message_part('digest', 'header', $send_method, NULL, $module);
  $text['footer'] = notifications_message_part('digest', 'footer', $send_method, NULL, $module);

  // We dont pass a subscription object here, won't be too much use anyway
  $text = messaging_text_replace($text, array('user' => $account, 'subscription' => NULL));
  
  // Compose body. All these lines have been text replaced
  $body = theme('notifications_digest_short_body', $text, $list);
    
  // Build the final digested message, and return in an array
  $message = array(
    'subject' => $text['subject'], 
    'body' => $body,
    'events' => $events,
    'subscriptions' => $subscriptions,
    'digest' => 'short',
  );

  return array($message);
}

/**
 * Digest multiple events in a single message, long format.
 * 
 * We use digest templates for subject, header, footer
 *   digest-subject
 *   digest-header
 *   digest-footer
 * but the regular templates for the message body for each event
 *   event-[type]-[action]-main
 *     or event-[type]-main
 *       or event-main
 * 
 * @return array with messages ready to be sent
 */
function notifications_process_digest_long($account, $events, $subscriptions, $send_interval, $send_method, $module = 'notifications') {
  // Build the message body as an array of event notifications
  $body = array();

  // Build up the digested list with text replacement, body as big array
  // We need text replacement for each line because it depends on different objects
  foreach ($events as $event) {
    notifications_log('Digesting long format', array('event' => $event));
    // We use the regular template for the events
    $part = array();
    $part[] = notifications_message_part('event', 'subject', $send_method, $event, $module);
    $part[] = notifications_message_part('event', 'main', $send_method, $event, $module);
    // Pass only the first subscription here
    $sid = is_array($subscriptions[$event->eid]) ? array_shift($subscriptions[$event->eid]) : 0;
    $subscription = $sid ? notifications_load_subscription($sid) : NULL;
    $objects = $event->objects + array('user' => $account, 'subscription' => $subscription, 'event' => $event);
    $body = array_merge($body, messaging_text_replace($part, $objects));
  }
  
  // Create message. Do all this in one replacement, then strip out the subject
  $text['subject'] = notifications_message_part('digest', 'subject', $send_method, NULL, $module);
  $text['header'] = notifications_message_part('digest', 'header', $send_method, NULL, $module);
  $text['footer'] = notifications_message_part('digest', 'footer', $send_method, NULL, $module);

  // We dont pass a subscription object here, won't be too much use anyway
  $text = messaging_text_replace($text, array('user' => $account, 'subscription' => NULL));
  
  // Compose body. All these lines have been text replaced, chance for theming
  $body = theme('notifications_digest_long_body', $text['header'], $body, $text['footer']);
  
  // Build the final digested message, and return in an array
  $message = array(
    'subject' => $text['subject'], 
    'body' => $body,
    'events' => $events,
    'subscriptions' => $subscriptions,
    'digest' => 'long',
  );
  return array($message);
}

/**
 * Get text parts for digests.
 * 
 * Useful to get the group title and footer given some kind of digesting
 * 
 * @param $digest
 *   Digest information (which object and field we use)
 * @param $part
 *   Template part: header, footer...
 * @param $method
 *   Send method
 */
function notifications_digest_group($digest, $part, $method) {
  static $texts = array();

  $type = $digest['type'];
  $value = $digest['value'];
  
  if (!isset($texts[$type][$value][$part][$method])) {
    if ($line = notifications_message_part('digest', $part, $method, array($type, $digest['field']), $digest['module'])) {
      $output = $line;
    } else {
      $output = '';
    }
    $texts[$type][$value][$part][$method] = $output;
  }
  
  return $texts[$type][$value][$part][$method];
}

/**
 * Digest each line, with some caching for performance
 */
function notifications_digest_line($event, $method) {
  static $digest = array();
  
  if (!isset($digest[$event->eid][$method])) {
    // The event may have an specific digest line, otherwise use template if present or even information
    if (!empty($event->text['digest'])) {
      $line = $event->text['digest'];
    } elseif ($part = notifications_message_part('event', 'digest', $method, $event)) {
      $line = $part;
    } else { // Get it from event information
      $info = notifications_event_types($event->type, $event->action);
      $line = $info['line'];
    }    
    $digest[$event->eid][$method] = $line;
  }
  
  return $digest[$event->eid][$method];
}

/** Themeable functions **/

/**
 * Theme notifications digest
 * 
 * @param $text
 *   Array with message parts, currently only 'header' and 'footer'
 * @param $list
 *   Structured array with list of digested items. For each object type
 *   'type' => (  // Type may be node, user, etc...
 *      'oid' => ( // One for each object, may be nid, uid...
 *        'group' => Group title and footer 
 *        'line' => Array of lines, one for each related event
 *       )
 *   )   
 * @return
 *   Structured array with 'header', 'footer', and multiple text lines
 */
function theme_notifications_digest_short_body($text, $list) {
  $body['header'] = $text['header'];
  foreach ($list as $type => $objects) {
    foreach ($objects as $oid => $data) {      
      $body['content'][] = $data['group']['title'];
      foreach ($data['line'] as $line) {
        $body['content'][] = theme('notifications_digest_short_line', $line, $data['group']);
      }
      $body['content'][] = $data['group']['footer'];
    }
  }
  $body['footer'] = $text['footer'];
  return $body;
}

/**
 * Single line of text
 */
function theme_notifications_digest_short_line($line, $group) {
  return '- ' . $line;
}

/**
 * Build the message body for long digests. 
 * 
 * Actually we do nothing here, but it will be themeable.
 */
function theme_notifications_digest_long_body($header, $content, $footer) {
  return array('header' => $header, 'content' => $content, 'footer' => $footer);
}

