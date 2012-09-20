<?php
/**
 * @file
 * commons_groups.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_groups_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_groups_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function commons_groups_node_info() {
  $items = array(
    'group' => array(
      'name' => t('Group'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Group name'),
      'help' => '',
    ),
  );
  return $items;
}
