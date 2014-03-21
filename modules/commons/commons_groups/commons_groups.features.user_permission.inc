<?php
/**
 * @file
 * commons_groups.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function commons_groups_user_default_permissions() {
  $permissions = array();

  $groups = commons_groups_get_group_types();

  if (isset($groups['node'])) {
    foreach ($groups['node'] as $bundle => $group_info) {
      // Exported permission: 'create group content'.
      $permissions["create $bundle content"] = array(
        'name' => "create $bundle content",
        'roles' => array(
          'administrator' => 'administrator',
          'authenticated user' => 'authenticated user',
        ),
        'module' => 'node',
      );

      // Exported permission: 'edit own group content'.
      $permissions["edit own $bundle content"] = array(
        'name' => "edit own $bundle content",
        'roles' => array(
          'administrator' => 'administrator',
          'authenticated user' => 'authenticated user',
        ),
        'module' => 'node',
      );
    }
  }

  return $permissions;
}
