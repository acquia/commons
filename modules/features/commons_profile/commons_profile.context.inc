<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_profile_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile-about-me';
  $context->description = 'User profile when viewing your about page';
  $context->tag = 'Profile';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_profile-image_links' => array(
          'module' => 'commons_profile',
          'delta' => 'image_links',
          'region' => 'sidebar_first',
          'weight' => 0,
        ),
        'views-profile_following-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_following-block_1',
          'region' => 'sidebar_first',
          'weight' => 1,
        ),
        'commons_profile-find_new_friends' => array(
          'module' => 'commons_profile',
          'delta' => 'find_new_friends',
          'region' => 'sidebar_first',
          'weight' => 2,
        ),
        'views-profile_user_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_user_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Profile');
  t('User profile when viewing your about page');
  $export['profile-about-me'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile-about-other';
  $context->description = 'User profile about page when viewing another user';
  $context->tag = 'Profile';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_profile-image_links' => array(
          'module' => 'commons_profile',
          'delta' => 'image_links',
          'region' => 'sidebar_first',
          'weight' => 0,
        ),
        'views-profile_about-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_about-block_1',
          'region' => 'sidebar_first',
          'weight' => 1,
        ),
        'views-profile_user_groups-block_2' => array(
          'module' => 'views',
          'delta' => 'profile_user_groups-block_2',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-profile_following-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_following-block_1',
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
  t('User profile about page when viewing another user');
  $export['profile-about-other'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile-me';
  $context->description = 'User profile when viewing yourself';
  $context->tag = 'Profile';
  $context->conditions = array(
    'user_page' => array(
      'values' => array(
        'view' => 'view',
      ),
      'options' => array(
        'mode' => 'current',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_profile-image_links' => array(
          'module' => 'commons_profile',
          'delta' => 'image_links',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-profile_user_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_user_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-profile_following-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_following-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Profile');
  t('User profile when viewing yourself');
  $export['profile-me'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile-other';
  $context->description = 'User profile when viewing another user';
  $context->tag = 'Profile';
  $context->conditions = array(
    'user_page' => array(
      'values' => array(
        'view' => 'view',
      ),
      'options' => array(
        'mode' => 'other',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_profile-image_links' => array(
          'module' => 'commons_profile',
          'delta' => 'image_links',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-profile_about-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_about-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-profile_user_groups-block_2' => array(
          'module' => 'views',
          'delta' => 'profile_user_groups-block_2',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-profile_following-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_following-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Profile');
  t('User profile when viewing another user');
  $export['profile-other'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile-track';
  $context->description = 'The user profile track page';
  $context->tag = 'Profile';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'user/*/track' => 'user/*/track',
      ),
    ),
    'user' => array(
      'values' => array(
        'authenticated user' => 'authenticated user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_profile-image_links' => array(
          'module' => 'commons_profile',
          'delta' => 'image_links',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-profile_following-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_following-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Profile');
  t('The user profile track page');
  $export['profile-track'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'user-browser';
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
  $export['user-browser'] = $context;

  return $export;
}
