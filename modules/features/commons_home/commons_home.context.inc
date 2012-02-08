<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_home_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'home';
  $context->description = 'The community homepage for authenticated users';
  $context->tag = 'Home';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
        'home' => 'home',
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
        'commons_core-join_learn' => array(
          'module' => 'commons_core',
          'delta' => 'join_learn',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-recent_notices-block_1' => array(
          'module' => 'views',
          'delta' => 'recent_notices-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'commons_core-your_content' => array(
          'module' => 'commons_core',
          'delta' => 'your_content',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-activity_log_stream-block_1' => array(
          'module' => 'views',
          'delta' => 'activity_log_stream-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
        'views-a3e7b5edbe74088872090245cc4288ec' => array(
          'module' => 'views',
          'delta' => 'a3e7b5edbe74088872090245cc4288ec',
          'region' => 'sidebar_last',
          'weight' => 4,
        ),
        'views-new_your_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'new_your_groups-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Home');
  t('The community homepage for authenticated users');
  $export['home'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'home_anon';
  $context->description = 'The community homepage for anonymous users';
  $context->tag = 'Home';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
        'home' => 'home',
      ),
    ),
    'user' => array(
      'values' => array(
        'anonymous user' => 'anonymous user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-join_learn' => array(
          'module' => 'commons_core',
          'delta' => 'join_learn',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-a3e7b5edbe74088872090245cc4288ec' => array(
          'module' => 'views',
          'delta' => 'a3e7b5edbe74088872090245cc4288ec',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-groups_most_active-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_most_active-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-recent_notices-block_1' => array(
          'module' => 'views',
          'delta' => 'recent_notices-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
        'views-tag_cloud-block_1' => array(
          'module' => 'views',
          'delta' => 'tag_cloud-block_1',
          'region' => 'sidebar_last',
          'weight' => 4,
        ),
        'boxes-homepage_info_box' => array(
          'module' => 'boxes',
          'delta' => 'homepage_info_box',
          'region' => 'content_top',
          'weight' => 0,
        ),
        'views-homepage_group_showcase-block_1' => array(
          'module' => 'views',
          'delta' => 'homepage_group_showcase-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Home');
  t('The community homepage for anonymous users');
  $export['home_anon'] = $context;

  return $export;
}
