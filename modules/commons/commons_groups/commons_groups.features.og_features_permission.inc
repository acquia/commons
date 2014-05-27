<?php
/**
 * @file
 * commons_groups.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function commons_groups_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'user:user:subscribe'
  $permissions['user:user:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'user:user:subscribe without approval'
  $permissions['user:user:subscribe without approval'] = array(
    'roles' => array(),
  );

  return $permissions;
}
