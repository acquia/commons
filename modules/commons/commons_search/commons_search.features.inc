<?php
/**
 * @file
 * commons_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_search_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_search_views_api() {
  return array("api" => "3.0");
}
