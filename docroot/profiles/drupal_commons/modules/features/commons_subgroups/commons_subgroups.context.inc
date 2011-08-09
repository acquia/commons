<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_subgroups_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-home-tree';
  $context->description = 'The group hierarchy tree';
  $context->tag = 'Group';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'og_subgroups-hierarchy' => array(
          'module' => 'og_subgroups',
          'delta' => 'hierarchy',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('The group hierarchy tree');

  $export['group-home-tree'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'subgroup-listing';
  $context->description = 'The list of available subgroups on the site';
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'subgroups_main_listing:page_2' => 'subgroups_main_listing:page_2',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-create_group' => array(
          'module' => 'commons_core',
          'delta' => 'create_group',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-groups_my_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_my_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-groups_most_active-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_most_active-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-groups_newest_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_newest_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('The list of available subgroups on the site');

  $export['subgroup-listing'] = $context;
  return $export;
}
