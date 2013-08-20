<?php
/**
 * @file
 * commons_events_solr.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function commons_events_solr_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'solr_events_search';
  $pm_existing_page->label = 'Solr Events Search';
  $pm_existing_page->context = '';
  $pm_existing_page->paths = 'events';
  $export['solr_events_search'] = $pm_existing_page;

  return $export;
}
