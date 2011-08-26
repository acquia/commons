<?php

/**
 * Implementation of hook_strongarm().
 */
function commons_notifications_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'messaging_default_filter';
  $strongarm->value = '4';

  $export['messaging_default_filter'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'messaging_default_method';
  $strongarm->value = 'mail';

  $export['messaging_default_method'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_per_type';
  $strongarm->value = '1';

  $export['notifications_content_per_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type';
  $strongarm->value = array(
    'grouptype' => 'grouptype',
    'thread' => 'thread',
    'nodetype' => 'nodetype',
    'author' => 'author',
    'typeauthor' => 0,
  );

  $export['notifications_content_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_group';
  $strongarm->value = array();

  $export['notifications_content_type_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_default_auto';
  $strongarm->value = 0;

  $export['notifications_default_auto'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_node_ui_group';
  $strongarm->value = array();

  $export['notifications_node_ui_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_account_options';
  $strongarm->value = array(
    'links' => 'links',
    'block' => 'block',
  );

  $export['notifications_ui_account_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_node';
  $strongarm->value = array(
    'form' => 'form',
    'comment' => 'comment',
    'links' => 'links',
    'teaserlinks' => 'teaserlinks',
    'block' => 'block',
    'subform' => 0,
  );

  $export['notifications_ui_node'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_per_type';
  $strongarm->value = '0';

  $export['notifications_ui_per_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_types';
  $strongarm->value = array(
    'thread' => 'thread',
    'nodetype' => 'nodetype',
    'author' => 'author',
    'typeauthor' => 0,
    'grouptype' => 'grouptype',
  );

  $export['notifications_ui_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_user';
  $strongarm->value = array(
    'page' => 'page',
    'create' => 'create',
  );

  $export['notifications_ui_user'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_notifications_autosubscribe';
  $strongarm->value = 0;

  $export['og_notifications_autosubscribe'] = $strongarm;
  return $export;
}
