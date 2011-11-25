<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_event_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content-event-calendar';
  $context->description = 'The event calendar';
  $context->tag = 'Event';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'content_event_calendar' => 'content_event_calendar',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-group_create_content' => array(
          'module' => 'commons_core',
          'delta' => 'group_create_content',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-event_latest-block_1' => array(
          'module' => 'views',
          'delta' => 'event_latest-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-event_past_events-block_1' => array(
          'module' => 'views',
          'delta' => 'event_past_events-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-event_latest_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'event_latest_comments-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Event');
  t('The event calendar');
  $export['content-event-calendar'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content-event-page';
  $context->description = 'The event page';
  $context->tag = 'Event';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'content_event_page:page_1' => 'content_event_page:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-group_create_content' => array(
          'module' => 'commons_core',
          'delta' => 'group_create_content',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-228f369cb15ea72f0c4ceed52aaf99c7' => array(
          'module' => 'views',
          'delta' => '228f369cb15ea72f0c4ceed52aaf99c7',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-event_latest-block_1' => array(
          'module' => 'views',
          'delta' => 'event_latest-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-event_past_events-block_1' => array(
          'module' => 'views',
          'delta' => 'event_past_events-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
        'views-event_latest_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'event_latest_comments-block_1',
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
  t('The event page');
  $export['content-event-page'] = $context;

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
        'views-group_block_events_past-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_events_past-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
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
          'weight' => 5,
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
  $context->tag = 'Event';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_tab_events:page_1' => 'group_tab_events:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-0cde383a1963a6ecc04a0e9e98fa4213' => array(
          'module' => 'views',
          'delta' => '0cde383a1963a6ecc04a0e9e98fa4213',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-a1d17833246cc27c991e939ae8e26a96' => array(
          'module' => 'views',
          'delta' => 'a1d17833246cc27c991e939ae8e26a96',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-group_block_events_past-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_events_past-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-5f71f8bfdda731f7f0c854e134dab79b' => array(
          'module' => 'views',
          'delta' => '5f71f8bfdda731f7f0c854e134dab79b',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Event');
  t('The event tab on a group');
  $export['group-tab-events'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-tab-events-calendar';
  $context->description = 'The event calendar for a group';
  $context->tag = 'Event';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_event_calendar' => 'group_event_calendar',
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
        'views-group_block_events_past-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_events_past-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-5f71f8bfdda731f7f0c854e134dab79b' => array(
          'module' => 'views',
          'delta' => '5f71f8bfdda731f7f0c854e134dab79b',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Event');
  t('The event calendar for a group');
  $export['group-tab-events-calendar'] = $context;

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
          'weight' => 5,
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
