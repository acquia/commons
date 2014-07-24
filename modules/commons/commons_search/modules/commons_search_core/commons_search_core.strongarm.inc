<?php
/**
 * @file
 * commons_search_core.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_search_core_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_search_disabled_search_facetapi';
  $strongarm->value = FALSE;
  $export['page_manager_search_disabled_search_facetapi'] = $strongarm;

  return $export;
}

/**
 * Implements hook_strongarm_alter().
 */
function commons_search_core_strongarm_alter(&$items) {
  // Enable the Facet API and User search modules and disable the node module.
  if (isset($items['search_active_modules'])) {
    $items['search_active_modules']->value['search_facetapi'] = 'search_facetapi';
    $items['search_active_modules']->value['user'] = 'user';
    $items['search_active_modules']->value['node']['group'] = 0;
  }

  // Set Facet API as the default search module.
  // Apache SOLR should take precedence if it is available.
  if (!module_exists('commons_search_solr')) {
    if (isset($items['search_default_module'])) {
      $items['search_default_module']->value = 'search_facetapi';
    }
  }

  // Add the Facet API and User search types as Custom Search search options.
  if (isset($items['custom_search_other'])) {
    $items['custom_search_other']->value['search_facetapi'] = 'search_facetapi';
    $items['custom_search_other']->value['user'] = 'user';
  }
}
