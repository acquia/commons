<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_discussion_user_default_permissions() {
  $permissions = array();

  // Exported permission: create discussion content
  $permissions['create discussion content'] = array(
    'name' => 'create discussion content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete any discussion content
  $permissions['delete any discussion content'] = array(
    'name' => 'delete any discussion content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete own discussion content
  $permissions['delete own discussion content'] = array(
    'name' => 'delete own discussion content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit any discussion content
  $permissions['edit any discussion content'] = array(
    'name' => 'edit any discussion content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit own discussion content
  $permissions['edit own discussion content'] = array(
    'name' => 'edit own discussion content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
