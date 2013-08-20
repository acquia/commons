<?php
/**
 * @file
 * commons_events.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_events_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_events_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function commons_events_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('Post information about planned activities or meetings.'),
      'has_title' => '1',
      'title_label' => t('Event title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_default_registration_type().
 */
function commons_events_default_registration_type() {
  $items = array();
  $items['event'] = entity_import('registration_type', '{
    "name" : "event",
    "label" : "Event",
    "locked" : "0",
    "weight" : "0",
    "data" : null,
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_rdf_default_mappings().
 */
function commons_events_rdf_default_mappings() {
  $schemaorg = array();

  // Exported RDF mapping: event
  $schemaorg['node']['event'] = array(
    'rdftype' => array(
      0 => 'schema:Event',
      1 => 'sioc:Item',
      2 => 'foaf:Document',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'schema:name',
      ),
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'schema:name',
      ),
    ),
    'comment_count' => array(
      'predicates' => array(
        0 => 'sioc:num_replies',
      ),
      'datatype' => 'xsd:integer',
    ),
    'last_activity' => array(
      'predicates' => array(
        0 => 'sioc:last_activity_date',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'field_date' => array(
      'predicates' => array(
        0 => 'schema:startDate',
      ),
    ),
    'url' => array(
      'predicates' => array(
        0 => 'schema:url',
      ),
      'type' => 'rel',
    ),
    'field_location' => array(
      'predicates' => array(),
    ),
    'field_address' => array(
      'predicates' => array(
        0 => 'schema:location',
      ),
    ),
  );

  return $schemaorg;
}
