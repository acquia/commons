<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_shoutbox_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer shoutbox
  $permissions['administer shoutbox'] = array(
    'name' => 'administer shoutbox',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer shoutbox_group
  $permissions['administer shoutbox_group'] = array(
    'name' => 'administer shoutbox_group',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: delete own shouts
  $permissions['delete own shouts'] = array(
    'name' => 'delete own shouts',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit own shouts
  $permissions['edit own shouts'] = array(
    'name' => 'edit own shouts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: moderate shoutbox
  $permissions['moderate shoutbox'] = array(
    'name' => 'moderate shoutbox',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: post shouts
  $permissions['post shouts'] = array(
    'name' => 'post shouts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: post shouts in all groups
  $permissions['post shouts in all groups'] = array(
    'name' => 'post shouts in all groups',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: post shouts without approval
  $permissions['post shouts without approval'] = array(
    'name' => 'post shouts without approval',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view shouts
  $permissions['view shouts'] = array(
    'name' => 'view shouts',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  return $permissions;
}
