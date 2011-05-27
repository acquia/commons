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
  $context->description = 'The community homepage';
  $context->tag = 'Home';
  $context->conditions = array();
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
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Home');
  t('The community homepage');

  $export['home'] = $context;
  return $export;
}
