<?php
/**
 * @file
 * commons_events_solr.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_events_solr_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pm_existing_pages_disabled_solr_events_search';
  $strongarm->value = FALSE;
  $export['pm_existing_pages_disabled_solr_events_search'] = $strongarm;

  return $export;
}
