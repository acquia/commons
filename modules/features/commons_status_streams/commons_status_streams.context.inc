<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_status_streams_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'activity';
  $context->description = 'An activity dashboard';
  $context->tag = 'Activity';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'stream' => 'stream',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-recent_notices-block_1' => array(
          'module' => 'views',
          'delta' => 'recent_notices-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-stream_recent_content-block_2' => array(
          'module' => 'views',
          'delta' => 'stream_recent_content-block_2',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-profile_user_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_user_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Activity');
  t('An activity dashboard');
  $export['activity'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-home-status-box';
  $context->description = 'Adds the status update box to the group home page';
  $context->tag = 'Group';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'node/*/group-activity' => 'node/*/group-activity',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Adds the status update box to the group home page');
  t('Group');
  $export['group-home-status-box'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile-me-status-box';
  $context->description = 'Adds the status update box to the user profile page';
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
        'facebook_status-facebook_status' => array(
          'module' => 'facebook_status',
          'delta' => 'facebook_status',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Adds the status update box to the user profile page');
  t('Profile');
  $export['profile-me-status-box'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile-other-status-box';
  $context->description = 'Adds the status update box to the user profile page';
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
        'facebook_status-facebook_status' => array(
          'module' => 'facebook_status',
          'delta' => 'facebook_status',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Adds the status update box to the user profile page');
  t('Profile');
  $export['profile-other-status-box'] = $context;

  return $export;
}
