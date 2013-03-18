<?php
/**
 * @file
 * commons_search_solr.apachesolr_search_defaults.inc
 */

/**
 * Implements hook_apachesolr_search_default_searchers().
 */
function commons_search_solr_apachesolr_search_default_searchers() {
  $export = array();

  $searcher = new stdClass();
  $searcher->disabled = FALSE; /* Edit this to true to make a default searcher disabled initially */
  $searcher->api_version = 3;
  $searcher->page_id = 'core_search';
  $searcher->label = 'Core Search';
  $searcher->description = 'Core Search';
  $searcher->search_path = 'search/site';
  $searcher->page_title = 'Site';
  $searcher->env_id = apachesolr_default_environment();
  $searcher->settings = array(
    'fq' => array(),
    'apachesolr_search_custom_enable' => FALSE,
    'apachesolr_search_search_type' => 'custom',
    'apachesolr_search_search_box' => TRUE,
    'apachesolr_search_per_page' => 10,
    'apachesolr_search_browse' => 'blocks',
    'apachesolr_search_spellcheck' => TRUE,
    'apachesolr_search_allow_user_input' => FALSE,
    'apachesolr_search_not_removable' => TRUE,
  );
  $export['core_search'] = $searcher;

  return $export;
}
