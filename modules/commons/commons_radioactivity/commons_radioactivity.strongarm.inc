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
  $strongarm->value = array(
    'node' => array(
      'group' => 1,
      'poll' => 1,
      'post' => 1,
      'wiki' => 1,
    ),
  );
  $export['commons_radioactivity_entity_types'] = $strongarm;

  return $export;
}
