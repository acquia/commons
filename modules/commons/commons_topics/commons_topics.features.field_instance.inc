<?php
/**
 * @file
 * commons_topics.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_topics_field_default_field_instances() {
  $field_instances = array();

  // Get a list of content types that should have the field_topics field added.
  $commons_groups_entity_types = commons_topics_get_entity_types_with_topics();
  if (!empty($commons_groups_entity_types)) {
    foreach ($commons_groups_entity_types as $entity_type => $bundles) {
      foreach(array_keys($bundles) as $bundle) {
        commons_topics_field_definition($field_instances, $entity_type, $bundle);
      }
    }
  }

  return $field_instances;
}

function commons_topics_field_definition(&$field_instances, $entity_type, $bundle) {
  // Exported field_instance: 'ENTITY_TYPE-BUNDLE-field_topics'
  $field_instances["$entity_type-$bundle-field_topics"] = array(
    'bundle' => $bundle,
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => '6',
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => $entity_type,
    'field_name' => 'field_topics',
    'label' => 'Topics',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => '13',
    ),
  );
}
