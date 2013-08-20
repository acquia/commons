<?php
/**
 * @file
 * commons_documents.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function commons_documents_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:group:create document content'
  $permissions['node:group:create document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:delete any document content'
  $permissions['node:group:delete any document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete own document content'
  $permissions['node:group:delete own document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:update any document content'
  $permissions['node:group:update any document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update own document content'
  $permissions['node:group:update own document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  return $permissions;
}
