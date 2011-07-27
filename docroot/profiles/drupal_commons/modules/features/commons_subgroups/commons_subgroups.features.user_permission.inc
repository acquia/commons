<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_subgroups_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer groups hierarchy
  $permissions['administer groups hierarchy'] = array(
    'name' => 'administer groups hierarchy',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: edit groups hierarchy
  $permissions['edit groups hierarchy'] = array(
    'name' => 'edit groups hierarchy',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
