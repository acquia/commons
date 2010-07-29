<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _commons_search_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'context_ui',
    'attribute' => 'search',
    'value' => 'search',
    'description' => 'Search Pages',
    'path' => array(
      'search/apachesolr_search/*' => 'search/apachesolr_search/*',
    ),
    'block' => array(
      'apachesolr_sort' => array(
        'module' => 'apachesolr',
        'delta' => 'sort',
        'weight' => 42,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Apache Solr Core: Sorting',
        'type' => 'context_ui',
      ),
      'apachesolr_search_type' => array(
        'module' => 'apachesolr_search',
        'delta' => 'type',
        'weight' => 43,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Apache Solr Search: Filter by content type',
        'type' => 'context_ui',
      ),
      'apachesolr_search_im_vid_2' => array(
        'module' => 'apachesolr_search',
        'delta' => 'im_vid_2',
        'weight' => 44,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Apache Solr Search: Filter by taxonomy Tags',
        'type' => 'context_ui',
      ),
      'apachesolr_og_im_og_gid' => array(
        'module' => 'apachesolr_og',
        'delta' => 'im_og_gid',
        'weight' => 45,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Apache Solr OG: Filter by Organic Group',
        'type' => 'context_ui',
      ),
      'apachesolr_search_uid' => array(
        'module' => 'apachesolr_search',
        'delta' => 'uid',
        'weight' => 46,
        'region' => 'sidebar_last',
        'status' => '0',
        'label' => 'Apache Solr Search: Filter by author',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _commons_search_ctools_plugin_api() {
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
function _commons_search_strongarm() {
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
