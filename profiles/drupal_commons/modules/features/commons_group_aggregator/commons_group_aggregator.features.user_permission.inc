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

  // Exported permission: access og_aggregator
  $permissions['access og_aggregator'] = array(
    'name' => 'access og_aggregator',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: administer news feeds
  $permissions['administer news feeds'] = array(
    'name' => 'administer news feeds',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer og_aggregator
  $permissions['administer og_aggregator'] = array(
    'name' => 'administer og_aggregator',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: view all og_aggregator sources
  $permissions['view all og_aggregator sources'] = array(
    'name' => 'view all og_aggregator sources',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  return $permissions;
}
