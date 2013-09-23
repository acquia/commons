<?php
/**
 * @file
 * commons_wikis.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function commons_wikis_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create wiki content'.
  $permissions['create wiki content'] = array(
    'name' => 'create wiki content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own wiki content'.
  $permissions['delete own wiki content'] = array(
    'name' => 'delete own wiki content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any wiki content'.
  $permissions['edit any wiki content'] = array(
    'name' => 'edit any wiki content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own wiki content'.
  $permissions['edit own wiki content'] = array(
    'name' => 'edit own wiki content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
