<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_group_aggregator_user_default_permissions() {
  $permissions = array();

  // Exported permission: access news feeds
  $permissions['access news feeds'] = array(
    'name' => 'access news feeds',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: administer news feeds
  $permissions['administer news feeds'] = array(
    'name' => 'administer news feeds',
    'roles' => array(),
  );

  return $permissions;
}
