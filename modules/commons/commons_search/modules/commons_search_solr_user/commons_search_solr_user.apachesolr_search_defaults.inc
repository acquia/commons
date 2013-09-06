<?php
/**
 * @file
 * commons_search_solr_user.apachesolr_search_defaults.inc
 */

/**
 * Implements hook_apachesolr_search_default_searchers().
 */
function commons_search_solr_user_apachesolr_search_default_searchers() {
  $export = array();

  $searcher = new stdClass();
  $searcher->disabled = FALSE; /* Edit this to true to make a default searcher disabled initially */
  $searcher->api_version = 3;
  $searcher->page_id = 'user_search';
  $searcher->label = 'User Search';
  $searcher->description = 'User Search';
  $searcher->search_path = 'people';
  $searcher->page_title = 'People';
  $searcher->env_id = apachesolr_default_environment();
  $searcher->settings = array(
    'fq' => array(
      0 => 'entity_type:user',
    ),
    'apachesolr_search_custom_enable' => 1,
    'apachesolr_search_search_type' => 'custom',
    'apachesolr_search_per_page' => 12,
    'apachesolr_search_browse' => 'none',
    'apachesolr_search_spellcheck' => 1,
    'apachesolr_search_search_box' => 1,
    'apachesolr_search_allow_user_input' => 0,
  );
  $export['user_search'] = $searcher;

  return $export;
}
