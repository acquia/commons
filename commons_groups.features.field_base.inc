<?php
/**
 * @file
 * commons_groups.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function commons_groups_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'og_group_ref'
  $field_bases['og_group_ref'] = array(
    'active' => '1',
    'cardinality' => '-1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'og_group_ref',
    'foreign keys' => array(
      'node' => array(
        'columns' => array(
          'target_id' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => '0',
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'og',
      'handler_settings' => array(
        'behaviors' => array(
          'og_behavior' => array(
            'status' => TRUE,
          ),
        ),
        'membership_type' => 'og_membership_type_default',
        'primary_field' => FALSE,
        'reference_type' => 'my_groups',
        'target_bundles' => array(),
      ),
      'handler_submit' => 'Change handler',
      'target_type' => 'node',
    ),
    'translatable' => '0',
    'type' => 'entityreference',
  );

  return $field_bases;
}
