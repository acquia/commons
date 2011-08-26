<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_poll_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content-poll-page';
  $context->description = 'The poll page';
  $context->tag = 'Poll';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'content_poll_page:page_1' => 'content_poll_page:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-group_create_content' => array(
          'module' => 'commons_core',
          'delta' => 'group_create_content',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-poll_latest_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'poll_latest_comments-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Poll');
  t('The poll page');

  $export['content-poll-page'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-home-poll';
  $context->description = 'Poll block for the group home page';
  $context->tag = 'Poll';
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
          'weight' => 6,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Poll');
  t('Poll block for the group home page');

  $export['group-home-poll'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-poll-node';
  $context->description = 'A poll node inside a group';
  $context->tag = 'Poll';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => 0,
      ),
    ),
    'node' => array(
      'values' => array(
        'poll' => 'poll',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-ff980fe8675569132670cd0a2b5be358' => array(
          'module' => 'views',
          'delta' => 'ff980fe8675569132670cd0a2b5be358',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-527d55149807f4938ae8e394bc5a1aba' => array(
          'module' => 'views',
          'delta' => '527d55149807f4938ae8e394bc5a1aba',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('A poll node inside a group');
  t('Poll');

  $export['group-poll-node'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-tab-polls';
  $context->description = 'The poll tab on a group';
  $context->tag = 'Poll';
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
        'views-527d55149807f4938ae8e394bc5a1aba' => array(
          'module' => 'views',
          'delta' => '527d55149807f4938ae8e394bc5a1aba',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Poll');
  t('The poll tab on a group');

  $export['group-tab-polls'] = $context;
  return $export;
}
