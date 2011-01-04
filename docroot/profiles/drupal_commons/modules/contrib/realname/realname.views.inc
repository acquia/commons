<?php
// $Id: realname.views.inc,v 1.1.2.3 2009/10/08 19:43:07 nancyw Exp $
/**
 * @file
 * Realname VIEW declarations.
 */

function realname_views_data_alter(&$data) {
  if (variable_get('realname_view', FALSE)) {
    // override username handling in order to use realname theme
    $data['users']['name']['field']['handler'] = 'realname_handler_field_user_name_override';
    $data['users']['uid']['filter']['handler'] = 'realname_handler_filter_user_name';
    $data['users']['uid']['argument']['handler'] = 'realname_handler_argument_user_uid';
  }
}

function realname_views_data() {
  $tables['realname'] =  array(
    'table' => array(
      'group' => t('Realname'),
      'join' => array(
        'users' => array(
          'field' => 'uid',
          'left_field' => 'uid'
          )
        ),
      ),
    'uid' => array(
      'title' => t('Uid'),
      'help' => t('The user ID'), // The help that appears on the UI,
      'argument' => array('handler' => 'realname_handler_argument_user_uid'),
      'filter' => array(
        'title' => t('User Realname'),
        'handler' => 'realname_handler_filter_user_name',
        ),
      'sort' => array('handler' => 'views_handler_sort'),
      ),
    'realname' => array(
      'title' => t('Name'), // The item as it appears on the UI,
      'help' => t('The user or author name.'), // The help that appears on the UI,
      'field' => array(
        'handler' => 'realname_handler_field_user_name',
        'click sortable' => TRUE,
        ),
      'sort' => array('handler' => 'views_handler_sort'),
      'argument' => array('handler' => 'views_handler_argument_string'),
      'filter' => array('handler' => 'views_handler_filter_string'),
     ),
  );

  return $tables;
}

/**
 * Implementation of hook_views_plugins
 */
function realname_views_plugins() {
  return array(
    'argument validator' => array(
      'user_realname' => array(
        'title' => t('User (realname)'),
        'handler' => 'realname_plugin_argument_validate_user',
        'parent' => 'user',
      ),
    ),
  );
}

/**
 * Define all realname views handlers
 *
 **/
function realname_views_handlers() {
  return array(
    'info' => array(),
    'handlers' => array(
      'realname_handler_field_user_name' => array('parent' => 'views_handler_field_user_name'),
      'realname_handler_argument_user_uid' => array('parent' => 'views_handler_argument_user_uid'),
      'realname_handler_filter_user_name' => array('parent' => 'views_handler_filter_user_name'),
      'realname_handler_field_user_name_override' => array('parent' => 'views_handler_field_user_name'),
    )
  );
}
