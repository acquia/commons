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
