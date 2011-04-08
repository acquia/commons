<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_poll_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-home-poll';
  $context->description = 'Poll block for the group home page';
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
        'views-group_block_poll_latest-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_poll_latest-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('Poll block for the group home page');

  $export['context_ui-group-group-home-poll'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-tab-polls';
  $context->description = 'The poll tab on a group';
  $context->tag = 'Group';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_tab_polls:page_1' => 'group_tab_polls:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-group_block_poll_latest_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_poll_latest_comments-block_1',
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
  t('The poll tab on a group');

  $export['context_ui-group-group-tab-polls'] = $context;
  return $export;
}
