<?php
/**
 * @file
 * commons_q_a.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function commons_q_a_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create answer content'.
  $permissions['create answer content'] = array(
    'name' => 'create answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create question content'.
  $permissions['create question content'] = array(
    'name' => 'create question content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any answer content'.
  $permissions['delete any answer content'] = array(
    'name' => 'delete any answer content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any question content'.
  $permissions['delete any question content'] = array(
    'name' => 'delete any question content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own answer content'.
  $permissions['delete own answer content'] = array(
    'name' => 'delete own answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own question content'.
  $permissions['delete own question content'] = array(
    'name' => 'delete own question content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any answer content'.
  $permissions['edit any answer content'] = array(
    'name' => 'edit any answer content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any question content'.
  $permissions['edit any question content'] = array(
    'name' => 'edit any question content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own answer content'.
  $permissions['edit own answer content'] = array(
    'name' => 'edit own answer content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own question content'.
  $permissions['edit own question content'] = array(
    'name' => 'edit own question content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
