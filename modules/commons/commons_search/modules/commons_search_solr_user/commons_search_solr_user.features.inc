<?php
/**
 * @file
 * commons_search_solr_user.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_search_solr_user_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "apachesolr_search" && $api == "apachesolr_search_defaults") {
    return array("version" => "3");
  }
}
