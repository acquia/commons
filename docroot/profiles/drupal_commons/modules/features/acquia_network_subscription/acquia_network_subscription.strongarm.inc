<?php

/**
 * Implementation of hook_strongarm().
 */
function acquia_network_subscription_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_enabled_facets';
  $strongarm->value = array(
    'apachesolr_search' => array(
      'type' => 'type',
      'uid' => 'uid',
      'imfield_vid_2' => 'imfield_vid_2',
      'imfield_vid_1' => 'imfield_vid_1',
    ),
  );

  $export['apachesolr_enabled_facets'] = $strongarm;
  return $export;
}
