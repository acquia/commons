<?php
/**
 * @file
 * commons_follow.features.inc
 */

/**
 * Implements hook_features_pipe_alter().
 *
 */
function commons_follow_features_pipe_alter(&$pipe, $data, $export) {
  $commons_follow_fields = array(
    'field_target_users', 'field_target_nodes', 'field_target_comments',
  );
  // Prevent Commons Follow fields from being piped in features
  // when a content type includes those fields.
  if (!empty($pipe['field_instance'])) {
    foreach ($pipe['field_instance'] as $delta => $value) {
      $args = explode('-', $value);
      $field_name = $args[2];
      if (in_array($field_name, $commons_follow_fields)) {
        unset($pipe['field_instance'][$delta]);
      }
    }
  }
  if (!empty($pipe['field_base'])) {
    foreach ($pipe['field_base'] as $delta => $value) {
      if (in_array($delta, $commons_follow_fields)) {
        unset($pipe['field_base'][$delta]);
      }
    }
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_follow_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function commons_follow_image_default_styles() {
  $styles = array();

  // Exported image style: 50x50_avatar.
  $styles['50x50_avatar'] = array(
    'label' => '50x50_avatar',
    'name' => '50x50_avatar',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 50,
          'height' => 50,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
