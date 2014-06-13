<?php
/**
 * @file
 * commons_bw.features.inc
 */

/**
 * Implements hook_ctools_plugin_directory().
 */
function commons_bw_ctools_plugin_directory($module, $plugin) {
  if ($module == 'ctools' && $plugin == 'content_types') {
    return 'plugins/' . $plugin;
  }
}

/**
 * Implements hook_views_api().
 */
function commons_bw_views_api() {
  return array(
    'api' => 3,
    'path' => drupal_get_path('module', 'commons_bw') . '/includes/views',
  );
}
