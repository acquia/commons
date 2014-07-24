<?php
/**
 * @file
 * commons_search_solr.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_search_solr_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_default_search_page';
  $strongarm->value = 'core_search';
  $export['apachesolr_search_default_search_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_search_disabled_apachesolr_search';
  $strongarm->value = TRUE;
  $export['page_manager_search_disabled_apachesolr_search'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pm_existing_pages_disabled_solr_search';
  $strongarm->value = FALSE;
  $export['pm_existing_pages_disabled_solr_search'] = $strongarm;

  return $export;
}

/**
 * Implements hook_strongarm_alter().
 */
function commons_search_solr_strongarm_alter(&$items) {
  // Enable the Apache SOLR search module.
  if (isset($items['search_active_modules'])) {
    $items['search_active_modules']->value['apachesolr_search'] = 'apachesolr_search';
  }

  // Set Apache SOLR as the default search module.
  if (isset($items['search_default_module'])) {
    $items['search_default_module']->value = 'apachesolr_search';
  }

  // Add the Apache SOLR and User search types as Custom Search search options.
  if (isset($items['custom_search_other'])) {
    $items['custom_search_other']->value['apachesolr_search'] = 'apachesolr_search';
    $items['custom_search_other']->value['user'] = 'user';
  }
}
