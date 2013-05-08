<?php
/**
 * @file
 * commons_posts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_posts_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_posts_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function commons_posts_node_info() {
  $items = array(
    'post' => array(
      'name' => t('Post'),
      'base' => 'node_content',
      'description' => t('Start a conversation or share some information.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
