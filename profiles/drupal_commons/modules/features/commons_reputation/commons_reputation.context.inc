<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_reputation_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'activity-stream-most_active_users';
  $context->description = 'Adds the "Most active users" block to the activity stream page';
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
        'views-most_active_users-block_1' => array(
          'module' => 'views',
          'delta' => 'most_active_users-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Activity');
  t('Adds the "Most active users" block to the activity stream page');

  $export['activity-stream-most_active_users'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'user-browser-most_active_users';
  $context->description = 'Display the most active users in the community';
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
        'views-most_active_users-block_1' => array(
          'module' => 'views',
          'delta' => 'most_active_users-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display the most active users in the community');
  t('User browser');

  $export['user-browser-most_active_users'] = $context;
  return $export;
}
