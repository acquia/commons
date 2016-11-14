<?php
/**
 * @file
 * commons_follow_group.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function commons_follow_group_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'flag commons_follow_group'.
  $permissions['flag commons_follow_group'] = array(
    'name' => 'flag commons_follow_group',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag email_group'.
  $permissions['flag email_group'] = array(
    'name' => 'flag email_group',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag commons_follow_group'.
  $permissions['unflag commons_follow_group'] = array(
    'name' => 'unflag commons_follow_group',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag email_group'.
  $permissions['unflag email_group'] = array(
    'name' => 'unflag email_group',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  return $permissions;
}
