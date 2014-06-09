<?php
/**
 * @file
 * commons_topics.features.inc
 */

/**
 * Implements hook_features_pipe_alter().
 */
function commons_topics_features_pipe_alter(&$pipe, $data, $export) {
  if (!empty($pipe['field_instance'])) {
    foreach ($pipe['field_instance'] as $delta => $value) {
      $args = explode('-', $value);
      $field_name = $args[2];
      if ($field_name == 'field_topics') {
        unset($pipe['field_instance'][$delta]);
      }
    }
  }
}
