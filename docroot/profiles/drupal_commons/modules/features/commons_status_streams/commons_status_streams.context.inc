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
        'views-stream_recent_content-block_2' => array(
          'module' => 'views',
          'delta' => 'stream_recent_content-block_2',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-profile_user_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'profile_user_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'userpoints-0' => array(
          'module' => 'userpoints',
          'delta' => 0,
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
  return $export;
}
