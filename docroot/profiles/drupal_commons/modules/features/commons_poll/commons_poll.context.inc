<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_poll_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-poll';
  $context->description = 'The latest group poll';
  $context->tag = 'Group';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-og_recent_poll-block_1' => array(
          'module' => 'views',
          'delta' => 'og_recent_poll-block_1',
          'region' => 'sidebar_last',
          'weight' => 5,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('The latest group poll');

  $export['context_ui-group-poll'] = $context;
  return $export;
}
