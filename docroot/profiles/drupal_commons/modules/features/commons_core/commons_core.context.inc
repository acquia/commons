<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_core_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content-global_content';
  $context->description = 'Various blocks to show on the global content views';
  $context->tag = 'Global content';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'content/*' => 'content/*',
        'featured' => 'featured',
        'notices' => 'notices',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-tag_cloud-block_1' => array(
          'module' => 'views',
          'delta' => 'tag_cloud-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Global content');
  t('Various blocks to show on the global content views');

  $export['content-global_content'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'global-global';
  $context->description = 'Show on every page';
  $context->tag = 'Sitewide';
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
        'commons_core-header_login' => array(
          'module' => 'commons_core',
          'delta' => 'header_login',
          'region' => 'header',
          'weight' => 1,
        ),
        'commons_core-commons_info' => array(
          'module' => 'commons_core',
          'delta' => 'commons_info',
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
  t('Sitewide');

  $export['global-global'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-context';
  $context->description = 'The context of a group';
  $context->tag = 'Group';
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
        'commons_core-group_create_content' => array(
          'module' => 'commons_core',
          'delta' => 'group_create_content',
          'region' => 'preface_top',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('The context of a group');

  $export['group-context'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-home';
  $context->description = 'The group home page';
  $context->tag = 'Group';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-group_menu' => array(
          'module' => 'commons_core',
          'delta' => 'group_menu',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'og_views-0' => array(
          'module' => 'og_views',
          'delta' => 0,
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'shoutbox-0' => array(
          'module' => 'shoutbox',
          'delta' => 0,
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'commons_core-group_activity' => array(
          'module' => 'commons_core',
          'delta' => 'group_activity',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('The group home page');

  $export['group-home'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'users-user_browser';
  $context->description = 'Various block to show on the user browser page';
  $context->tag = 'User browser';
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
        'commons_core-user_statistics' => array(
          'module' => 'commons_core',
          'delta' => 'user_statistics',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-users_online-block_1' => array(
          'module' => 'views',
          'delta' => 'users_online-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
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
  t('User browser');
  t('Various block to show on the user browser page');

  $export['users-user_browser'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-listing';
  $context->description = 'The list of available groups on the site';
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'groups_main_listing' => 'groups_main_listing',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-groups_my_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_my_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-groups_most_active-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_most_active-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-groups_newest_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_newest_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-groups_featured_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_featured_groups-block_1',
          'region' => 'content_top',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('The list of available groups on the site');

  $export['group-listing'] = $context;
  return $export;
}
