<?php
/**
 * @file
 * commons_polls.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function commons_polls_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:group:create poll content'
  $permissions['node:group:create poll content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:delete any poll content'
  $permissions['node:group:delete any poll content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete own poll content'
  $permissions['node:group:delete own poll content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:update any poll content'
  $permissions['node:group:update any poll content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update own poll content'
  $permissions['node:group:update own poll content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  return $permissions;
}
