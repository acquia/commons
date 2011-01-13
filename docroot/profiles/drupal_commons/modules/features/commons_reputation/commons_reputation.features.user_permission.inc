<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_reputation_user_default_permissions() {
  $permissions = array();

  // Exported permission: change badge assignments
  $permissions['change badge assignments'] = array(
    'name' => 'change badge assignments',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: manage badges
  $permissions['manage badges'] = array(
    'name' => 'manage badges',
    'roles' => array(),
  );

  // Exported permission: userpoints user picture
  $permissions['userpoints user picture'] = array(
    'name' => 'userpoints user picture',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view own userpoints
  $permissions['view own userpoints'] = array(
    'name' => 'view own userpoints',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view userpoints
  $permissions['view userpoints'] = array(
    'name' => 'view userpoints',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
