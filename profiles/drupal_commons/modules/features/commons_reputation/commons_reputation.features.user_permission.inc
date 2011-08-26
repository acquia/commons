<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_reputation_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer userpoints
  $permissions['administer userpoints'] = array(
    'name' => 'administer userpoints',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: change badge assignments
  $permissions['change badge assignments'] = array(
    'name' => 'change badge assignments',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: manage badges
  $permissions['manage badges'] = array(
    'name' => 'manage badges',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: upload files
  $permissions['upload files'] = array(
    'name' => 'upload files',
    'roles' => array(
      '0' => 'site admin',
    ),
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

  // Exported permission: view uploaded files
  $permissions['view uploaded files'] = array(
    'name' => 'view uploaded files',
    'roles' => array(
      '0' => 'site admin',
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
