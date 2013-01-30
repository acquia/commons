<?php
/**
 * @file
 * commons_wikis_pages.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_wikis_pages_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_wiki';
  $strongarm->value = array(
    'status' => 1,
    'default' => 1,
    'choice' => 0,
  );
  $export['panelizer_defaults_node_wiki'] = $strongarm;

  return $export;
}
