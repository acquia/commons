<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_shoutbox_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-home-shoutbox';
  $context->description = 'Shoutbox block for the group home page';
  $context->tag = 'Shoutbox';
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
        'shoutbox-0' => array(
          'module' => 'shoutbox',
          'delta' => 0,
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Shoutbox');
  t('Shoutbox block for the group home page');

  $export['group-home-shoutbox'] = $context;
  return $export;
}
