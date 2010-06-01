<?php
// $Id: messaging.store.inc,v 1.1.2.4.2.9.2.2 2009/11/11 18:07:24 jareyero Exp $
/**
 * @file
 *   Database storage for the messaging framework
 */

// Max number of rows to process for each step before clean up
define('MESSAGING_STEP_ROWS', 1000);

// Minimum amount of seconds the process will need for clean-up tasks
// Just to make sure that after exhausting cron assigned time we'll have a few spare seconds for some cleanup
define('MESSAGING_TIME_MARGIN', 5);

/**
 * Process and send messages in queue, to be called from cron
 * 
 * It will check for predefined limits and repeat the cycle
 *   [fetch] -> [send] -> [check]
 * until the queue is empty or any of the limits are met
 * 
 * @param $timeout
 *   Optional time out to use instead of cron, just for this api to be testable
 */
function messaging_store_queue_process($timeout = 0) {
  $limit = variable_get('messaging_process_limit', array('message' => 0, 'time' => 0, 'percent' => 0));
  // Calculate time limit. We get the smaller of all these times in seconds
  if ($timeout) {
    $timelimit[] = time() + $timeout;
  } else {
    $timelimit[] = variable_get('cron_semaphore', 0) + ini_get('max_execution_time') - MESSAGING_TIME_MARGIN;
  }
  if ($limit['time']) {
    $timelimit[] = time() + $limit['time'];
  }
  if ($limit['percent']) {
    $timelimit[] = time() + ini_get('max_execution_time') * $limit['percent'] / 100;
    unset($limit['percent']);
  }
  $limit['time'] = min($timelimit);
  
  // Processing loop. Will stop when we run out of rows or reach time / messages limit
  $count = 0;
  $max = !empty($limit['message']) ? $limit['message'] : 0;
  do {
    $step = $max ? min(MESSAGING_STEP_ROWS, $max - $count) : MESSAGING_STEP_ROWS;
    $number = messaging_store_queue_process_step($step, $limit['time']);
    $count += $number;   
  } 
  while ($number == $step && time() <= $limit['time'] && (!$max || $max > $count));    
}

/**
 * Retrieve and send queued messages
 * 
 * @param $limit
 *   Maximum number of queued messages to process for this step
 * @param $timeout
 *   Optional time limit for processing, will return when if reached during processing
 * @return
 *   Number of messages processed in this step
 */
function messaging_store_queue_process_step($limit, $timeout = 0) {
  $count = 0;
  $sent = $unsent = array();
  $result = db_query_range("SELECT * FROM {messaging_store} WHERE queue = 1 AND cron = 1 ORDER BY mqid", 0, $limit);
  while ($message = db_fetch_object($result)) {
    messaging_store_unpack($message, TRUE);
    // Actual sending functions function
    $message->process = TRUE;
    $message = messaging_message_callbacks(array('multisend', 'aftersend'), $message, messaging_method_info($message->method));
    if ($message->success) {
      $sent[] = $message->mqid;
    } else {
      $unsent[] = $message->mqid;
    }
    $count++;
    // Check timeout after each message
    if ($timeout && time() > $timeout) break;
  }
  if ($sent) {
    messaging_store_sent($sent);
  }
  if ($unsent) {
    messaging_store_sent($unsent, TRUE);
  }
  return $count;
}

/**
 * Queue clean up
 * - Remove expired logs
 * - @ TODO Remove expired queued messages
 */
function messaging_store_queue_cleanup() {
  if ($expire = variable_get('messaging_log', 0)) {
    db_query('DELETE FROM {messaging_store} WHERE log = 1 AND queue = 0 AND sent < %d', time() - $expire);
  }
}

/**
 * Retrieve from messaging database storage
 * 
 * @param $params
 *   Array of field value pairs
 * @param $order
 *   Optional array of field names to order by
 * @param $limit
 *   Optional maximum number of rows to retrieve
 * @param $pager
 *   Optional pager element for pager queries
 * @param $unpack
 *   Optional fully load stored data
 */
function messaging_store_get($params, $order = NULL, $limit = NULL, $pager = NULL, $unpack = FALSE) {
  $messages = $where = $args = array();
  list ($where, $args) = messaging_store_query($params);
  $sql = 'SELECT * FROM {messaging_store}';
  $sql .= $where ? ' WHERE '.implode(' AND ', $where) : '';
  $sql .= $order ? ' ORDER BY '.implode(', ', $order) : '';

  if (!is_null($pager)) {
    $result = pager_query($sql, $limit, $pager, NULL, $args);
  } elseif ($limit) {
    $result = db_query_range($sql, $args, 0, $limit);
  } else {
    $result = db_query($sql, $args);
  }
  while ($msg = db_fetch_object($result)) {
    messaging_store_unpack($msg, $unpack);
    $messages[$msg->mqid] = $msg;
  }
  return $messages;
}

/**
 * Load single message from store
 */
function messaging_store_load($mqid) {
  if ($message = db_fetch_object(db_query('SELECT * FROM {messaging_store} WHERE mqid = %d', $mqid))) {
    messaging_store_unpack($message, TRUE);
    return $message;
  } 
}

/**
 * Build query with field conditions
 * 
 * This function supports IN() conditions when passing array field values
 * @param $query
 *   Array of field => value pars
 */
