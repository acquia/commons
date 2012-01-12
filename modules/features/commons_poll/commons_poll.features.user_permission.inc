<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_poll_user_default_permissions() {
  $permissions = array();

  // Exported permission: cancel own vote
  $permissions['cancel own vote'] = array(
    'name' => 'cancel own vote',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create poll content
  $permissions['create poll content'] = array(
    'name' => 'create poll content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete any poll content
  $permissions['delete any poll content'] = array(
    'name' => 'delete any poll content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete own poll content
  $permissions['delete own poll content'] = array(
    'name' => 'delete own poll content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit any poll content
  $permissions['edit any poll content'] = array(
    'name' => 'edit any poll content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit field_poll_body
  $permissions['edit field_poll_body'] = array(
    'name' => 'edit field_poll_body',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit own poll content
  $permissions['edit own poll content'] = array(
    'name' => 'edit own poll content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: inspect all votes
  $permissions['inspect all votes'] = array(
    'name' => 'inspect all votes',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view field_poll_body
  $permissions['view field_poll_body'] = array(
    'name' => 'view field_poll_body',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: vote on polls
  $permissions['vote on polls'] = array(
    'name' => 'vote on polls',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
