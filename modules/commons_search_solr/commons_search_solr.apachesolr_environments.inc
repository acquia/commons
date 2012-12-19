<?php
/**
 * @file
 * commons_search_solr.apachesolr_environments.inc
 */

/**
 * Implements hook_apachesolr_environments().
 */
function commons_search_solr_apachesolr_environments() {
  $export = array();

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'local_solr';
  $environment->name = 'Default local Solr server';
  $environment->url = 'http://localhost:8983/solr';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_search_facet_pages' => '',
    'apachesolr_search_show_facets' => 1,
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'event',
      1 => 'group',
      2 => 'page',
      3 => 'post',
      4 => 'wiki',
    ),
  );
  $export['solr'] = $environment;

  return $export;
}
