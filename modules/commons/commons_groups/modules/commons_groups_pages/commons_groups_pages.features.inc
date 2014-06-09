<?php
/**
 * @file
 * commons_groups_pages.features.inc
 */

/*
 * Implements hook_features_pipe_alter().
 */
function commons_groups_pages_features_pipe_alter(&$pipe, $data, $export) {
  // Prevent Commons Groups related fields from being piped in features
  // when a content type includes those fields.
  if (!empty($pipe['panelizer_defaults'])) {

    foreach ($pipe['panelizer_defaults'] as $delta => $value) {
      $args = explode(':', $value);
      $group_name = $args[1];

      $group_bundles = og_get_all_group_bundle();
      if (isset($group_bundles['node']) && isset($group_bundles['node']['group'])) {
        unset($group_bundles['node']['group']);
      }
      $excluded_groups = array_keys($group_bundles);
      if (in_array($group_name, $excluded_groups)) {
        unset($pipe['field_instance'][$delta]);
      }
    }
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_groups_pages_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
