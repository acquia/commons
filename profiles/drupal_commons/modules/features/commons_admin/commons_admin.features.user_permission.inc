<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_admin_user_default_permissions() {
  $permissions = array();

  // Exported permission: use admin toolbar
  $permissions['use admin toolbar'] = array(
    'name' => 'use admin toolbar',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer rules
  $permissions['administer rules'] = array(
    'name' => 'administer rules',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  return $permissions;
}
