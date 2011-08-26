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
  $default_rule_count = _activity_log_rebuild_templates();
  if ($default_rule_count) {
    drupal_set_message(t('Finished building !count default Activity Log templates.', array('!count' => $default_rule_count)));
  }
  activity_log_clear_message_cache();
  drupal_set_message(t('Message caches cleared.'));
}
