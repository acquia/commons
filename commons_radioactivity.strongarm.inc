<?php
/**
 * @file
 * commons_radioactivity.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_radioactivity_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commons_radioactivity_entity_types';
  $strongarm->value = array();
  $export['commons_radioactivity_entity_types'] = $strongarm;

  return $export;
}
