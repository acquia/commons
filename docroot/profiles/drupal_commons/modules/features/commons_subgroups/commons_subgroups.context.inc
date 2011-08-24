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
  return $export;
}
