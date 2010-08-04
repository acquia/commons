<?php

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _acquia_network_subscription_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _acquia_network_subscription_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_enabled_facets';
  $strongarm->value = array(
    'apachesolr_search' => array(
      'uid' => 'uid',
      'type' => 'type',
      'im_vid_2' => 'im_vid_2',
    ),
    'apachesolr_og' => array(
      'im_og_gid' => 'im_og_gid',
    ),
  );

  $export['apachesolr_enabled_facets'] = $strongarm;
  return $export;
}
