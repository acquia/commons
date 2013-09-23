<?php
/**
 * @file
 * commons_activity_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_activity_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
