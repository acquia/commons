<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_core_context_default_contexts() {
  $items = array();

  $items['context_ui-content-global_content'] = array(
    'namespace' => 'context_ui',
    'attribute' => 'content',
    'value' => 'global_content',
    'description' => 'Site-wide content pages',
    'path' => array(
      'content/*' => 'content/*',
      'featured' => 'featured',
      'notices' => 'notices',
    ),
    'block' => array(
      'views_tag_cloud-block_1' => array(
        'module' => 'views',
        'delta' => 'tag_cloud-block_1',
        'weight' => 43,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Popular Tags',
        'type' => 'context_ui',
      ),
      'views_most_active_users-block_1' => array(
        'module' => 'views',
        'delta' => 'most_active_users-block_1',
        'weight' => 44,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Most Active Users',
        'type' => 'context_ui',
      ),
    ),
  );
  $items['context_ui-dashboard-dashboard'] = array(
    'namespace' => 'context_ui',
    'attribute' => 'dashboard',
    'value' => 'dashboard',
    'description' => 'User Dashboard',
    'path' => array(
      'dashboard' => 'dashboard',
    ),
    'block' => array(
      'views_og_dashboard_groups-block_1' => array(
        'module' => 'views',
        'delta' => 'og_dashboard_groups-block_1',
        'weight' => 44,
        'region' => 'sidebar_first',
        'status' => '0',
        'label' => 'My Groups (custom)',
        'type' => 'context_ui',
      ),
      'views_my_recent_items-block_1' => array(
        'module' => 'views',
        'delta' => 'my_recent_items-block_1',
        'weight' => 45,
        'region' => 'sidebar_first',
        'status' => '0',
        'label' => 'My Recent Items',
        'type' => 'context_ui',
      ),
      'views_my_unread_items-block_1' => array(
        'module' => 'views',
        'delta' => 'my_unread_items-block_1',
        'weight' => 46,
        'region' => 'sidebar_first',
        'status' => '0',
        'label' => 'My Unread Items',
        'type' => 'context_ui',
      ),
      'user_relationship_blocks_my-1' => array(
        'module' => 'user_relationship_blocks',
        'delta' => 'my-1',
        'weight' => 47,
        'region' => 'sidebar_first',
        'status' => '0',
        'label' => 'My Relationships: Friends ',
        'type' => 'context_ui',
      ),
      'views_recent_notices-block_1' => array(
        'module' => 'views',
        'delta' => 'recent_notices-block_1',
        'weight' => 44,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Recent Notices',
        'type' => 'context_ui',
      ),
      'views_upcoming_events-block_2' => array(
        'module' => 'views',
        'delta' => 'upcoming_events-block_2',
        'weight' => 45,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Upcoming Events (My Groups)',
        'type' => 'context_ui',
      ),
      'views_og_featured-block_1' => array(
        'module' => 'views',
        'delta' => 'og_featured-block_1',
        'weight' => 46,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Featured groups',
        'type' => 'context_ui',
      ),
      'views_most_active_users-block_1' => array(
        'module' => 'views',
        'delta' => 'most_active_users-block_1',
        'weight' => 47,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Most Active Users',
        'type' => 'context_ui',
      ),
    ),
  );
  $items['context_ui-global-global'] = array(
    'namespace' => 'context_ui',
    'attribute' => 'global',
    'value' => 'global',
    'description' => 'Show on every page',
    'sitewide' => '1',
    'block' => array(
      'views_user_meta-block_1' => array(
        'module' => 'views',
        'delta' => 'user_meta-block_1',
        'weight' => 37,
        'region' => 'header',
        'status' => '0',
        'label' => 'User meta info',
        'type' => 'context_ui',
      ),
      'user_0' => array(
        'module' => 'user',
        'delta' => '0',
        'weight' => 38,
        'region' => 'header',
        'status' => '0',
        'label' => 'User login',
        'type' => 'context_ui',
      ),
      'commons_2' => array(
        'module' => 'commons',
        'delta' => '2',
        'weight' => 37,
        'region' => 'footer',
        'status' => '0',
        'label' => 'Drupal Commons information',
        'type' => 'context_ui',
      ),
    ),
  );
  $items['context_ui-group-group'] = array(
    'namespace' => 'context_ui',
    'attribute' => 'group',
    'value' => 'group',
    'description' => 'Show on group context',
    'og_group_type' => array(
      '0' => 'group',
    ),
    'block' => array(
      'og_0' => array(
        'module' => 'og',
        'delta' => '0',
        'weight' => 37,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Group details',
        'type' => 'context_ui',
      ),
      'og_views_0' => array(
        'module' => 'og_views',
        'delta' => '0',
        'weight' => 38,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Group search',
        'type' => 'context_ui',
      ),
      'views_og_upcoming_events-block_1' => array(
        'module' => 'views',
        'delta' => 'og_upcoming_events-block_1',
        'weight' => 39,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Upcoming events (Group)',
        'type' => 'context_ui',
      ),
      'views_og_members_custom_block-block_1' => array(
        'module' => 'views',
        'delta' => 'og_members_custom_block-block_1',
        'weight' => 40,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Group members',
        'type' => 'context_ui',
      ),
      'og_aggregator_0' => array(
        'module' => 'og_aggregator',
        'delta' => '0',
        'weight' => 41,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Group aggregator',
        'type' => 'context_ui',
      ),
      'views_og_recent_poll-block_1' => array(
        'module' => 'views',
        'delta' => 'og_recent_poll-block_1',
        'weight' => 42,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Latest group poll',
        'type' => 'context_ui',
      ),
      'views_og_tag_cloud-block_1' => array(
        'module' => 'views',
        'delta' => 'og_tag_cloud-block_1',
        'weight' => 43,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Group content tag cloud',
        'type' => 'context_ui',
      ),
      'views_og_members_custom_block-block' => array(
        'module' => 'views',
        'delta' => 'og_members_custom_block-block',
        'weight' => 44,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Group admins',
        'type' => 'context_ui',
      ),
    ),
  );
  $items['context_ui-profile-profile'] = array(
    'namespace' => 'context_ui',
    'attribute' => 'profile',
    'value' => 'profile',
    'description' => 'User Profile',
    'user' => array(
      '0' => 2,
    ),
    'block' => array(
      'user_relationship_blocks_actions' => array(
        'module' => 'user_relationship_blocks',
        'delta' => 'actions',
        'weight' => -43,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'User Relationships: Actions',
        'type' => 'context_ui',
      ),
      'views_og_profile_user_groups-block_1' => array(
        'module' => 'views',
        'delta' => 'og_profile_user_groups-block_1',
        'weight' => -42,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'User Being Viewed\'s Groups',
        'type' => 'context_ui',
      ),
      'user_relationship_blocks_user-1' => array(
        'module' => 'user_relationship_blocks',
        'delta' => 'user-1',
        'weight' => -41,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'User Relationships: Friends ',
        'type' => 'context_ui',
      ),
    ),
  );
  $items['context_ui-users-user_browser'] = array(
    'namespace' => 'context_ui',
    'attribute' => 'users',
    'value' => 'user_browser',
    'description' => 'User Browser',
    'views' => array(
      '0' => 'user_directory',
    ),
    'block' => array(
      'commons_0' => array(
        'module' => 'commons',
        'delta' => '0',
        'weight' => 45,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'User Statistics',
        'type' => 'context_ui',
      ),
      'views_users_online-block_1' => array(
        'module' => 'views',
        'delta' => 'users_online-block_1',
        'weight' => 46,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Who\'s Online? (Custom)',
        'type' => 'context_ui',
      ),
      'views_most_active_users-block_1' => array(
        'module' => 'views',
        'delta' => 'most_active_users-block_1',
        'weight' => 47,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Most Active Users',
        'type' => 'context_ui',
      ),
      'views_newest_users-block_1' => array(
        'module' => 'views',
        'delta' => 'newest_users-block_1',
        'weight' => 48,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Newest Users',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_ctools_plugin_api().
 */
function commons_core_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => 1);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function commons_core_imagecache_default_presets() {
  $items = array(
    'Featured' => array(
      'presetname' => 'Featured',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '250',
            'height' => '250',
          ),
        ),
      ),
    ),
    'Small' => array(
      'presetname' => 'Small',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '150',
            'height' => '150',
          ),
        ),
      ),
    ),
    'group_images' => array(
      'presetname' => 'group_images',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '380',
            'height' => '90',
            'upscale' => 0,
          ),
        ),
        '1' => array(
          'weight' => '0',
          'module' => 'imagecache_canvasactions',
          'action' => 'canvasactions_definecanvas',
          'data' => array(
            'RGB' => array(
              'HEX' => '',
            ),
            'under' => 1,
            'exact' => array(
              'width' => '380',
              'height' => '90',
              'xpos' => 'left',
              'ypos' => 'top',
            ),
            'relative' => array(
              'leftdiff' => '',
              'rightdiff' => '',
              'topdiff' => '',
              'bottomdiff' => '',
            ),
          ),
        ),
      ),
    ),
    'group_images_thumb' => array(
      'presetname' => 'group_images_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '24',
            'height' => '24',
            'upscale' => 1,
          ),
        ),
        '1' => array(
          'weight' => '0',
          'module' => 'imagecache_canvasactions',
          'action' => 'canvasactions_definecanvas',
          'data' => array(
            'RGB' => array(
              'HEX' => '',
            ),
            'under' => 1,
            'exact' => array(
              'width' => '24',
              'height' => '24',
              'xpos' => 'left',
              'ypos' => 'center',
            ),
            'relative' => array(
              'leftdiff' => '',
              'rightdiff' => '',
              'topdiff' => '',
              'bottomdiff' => '',
            ),
          ),
        ),
      ),
    ),
    'member_list_image' => array(
      'presetname' => 'member_list_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '90',
            'height' => '90',
          ),
        ),
      ),
    ),
    'profile_pictures' => array(
      'presetname' => 'profile_pictures',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '150',
            'height' => '150',
          ),
        ),
      ),
    ),
    'user_picture_meta' => array(
      'presetname' => 'user_picture_meta',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '30',
            'height' => '30',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function commons_core_node_info() {
  $items = array(
    'discussion' => array(
      'name' => t('Discussion'),
      'module' => 'features',
      'description' => t('A item which allows the open discussion of a given topic.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'document' => array(
      'name' => t('Document'),
      'module' => 'features',
      'description' => t('A document item which contains a title, description, an unlimited amount of attached files.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'event' => array(
      'name' => t('Event'),
      'module' => 'features',
      'description' => t('An item that is used to provide details about an event. Events can be connected to multiple groups.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'group' => array(
      'name' => t('Group'),
      'module' => 'features',
      'description' => t('A group which members can be a part of.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'notice' => array(
      'name' => t('Notice'),
      'module' => 'features',
      'description' => t('A notice is an informative message that is meant to broadcast information to all of the users of the site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'module' => 'features',
      'description' => t('A <em>page</em>, similar in form to a <em>story</em>, is a simple method for creating and displaying information that rarely changes, such as an "About us" section of a website. By default, a <em>page</em> entry does not allow visitor comments and is not featured on the site\'s initial home page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'wiki' => array(
      'name' => t('Wiki page'),
      'module' => 'features',
      'description' => t('A wiki is used for information collaboration.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_rules_defaults().
 */
function commons_core_rules_defaults() {
  return array(
    'rules' => array(
      'commons_core_5' => array(
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'Heartbeat: when user deletes content, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '[author:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_delete_content',
              'variables_param' => '@user_name=|=[user:user-name-url]-|-@type=|=[node:type-name]-|-@node_title=|=[node:title]-|-@types=|=[node:type-name]s-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'uid_target_param' => array(
                    '0' => 'author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'node',
                    '1' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_1' => array(
        '#type' => 'rule',
        '#set' => 'event_user_relationships_approve',
        '#label' => 'Heartbeat: user B and user A are now friends',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[requestee:uid]',
              'uid_target_param' => '[requester:uid]',
              'nid_param' => 0,
              'nid_target_param' => 0,
              'message_id_param' => 'heartbeat_become_friends',
              'variables_param' => '@user1=|=[requestee:user-name-url]-|-@relation_type=|=[relationship:relationship-name]s-|-@user2=|=[requester:user-name-url]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'requestee',
                  ),
                  'uid_target_param' => array(
                    '0' => 'requester',
                  ),
                  'variables_param' => array(
                    '0' => 'requester',
                    '1' => 'requestee',
                    '2' => 'relationship',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_users_action',
            '#info' => array(
              'label' => 'Logs default user activity between users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'message_id_param',
                '3' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_2' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Heartbeat: when user adds a node, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'page is published',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
          '1' => array(
            '#weight' => 0,
            '#negate' => 1,
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'page' => 'page',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#info' => array(
              'label' => 'Content has type page',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs activity for single users adding a page',
              'label callback' => FALSE,
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[author:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_add_node',
              'variables_param' => '@username=|=[author:user-name-url]-|-@node_type=|=[node:type-name]-|-@node_title=|=[node:title-link]-|-@types=|=[node:type-name]s-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'node',
                    '1' => 'author',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_3' => array(
        '#type' => 'rule',
        '#set' => 'event_user_insert',
        '#label' => 'Heartbeat: when user account is created, save activity',
        '#active' => 0,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '[account:uid]',
              'nid_param' => '',
              'nid_target_param' => '',
              'message_id_param' => 'heartbeat_create_user',
              'variables_param' => '@user_name=|=[account:account-url]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_4' => array(
        '#type' => 'rule',
        '#set' => 'event_user_delete',
        '#label' => 'Heartbeat: when user account is deleted, save activity',
        '#active' => 0,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '[account:uid]',
              'nid_param' => '',
              'nid_target_param' => '',
              'message_id_param' => 'heartbeat_delete_user',
              'variables_param' => '@user_name=|=[account:user]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_6' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_delete',
        '#label' => 'Heartbeat: when deletes adds a comment, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Commented content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '[comment_author:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_delete_comment',
              'variables_param' => '@username=|=[user:user-name-url]-|-@comment_title=|=[comment:comment-title]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'uid_target_param' => array(
                    '0' => 'comment_author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'comment',
                    '1' => 'node',
                    '2' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_7' => array(
        '#type' => 'rule',
        '#set' => 'event_user_relationships_approve',
        '#label' => 'Heartbeat: user A and user B are now friends',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs default user activity between users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'message_id_param',
                '3' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_users_action',
            '#settings' => array(
              'uid_param' => '[requester:uid]',
              'uid_target_param' => '[requestee:uid]',
              'nid_param' => 0,
              'nid_target_param' => 0,
              'message_id_param' => 'heartbeat_become_friends',
              'variables_param' => '@user1=|=[requester:user-name-url]-|-@relation_type=|=[relationship:relationship-name]s-|-@user2=|=[requestee:user-name-url]',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'requester',
                  ),
                  'uid_target_param' => array(
                    '0' => 'requestee',
                  ),
                  'variables_param' => array(
                    '0' => 'requester',
                    '1' => 'requestee',
                    '2' => 'relationship',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_8' => array(
        '#type' => 'rule',
        '#set' => 'event_user_relationships_remove',
        '#label' => 'Heartbeat: user A and user B are no longer friends',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs default user activity between users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'message_id_param',
                '3' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_users_action',
            '#settings' => array(
              'uid_param' => '[requester:uid]',
              'uid_target_param' => '[requestee:uid]',
              'nid_param' => 0,
              'nid_target_param' => 0,
              'message_id_param' => 'heartbeat_friend_removed',
              'variables_param' => '@userA=|=[requester:user-name-url]-|-@userB=|=[requestee:user-name-url]-|-@relationship_type=|=[relationship:relationship-name]s',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'requester',
                  ),
                  'uid_target_param' => array(
                    '0' => 'requestee',
                  ),
                  'variables_param' => array(
                    '0' => 'requester',
                    '1' => 'requestee',
                    '2' => 'relationship',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_9' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Heartbeat: when user edits a group, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'page is published',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
          '1' => array(
            '#info' => array(
              'label' => 'Content is a group',
              'arguments' => array(
                'group' => array(
                  'type' => 'node',
                  'label' => 'Group',
                ),
              ),
              'module' => 'Organic groups',
            ),
            '#name' => 'og_rules_condition_content_is_group',
            '#settings' => array(
              '#argument map' => array(
                'group' => 'node',
              ),
            ),
            '#type' => 'condition',
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs activity for single users adding a page',
              'label callback' => FALSE,
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:nid]',
              'message_id_param' => 'heartbeat_edit_node',
              'variables_param' => '@username=|=[user:user-name-url]-|-@node_type=|=[node:type-name]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'node',
                    '1' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_10' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Heartbeat: when user edits a page, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'page is published',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
          '1' => array(
            '#negate' => 1,
            '#weight' => 0,
            '#info' => array(
              'label' => 'Content is a group',
              'arguments' => array(
                'group' => array(
                  'type' => 'node',
                  'label' => 'Group',
                ),
              ),
              'module' => 'Organic groups',
            ),
            '#name' => 'og_rules_condition_content_is_group',
            '#settings' => array(
              '#argument map' => array(
                'group' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#info' => array(
              'label' => 'Logs activity for single users adding a page',
              'label callback' => FALSE,
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_edit_node',
              'variables_param' => '@username=|=[user:user-name-url]-|-@node_type=|=[node:type-name]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'node',
                    '1' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_11' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_insert',
        '#label' => 'Heartbeat: when user adds a comment, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Commented content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[comment_author:uid]',
              'uid_target_param' => '[node_author:user]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_add_comment',
              'variables_param' => '@username=|=[comment_author:user-name-url]-|-@title=|=[node:title-link]-|-@comment=|=[comment:comment-title]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'comment_author',
                  ),
                  'uid_target_param' => array(
                    '0' => 'node_author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'comment',
                    '1' => 'comment_author',
                    '2' => 'node',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_12' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_update',
        '#label' => 'Heartbeat: when user edits a comment, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Commented content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '[node_author:user]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_edit_comment',
              'variables_param' => '@username=|=[user:user-name-url]-|-@comment_title=|=[comment:comment-title]-|-@title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'uid_target_param' => array(
                    '0' => 'node_author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'comment',
                    '1' => 'node',
                    '2' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_13' => array(
        '#type' => 'rule',
        '#set' => 'event_user_update',
        '#label' => 'Heartbeat: when user edits a profile, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '',
              'nid_param' => '',
              'nid_target_param' => '',
              'message_id_param' => 'heartbeat_edit_account',
              'variables_param' => '@username=|=[account:user-name-url]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_14' => array(
        '#type' => 'rule',
        '#set' => 'event_og_user_insert',
        '#label' => 'Heartbeat: when user joins a group, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[group:nid]',
              'nid_target_param' => '[group:nid]',
              'message_id_param' => 'heartbeat_join_group',
              'variables_param' => '@username=|=[account:user-name-url]-|-@group_title=|=[group:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'nid_param' => array(
                    '0' => 'group',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                    '1' => 'group',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'nid_target_param' => array(
                    '0' => 'group',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_15' => array(
        '#type' => 'rule',
        '#set' => 'event_og_user_delete',
        '#label' => 'Heartbeat: when user leaves a group, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[group:nid]',
              'nid_target_param' => '[group:nid]',
              'message_id_param' => 'heartbeat_leave_group',
              'variables_param' => '@username=|=[account:user-name-url]-|-@group_name=|=[group:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'nid_param' => array(
                    '0' => 'group',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                    '1' => 'group',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'nid_target_param' => array(
                    '0' => 'group',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_16' => array(
        '#type' => 'rule',
        '#set' => 'event_flag_flagged_bookmarks',
        '#label' => 'Heartbeat: when user flags a page, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_published',
            '#info' => array(
              'label' => 'Flagged content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[flagging_user:uid]',
              'uid_target_param' => '[flagging_user:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '',
              'message_id_param' => 'heartbeat_flag_content',
              'variables_param' => '@username=|=[flagging_user:user-name-url]-|-@type=|=[node:type-name]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'flagging_user',
                  ),
                  'uid_target_param' => array(
                    '0' => 'flagging_user',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'flagging_user',
                    '1' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_17' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_publish',
        '#label' => 'Heartbeat: When a user adds a comment',
        '#active' => 0,
        '#weight' => '0',
        '#categories' => array(
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[comment_author:uid]',
              'uid_target_param' => '[node_author:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '0',
              'message_id_param' => 'heartbeat_add_comment',
              'variables_param' => '@username=|=[comment_author:user-name-url]-|-@title=|=[node:title-link]-|-@comment=|=[comment:comment-body-raw]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'comment_author',
                  ),
                  'uid_target_param' => array(
                    '0' => 'node_author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'comment',
                    '1' => 'comment_author',
                    '2' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}

/**
 * Implementation of hook_views_api().
 */
function commons_core_views_api() {
  return array(
    'api' => '2',
  );
}
