<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_event_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer date tools
  $permissions['administer date tools'] = array(
    'name' => 'administer date tools',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: create event content
  $permissions['create event content'] = array(
    'name' => 'create event content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete any event content
  $permissions['delete any event content'] = array(
    'name' => 'delete any event content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete own event content
  $permissions['delete own event content'] = array(
    'name' => 'delete own event content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit any event content
  $permissions['edit any event content'] = array(
    'name' => 'edit any event content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit field_date
  $permissions['edit field_date'] = array(
    'name' => 'edit field_date',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'site admin',
    ),
  );

  // Exported permission: edit field_location
  $permissions['edit field_location'] = array(
    'name' => 'edit field_location',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'site admin',
    ),
  );

  // Exported permission: edit own event content
  $permissions['edit own event content'] = array(
    'name' => 'edit own event content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view field_date
  $permissions['view field_date'] = array(
    'name' => 'view field_date',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'site admin',
    ),
  );

  // Exported permission: view field_location
  $permissions['view field_location'] = array(
    'name' => 'view field_location',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'site admin',
    ),
  );

  return $permissions;
}