function messaging_store_query($fields) {
  $where = $args = array();
  foreach ($fields as $key => $value) {     
    if (is_array($value)) {
      // Special processing for array parameters. Many ints are expected for 'mqid' field
      $type = ($key == 'mqid') ? 'int' : 'varchar';
      $where[] = $key . ' IN(' . db_placeholders($value, $type) . ')';
      $args = array_merge($args, $value);
    } else {
      $where[] = $key . " = '%s'";
      $args[] = $value;
    }
  }
  return array($where, $args);
}

/**
 * Unpack stored messages
 * 
 * @param $message
 *   Array as retrieved from the db store
 * @param $full
 *   True for loading the account data if this message is intended for a user
 *   And loading the file objects associated too
 */
function messaging_store_unpack(&$message, $full = FALSE) {
  // Preprocessing stored parameters
  if ($message->params) {
    $params = unserialize($message->params);
    $message->params = array();
    // Some optional fields that may be into params, may be extended
    foreach (array('destination', 'sender_name', 'destinations') as $field) {
      if (!empty($params[$field])) {
        $message->$field = $params[$field];
        unset($params[$field]);
      }
    }
    // Load files attached to this message if any
    // This will serve as a check of whether the files still exist
    if (!empty($message->params['files']) && $full) {
      $message->files = array();
      $result = db_query('SELECT * FROM {upload} WHERE fid IN (' . db_placeholders($message->params['files']) . ')', $message->params['files']);
      while ($file = db_fetch_object($result)) {
        $message->files[$file->fid] = $file;
      }
    }
    // We only saved params for current sending method group
    $group = messaging_method_info($message->method, 'group');
    if ($group && empty($message->params[$group])) {
      $message->params[$group] = $params;
    } else {
      $message->params = $params;
    }
  }
  if ($message->uid && $full) {
    $message->account = messaging_load_user($message->uid);       
  }
  if ($message->sender && $full) {
    $message->sender_account = messaging_load_user($message->sender);
  }
  // Check destinations array, in case it was not properly filled
  if (empty($message->destinations)) {
    if (!empty($message->account) && ($userdest = messaging_user_destination($message->account, $message->method, $message))) {
      $message->destinations = array($userdest);
    }
    elseif (!empty($message->destination)) {
      $message->destinations = array($message->destination);
    }
  }
}

/**
 * Mark messages as sent, either deleting them, or keeping logs
 * 
 * @param $mqid
 *   Single message id or array of message ids
 * @param $error
 *   Optional, just mark as error move queue messages to log, for messages on which sending failed 
 */
function messaging_store_sent($mqid, $error = FALSE) {
  $mqid = is_array($mqid) ? $mqid : array($mqid);
  list($where, $args) = messaging_store_query(array('mqid' => $mqid));
  
  
  if ($error) {
    // Error, log them all, sent = 0
    $sent = 0;
  } else {
    // First delete the ones that are not for logging, then mark as sent
    db_query("DELETE FROM {messaging_store} WHERE log = 0 AND ".implode(' AND ', $where) , $args);
    $sent = time();
  }

  // Now unmark the rest for queue processing, as logs
  $args = array_merge(array($sent), $args);
  db_query("UPDATE {messaging_store} SET queue = 0, cron = 0, log = 1, sent = %d WHERE ".implode(' AND ', $where), $args);
}

/**
 * Delete messages from queue
 */
function messaging_store_del($params) {
  list($where, $args) = messaging_store_query($params);
  db_query("DELETE FROM {messaging_store} WHERE ".implode(' AND ', $where), $args);
}

/**
 * Put into database storage, create one line for each destination
 * 
 * If there are many destinations they will be stored as 'multiple'
 * 
 * @param $message
 *   Message object
 */
function messaging_store_save($message) {
  // Normalize some values. Boolean parameters must be 0|1
  foreach (array('queue', 'log', 'cron') as $field) {
    $message->$field = empty($message->$field) ? 0 : 1;
  }
  // If sender is a user account, save sender field
  if (!empty($message->sender_account)) {
    $message->sender = $message->sender_account->uid;
  }
  // We just save the params for current sending method group
  $group = messaging_method_info($message->method, 'group');
  $params = !empty($message->params[$group]) ? $message->params[$group] : array();
  
  // And there's one more optional param that is sender_name
  if (!empty($message->sender_name)) {
    $params['sender_name'] = $message->sender_name;
  }
  
  // Mark for a user if there's an account parameter, produced by messaging_send_user()
  if (!empty($message->account)) {
    $message->uid = $message->account->uid;
    $message->destination = 'user:' . $message->uid;
  }
  // Save serialized destinations
  if (!empty($message->destinations)) {
    $params['destinations'] = $message->destinations;
  }
  // Check destination, but preserve field in case it is already set. I.e. 'all users'
  if (empty($message->destination) && !empty($message->destinations)) {
    // Check for multiple destinations, just store 'multiple'
    // Bulk sending modules may store each destination differently
    if (count($message->destinations) > 1) {
      $message->destination = 'multiple';      
    }
    // In case there's a single destination, try to put it as string
    elseif ($destination = $message->destinations[0]) {
      if (is_string($destination) || is_numeric($destination)) {
        $message->destination = $destination;
      }
    }
  }
  // If there are files, serialize $file->fids in an array
  if (!empty($message->files)) {
    $params['files'] = array_keys($message->files);
  }
  // Add parameters, timestamp and save
  $message->params = $params ? $params : NULL;
  $message->created = time();
  drupal_write_record('messaging_store', $message);
  
  // Finally, return the message object which should have a unique 'mqid'
  return $message;
}

