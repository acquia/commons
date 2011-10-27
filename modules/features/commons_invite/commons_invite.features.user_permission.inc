<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_invite_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer invitations
  $permissions['administer invitations'] = array(
    'name' => 'administer invitations',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: send invitations
  $permissions['send invitations'] = array(
    'name' => 'send invitations',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: send mass invitations
  $permissions['send mass invitations'] = array(
    'name' => 'send mass invitations',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: track invitations
  $permissions['track invitations'] = array(
    'name' => 'track invitations',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view invite statistics
  $permissions['view invite statistics'] = array(
    'name' => 'view invite statistics',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: view own invite statistics
  $permissions['view own invite statistics'] = array(
    'name' => 'view own invite statistics',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: withdraw accepted invitations
  $permissions['withdraw accepted invitations'] = array(
    'name' => 'withdraw accepted invitations',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  return $permissions;
}
