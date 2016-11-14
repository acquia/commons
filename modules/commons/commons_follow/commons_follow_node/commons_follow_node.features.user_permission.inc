<?php
/**
 * @file
 * commons_follow_node.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function commons_follow_node_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'flag commons_follow_node'.
  $permissions['flag commons_follow_node'] = array(
    'name' => 'flag commons_follow_node',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag email_node'.
  $permissions['flag email_node'] = array(
    'name' => 'flag email_node',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag commons_follow_node'.
  $permissions['unflag commons_follow_node'] = array(
    'name' => 'unflag commons_follow_node',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag email_node'.
  $permissions['unflag email_node'] = array(
    'name' => 'unflag email_node',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  return $permissions;
}
