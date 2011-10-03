<?php

/**
 * Implementation of hook_user_default_roles().
 */
function commons_core_user_default_roles() {
  $roles = array();

  // Exported role: community manager
  $roles['community manager'] = array(
    'name' => 'community manager',
  );

  // Exported role: content manager
  $roles['content manager'] = array(
    'name' => 'content manager',
  );

  // Exported role: site admin
  $roles['site admin'] = array(
    'name' => 'site admin',
  );

  return $roles;
}
