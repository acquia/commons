<?php
/**
 * @file
 * commons_wikis.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function commons_wikis_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:group:create wiki content'
  $permissions['node:group:create wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:delete any wiki content'
  $permissions['node:group:delete any wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete own wiki content'
  $permissions['node:group:delete own wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:update any wiki content'
  $permissions['node:group:update any wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:update own wiki content'
  $permissions['node:group:update own wiki content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  return $permissions;
}
