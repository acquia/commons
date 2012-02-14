<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_discussion_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content-discussion-page';
  $context->description = 'The discussion page';
  $context->tag = 'Discussion';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'content_discussion_page:page_1' => 'content_discussion_page:page_1',
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
          'weight' => 1,
        ),
        'views-f24f764575fea8b17a65697fa4ac9a8d' => array(
          'module' => 'views',
          'delta' => 'f24f764575fea8b17a65697fa4ac9a8d',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Discussion');
  t('The discussion page');

  $export['content-discussion-page'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-discussion-node';
  $context->description = 'A discussion node inside a group';
  $context->tag = 'Discussion';
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
        'discussion' => 'discussion',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-7c1e1568b7392470cbb8406f05742e0e' => array(
          'module' => 'views',
          'delta' => '7c1e1568b7392470cbb8406f05742e0e',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-1048f0a19e6b5b9b52580ed82aae1972' => array(
          'module' => 'views',
          'delta' => '1048f0a19e6b5b9b52580ed82aae1972',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('A discussion node inside a group');
  t('Discussion');

  $export['group-discussion-node'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-tab-discussions';
  $context->description = 'The discussion tab on a group';
  $context->tag = 'Discussion';
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
  t('Discussion');
  t('The discussion tab on a group');

  $export['group-tab-discussions'] = $context;
  return $export;
}
