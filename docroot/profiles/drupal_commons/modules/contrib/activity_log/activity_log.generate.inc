<?php

/**
 * @file
 *   Provides functions that regenerate activity messages.
 */

define('ACTIVITY_LOG_GENERATE_COUNT', 50);

//================
// ADMINISTRATION
//================

/**
 * The regenerate activity messages form.
 */
function activity_log_admin_regenerate($form_state) {
  $form = array();
  $events = activity_log_get_rules_activity_events();
  if (empty($events)) {
    $form['notice'] = array(
      '#value' => t('There are no active Rules set up that log activity messages.') .' '.
        t('In order to use Activity Log, <a href="!href">create a Rule</a> that uses the "Log activity" action.',
          array('!href' => url('admin/rules/trigger'))
        ),
    );
    return $form;
  }
  $form['events'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Events to trigger'),
    '#description' => t('Activity Log will trigger the selected event for each related entity it can find.') .' '.
      t('This will trigger every Rule for that event and every action for each triggered Rule.') .' '.
      t('The events shown all have associated Rules with Activity Log actions.') .' '.
      t('However, you may want to temporarily disable any Rules that log activities so that they are not executed while regenerating activity messages.'),
    '#required' => TRUE,
    '#options' => $events,
  );
  $form['age'] = array(
    '#type' => 'textfield',
    '#title' => t('Oldest content to regenerate'),
    '#description' => t('The greatest number of days old that content can be for it to have an activity message generated.') .' '.
      t('Leave blank or enter 0 to regenerate activity messages for all content.'),
    '#field_suffix' => t('days'),
    '#default_value' => 7,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Regenerate'),
  );
  return $form;
}

/**
 * The validate callback for the regenerate activity messages form.
 */
function activity_log_admin_regenerate_validate($form, $form_state) {
  $v = $form_state['values']['age'];
  if ($v && (!is_numeric($v) || $v < 0)) {
    form_set_error('age', t('The oldest content to regenerate setting must have a nonnegative numeric value.'));
  }
}

/**
 * The submit callback for the regenerate activity messages form.
 */
function activity_log_admin_regenerate_submit($form, $form_state) {
  $events = array_filter($form_state['values']['events']);
  $age = $form_state['values']['age'] ? time() - $form_state['values']['age'] * 86400 : 0;
  activity_log_regenerate($events, $age);
}

//=========
// HELPERS
//=========

/**
 * Get a list of events that have associated Rules with Activity Log actions.
 */
function activity_log_get_rules_activity_events() {
  $regenerate = array_keys(module_invoke_all('activity_log_regenerate_info'));
  $events = array();
  foreach (_rules_get_rule_sets() as $key => $event) {
    if (strpos($key, 'event_') === 0 && in_array(drupal_substr($key, 6), $regenerate)) {
      foreach ($event['rules'] as $name => $info) {
        if ($info['#active']) {
          foreach ($info['#actions'] as $action) {
            if ($action['#name'] == 'activity_log_log_action') {
              $events[drupal_substr($key, 6)] = $event['info']['label'];
              break;
            }
          }
        }
      }
    }
  }
  return $events;
}

//============
// PROCESSING
//============

function activity_log_regenerate($events = array(), $age = 0) {
  if (empty($events)) {
    $events = drupal_map_assoc(array_keys(activity_log_get_rules_activity_events()));
  }
  $batch = array(
    'operations' => array(
      array('activity_log_regenerate_prepare', array($age)),
      array('activity_log_regenerate_process', array($events, $age)),
    ),
    'finished' => 'activity_log_regenerate_batch_finished',
    'title' => t('Generating activity messages'),
    'file' => drupal_get_path('module', 'activity_log') .'/activity_log.generate.inc',
  );
  batch_set($batch);
}

/**
 * Delete activity messages created within the specified period.
 */
function activity_log_regenerate_prepare($age, &$context) {
  if ($age == 0) {
    db_query("TRUNCATE TABLE {activity_log_events}");
    db_query("TRUNCATE TABLE {activity_log_messages}");
  }
  else {
    db_query("DELETE FROM {activity_log_events} WHERE created > %d", $age);
    db_query("DELETE FROM {activity_log_messages} WHERE created > %d", $age);
  }
  $context['finished'] = 1;
}

/**
 * Regenerate activity messages.
 */
