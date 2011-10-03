<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_dashboard_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer homebox
  $permissions['administer homebox'] = array(
    'name' => 'administer homebox',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  return $permissions;
}
