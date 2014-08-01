<?php
/**
 * @file
 * commons_bw.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_bw_field_default_field_instances() {
  $field_instances = array();

  foreach (node_type_get_types() as $node_type) {
    if (commons_bw_node_auto_title_instance($node_type->type)) {
      commons_bw_field_definition($field_instances, $node_type->type);
    }
  }

  // Translatables
  // Included for use with string extractors like potx.
  t('Title');

  return $field_instances;
}

/**
 * Creates field instance definitions for all node types.
 */
function commons_bw_field_definition(&$field_instances, $bundle) {
  // Exported field_instance: 'node-[Bundle]-title_field'
  $field_instances["node-$bundle-title_field"] = array(
    'bundle' => $bundle,
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => -50,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => -50,
      ),
    ),
    'display_in_partial_form' => !empty($display_in_partial_form[$bundle]),
    'entity_type' => 'node',
    'field_name' => 'title_field',
    'label' => 'Title',
    'required' => 1,
    'settings' => array(
      'hide_label' => array(
        'entity' => 0,
        'page' => 0,
      ),
      'text_processing' => '0',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => '60',
      ),
      'type' => 'text_textfield',
      'weight' => -50,
    ),
  );
}
