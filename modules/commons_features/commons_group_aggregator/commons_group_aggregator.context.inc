<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_group_aggregator_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'aggregator-group';
  $context->description = 'The group aggregator pages';
  $context->tag = 'Aggregator';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'node/*/aggregator*' => 'node/*/aggregator*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-group_menu' => array(
          'module' => 'commons_core',
          'delta' => 'group_menu',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'commons_core-group_members' => array(
          'module' => 'commons_core',
          'delta' => 'group_members',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Aggregator');
  t('The group aggregator pages');

  $export['aggregator-group'] = $context;
  return $export;
}
