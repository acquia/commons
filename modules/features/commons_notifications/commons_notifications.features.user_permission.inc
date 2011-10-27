<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_notifications_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer messaging
  $permissions['administer messaging'] = array(
    'name' => 'administer messaging',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer notifications
  $permissions['administer notifications'] = array(
    'name' => 'administer notifications',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: maintain own subscriptions
  $permissions['maintain own subscriptions'] = array(
    'name' => 'maintain own subscriptions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: manage all subscriptions
  $permissions['manage all subscriptions'] = array(
    'name' => 'manage all subscriptions',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: manage own subscriptions
  $permissions['manage own subscriptions'] = array(
    'name' => 'manage own subscriptions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: skip notifications
  $permissions['skip notifications'] = array(
    'name' => 'skip notifications',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: subscribe to author
  $permissions['subscribe to author'] = array(
    'name' => 'subscribe to author',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: subscribe to content
  $permissions['subscribe to content'] = array(
    'name' => 'subscribe to content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: subscribe to content in groups
  $permissions['subscribe to content in groups'] = array(
    'name' => 'subscribe to content in groups',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: subscribe to content type
  $permissions['subscribe to content type'] = array(
    'name' => 'subscribe to content type',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
