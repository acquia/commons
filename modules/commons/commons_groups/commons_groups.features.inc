<?php
/**
 * @file
 * commons_groups.features.inc
 */

/**
 * Implements hook_features_pipe_alter().
 */
function commons_groups_features_pipe_alter(&$pipe, $data, $export) {
  // Prevent Commons Groups related fields from being piped in features
  // when a content type includes those fields.
  if (!empty($pipe['field_instance'])) {
    foreach ($pipe['field_instance'] as $delta => $value) {
      $args = explode('-', $value);
      $field_name = $args[2];
      $excluded_fields = array('og_group_ref', 'field_og_access_default_value',
        'field_og_subscribe_settings', 'og_roles_permissions', 'group_access', 'field_group_logo', 'group_group', 'body');
      if (in_array($field_name, $excluded_fields)) {
        unset($pipe['field_instance'][$delta]);
      }
    }
  }
  if (!empty($pipe['field_base'])) {
    foreach ($pipe['field_base'] as $delta => $value) {
      if ($delta == 'og_group_ref') {
        unset($pipe['field_base'][$delta]);
      }
    }
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_groups_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_groups_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function commons_groups_image_default_styles() {
  $styles = array();

  // Exported image style: 35x35.
  $styles['35x35'] = array(
    'label' => '35x35',
    'name' => '35x35',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 35,
          'height' => 35,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: 50x50.
  $styles['50x50'] = array(
    'label' => '50x50',
    'name' => '50x50',
    'effects' => array(
      2 => array(
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

/**
 * Implements hook_node_info().
 */
function commons_groups_node_info() {
  $items = array(
    'group' => array(
      'name' => t('Group'),
      'base' => 'node_content',
      'description' => t('Use groups to contain people and content related by a shared interest or purpose.'),
      'has_title' => '1',
      'title_label' => t('Group name'),
      'help' => '',
    ),
  );
  return $items;
}
