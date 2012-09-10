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
    foreach($commons_radioactivity_entity_types['node'] as $type => $status) {
      if ($status) {
        commons_radioactivity_field_definition($field_instances, $type);  
      }
    }
    return $field_instances;  
  }
  
}

/**
* Contains a field definition export for the Radioactivity field for re-use
* across content types.
*/
function commons_radioactivity_field_definition(&$field_instances, $bundle) {
  $field_instances["node-$bundle-field_radioactivity"] = array(
  'bundle' => $bundle,
  'default_value' => array(
    0 => array(
      'radioactivity_energy' => '8',
    ),
  ),
  'deleted' => '0',
  'description' => '',
  'display' => array(
    'default' => array(
      'label' => 'above',
      'module' => 'radioactivity',
      'settings' => array(
        'energy' => 10,
        'type' => 'none',
      ),
      'type' => 'radioactivity_combo_formatter',
      'weight' => 3,
    ),
    'teaser' => array(
      'label' => 'above',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 0,
    ),
  ),
  'entity_type' => 'node',
  'field_name' => 'field_radioactivity',
  'label' => 'Radioactivity',
  'required' => 0,
  'settings' => array(
    'profile' => 'commons_ra_node',
    'user_register_form' => FALSE,
  ),
  'widget' => array(
    'active' => 0,
    'module' => 'radioactivity',
    'settings' => array(),
    'type' => 'radioactivity_basic_widget',
    'weight' => '3',
  ));
}