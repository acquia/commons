<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_event_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-event-node';
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

  $export['group-event-node'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-home-events';
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
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-deb9ea35a724682175e6d2c990e7009c' => array(
          'module' => 'views',
          'delta' => 'deb9ea35a724682175e6d2c990e7009c',
          'region' => 'sidebar_last',
          'weight' => 4,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Event');
  t('Events block for the group home page');

  $export['group-home-events'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-tab-events';
  $context->description = 'The event tab on a group';
  $context->tag = 'Document';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_tab_event_calendar' => 'group_tab_event_calendar',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-a1d17833246cc27c991e939ae8e26a96' => array(
          'module' => 'views',
          'delta' => 'a1d17833246cc27c991e939ae8e26a96',
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
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Document');
  t('The event tab on a group');

  $export['group-tab-events'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'profile-me-events';
  $context->description = 'Add events listings to user profiles when viewing your own profile';
  $context->tag = 'Event';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        'profile-me' => 'profile-me',
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
  t('Event');

  $export['profile-me-events'] = $context;
  return $export;
}
