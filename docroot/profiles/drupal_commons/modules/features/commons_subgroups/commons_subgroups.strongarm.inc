<?php

/**
 * Implementation of hook_strongarm().
 */
function commons_subgroups_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_subgroups_node_type_enabled_group';
  $strongarm->value = 1;

  $export['og_subgroups_node_type_enabled_group'] = $strongarm;
  return $export;
}
