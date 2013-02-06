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
  
  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_active_modules';
  $strongarm->value = array(
    'search_facetapi' => 'search_facetapi',
    'user' => 'user',
    'node' => 0,
  );
  $export['search_active_modules'] = $strongarm;
  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_default_module';
  $strongarm->value = 'search_facetapi';
  $export['search_default_module'] = $strongarm;
  
  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'custom_search_other';
  $strongarm->value = array(
    'search_facetapi' => 'search_facetapi',
    'user' => 'user',
  );
  $export['custom_search_other'] = $strongarm;

  return $export;
}
