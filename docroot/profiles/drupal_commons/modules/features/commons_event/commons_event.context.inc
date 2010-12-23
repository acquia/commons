<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_event_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-event';
  $context->description = 'Upcoming group events';
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
        'views-og_upcoming_events-block_1' => array(
          'module' => 'views',
          'delta' => 'og_upcoming_events-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('Upcoming group events');

  $export['context_ui-group-event'] = $context;
  return $export;
}
