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
  return system_settings_form($form);
}
