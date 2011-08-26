<?php

/**
 * @file
 *   Provide views data and handlers for the Facebook-style Micropublisher.
 */

/**
 * Implementation of hook_views_data().
 */
function fbsmp_views_data() {

  $data['fbsmp']['table']['group']  = t('Facebook-style Micropublisher');
  
  $data['fbsmp']['table']['join'] = array(
    'facebook_status' => array(
      'left_field' => 'sid',
      'field' => 'sid',
    ),
    'users' => array(
      'left_table' => 'facebook_status',
      'left_field' => 'sid',
      'field' => 'sid',
    ),
  );
  
  $data['fbsmp']['sid'] = array(
    'title' => t('Status ID'),
    'help' => t('The ID of the FBSS status.'),
  );
  
  $data['fbsmp']['type'] = array(
    'title' => t('Attachment type'),
    'help' => t('The type of plugin for the attachment.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['fbsmp']['attachment'] = array(
    'title' => t('Themed attachment'),
    'help' => t('The themed attachment for the FBSS status.'),
    'field' => array(
      'field' => 'data',
      'handler' => 'fbsmp_views_handler_field_themed_attachment',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  
  $data['fbsmp']['empty_status_attachment'] = array(
    'title' => t('Do not show empty status'),
    'help' => t('Do not show a status without a status text and attachment'),
    'filter' => array(
      'field' => 'data',
      'handler' => 'fbsmp_views_handler_filter_empty_status_attachment',
     ),
  );
  
  return $data;
 
}

/**
 * Implementation of hook_views_handlers().
 */
function fbsmp_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'fbsmp'),
    ),
    'handlers' => array(
      'fbsmp_views_handler_field_themed_attachment' => array(
        'parent' => 'views_handler_field',
      ),
      'fbsmp_views_handler_filter_empty_status_attachment' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
    ),
  );
}