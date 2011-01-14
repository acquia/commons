<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_wiki_user_default_permissions() {
  $permissions = array();

  // Exported permission: access freelinking list
  $permissions['access freelinking list'] = array(
    'name' => 'access freelinking list',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: administer freelinking
  $permissions['administer freelinking'] = array(
    'name' => 'administer freelinking',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: create wiki content
  $permissions['create wiki content'] = array(
    'name' => 'create wiki content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete any wiki content
  $permissions['delete any wiki content'] = array(
    'name' => 'delete any wiki content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete own wiki content
  $permissions['delete own wiki content'] = array(
    'name' => 'delete own wiki content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit any wiki content
  $permissions['edit any wiki content'] = array(
    'name' => 'edit any wiki content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit own wiki content
  $permissions['edit own wiki content'] = array(
    'name' => 'edit own wiki content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
