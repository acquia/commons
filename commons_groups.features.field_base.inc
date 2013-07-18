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

    // Exported field_base: 'group_access'
    $field_bases['group_access'] = array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'group_access',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'no_ui' => TRUE,
      'settings' => array(
        'allowed_values' => array(
          0 => 'Public - accessible to all site users',
          1 => 'Private - accessible only to group members',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_boolean',
    );

    // Exported field_base: 'group_content_access'
    $field_bases['group_content_access'] = array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'group_content_access',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'no_ui' => TRUE,
      'settings' => array(
        'allowed_values' => array(
          0 => 'Use group defaults',
          1 => 'Public - accessible to all site users',
          2 => 'Private - accessible only to group members',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_integer',
    );

  // Exported field_base: 'field_og_access_default_value'
  $field_bases['field_og_access_default_value'] = array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_og_access_default_value',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => '0',
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => '0',
    'type' => 'list_boolean',
  );

  // Exported field_base: 'field_og_subscribe_settings'
  $field_bases['field_og_subscribe_settings'] = array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_og_subscribe_settings',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => '0',
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'anyone' => 'Any site member can contribute',
        'approval' => 'Joining requires admin approval',
        'invitation' => 'Joining requires an invitation',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => '0',
    'type' => 'list_text',
  );

  // Alter the "approval" description when og_access is on.
  if (module_exists('og_access')) {
    $field_bases['field_og_subscribe_settings']['settings']['allowed_values']['invitation'] = 'Joining requires an invitation. The group and content is hidden from non-members.';
  }

  // Exported field_base: 'group_group'
  $field_bases['group_group'] = array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'group_group',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => '0',
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'Not a group',
        1 => 'Group',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => '0',
    'type' => 'list_boolean',
  );

// Exported field_base: 'og_group_ref'
 $field_bases['og_group_ref'] = array(
    'active' => '1',
    'cardinality' => '-1',
    'deleted' => '0',
    'entity_types' => array(),
    'description' => 'Separate group names with commas',
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
      'handler' => 'og_commons',
      'handler_settings' => array(
        'behaviors' => array(
          'og_behavior' => array(
            'status' => TRUE,
          ),
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'membership_type' => 'og_membership_type_default',
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(),
      ),
      'handler_submit' => 'Change handler',
      'target_type' => 'node',
    ),
    'target_type' => 'node',
    'translatable' => '0',
    'type' => 'entityreference',
  );


  // Exported field_base: 'og_membership_request'
  $field_bases['og_membership_request'] = array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(
      0 => 'og_membership',
    ),
    'field_name' => 'og_membership_request',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => '0',
    'module' => 'text',
    'settings' => array(),
    'translatable' => '0',
    'type' => 'text_long',
  );

  // Exported field_base: 'field_group_logo'
  $field_bases['field_group_logo'] = array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'field_group_logo',
    'foreign keys' => array(
      'fid' => array(
        'columns' => array(
          'fid' => 'fid',
        ),
        'table' => 'file_managed',
      ),
    ),
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => '0',
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => '0',
    'type' => 'image',
  );

  // Exported field_base: 'og_roles_permissions'
  $field_bases['og_roles_permissions'] = array(
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'entity_types' => array(),
    'field_name' => 'og_roles_permissions',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => '0',
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => 'Use default roles and permissions',
        1 => 'Override default roles and permissions',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => '0',
    'type' => 'list_boolean',
  );

  return $field_bases;
}
