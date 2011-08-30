<?php

/**
 * @file
 *   Provide Views data and handlers for the FBSS Flag module.
 */

/**
 * Implementation of hook_views_data().
 */
function fbss_flag_views_data() {
  $data = array();

  $data['facebook_status']['user-flag-plus-current'] = array(
    'title' => t('Content from flagged users or the current user'),
    'help' => t('Shows content from only flagged users or the current user.'),
    'filter' => array(
      'field' => 'sender',
      'handler' => 'facebook_status_views_handler_filter_flagged_user',
    ),
  );
  $data['facebook_status']['user-flag-plus-arg'] = array(
    'title' => t('Content from flagged users or the argument user'),
    'help' => t('Shows content from only flagged users or the argument user.'),
    'argument' => array(
      'field' => 'sender',
      'handler' => 'facebook_status_views_handler_argument_flagged_user',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function fbss_flag_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'fbss_flag') .'/views',
    ),
    'handlers' => array(
      'facebook_status_views_handler_filter_flagged_user' => array(
        'parent' => 'views_handler_filter',
      ),
      'facebook_status_views_handler_argument_flagged_user' => array(
        'parent' => 'views_handler_argument',
      ),
    ),
  );
}
