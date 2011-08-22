<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_blog_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content-blog-page';
  $context->description = 'The blog page';
  $context->tag = 'Blog';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'content_blog_page:page_1' => 'content_blog_page:page_1',
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
        'views-blog_latest_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'blog_latest_comments-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blog');
  t('The blog page');

  $export['content-blog-page'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-blog-node';
  $context->description = 'A blog node inside a group';
  $context->tag = 'Blog';
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
        'blog' => 'blog',
      ),
      'options' => array(
        'node_form' => '0',
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
          'weight' => 0,
        ),
        'views-f8cb0875780fe573595fe3b2bb97ff69' => array(
          'module' => 'views',
          'delta' => 'f8cb0875780fe573595fe3b2bb97ff69',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('A blog node inside a group');
  t('Blog');

  $export['group-blog-node'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-tab-blogs';
  $context->description = 'The blog tab on a group';
  $context->tag = 'Blog';
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
        'views-f8cb0875780fe573595fe3b2bb97ff69' => array(
          'module' => 'views',
          'delta' => 'f8cb0875780fe573595fe3b2bb97ff69',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blog');
  t('The blog tab on a group');

  $export['group-tab-blogs'] = $context;
  return $export;
}
