<?php
/**
 * @file
 * commons_notices.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_notices_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function commons_notices_node_info() {
  $items = array(
    'notice' => array(
      'name' => t('Community notice'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
