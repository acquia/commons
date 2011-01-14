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

  $export['context_ui-content-global_content'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-global-global';
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
        'commons_core-3' => array(
          'module' => 'commons_core',
          'delta' => '3',
          'region' => 'header',
          'weight' => 1,
        ),
        'commons_core-2' => array(
          'module' => 'commons_core',
          'delta' => '2',
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

  $export['context_ui-global-global'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group';
  $context->description = 'Various group blocks';
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
        'commons_core-5' => array(
          'module' => 'commons_core',
          'delta' => 5,
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'og_views-0' => array(
          'module' => 'og_views',
          'delta' => 0,
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-og_members_custom_block-block_1' => array(
          'module' => 'views',
          'delta' => 'og_members_custom_block-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-og_tag_cloud-block_1' => array(
          'module' => 'views',
          'delta' => 'og_tag_cloud-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('Various group blocks');

  $export['context_ui-group-group'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-profile-profile';
  $context->description = 'User profile';
  $context->tag = 'Profile';
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
        'views-og_profile_user_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'og_profile_user_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'user_relationship_blocks-user-1' => array(
          'module' => 'user_relationship_blocks',
          'delta' => 'user-1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Profile');
  t('User profile');

  $export['context_ui-profile-profile'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-users-user_browser';
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
        'commons_core-0' => array(
          'module' => 'commons_core',
          'delta' => '0',
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

  $export['context_ui-users-user_browser'] = $context;
  return $export;
}
