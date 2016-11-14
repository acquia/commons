<?php
/**
 * @file
 * commons_follow_term.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function commons_follow_term_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'flag commons_follow_term'.
  $permissions['flag commons_follow_term'] = array(
    'name' => 'flag commons_follow_term',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag email_term'.
  $permissions['flag email_term'] = array(
    'name' => 'flag email_term',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag commons_follow_term'.
  $permissions['unflag commons_follow_term'] = array(
    'name' => 'unflag commons_follow_term',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag email_term'.
  $permissions['unflag email_term'] = array(
    'name' => 'unflag email_term',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  return $permissions;
}
