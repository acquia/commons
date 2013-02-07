<?php
/**
 * @file
 * commons_social_sharing.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_social_sharing_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
