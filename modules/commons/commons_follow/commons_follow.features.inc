<?php
/**
 * @file
 * commons_follow.features.inc
 */

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
    'effects' => array(
      3 => array(
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
