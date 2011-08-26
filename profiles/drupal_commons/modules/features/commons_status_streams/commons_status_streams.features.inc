<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function commons_status_streams_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_views_api().
 */
function commons_status_streams_views_api() {
  return array(
    'api' => '2',
  );
}
