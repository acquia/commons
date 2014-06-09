<?php
/**
 * @file
 * commons_radioactivity.features.inc
 */

/**
 * Implements hook_features_pipe_alter().
 */
function commons_radioactivity_features_pipe_alter(&$pipe, $data, $export) {
  // Prevent Commons Radioactivity fields from being piped in features
  // when a content type includes those fields.
  if (!empty($pipe['field_instance'])) {
    foreach ($pipe['field_instance'] as $delta => $value) {
      $args = explode('-', $value);
      $field_name = $args[2];
      if ($field_name == 'field_radioactivity') {
        unset($pipe['field_instance'][$delta]);
      }
    }
  }
  if (!empty($pipe['field_base'])) {
    foreach ($pipe['field_base'] as $delta => $value) {
      if ($delta == 'field_radioactivity') {
        unset($pipe['field_base'][$delta]);
      }
    }
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_radioactivity_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "radioactivity" && $api == "radioactivity_decay_profile") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_radioactivity_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
