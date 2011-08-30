<?php

/**
 * @file
 *   Functions to aid drush-based installations
 */

/**
 * Automated run through the option forms since drush can't 
 * handle the forms
 * 
 * @param &$task
 *   The installation profile task
 */
function _drupal_commons_drush_tasks(&$task) {
  drupal_commons_include('form');
  
  // Set the features
  $form = array();
  $form_state = array();
  $form_state['values'] = array(
    'feature-commons_core' => 1,
    'feature-commons_home' => 1,
    'feature-commons_blog' => 1,
    'feature-commons_discussion' => 1,
    'feature-commons_document' => 1,
    'feature-commons_wiki' => 1,
    'feature-commons_poll' => 1,
    'feature-commons_event' => 1,
    'feature-commons_dashboard' => 1,
    'feature-commons_notifications' => 1,
    'feature-commons_reputation' => 1,
    'feature-commons_group_aggregator' => 1,
    'feature-commons_admin' => 1,
    'feature-commons_seo' => 1,
    'feature-commons_invite' => 1,
    'feature-commons_profile' => 1,
    'feature-commons_shoutbox' => 1,
  );
  drupal_commons_features_form_submit($form, $form_state);
  
  // Set the theme
  $form = drupal_commons_theme_form();
  $form_state = array();
  $form_state['values']['theme'] = DRUPAL_COMMONS_DEFAULT_THEME;
  drupal_commons_theme_form_submit($form, $form_state);
    
  // Initiate the installation
  $task = 'install-commons';
  variable_set('install_task', $task);
}
