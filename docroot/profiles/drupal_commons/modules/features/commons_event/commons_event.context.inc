<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_event_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-home-events';
  $context->description = 'Events block for the group home page';
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
        'views-group_block_events_upcoming-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_events_upcoming-block_1',
          'region' => 'sidebar_last',
          'weight' => 4,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Events block for the group home page');
  t('Group');

  $export['context_ui-group-group-home-events'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-profile-profile-me-events';
  $context->description = 'Add events listings to user profiles when viewing your own profile';
  $context->tag = 'Profile';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        'context_ui-profile-profile-me' => 'context_ui-profile-profile-me',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-upcoming_events-block_2' => array(
          'module' => 'views',
          'delta' => 'upcoming_events-block_2',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Add events listings to user profiles when viewing your own profile');
  t('Profile');

  $export['context_ui-profile-profile-me-events'] = $context;
  return $export;
}
