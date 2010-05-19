<?php
// $Id: features.user.inc,v 1.1.2.11 2010/02/07 04:45:22 yhahn Exp $

/**
 * Implementation of hook_features_api().
 */
function user_features_api() {
  return array(
    'user' => array(
      'name' => t('Permissions'),
      'feature_source' => TRUE,
      'default_hook' => 'user_default_permissions',
    )
  );
}

/**
 * Implementation of hook_features_export().
 */
function user_features_export($data, &$export, $module_name = '') {
  // The default_permissions() hook integration is provided by the
  // features module so we need to add it as a dependency.
  $export['dependencies']['features'] = 'features';

  // Ensure the modules that provide the given permissions are included as dependencies.
  $map = _user_features_permission_map();
  foreach ($data as $perm) {
    if (isset($map[$perm])) {
      $perm_module = $map[$perm];
      $export['dependencies'][$perm_module] = $perm_module;
      $export['features']['user'][$perm] = $perm;
    }
  }

  $pipe = array();
  return $pipe;
}

/**
 * Implementation of hook_features_export_options().
 */
function user_features_export_options() {
  $options = array();
  foreach (module_list() as $module) {
    $prefix = check_plain($module) .': ';
    if ($permissions = module_invoke($module, 'perm')) {
      foreach ($permissions as $permission) {
        $options[$permission] = $prefix . check_plain($permission);
      }
    }
  }
  asort($options);
  return $options;
}

/**
 * Implementation of hook_features_export_render().
 */
function user_features_export_render($module = 'foo', $data) {
  $code = array();
  $code[] = '  $permissions = array();';
  $code[] = '';

  $permissions = _user_features_get_permissions();

  foreach ($data as $perm_name) {
    $permission = array();
    $permission['name'] = $perm_name;
    if (isset($permissions[$perm_name])) {
      sort($permissions[$perm_name]);
      $permission['roles'] = $permissions[$perm_name];
    }
    else {
      $permission['roles'] = array();
    }

    $code[] = '  // Exported permission: '. $perm_name;
    $code[] = '  $permissions[] = '. features_var_export($permission, '  ') .';';
    $code[] = '';
  }

  $code[] = '  return $permissions;';
  $code = implode("\n", $code);
  return array('user_default_permissions' => $code);
}

/**
 * Implementation of hook_features_revert().
 */
function user_features_revert($module) {
  user_features_rebuild($module);
}

/**
 * Implementation of hook_features_rebuild().
 * Iterate through default permissions and update the permissions map.
 *
 * @param $module
 *   The module whose default user permissions should be rebuilt.
 */
function user_features_rebuild($module) {
  $defaults = module_invoke($module, 'user_default_permissions');
  if (!empty($defaults)) {
    $roles = _features_get_roles();
    foreach ($defaults as $permission) {
      $perm = $permission['name'];

      // Add permissions for any roles that should have them.
      foreach ($permission['roles'] as $role) {
        // Ensure that each role exists. If it does not, create it and store the rid.
        if (!isset($roles[$role])) {
          $record = array('name' => $role);
          drupal_write_record('role', $record);
          $roles[$role] = array(
            'rid' => $record['rid'],
            'perm' => array(),
          );
        }
        if (!in_array($perm, $roles[$role]['perm'])) {
          $roles[$role]['perm'][] = $perm;
        }
      }

      // Remove permissions for any roles that shouldn't have them.
      foreach (array_keys($roles) as $role) {
        if (in_array($perm, $roles[$role]['perm']) && !in_array($role, $permission['roles'])) {
          $position = array_search($perm, $roles[$role]['perm']);
          unset($roles[$role]['perm'][$position]);
        }
      }
    }
    // Write the updated permissions.
    _user_features_save_roles($roles);
  }
}

/**
 * Generate a perm to module mapping.
 */
function _user_features_permission_map($reset = FALSE) {
  static $map;
  if (!isset($map) || $reset) {
    $map = array();
    foreach (module_implements('perm') as $module) {
      if ($permissions = module_invoke($module, 'perm')) {
        foreach ($permissions as $permission) {
          $map[$permission] = $module;
        }
      }
    }
  }
  return $map;
}

/**
 * Represent the current state of permissions as a perm to role name array map.
 */
function _user_features_get_permissions() {
  $result = db_query("SELECT p.perm, r.name FROM {role} r INNER JOIN {permission} p ON p.rid = r.rid ORDER BY r.rid ASC, p.perm ASC");
  $permissions = array();
  while ($row = db_fetch_object($result)) {
    $role = $row->name;
    $role_perms = explode(', ', $row->perm);
    foreach ($role_perms as $perm) {
      if (!isset($permissions[$perm])) {
        $permissions[$perm] = array();
      }
      if(!in_array($role, $permissions[$perm])) {
        $permissions[$perm][] = $role;
      }
    }
  }
  return $permissions;
}

/**
 * Save/update an array of roles to the database.
 */
function _user_features_save_roles($roles) {
  // Write the updated permissions.
  foreach ($roles as $role) {
    db_query("DELETE FROM {permission} WHERE rid = %d", $role['rid']);
    $role['perm'] = implode(', ', $role['perm']);
    drupal_write_record('permission', $role);
  }
}
