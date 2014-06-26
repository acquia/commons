<?php
/**
 * @file
 * commons_groups.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_groups_strongarm() {
  $export = array();
  $commons_groups = commons_groups_get_group_types();
  $group_bundles = og_get_all_group_bundle();

  // These settings are automatic for all groups used within commons.
  if (isset($group_bundles['node'])) {
    foreach ($group_bundles['node'] as $bundle => $group_info) {
      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "comment_anonymous_$bundle";
      $strongarm->value = 0;
      $export["comment_anonymous_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "comment_default_mode_$bundle";
      $strongarm->value = 1;
      $export["comment_default_mode_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "comment_default_per_page_$bundle";
      $strongarm->value = '50';
      $export["comment_default_per_page_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "comment_form_location_$bundle";
      $strongarm->value = 1;
      $export["comment_form_location_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "comment_$bundle";
      $strongarm->value = '0';
      $export["comment_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "comment_preview_$bundle";
      $strongarm->value = '1';
      $export["comment_preview_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "comment_subject_field_$bundle";
      $strongarm->value = 1;
      $export["comment_subject_field_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "field_bundle_settings_node__$bundle";
      $strongarm->value = array(
        'view_modes' => array(
          'teaser' => array(
            'custom_settings' => TRUE,
          ),
          'full' => array(
            'custom_settings' => FALSE,
          ),
          'rss' => array(
            'custom_settings' => FALSE,
          ),
          'search_index' => array(
            'custom_settings' => FALSE,
          ),
          'search_result' => array(
            'custom_settings' => FALSE,
          ),
          'diff_standard' => array(
            'custom_settings' => FALSE,
          ),
          'token' => array(
            'custom_settings' => FALSE,
          ),
        ),
        'extra_fields' => array(
          'form' => array(
            'title' => array(
              'weight' => '-5',
            ),
          ),
          'display' => array(),
        ),
      );
      $export["field_bundle_settings_node__$bundle"] = $strongarm;
    }
  }

  // Add some additional default settings if the node implements the commons
  // Specific entity integrations hook.
  if (isset($commons_groups['node'])) {
    foreach ($commons_groups['node'] as $bundle => $group_info) {

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "node_options_$bundle";
      $strongarm->value = array(
        0 => 'revision',
      );
      $export["node_options_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "node_preview_$bundle";
      $strongarm->value = '1';
      $export["node_preview_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "node_submitted_$bundle";
      $strongarm->value = 0;
      $export["node_submitted_$bundle"] = $strongarm;

      $strongarm = new stdClass();
      $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
      $strongarm->api_version = 1;
      $strongarm->name = "og_group_manager_default_rids_node_$bundle";
      $strongarm->value = array(
        3 => '3',
      );
      $export["og_group_manager_default_rids_node_$bundle"] = $strongarm;
    }
  }

  // These following settings are ONLY for the group content type.
  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = "pathauto_node_group_pattern";
  $strongarm->value = 'groups/[node:title]';
  $export["pathauto_node_group_pattern"] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_group';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_group';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_pattern';
  $strongarm->value = 'groups/[node:commons-groups-first-group]/[node:title]';
  $export['pathauto_node_pattern'] = $strongarm;

  return $export;
}
