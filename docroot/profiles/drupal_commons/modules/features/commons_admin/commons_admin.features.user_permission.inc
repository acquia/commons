<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_admin_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration menu
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
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
