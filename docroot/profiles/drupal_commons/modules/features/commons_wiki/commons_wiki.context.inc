<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_wiki_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content-wiki-page';
  $context->description = 'The wiki page';
  $context->tag = 'Wiki';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'content_wiki_page:page_1' => 'content_wiki_page:page_1',
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
        'views-wiki_latest_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'wiki_latest_comments-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('The wiki page');
  t('Wiki');

  $export['content-wiki-page'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-tab-wikis';
  $context->description = 'The wiki tab on a group';
  $context->tag = 'Wiki';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_tab_wikis:page_1' => 'group_tab_wikis:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-157e77ff7551b8ace96fdd6c04d716cf' => array(
          'module' => 'views',
          'delta' => '157e77ff7551b8ace96fdd6c04d716cf',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('The wiki tab on a group');
  t('Wiki');

  $export['group-tab-wikis'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-wiki-node';
  $context->description = 'A wiki node inside a group';
  $context->tag = 'Wiki';
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
        'wiki' => 'wiki',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-group_block_wiki_latest-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_wiki_latest-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-157e77ff7551b8ace96fdd6c04d716cf' => array(
          'module' => 'views',
          'delta' => '157e77ff7551b8ace96fdd6c04d716cf',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('A wiki node inside a group');
  t('Wiki');

  $export['group-wiki-node'] = $context;
  return $export;
}
