<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_discussion_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-home-discussions';
  $context->description = 'Discussion block for the group home page';
  $context->tag = 'Group';
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
        'views-group_block_discussion_latest-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_discussion_latest-block_1',
          'region' => 'sidebar_last',
          'weight' => 7,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Discussion block for the group home page');
  t('Group');

  $export['context_ui-group-group-home-discussions'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-tab-discussions';
  $context->description = 'The discussion tab on a group';
  $context->tag = 'Group';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_tab_discussions:page_1' => 'group_tab_discussions:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-1048f0a19e6b5b9b52580ed82aae1972' => array(
          'module' => 'views',
          'delta' => '1048f0a19e6b5b9b52580ed82aae1972',
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
  t('The discussion tab on a group');

  $export['context_ui-group-group-tab-discussions'] = $context;
  return $export;
}
