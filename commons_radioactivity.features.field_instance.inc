<?php
/**
 * @file
 * commons_radioactivity.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_radioactivity_field_default_field_instances() {
  // Get a list of content types that should have the Radioactivity field added.
  // Modules can alter this list by implementing hook_strongarm_alter().
  $commons_radioactivity_entity_types = variable_get('commons_radioactivity_entity_types', array());
  if (!empty($commons_radioactivity_entity_types['node'])) {
    $field_instances = array();
    foreach($commons_radioactivity_entity_types['node'] as $key => $type) {
      commons_radioactivity_field_definition($field_instances, $type);
    }
  }
  return $field_instances;  
}