<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_status_streams_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer Facebook-style Statuses settings
  $permissions['administer Facebook-style Statuses settings'] = array(
    'name' => 'administer Facebook-style Statuses settings',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer loading arbitrary CSS and JS files for cached messages
  $permissions['administer loading arbitrary CSS and JS files for cached messages'] = array(
    'name' => 'administer loading arbitrary CSS and JS files for cached messages',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: configure preferences for which activity types appear in activity streams
  $permissions['configure preferences for which activity types appear in activity streams'] = array(
    'name' => 'configure preferences for which activity types appear in activity streams',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete all status comments
  $permissions['delete all status comments'] = array(
    'name' => 'delete all status comments',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
      '2' => 'site admin',
    ),
  );

  // Exported permission: delete all statuses
  $permissions['delete all statuses'] = array(
    'name' => 'delete all statuses',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
      '2' => 'site admin',
    ),
  );

  // Exported permission: delete comments on own statuses
  $permissions['delete comments on own statuses'] = array(
    'name' => 'delete comments on own statuses',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete own status comments
  $permissions['delete own status comments'] = array(
    'name' => 'delete own status comments',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete own statuses
  $permissions['delete own statuses'] = array(
    'name' => 'delete own statuses',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete status messages on own nodes
  $permissions['delete status messages on own nodes'] = array(
    'name' => 'delete status messages on own nodes',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
      '2' => 'site admin',
    ),
  );

  // Exported permission: delete status messages on own profile
  $permissions['delete status messages on own profile'] = array(
    'name' => 'delete status messages on own profile',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit all status comments
  $permissions['edit all status comments'] = array(
    'name' => 'edit all status comments',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
      '2' => 'site admin',
    ),
  );

  // Exported permission: edit all statuses
  $permissions['edit all statuses'] = array(
    'name' => 'edit all statuses',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
      '2' => 'site admin',
    ),
  );

  // Exported permission: edit comments on own statuses
  $permissions['edit comments on own statuses'] = array(
    'name' => 'edit comments on own statuses',
    'roles' => array(),
  );

  // Exported permission: edit own status comments
  $permissions['edit own status comments'] = array(
    'name' => 'edit own status comments',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit own statuses
  $permissions['edit own statuses'] = array(
    'name' => 'edit own statuses',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: post status comment
  $permissions['post status comment'] = array(
    'name' => 'post status comment',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: post status messages to other streams
  $permissions['post status messages to other streams'] = array(
    'name' => 'post status messages to other streams',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: receive digests
  $permissions['receive digests'] = array(
    'name' => 'receive digests',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: send messages to all users at once
  $permissions['send messages to all users at once'] = array(
    'name' => 'send messages to all users at once',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: send private status messages
  $permissions['send private status messages'] = array(
    'name' => 'send private status messages',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: update and view own stream
  $permissions['update and view own stream'] = array(
    'name' => 'update and view own stream',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view all activity messages
  $permissions['view all activity messages'] = array(
    'name' => 'view all activity messages',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view all private status messages
  $permissions['view all private status messages'] = array(
    'name' => 'view all private status messages',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: view all status comments
  $permissions['view all status comments'] = array(
    'name' => 'view all status comments',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view all statuses
  $permissions['view all statuses'] = array(
    'name' => 'view all statuses',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view own activity messages
  $permissions['view own activity messages'] = array(
    'name' => 'view own activity messages',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view own status comments
  $permissions['view own status comments'] = array(
    'name' => 'view own status comments',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
