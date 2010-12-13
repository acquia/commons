<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_admin_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer views
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(),
  );

  return $permissions;
}
