<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_profile_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-profile-profile-about-me';
  $context->description = 'User profile when viewing your about page';
  $context->tag = 'Profile';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_profile-profile_image_links' => array(
          'module' => 'commons_profile',
          'delta' => 'profile_image_links',
          'region' => 'sidebar_first',
          'weight' => 0,
        ),
        'views-profile_friends-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_friends-block_1',
          'region' => 'sidebar_first',
          'weight' => 1,
        ),
        'commons_profile-profile_find_new_friends' => array(
          'module' => 'commons_profile',
          'delta' => 'profile_find_new_friends',
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

  $export['context_ui-profile-profile-about-me'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-profile-profile-about-other';
  $context->description = 'User profile about page when viewing another user';
  $context->tag = 'Profile';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_profile-profile_image_links' => array(
          'module' => 'commons_profile',
          'delta' => 'profile_image_links',
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
        'views-profile_friends-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_friends-block_1',
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

  $export['context_ui-profile-profile-about-other'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-profile-profile-me';
  $context->description = 'User profile when viewing yourself';
  $context->tag = 'Profile';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_profile-profile_image_links' => array(
          'module' => 'commons_profile',
          'delta' => 'profile_image_links',
          'region' => 'sidebar_first',
          'weight' => 0,
        ),
        'views-profile_friends-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_friends-block_1',
          'region' => 'sidebar_first',
          'weight' => 1,
        ),
        'commons_profile-profile_find_new_friends' => array(
          'module' => 'commons_profile',
          'delta' => 'profile_find_new_friends',
          'region' => 'sidebar_first',
          'weight' => 2,
        ),
        'views-profile_user_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_user_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'commons_profile-profile_recent_activity' => array(
          'module' => 'commons_profile',
          'delta' => 'profile_recent_activity',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Profile');
  t('User profile when viewing yourself');

  $export['context_ui-profile-profile-me'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-profile-profile-other';
  $context->description = 'User profile when viewing another user';
  $context->tag = 'Profile';
  $context->conditions = array();
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_profile-profile_image_links' => array(
          'module' => 'commons_profile',
          'delta' => 'profile_image_links',
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
        'views-profile_friends-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_friends-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'commons_profile-profile_recent_activity' => array(
          'module' => 'commons_profile',
          'delta' => 'profile_recent_activity',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Profile');
  t('User profile when viewing another user');

  $export['context_ui-profile-profile-other'] = $context;
  return $export;
}
