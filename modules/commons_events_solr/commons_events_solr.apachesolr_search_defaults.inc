<?php
/**
 * @file
 * commons_events_solr.apachesolr_search_defaults.inc
 */

/**
 * Implements hook_apachesolr_search_default_searchers().
 */
function commons_events_solr_apachesolr_search_default_searchers() {
  $export = array();

  $searcher = new stdClass();
  $searcher->disabled = FALSE; /* Edit this to true to make a default searcher disabled initially */
  $searcher->api_version = 3;
  $searcher->page_id = 'solr_events';
  $searcher->label = 'Solr Events';
  $searcher->description = '';
  $searcher->search_path = 'events';
  $searcher->page_title = 'Events';
  $searcher->env_id = apachesolr_default_environment();
  $searcher->settings = array(
    'fq' => array(
      0 => 'bundle:event',
    ),
    'apachesolr_search_custom_enable' => 1,
    'apachesolr_search_search_type' => 'custom',
    'apachesolr_search_search_box' => 0,
    'apachesolr_search_per_page' => '10',
    'apachesolr_search_browse' => 'results',
    'apachesolr_search_spellcheck' => 0,
    'apachesolr_search_allow_user_input' => 0,
  );
  $export['solr_events'] = $searcher;

  return $export;
}
