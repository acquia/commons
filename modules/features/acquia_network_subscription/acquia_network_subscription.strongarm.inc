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
      'created' => 'created',
      'im_vid_2' => 'im_vid_2',
      'changed' => 'changed',
    ),
    'apachesolr_og' => array(
      'im_og_gid' => 'im_og_gid',
    ),
  );

  $export['apachesolr_enabled_facets'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_search_taxonomy_links';
  $strongarm->value = '1';

  $export['apachesolr_search_taxonomy_links'] = $strongarm;
  return $export;
}
