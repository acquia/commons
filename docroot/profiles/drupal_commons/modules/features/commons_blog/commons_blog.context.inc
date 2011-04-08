<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_blog_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-home-blogs';
  $context->description = 'Blog posts block for the group home page';
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
        'views-group_block_blog_latest-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_blog_latest-block_1',
          'region' => 'sidebar_last',
          'weight' => 5,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blog posts block for the group home page');
  t('Group');

  $export['context_ui-group-group-home-blogs'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-tab-blogs';
  $context->description = 'The blog tab on a group';
  $context->tag = 'Group';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_tab_blogs:page_1' => 'group_tab_blogs:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-group_block_blog_latest_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_blog_latest_comments-block_1',
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
  t('The blog tab on a group');

  $export['context_ui-group-group-tab-blogs'] = $context;
  return $export;
}
