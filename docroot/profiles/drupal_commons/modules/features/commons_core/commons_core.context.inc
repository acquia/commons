<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_core_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-content-global_content';
  $context->description = 'Site-wide content pages';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'content/*' => 'content/*',
        'featured' => 'featured',
        'notices' => 'notices',
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-tag_cloud-block_1' => array(
          'module' => 'views',
          'delta' => 'tag_cloud-block_1',
          'weight' => 43,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Popular Tags',
          'type' => 'context_ui',
        ),
        'views-most_active_users-block_1' => array(
          'module' => 'views',
          'delta' => 'most_active_users-block_1',
          'weight' => 44,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Most Active Users',
          'type' => 'context_ui',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Site-wide content pages');

  $export['context_ui-content-global_content'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-dashboard-dashboard';
  $context->description = 'User Dashboard';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'dashboard' => 'dashboard',
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-og_dashboard_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'og_dashboard_groups-block_1',
          'weight' => 44,
          'region' => 'sidebar_first',
          'status' => '0',
          'label' => 'My Groups (custom)',
          'type' => 'context_ui',
        ),
        'views-my_recent_items-block_1' => array(
          'module' => 'views',
          'delta' => 'my_recent_items-block_1',
          'weight' => 45,
          'region' => 'sidebar_first',
          'status' => '0',
          'label' => 'My Recent Items',
          'type' => 'context_ui',
        ),
        'views-my_unread_items-block_1' => array(
          'module' => 'views',
          'delta' => 'my_unread_items-block_1',
          'weight' => 46,
          'region' => 'sidebar_first',
          'status' => '0',
          'label' => 'My Unread Items',
          'type' => 'context_ui',
        ),
        'user_relationship_blocks-my-1' => array(
          'module' => 'user_relationship_blocks',
          'delta' => 'my-1',
          'weight' => 47,
          'region' => 'sidebar_first',
          'status' => '0',
          'label' => 'My Relationships: Friends ',
          'type' => 'context_ui',
        ),
        'views-recent_notices-block_1' => array(
          'module' => 'views',
          'delta' => 'recent_notices-block_1',
          'weight' => 44,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Recent Notices',
          'type' => 'context_ui',
        ),
        'views-upcoming_events-block_2' => array(
          'module' => 'views',
          'delta' => 'upcoming_events-block_2',
          'weight' => 45,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Upcoming Events (My Groups)',
          'type' => 'context_ui',
        ),
        'views-og_featured-block_1' => array(
          'module' => 'views',
          'delta' => 'og_featured-block_1',
          'weight' => 46,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Featured groups',
          'type' => 'context_ui',
        ),
        'views-most_active_users-block_1' => array(
          'module' => 'views',
          'delta' => 'most_active_users-block_1',
          'weight' => 47,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Most Active Users',
          'type' => 'context_ui',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('User Dashboard');

  $export['context_ui-dashboard-dashboard'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-global-global';
  $context->description = 'Show on every page';
  $context->tag = '';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        0 => '1',
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-user_meta-block_1' => array(
          'module' => 'views',
          'delta' => 'user_meta-block_1',
          'weight' => 37,
          'region' => 'header',
          'status' => '0',
          'label' => 'User meta info',
          'type' => 'context_ui',
        ),
        'user-0' => array(
          'module' => 'user',
          'delta' => '0',
          'weight' => 38,
          'region' => 'header',
          'status' => '0',
          'label' => 'User login',
          'type' => 'context_ui',
        ),
        'commons-2' => array(
          'module' => 'commons',
          'delta' => '2',
          'weight' => 37,
          'region' => 'footer',
          'status' => '0',
          'label' => 'Drupal Commons information',
          'type' => 'context_ui',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Show on every page');

  $export['context_ui-global-global'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group';
  $context->description = 'Show on group context';
  $context->tag = '';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'og-0' => array(
          'module' => 'og',
          'delta' => 0,
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'og_views-0' => array(
          'module' => 'og_views',
          'delta' => 0,
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-og_upcoming_events-block_1' => array(
          'module' => 'views',
          'delta' => 'og_upcoming_events-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-og_members_custom_block-block_1' => array(
          'module' => 'views',
          'delta' => 'og_members_custom_block-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
        'og_aggregator-0' => array(
          'module' => 'og_aggregator',
          'delta' => 0,
          'region' => 'sidebar_last',
          'weight' => 4,
        ),
        'views-og_recent_poll-block_1' => array(
          'module' => 'views',
          'delta' => 'og_recent_poll-block_1',
          'region' => 'sidebar_last',
          'weight' => 5,
        ),
        'views-og_tag_cloud-block_1' => array(
          'module' => 'views',
          'delta' => 'og_tag_cloud-block_1',
          'region' => 'sidebar_last',
          'weight' => 6,
        ),
        'views-og_members_custom_block-block' => array(
          'module' => 'views',
          'delta' => 'og_members_custom_block-block',
          'region' => 'sidebar_last',
          'weight' => 7,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Show on group context');

  $export['context_ui-group-group'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-profile-profile';
  $context->description = 'User Profile';
  $context->tag = '';
  $context->conditions = array(
    'user' => array(
      'values' => array(
        0 => 2,
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'user_relationship_blocks-actions' => array(
          'module' => 'user_relationship_blocks',
          'delta' => 'actions',
          'weight' => -43,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'User Relationships: Actions',
          'type' => 'context_ui',
        ),
        'views-og_profile_user_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'og_profile_user_groups-block_1',
          'weight' => -42,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'User Being Viewed\'s Groups',
          'type' => 'context_ui',
        ),
        'user_relationship_blocks-user-1' => array(
          'module' => 'user_relationship_blocks',
          'delta' => 'user-1',
          'weight' => -41,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'User Relationships: Friends ',
          'type' => 'context_ui',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('User Profile');

  $export['context_ui-profile-profile'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-users-user_browser';
  $context->description = 'User Browser';
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        0 => 'user_directory',
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons-0' => array(
          'module' => 'commons',
          'delta' => '0',
          'weight' => 45,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'User Statistics',
          'type' => 'context_ui',
        ),
        'views-users_online-block_1' => array(
          'module' => 'views',
          'delta' => 'users_online-block_1',
          'weight' => 46,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Who\'s Online? (Custom)',
          'type' => 'context_ui',
        ),
        'views-most_active_users-block_1' => array(
          'module' => 'views',
          'delta' => 'most_active_users-block_1',
          'weight' => 47,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Most Active Users',
          'type' => 'context_ui',
        ),
        'views-newest_users-block_1' => array(
          'module' => 'views',
          'delta' => 'newest_users-block_1',
          'weight' => 48,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Newest Users',
          'type' => 'context_ui',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('User Browser');

  $export['context_ui-users-user_browser'] = $context;
  return $export;
}
