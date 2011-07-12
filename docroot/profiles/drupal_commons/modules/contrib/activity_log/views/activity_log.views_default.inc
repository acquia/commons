<?php

/**
 * Implementation of hook_views_default_views().
 */
function activity_log_views_default_views() {
  $view = new view;
  $view->name = 'activity_log_stream';
  $view->description = 'Displays activity streams.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'activity_log_messages';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE;
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'message' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'message',
      'table' => 'activity_log_messages',
      'field' => 'message',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'last_updated' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'last_updated',
      'table' => 'activity_log_messages',
      'field' => 'last_updated',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'stream_owner_type' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'activity_log_default_stream_owner_type',
      'default_argument' => '',
      'validate_type' => 'activity_log_validate_stream_owner_type',
      'validate_fail' => 'not found',
      'glossary' => 0,
      'limit' => '0',
      'case' => 'none',
      'path_case' => 'none',
      'transform_dash' => 0,
      'id' => 'stream_owner_type',
      'table' => 'activity_log_messages',
      'field' => 'stream_owner_type',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_activity_log_stream_owner_type' => 'user',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
    ),
    'stream_owner_id' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'include' => array(
        'og' => 'og',
        'ur' => 'ur',
      ),
      'id' => 'stream_owner_id',
      'table' => 'activity_log_messages',
      'field' => 'stream_owner_id',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_activity_log_stream_owner_type' => 'user',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'view all activity messages',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('use_pager', '1');
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'activities');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Activity stream',
    'description' => 'Displays activity streams.',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;
  return $views;
}
