<?php
/**
 * @file
 * commons_misc.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function commons_misc_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 10,
  );

  return $roles;
}
