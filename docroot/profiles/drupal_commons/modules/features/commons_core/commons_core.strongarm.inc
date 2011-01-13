<?php

/**
 * Implementation of hook_strongarm().
 */
function commons_core_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_blog';
  $strongarm->value = '2';

  $export['comment_default_order_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_discussion';
  $strongarm->value = '2';

  $export['comment_default_order_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_document';
  $strongarm->value = '2';

  $export['comment_default_order_document'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_event';
  $strongarm->value = '2';

  $export['comment_default_order_event'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_notice';
  $strongarm->value = '2';

  $export['comment_default_order_notice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_poll';
  $strongarm->value = '2';

  $export['comment_default_order_poll'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_wiki';
  $strongarm->value = '2';

  $export['comment_default_order_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_group';
  $strongarm->value = '0';

  $export['comment_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_blog';
  $strongarm->value = '0';

  $export['comment_preview_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_discussion';
  $strongarm->value = '0';

  $export['comment_preview_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_document';
  $strongarm->value = '0';

  $export['comment_preview_document'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_event';
  $strongarm->value = '0';

  $export['comment_preview_event'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_notice';
  $strongarm->value = '0';

  $export['comment_preview_notice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_poll';
  $strongarm->value = '0';

  $export['comment_preview_poll'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_wiki';
  $strongarm->value = '0';

  $export['comment_preview_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_blog';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-3',
    'revision_information' => '2',
    'author' => '6',
    'options' => '7',
    'comment_settings' => '4',
    'menu' => '3',
    'taxonomy' => '-4',
    'path' => '5',
    'flag' => '1',
    'og_nodeapi' => '-1',
  );

  $export['content_extra_weights_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_discussion';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-3',
    'revision_information' => '2',
    'author' => '6',
    'options' => '7',
    'comment_settings' => '4',
    'menu' => '3',
    'taxonomy' => '-4',
    'path' => '5',
    'flag' => '1',
    'og_nodeapi' => '-1',
  );

  $export['content_extra_weights_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_document';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-3',
    'revision_information' => '2',
    'author' => '5',
    'options' => '6',
    'comment_settings' => '4',
    'menu' => '3',
    'taxonomy' => '-4',
    'path' => '7',
    'flag' => '1',
    'og_nodeapi' => '-1',
  );

  $export['content_extra_weights_document'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_event';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-3',
    'revision_information' => '3',
    'author' => '7',
    'options' => '8',
    'comment_settings' => '5',
    'menu' => '4',
    'taxonomy' => '-4',
    'path' => '6',
    'flag' => '2',
    'og_nodeapi' => '0',
  );

  $export['content_extra_weights_event'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_group';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-2',
    'revision_information' => '5',
    'author' => '9',
    'options' => '10',
    'comment_settings' => '7',
    'menu' => '6',
    'taxonomy' => '-3',
    'path' => '8',
    'og_description' => '-4',
    'og_selective' => '2',
    'og_register' => '-1',
    'og_directory' => '0',
    'og_private' => '1',
  );

  $export['content_extra_weights_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_notice';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-2',
    'revision_information' => '-1',
    'author' => '3',
    'options' => '4',
    'comment_settings' => '2',
    'menu' => '0',
    'taxonomy' => '-4',
    'path' => '1',
  );

  $export['content_extra_weights_notice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_poll';
  $strongarm->value = array(
    'title' => '-5',
    'revision_information' => '3',
    'author' => '7',
    'options' => '8',
    'comment_settings' => '5',
    'menu' => '4',
    'taxonomy' => '-3',
    'path' => '6',
    'choice_wrapper' => '-4',
    'settings' => '-2',
    'flag' => '2',
    'og_nodeapi' => '1',
  );

  $export['content_extra_weights_poll'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_wiki';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-3',
    'revision_information' => '2',
    'author' => '6',
    'options' => '7',
    'comment_settings' => '4',
    'menu' => '3',
    'taxonomy' => '-4',
    'path' => '5',
    'flag' => '1',
    'og_nodeapi' => '-1',
  );

  $export['content_extra_weights_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_camelcase';
  $strongarm->value = 0;

  $export['freelinking_camelcase'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_nodetype';
  $strongarm->value = 'wiki';

  $export['freelinking_nodetype'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_notfound';
  $strongarm->value = 'no access search';

  $export['freelinking_notfound'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_onceonly';
  $strongarm->value = 0;

  $export['freelinking_onceonly'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_restriction';
  $strongarm->value = array(
    'wiki' => 'wiki',
  );

  $export['freelinking_restriction'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'heartbeat_access_types';
  $strongarm->value = array(
    'privateheartbeat' => array(
      'name' => 'Personal Heartbeat',
      'class' => 'PrivateHeartbeat',
      'path' => 'includes/privateheartbeat.inc',
      'module' => 'heartbeat',
      'access' => 'user_is_logged_in',
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'publicheartbeat' => array(
      'name' => 'Public Heartbeat',
      'class' => 'PublicHeartbeat',
      'path' => 'includes/publicheartbeat.inc',
      'module' => 'heartbeat',
      'access' => TRUE,
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'singleheartbeat' => array(
      'name' => 'Single activity',
      'class' => 'SingleHeartbeat',
      'path' => 'includes/singleheartbeat.inc',
      'module' => 'heartbeat',
      'access' => TRUE,
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'connectedheartbeat' => array(
      'name' => 'Heartbeat relational activity',
      'class' => 'ConnectedHeartbeat',
      'path' => 'connectedheartbeat.inc',
      'module' => 'friendlist_activity',
      'access' => 'user_is_logged_in',
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'ogheartbeat' => array(
      'name' => 'Organic group activity',
      'class' => 'OgHeartbeat',
      'path' => 'ogheartbeat.inc',
      'module' => 'og_activity',
      'access' => NULL,
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'groupsactivity' => array(
      'name' => 'Organic groups activity',
      'class' => 'GroupsActivity',
      'path' => 'groupsactivity.inc',
      'module' => 'og_activity',
      'access' => NULL,
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
  );

  $export['heartbeat_access_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'heartbeat_relations_api';
  $strongarm->value = 'user_relationships_api';

  $export['heartbeat_relations_api'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'heartbeat_show_user_profile_messages_privateheartbeat';
  $strongarm->value = 1;

  $export['heartbeat_show_user_profile_messages_privateheartbeat'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_blog';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_discussion';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_document';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_document'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_event';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_event'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_forum';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_forum'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_group';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_notice';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_notice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_page';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_poll';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_poll'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_wiki';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
    2 => 'revision',
  );

  $export['node_options_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_audience_required';
  $strongarm->value = '1';

  $export['og_audience_required'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_blog';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_discussion';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_document';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_document'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_event';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_event'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_group';
  $strongarm->value = 'group';

  $export['og_content_type_usage_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_notice';
  $strongarm->value = 'omitted';

  $export['og_content_type_usage_notice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_page';
  $strongarm->value = 'omitted';

  $export['og_content_type_usage_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_poll';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_poll'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_wiki';
  $strongarm->value = 'group_post_wiki';

  $export['og_content_type_usage_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_home_page_view';
  $strongarm->value = '0';

  $export['og_home_page_view'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_private_groups';
  $strongarm->value = '3';

  $export['og_private_groups'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility';
  $strongarm->value = '2';

  $export['og_visibility'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_blog_pattern';
  $strongarm->value = 'blog/[title-raw]';

  $export['pathauto_node_blog_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_discussion_pattern';
  $strongarm->value = 'discussion/[title-raw]';

  $export['pathauto_node_discussion_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_document_pattern';
  $strongarm->value = 'document/[title-raw]';

  $export['pathauto_node_document_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_event_pattern';
  $strongarm->value = 'event/[title-raw]';

  $export['pathauto_node_event_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_group_pattern';
  $strongarm->value = 'groups/[title-raw]';

  $export['pathauto_node_group_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_notice_pattern';
  $strongarm->value = 'notice/[title-raw]';

  $export['pathauto_node_notice_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_page_pattern';
  $strongarm->value = '';

  $export['pathauto_node_page_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_poll_pattern';
  $strongarm->value = 'poll/[title-raw]';

  $export['pathauto_node_poll_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_wiki_pattern';
  $strongarm->value = 'wiki/[title-raw]';

  $export['pathauto_node_wiki_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_2_pattern';
  $strongarm->value = 'tag/[catpath-raw]';

  $export['pathauto_taxonomy_2_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_tracker_pattern';
  $strongarm->value = 'users/[user-raw]/track';

  $export['pathauto_tracker_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_user_pattern';
  $strongarm->value = 'users/[user-raw]';

  $export['pathauto_user_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagadelic_block_tags_2';
  $strongarm->value = '20';

  $export['tagadelic_block_tags_2'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagadelic_sort_order';
  $strongarm->value = 'weight,desc';

  $export['tagadelic_sort_order'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagging_inject_2';
  $strongarm->value = 1;

  $export['tagging_inject_2'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagging_show_suggestion_example';
  $strongarm->value = 0;

  $export['tagging_show_suggestion_example'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_settings';
  $strongarm->value = array(
    'toggle_logo' => 1,
    'toggle_name' => 1,
    'toggle_slogan' => 0,
    'toggle_mission' => 1,
    'toggle_node_user_picture' => 0,
    'toggle_comment_user_picture' => 0,
    'toggle_search' => 1,
    'toggle_favicon' => 1,
    'toggle_primary_links' => 1,
    'toggle_secondary_links' => 1,
    'toggle_node_info_blog' => 1,
    'toggle_node_info_discussion' => 1,
    'toggle_node_info_document' => 1,
    'toggle_node_info_event' => 0,
    'toggle_node_info_group' => 1,
    'toggle_node_info_notice' => 0,
    'toggle_node_info_page' => 0,
    'toggle_node_info_poll' => 1,
    'toggle_node_info_wiki' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'favicon_upload' => '',
  );

  $export['theme_settings'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_dimensions';
  $strongarm->value = '';

  $export['user_picture_dimensions'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_comments';
  $strongarm->value = 'user_picture_meta';

  $export['user_picture_imagecache_comments'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles';
  $strongarm->value = 'profile_pictures';

  $export['user_picture_imagecache_profiles'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles_default';
  $strongarm->value = 'user_picture_meta';

  $export['user_picture_imagecache_profiles_default'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_path';
  $strongarm->value = 'pictures';

  $export['user_picture_path'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_pictures';
  $strongarm->value = '1';

  $export['user_pictures'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_group_terms';
  $strongarm->value = 0;

  $export['user_terms_group_terms'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_group_title';
  $strongarm->value = 'User terms';

  $export['user_terms_group_title'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_profile_path';
  $strongarm->value = 'account';

  $export['user_terms_profile_path'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_vocabs';
  $strongarm->value = array(
    2 => '2',
  );

  $export['user_terms_vocabs'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_404_type';
  $strongarm->value = array(
    'Link to creation' => 'Link to creation',
    'Link to search' => 0,
    'Creation form' => 0,
  );

  $export['wikitools_404_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_disallowed_characters';
  $strongarm->value = '[]{}|';

  $export['wikitools_disallowed_characters'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_main_page_title';
  $strongarm->value = 'Main Page';

  $export['wikitools_main_page_title'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_node_types';
  $strongarm->value = array(
    'wiki' => 'wiki',
    'blog' => 0,
    'discussion' => 0,
    'document' => 0,
    'event' => 0,
    'group' => 0,
    'page' => 0,
    'poll' => 0,
    'story' => 0,
  );

  $export['wikitools_node_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_options';
  $strongarm->value = array(
    'node creation' => 'node creation',
    'node search' => 'node search',
    'unique titles' => 'unique titles',
    'underscore as space' => 'underscore as space',
    'auto redirect' => 0,
    'move protection' => 0,
    'dash as space' => 0,
  );

  $export['wikitools_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_path';
  $strongarm->value = 'wiki';

  $export['wikitools_path'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_subpages';
  $strongarm->value = 'edit, delete, view, revisions';

  $export['wikitools_subpages'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_subpages_handling';
  $strongarm->value = 'disabled';

  $export['wikitools_subpages_handling'] = $strongarm;
  return $export;
}
