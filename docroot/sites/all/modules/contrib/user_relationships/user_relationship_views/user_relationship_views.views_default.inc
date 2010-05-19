<?php
// $Id: user_relationship_views.views_default.inc,v 1.1.2.1 2008/10/09 08:53:48 alexk Exp $

/**
 * @file
 * User Relationships Views support. A couple of default example views.
 * @author Alex Karshakevich http://drupal.org/user/183217
 */

/**
 * Implementation of hook_default_view_views().
 */
function user_relationship_views_views_default_views() {
  $view = new view;
  $view->name = 'user_relationships_content';
  $view->description = 'Use this view to show content posted by someone\'s related users. If you use content_profile, setting the content type filter to your profile node types will display your user profiles.';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'requester_id' => array(
      'label' => 'requester',
      'required' => 0,
      'id' => 'requester_id',
      'table' => 'user_relationships',
      'field' => 'requester_id',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Title',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'rtype' => array(
      'label' => 'Relationship type',
      'name_field' => 'name',
      'exclude' => 0,
      'id' => 'rtype',
      'table' => 'user_relationships',
      'field' => 'rtype',
      'relationship' => 'requester_id',
    ),
    'updated_at' => array(
      'label' => 'Updated date',
      'date_format' => 'small',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'updated_at',
      'table' => 'user_relationships',
      'field' => 'updated_at',
      'relationship' => 'requester_id',
    ),
  ));
  $handler->override_option('arguments', array(
    'requester_id' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'requester_id',
      'table' => 'user_relationships',
      'field' => 'requester_id',
      'relationship' => 'requester_id',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
    ),
    'rtype' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'rtype',
      'table' => 'user_relationships',
      'field' => 'rtype',
      'relationship' => 'requester_id',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'approved' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'approved',
      'table' => 'user_relationships',
      'field' => 'approved',
      'relationship' => 'requester_id',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'blog' => 'blog',
      ),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'type_op',
        'identifier' => 'type',
        'label' => 'Node: Type',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'rtype' => 'rtype',
      'updated_at' => 'updated_at',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'rtype' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'updated_at' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'user/%/associates');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  $view = new view;
  $view->name = 'user_relationships_browser';
  $view->description = 'Shows someone\'s related users';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'user_relationships';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'requestee_id' => array(
      'label' => 'requestee',
      'required' => 0,
      'id' => 'requestee_id',
      'table' => 'user_relationships',
      'field' => 'requestee_id',
      'relationship' => 'none',
    ),
    'requester_id' => array(
      'label' => 'requester',
      'required' => 0,
      'id' => 'requester_id',
      'table' => 'user_relationships',
      'field' => 'requester_id',
      'relationship' => 'none',
    ),
    'rtid' => array(
      'label' => 'rtid',
      'required' => 0,
      'id' => 'rtid',
      'table' => 'user_relationships',
      'field' => 'rtid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'plural_name' => array(
      'label' => '',
      'exclude' => 1,
      'id' => 'plural_name',
      'table' => 'user_relationship_types',
      'field' => 'plural_name',
      'relationship' => 'rtid',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'name' => array(
      'label' => '',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'requestee_id',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'updated_at' => array(
      'label' => 'Added',
      'date_format' => 'time ago',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'updated_at',
      'table' => 'user_relationships',
      'field' => 'updated_at',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
    'plural_name' => array(
      'order' => 'ASC',
      'id' => 'plural_name',
      'table' => 'user_relationship_types',
      'field' => 'plural_name',
      'relationship' => 'rtid',
    ),
  ));
  $handler->override_option('arguments', array(
    'requester_id' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'user',
      'default_argument' => '',
      'validate_type' => 'numeric',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'requester_id',
      'table' => 'user_relationships',
      'field' => 'requester_id',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'approved' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'approved',
      'table' => 'user_relationships',
      'field' => 'approved',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Relationships');
  $handler->override_option('items_per_page', 30);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => 'plural_name',
    'type' => 'ul',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(
      'name_1' => 'name_1',
    ),
    'separator' => ', ',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'relationships/%');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'All Relationships',
    'weight' => '0',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'Block by type', 'block_1');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 10);
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('block_description', 'Display user\'s relationships grouped by relationship type');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('block', 'Block by user', 'block_2');
  $handler->override_option('fields', array(
    'plural_name' => array(
      'label' => '',
      'exclude' => 1,
      'id' => 'plural_name',
      'table' => 'user_relationship_types',
      'field' => 'plural_name',
      'relationship' => 'rtid',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'name' => array(
      'label' => '',
      'link_to_user' => 1,
      'exclude' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'requestee_id',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'updated_at' => array(
      'label' => 'Added',
      'date_format' => 'time ago',
      'custom_date_format' => '',
      'exclude' => 1,
      'id' => 'updated_at',
      'table' => 'user_relationships',
      'field' => 'updated_at',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name_1' => array(
      'label' => '',
      'exclude' => 0,
      'id' => 'name_1',
      'table' => 'user_relationship_types',
      'field' => 'name',
      'relationship' => 'rtid',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('title', 'Related users');
  $handler->override_option('style_options', array(
    'grouping' => 'name',
    'type' => 'ul',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(),
    'separator' => '',
  ));
  $handler->override_option('block_description', 'Display user\'s relationships grouped by user');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  return $views;
}