function activity_log_regenerate_process($events, $age, &$context) {
  $regenerate = module_invoke_all('activity_log_regenerate_info');
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($events);
  }
  if (!empty($events) && $context['sandbox']['progress'] < $context['sandbox']['max']) {
    if (empty($context['sandbox']['last_result'])) {
      $context['sandbox']['last_result'] = FALSE;
      $event = array_shift($events);
      $context['sandbox']['event'] = $event;
      $context['sandbox']['progress']++;
    }
    $info = $regenerate[$context['sandbox']['event']];
    if (isset($info['file']) && file_exists($info['file'])) {
      include_once $info['file'];
    }
    if (!isset($info['arguments'])) {
      $info['arguments'] = array();
    }
    $context['sandbox']['last_result'] = call_user_func_array($info['callback'],
      array_merge(array($age), array($context['sandbox']['last_result']), $info['arguments'])
    );
  }
  $context['message'] = t('Processing Rules for event %event (@current of @total)',
    array(
      '%event' => $context['sandbox']['event'],
      '@current' => $context['sandbox']['progress'],
      '@total' => $context['sandbox']['max'],
    )
  );
  $context['results'][] = $context['sandbox']['event'];
  $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
}

/**
 * Batch finished callback.
 */
function activity_log_regenerate_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Finished regenerating activity messages.'));
  }
  else {
    drupal_set_message(t('An error occurred while regenerating activity messages.'));
  }
}

//===========
// EXECUTION
//===========

/**
 * Implementation of hook_activity_log_regenerate_info().
 */
function activity_log_activity_log_regenerate_info() {
  $path = drupal_get_path('module', 'activity_log') .'/activity_log.generate.inc';
  $items = array(
    'comment_insert' => array(
      'callback' => 'activity_log_regenerate_comments',
      'file' => $path,
    ),
    'node_insert' => array(
      'callback' => 'activity_log_regenerate_nodes',
      'file' => $path,
    ),
    'taxonomy_term_insert' => array(
      'callback' => 'activity_log_regenerate_taxonomy_terms',
      'file' => $path,
    ),
    'user_insert' => array(
      'callback' => 'activity_log_regenerate_users',
      'file' => $path,
    ),
    'facebook_status_tags_user_was_tagged' => array(
      'callback' => 'activity_log_regenerate_fbss_mentions',
      'file' => $path,
    ),
    'fbss_comments_save' => array(
      'callback' => 'activity_log_regenerate_fbss_comments',
      'file' => $path,
    ),
    'facebook_status_save' => array(
      'callback' => 'activity_log_regenerate_statuses',
      'file' => $path,
    ),
    'og_user_insert' => array(
      'callback' => 'activity_log_regenerate_og_join',
      'file' => $path,
    ),
  );
  if (module_exists('flag')) {
    foreach (flag_get_flags() as $flag) {
      $items['flag_flagged_'. $flag->name] = array(
        'callback' => 'activity_log_regenerate_flag',
        'arguments' => array($flag),
        'file' => $path,
      );
    }
  }
  return $items;
}

/**
 * Triggers the comment_insert Rules event for each relevant comment.
 */
function activity_log_regenerate_comments($age, $offset) {
  return _activity_log_regenerate_object('comment_insert', "SELECT * FROM {comments} WHERE status = 0 AND timestamp > %d", $age, $offset);
}

/**
 * Triggers the node_insert Rules event for each relevant node.
 */
function activity_log_regenerate_nodes($age, $offset) {
  return _activity_log_regenerate_object('node_insert', "SELECT * FROM {node} WHERE status = 1 AND created > %d", $age, $offset);
}

/**
 * Triggers the taxonomy_term_insert Rules event for each relevant term.
 */
function activity_log_regenerate_taxonomy_terms($age, $offset) {
  return _activity_log_regenerate_object('taxonomy_term_insert', "", 0, $offset, "SELECT * FROM {term_data}");
}

/**
 * Triggers the user_insert Rules event for each relevant user.
 */
function activity_log_regenerate_users($age, $offset) {
  return _activity_log_regenerate_object('user_insert', "SELECT * FROM {users} WHERE status = 1 AND created > %d", $age, $offset);
}

/**
 * Triggers the facebook_status_tags_user_was_tagged Rules event for @mentions.
 */
