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
  $commons_radioactivity_entity_types = commons_radioactivity_get_radioactive_entity_types();
  if (!empty($commons_radioactivity_entity_types)) {
    foreach ($commons_radioactivity_entity_types as $entity_type => $bundles) {
      foreach (array_keys($bundles) as $bundle) {
        commons_radioactivity_field_definition($field_instances, $entity_type, $bundle);
      }
    }
  }
  return $field_instances;
}

/**
 * Contains a field definition export for the Radioactivity field for re-use
 * across content types.
 */
function commons_radioactivity_field_definition(&$field_instances, $entity_type, $bundle) {
  $field_instances["$entity_type-$bundle-field_radioactivity"] = array(
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
          'accuracy' => '100',
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
    'entity_type' => $entity_type,
    'field_name' => 'field_radioactivity',
    'label' => 'Radioactivity',
    'required' => 0,
    'settings' => array(
      'history_limit' => 8,
      'profile' => "commons_ra_$entity_type",
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