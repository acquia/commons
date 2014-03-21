<?php
/**
 * @file
 * commons_groups_pages.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_groups_pages_strongarm() {
  $export = array();

  $group_bundles = og_get_all_group_bundle();
  if (!empty($group_bundles['node'])) {
    // Don't alter the group panel.
    foreach ($group_bundles['node'] as $bundle => $name) {
      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "panelizer_defaults_node_$bundle";
      $strongarm->value = array(
        'status' => 1,
        'view modes' => array(
          'page_manager' => array(
            'status' => 1,
            'default' => 1,
            'choice' => 0,
          ),
          'default' => array(
            'status' => 0,
            'default' => 0,
            'choice' => 0,
          ),
          'teaser' => array(
            'status' => 1,
            'default' => 1,
            'choice' => 0,
          ),
        ),
      );
      $export["panelizer_defaults_node_$bundle"] = $strongarm;
    }
  }

  return $export;
}
