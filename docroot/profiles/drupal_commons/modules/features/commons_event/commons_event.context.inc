<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_event_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-event-node';
  $context->description = 'An event node inside a group';
  $context->tag = 'Event';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => 0,
      ),
    ),
    'node' => array(
      'values' => array(
        'event' => 'event',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-deb9ea35a724682175e6d2c990e7009c' => array(
          'module' => 'views',
          'delta' => 'deb9ea35a724682175e6d2c990e7009c',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-5f71f8bfdda731f7f0c854e134dab79b' => array(
          'module' => 'views',
          'delta' => '5f71f8bfdda731f7f0c854e134dab79b',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('An event node inside a group');
  t('Event');

  $export['context_ui-group-group-event-node'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-home-events';
  $context->description = 'Events block for the group home page';
  $context->tag = 'Event';
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
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Event');
  t('Events block for the group home page');

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
