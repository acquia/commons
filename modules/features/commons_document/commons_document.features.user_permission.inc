<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_document_user_default_permissions() {
  $permissions = array();

  // Exported permission: create document content
  $permissions['create document content'] = array(
    'name' => 'create document content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete any document content
  $permissions['delete any document content'] = array(
    'name' => 'delete any document content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete own document content
  $permissions['delete own document content'] = array(
    'name' => 'delete own document content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit any document content
  $permissions['edit any document content'] = array(
    'name' => 'edit any document content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit field_file
  $permissions['edit field_file'] = array(
    'name' => 'edit field_file',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit own document content
  $permissions['edit own document content'] = array(
    'name' => 'edit own document content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view field_file
  $permissions['view field_file'] = array(
    'name' => 'view field_file',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  return $permissions;
}
