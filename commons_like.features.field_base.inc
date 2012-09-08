<?php
/**
 * @file
 * commons_like.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function commons_like_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_target_nodes'
  $field_bases['field_target_nodes'] = array(
    'active' => '1',
    'cardinality' => '-1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_target_nodes',
    'field_permissions' => array(
      'type' => '0',
    ),
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
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'direction' => 'ASC',
          'field' => 'body:value',
          'property' => 'nid',
          'type' => 'none',
        ),
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
