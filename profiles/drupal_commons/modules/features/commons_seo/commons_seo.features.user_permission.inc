<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_seo_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer pathauto
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  return $permissions;
}
