<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function acquia_network_subscription_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer mollom
  $permissions['administer mollom'] = array(
    'name' => 'administer mollom',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: bypass mollom protection
  $permissions['bypass mollom protection'] = array(
    'name' => 'bypass mollom protection',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
      '2' => 'site admin',
    ),
  );

  return $permissions;
}
