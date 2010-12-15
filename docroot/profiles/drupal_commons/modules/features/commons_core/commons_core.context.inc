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
  $context->name = 'context_ui-global-global';
  $context->description = 'Show on every page';
  $context->tag = '';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-user_meta-block_1' => array(
          'module' => 'views',
          'delta' => 'user_meta-block_1',
          'region' => 'header',
          'weight' => 0,
        ),
        'user-0' => array(
          'module' => 'user',
          'delta' => 0,
          'region' => 'header',
          'weight' => 1,
        ),
        'commons_core-2' => array(
          'module' => 'commons_core',
          'delta' => 2,
          'region' => 'footer',
          'weight' => 0,
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
    'user_page' => array(
      'values' => array(
        'view' => 'view',
      ),
      'options' => array(
        'mode' => 'all',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'user_relationship_blocks-actions' => array(
          'module' => 'user_relationship_blocks',
          'delta' => 'actions',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-og_profile_user_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'og_profile_user_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'user_relationship_blocks-user-1' => array(
          'module' => 'user_relationship_blocks',
          'delta' => 'user-1',
          'region' => 'sidebar_last',
          'weight' => 2,
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
        'user_directory' => 'user_directory',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-0' => array(
          'module' => 'commons_core',
          'delta' => 0,
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-users_online-block_1' => array(
          'module' => 'views',
          'delta' => 'users_online-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-most_active_users-block_1' => array(
          'module' => 'views',
          'delta' => 'most_active_users-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-newest_users-block_1' => array(
          'module' => 'views',
          'delta' => 'newest_users-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
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
