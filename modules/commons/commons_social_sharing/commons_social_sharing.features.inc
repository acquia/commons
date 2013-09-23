<?php
/**
 * @file
 * commons_social_sharing.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_social_sharing_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