function activity_log_regenerate_fbss_mentions($age, $offset) {
  return _activity_log_regenerate_object(
    'facebook_status_tags_user_was_tagged', "
      SELECT f.*, t.rid
      FROM {facebook_status_tags} t
      INNER JOIN {facebook_status} f
        ON t.sid = f.sid
      WHERE t.type = 'user' AND f.created > %d
  ", $age, $offset);
}

/**
 * Triggers the fbss_comments_save Rules event for relevant status comments.
 */
function activity_log_regenerate_fbss_comments($age, $offset) {
  return _activity_log_regenerate_object('fbss_comments_save', "SELECT * FROM {fbss_comments} WHERE created > %d", $age, $offset);
}

/**
 * Triggers the facebook_status_save Rules event for each relevant status.
 */
function activity_log_regenerate_statuses($age, $offset) {
  return _activity_log_regenerate_object('facebook_status_save', "SELECT * FROM {facebook_status} WHERE created > %d", $age, $offset);
}

/**
 * Triggers the og_user_insert Rules event for group joins.
 */
function activity_log_regenerate_og_join($age, $offset) {
  return _activity_log_regenerate_object('og_user_insert', "SELECT nid, uid FROM {og_uid} WHERE is_active = 1 AND created > %d", $age, $offset);
}

/**
 * Triggers the flag_flagged_$flag Rules event for flagging.
 */
function activity_log_regenerate_flag($age, $offset, $flag) {
  return _activity_log_regenerate_object('flag_flagged_'. $flag->name, "
    SELECT c.content_id, c.uid, f.*
    FROM {flag_content} c
    LEFT JOIN {flags} f
      ON c.fid = f.fid
    WHERE timestamp > %d
  ", $age, $offset);
}

/**
 * Trigger events for historical data.
 */
function _activity_log_regenerate_object($event, $query, $age, $offset, $timeless_query = NULL) {
  if (!$age && $timeless_query) {
    $result = db_query_range($timeless_query, $offset, ACTIVITY_LOG_GENERATE_COUNT);
  }
  else {
    $result = db_query_range($query, $age, $offset, ACTIVITY_LOG_GENERATE_COUNT);
  }
  $count = 0;
  while ($object = db_fetch_object($result)) {
    if ($event == 'user_insert') {
      $object = array('account' => $object);
    }
    elseif (strpos($event, 'flag_flagged_') === 0) {
      $object = array('flag' => $object, 'flag_content_id' => $object->content_id, 'flagging_user' => activity_log_user_load($object->uid));
    }
    if ($event == 'facebook_status_tags_user_was_tagged') {
      $account = activity_log_user_load($object->rid);
      rules_invoke_event('facebook_status_tags_user_was_tagged', $object, $account);
    }
    elseif ($event == 'og_user_insert') {
      rules_invoke_event('og_user_insert', $object->uid, $object->nid);
    }
    else {
      rules_invoke_event($event, $object);
    }
    $count++;
  }
  if ($count < ACTIVITY_LOG_GENERATE_COUNT) {
    drupal_set_message(format_plural(
      $offset + $count,
      'One activity message generated for the event %event.',
      '@count activity messages generated for the event %event.',
      array('%event' => $event)
    ));
  }
  elseif ($count == ACTIVITY_LOG_GENERATE_COUNT) {
    return $offset + ACTIVITY_LOG_GENERATE_COUNT;
  }
}

//====================================================
// IMPORT DIRECTLY FROM OTHER ACTIVITY STREAM MODULES
//====================================================

/*
function activity_log_import() {
  // Import data directly from Heartbeat.
  if (db_table_exists('heartbeat_activity')) {
    db_query("INSERT INTO activity_log_templates SET tid = 0, cacheable = 1");
    db_query("
      INSERT INTO activity_log_messages
        (tid, created, last_updated, stream_owner_id, stream_owner_type, cached)
      SELECT 0, timestamp, timestamp, uid, 'user', message
      FROM heartbeat_activity
      WHERE nid = 0
    ");
    db_query("
      INSERT INTO activity_log_messages
        (tid, created, last_updated, stream_owner_id, stream_owner_type, cached)
      SELECT 0, timestamp, timestamp, nid, 'node', message
      FROM heartbeat_activity
      WHERE nid <> 0
    ");
    drupal_set_message(t('Heartbeat activity has been ported to Activity Log.') .' '.
      t('You can now uninstall the Heartbeat module.')
    );
  }

  // Import data directly from Activity.
  if (db_table_exists('activity_messages')) {
    db_query("INSERT IGNORE INTO activity_log_templates SET tid = 0, cacheable = 1");
    db_query("
      INSERT INTO activity_log_messages
        (tid, created, last_updated, stream_owner_id, stream_owner_type, viewer_id, cached)
      SELECT 0, created, created, value, 'user', at.uid, message
      FROM activity_access aa
      LEFT JOIN activity a
        ON aa.aid = a.aid
      LEFT JOIN activity_targets at
        ON aa.aid = at.aid
      LEFT JOIN activity_messages am
        ON at.amid = am.amid
    ");
    drupal_set_message(t('Activity has been ported to Activity Log.') .' '.
      t('You can now uninstall the Activity module.')
    );
  }
}
 */
