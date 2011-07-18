<?php

/**
 * @file
 *   Administrative settings for the Activity Log module.
 */

/**
 * The administrative settings form.
 */
function activity_log_admin($form_state) {
  $form = array();
  $form['info'] = array(
    '#value' => t('This page allows you to configure global settings for the Activity Log module.') .' '.
      t('In order to set up events to be logged to activity streams, you should <a href="!path">create a Rule</a> that uses the "Log Activity" action.', array(
        '!path' => 'admin/rules/trigger',
      )),
  );
  $form['activity_log_max_age'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of days to store an activity record'),
    '#description' => t('Activity records older than this many days will be deleted when cron runs.'),
    '#default_value' => variable_get('activity_log_max_age', 30),
    '#maxlength' => 6,
    '#size' => 4,
  );
  $options = array('node' => t('Node messages when someone comments on the relevant node'));
  if (module_exists('fbss_comments')) {
    $options['status'] = t('Status messages when someone comments on the relevant status');
  }
  $form['activity_log_comments_bump'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Bump to the top of the stream'),
    '#description' => t('Bump activity messages to the top of activity streams when someone comments on the relevant entities.'),
    '#options' => $options,
    '#default_value' => variable_get('activity_log_comments_bump', array('status' => 'status')),
  );
  $form['activity_log_clear_cache'] = array(
    '#type' => 'submit',
    '#value' => t('Clear all message caches'),
    '#submit' => array('activity_log_admin_clear_caches'),
    '#description' => t('Clear all activity message caches.') .' '.
      t('<strong>Warning:</strong> viewing activity messages will be slow after this until the cache is rebuilt.'),
  );
  return system_settings_form($form);
}

/**
 * Submit callback for the "clear caches" button.
 */
function activity_log_admin_clear_caches() {
  drupal_set_message(t('Message caches cleared.'));
  activity_log_clear_message_cache();
}

/**
 * The regenerate activity messages form.
 */
function activity_log_admin_regenerate($form_state) {
  module_load_include('inc', 'activity_log', 'activity_log.generate');
  $regenerate = array_keys(module_invoke_all('activity_log_regenerate_info'));
  $form = array();
  // Extract the relevant information from the list of all Rules.
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
    '#title' => t('Rules to execute'),
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
    '#title' => t('Regenerate'),
  );
  return $form;
}

/**
 * The validate callback for the regenerate activity messages form.
 */
function activity_log_admin_regenerate_validate($form, $form_state) {
  $v = $form_state['values']['age'];
  if (!is_numeric($v) || $v < 0) {
    form_set_error('age', t('The oldest content to regenerate setting must have a nonnegative numeric value.'));
  }
}

/**
 * The submit callback for the regenerate activity messages form.
 */
function activity_log_admin_regenerate_submit($form, $form_state) {
  $events = array_filter($form_state['values']['events']);
  $age = $form_state['values']['age'] ? time() - $form_state['values']['age'] * 86400 : 0;
  $batch = array(
    'operations' => array(
      array('activity_log_prepare_regenerate', array($age)),
      array('activity_log_regenerate', array($events, $age)),
    ),
    'finished' => 'activity_log_regenerate_batch_finished',
    'title' => t('Generating activity messages'),
    'file' => drupal_get_path('module', 'activity_log') .'/facebook_status.admin.inc',
  );
  batch_set($batch);
}

/**
 * Delete activity messages created within the specified period.
 */
function activity_log_prepare_regenerate($age, &$context) {
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
function activity_log_regenerate($events, $age, &$context) {
  module_load_include('inc', 'activity_log', 'activity_log.generate');
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

/*
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
 */
