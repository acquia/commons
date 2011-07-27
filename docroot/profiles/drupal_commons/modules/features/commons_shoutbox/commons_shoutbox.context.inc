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
        'node_form' => '0',
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
          'weight' => 4,
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
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'shoutbox-group';
  $context->description = 'The shoutbox group page';
  $context->tag = 'Shoutbox';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'node/*/shoutbox' => 'node/*/shoutbox',
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
  t('Shoutbox');
  t('The shoutbox group page');

  $export['shoutbox-group'] = $context;
  return $export;
}
