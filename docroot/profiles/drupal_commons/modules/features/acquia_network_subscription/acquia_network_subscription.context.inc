<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function acquia_network_subscription_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-search';
  $context->description = 'Apache solr blocks';
  $context->tag = 'Search';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'search*' => 'search*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'apachesolr-sort' => array(
          'module' => 'apachesolr',
          'delta' => 'sort',
          'region' => 'sidebar_first',
          'weight' => 0,
        ),
        'apachesolr_search-im_vid_2' => array(
          'module' => 'apachesolr_search',
          'delta' => 'im_vid_2',
          'region' => 'sidebar_first',
          'weight' => 1,
        ),
        'apachesolr_search-created' => array(
          'module' => 'apachesolr_search',
          'delta' => 'created',
          'region' => 'sidebar_first',
          'weight' => 2,
        ),
        'apachesolr_search-changed' => array(
          'module' => 'apachesolr_search',
          'delta' => 'changed',
          'region' => 'sidebar_first',
          'weight' => 3,
        ),
        'apachesolr_og-im_og_gid' => array(
          'module' => 'apachesolr_og',
          'delta' => 'im_og_gid',
          'region' => 'sidebar_first',
          'weight' => 4,
        ),
        'apachesolr_search-type' => array(
          'module' => 'apachesolr_search',
          'delta' => 'type',
          'region' => 'sidebar_first',
          'weight' => 5,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Apache solr blocks');
  t('Search');

  $export['context_ui-search'] = $context;
  return $export;
}
