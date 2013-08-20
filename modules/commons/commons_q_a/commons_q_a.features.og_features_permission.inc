<?php
/**
 * @file
 * commons_q_a.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function commons_q_a_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:group:create answer content'
  $permissions['node:group:create answer content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:create question content'
  $permissions['node:group:create question content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:delete any answer content'
  $permissions['node:group:delete any answer content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete any question content'
  $permissions['node:group:delete any question content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete own answer content'
  $permissions['node:group:delete own answer content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:delete own question content'
  $permissions['node:group:delete own question content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:update any answer content'
  $permissions['node:group:update any answer content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update any question content'
  $permissions['node:group:update any question content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update own answer content'
  $permissions['node:group:update own answer content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:update own question content'
  $permissions['node:group:update own question content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  return $permissions;
}
