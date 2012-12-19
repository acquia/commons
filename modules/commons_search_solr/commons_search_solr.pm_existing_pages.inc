<?php
/**
 * @file
 * commons_search_solr.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function commons_search_solr_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'solr_search';
  $pm_existing_page->label = 'ApacheSolr site search';
  $pm_existing_page->context = '';
  $pm_existing_page->paths = 'search/site
search/site/%';
  $export['solr_search'] = $pm_existing_page;

  return $export;
}
