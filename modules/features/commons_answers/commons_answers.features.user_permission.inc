<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_answers_user_default_permissions() {
  $permissions = array();

  // Exported permission: access vote up/down statistics
  $permissions['access vote up/down statistics'] = array(
    'name' => 'access vote up/down statistics',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
      '2' => 'site admin',
    ),
  );

  // Exported permission: administer vote up/down
  $permissions['administer vote up/down'] = array(
    'name' => 'administer vote up/down',
    'roles' => array(),
  );

  // Exported permission: administer vote up/down on nodes
  $permissions['administer vote up/down on nodes'] = array(
    'name' => 'administer vote up/down on nodes',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
      '2' => 'site admin',
    ),
  );

  // Exported permission: create answer content
  $permissions['create answer content'] = array(
    'name' => 'create answer content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create question content
  $permissions['create question content'] = array(
    'name' => 'create question content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete any answer content
  $permissions['delete any answer content'] = array(
    'name' => 'delete any answer content',
    'roles' => array(
      '0' => 'content manager',
    ),
  );

  // Exported permission: delete any question content
  $permissions['delete any question content'] = array(
    'name' => 'delete any question content',
    'roles' => array(
      '0' => 'content manager',
    ),
  );

  // Exported permission: edit any answer content
  $permissions['edit any answer content'] = array(
    'name' => 'edit any answer content',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
    ),
  );

  // Exported permission: edit any question content
  $permissions['edit any question content'] = array(
    'name' => 'edit any question content',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
    ),
  );

  // Exported permission: reset vote up/down votes
  $permissions['reset vote up/down votes'] = array(
    'name' => 'reset vote up/down votes',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: see vote up/down node stats
  $permissions['see vote up/down node stats'] = array(
    'name' => 'see vote up/down node stats',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'community manager',
      '3' => 'content manager',
      '4' => 'site admin',
    ),
  );

  // Exported permission: use vote up/down
  $permissions['use vote up/down'] = array(
    'name' => 'use vote up/down',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: use vote up/down on nodes
  $permissions['use vote up/down on nodes'] = array(
    'name' => 'use vote up/down on nodes',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view field_answer_count
  $permissions['view field_answer_count'] = array(
    'name' => 'view field_answer_count',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_answer_question
  $permissions['view field_answer_question'] = array(
    'name' => 'view field_answer_question',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view vote up/down count on nodes
  $permissions['view vote up/down count on nodes'] = array(
    'name' => 'view vote up/down count on nodes',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  return $permissions;
}
