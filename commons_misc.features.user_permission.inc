<?php
/**
 * @file
 * commons_misc.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function commons_misc_user_default_permissions() {
  $permissions = array();

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: view own unpublished content.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'anonymous user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}