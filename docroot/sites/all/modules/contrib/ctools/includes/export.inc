<?php
// $Id: export.inc,v 1.19.2.7 2010/01/29 23:42:12 merlinofchaos Exp $

/**
 * @file
 * Contains code to make it easier to have exportable objects.
 *
 * Documentation for exportable objects is contained in help/export.html
 */

/**
 * A bit flag used to let us know if an object is in the database.
 */
define('EXPORT_IN_DATABASE', 0x01);

/**
 * A bit flag used to let us know if an object is a 'default' in code.
 */
define('EXPORT_IN_CODE', 0x02);

/**
 * Load some number of exportable objects.
 *
 * This function will cache the objects, load subsidiary objects if necessary,
 * check default objects in code and properly set them up. It will cache
 * the results so that multiple calls to load the same objects
 * will not cause problems.
 *
 * It attempts to reduce, as much as possible, the number of queries
 * involved.
 *
 * @param $table
 *   The name of the table to be loaded from. Data is expected to be in the
 *   schema to make all this work.
 * @param $type
 *   A string to notify the loader what the argument is
 *   - all: load all items. This is the default. $args is unused.
 *   - names: $args will be an array of specific named objects to load.
 *   - conditions: $args will be a keyed array of conditions. The conditions
 *       must be in the schema for this table or errors will result.
 * @param $args
 *   An array of arguments whose actual use is defined by the $type argument.
 */
function ctools_export_load_object($table, $type = 'all', $args = array()) {
  $cache = &ctools_static(__FUNCTION__);
  $cached_database = &ctools_static('ctools_export_load_object_all');

  $schema = ctools_export_get_schema($table);
  $export = $schema['export'];

  if (!isset($cache[$table])) {
    $cache[$table] = array();
  }

  // If fetching all and cached all, we've done so and we are finished.
  if ($type == 'all' && !empty($cached_database[$table])) {
    return $cache[$table];
  }

  $return = array();

  // Don't load anything we've already cached.
  if ($type == 'names' && !empty($args)) {
    foreach ($args as $id => $name) {
      if (isset($cache[$table][$name])) {
        $return[$name] = $cache[$table][$name];
        unset($args[$id]);
      }
    }

    // If nothing left to load, return the result.
    if (empty($args)) {
      return $return;
    }
  }

  // Build the query
  $query = "SELECT * FROM {" . $table . "}";
  $conditions = array();
  $query_args = array();

  // If they passed in names, add them to the query.
  if ($type == 'names') {
    $conditions[] = "$export[key] IN (" . db_placeholders($args, $schema['fields'][$export['key']]['type']) . ")";
    $query_args = $args;
  }
  else if ($type == 'conditions') {
    foreach ($args as $key => $value) {
      if (isset($schema['fields'][$key])) {
        $conditions[] = "$key = " . db_type_placeholder($schema['fields'][$key]['type']);
        $query_args[] = $value;
      }
    }
  }

  // Make a string out of the conditions.
  if ($conditions) {
    $query .= " WHERE " . implode(' AND ', $conditions);
  }

  $result = db_query($query, $query_args);

  $status = variable_get($export['status'], array());
  // Unpack the results of the query onto objects and cache them.
  while ($data = db_fetch_object($result)) {
    $object = _ctools_export_unpack_object($schema, $data, $export['object']);
    $object->table = $table;
    $object->type = t('Normal');
    $object->export_type = EXPORT_IN_DATABASE;
    // Determine if default object is enabled or disabled.
    if (isset($status[$object->{$export['key']}])) {
      $object->disabled = $status[$object->{$export['key']}];
    }

    $cache[$table][$object->{$export['key']}] = $object;
    if ($type == 'conditions') {
      $return[$object->{$export['key']}] = $object;
    }
  }

  // @todo Load subrecords.

  if ($defaults = _ctools_export_get_defaults($table, $export)) {

    foreach ($defaults as $object) {
      if ($type == 'conditions') {
        // if this does not match all of our conditions, skip it.
        foreach ($args as $key => $value) {
          if (!isset($object->$key) || $object->$key != $value) {
            continue 2;
          }
        }
      }
      else if ($type == 'names') {
        if (!in_array($object->{$export['key']}, $args)) {
          continue;
        }
      }

      // Determine if default object is enabled or disabled.
      if (isset($status[$object->{$export['key']}])) {
        $object->disabled = $status[$object->{$export['key']}];
      }

      if (!empty($cache[$table][$object->{$export['key']}])) {
        $cache[$table][$object->{$export['key']}]->type = t('Overridden');
        $cache[$table][$object->{$export['key']}]->export_type |= EXPORT_IN_CODE;
        if ($type == 'conditions') {
          $return[$object->{$export['key']}] = $cache[$table][$object->{$export['key']}];
        }
      }
      else {
        $object->type = t('Default');
        $object->export_type = EXPORT_IN_CODE;
        $object->in_code_only = TRUE;
        $object->table = $table;

        $cache[$table][$object->{$export['key']}] = $object;
        if ($type == 'conditions') {
          $return[$object->{$export['key']}] = $object;
        }
      }
    }
  }

  // If fetching all, we've done so and we are finished.
  if ($type == 'all') {
    $cached_database[$table] = TRUE;
    return $cache[$table];
  }

  if ($type == 'names') {
    foreach ($args as $name) {
      if (isset($cache[$table][$name])) {
        $return[$name] = $cache[$table][$name];
      }
    }
  }

  // For conditions,
  return $return;
}

/**
 * Reset all static caches in ctools_export_load_object() or static caches for
 * a given table in ctools_export_load_object().
 *
 * @param $table
 *   String that is the name of a table. If not defined, all static caches in
 *   ctools_export_load_object() will be reset.
 */
function ctools_export_load_object_reset($table = NULL) {
  if (empty($table)) {
    ctools_static_reset('ctools_export_load_object');
    ctools_static_reset('ctools_export_load_object_all');
  }
  else {
    $cache = &ctools_static('ctools_export_load_object');
    $cached_database = &ctools_static('ctools_export_load_object_all');
    unset($cache[$table]);
    unset($cached_database[$table]);
  }
}

/**
 * Get the default version of an object, if it exists.
 *
 * This function doesn't care if an object is in the database or not and
 * does not check. This means that export_type could appear to be incorrect,
 * because a version could exist in the database. However, it's not
 * incorrect for this function as it is *only* used for the default
 * in code version.
 */
function ctools_get_default_object($table, $name) {
  $schema = ctools_export_get_schema($table);
  $export = $schema['export'];

  if (!$export['default hook']) {
    return;
  }

  // @todo add a method to load .inc files for this.
  $defaults = _ctools_export_get_defaults($table, $export);
  $status = variable_get($export['status'], array());

  if (!isset($defaults[$name])) {
    return;
  }

  $object = $defaults[$name];

  // Determine if default object is enabled or disabled.
  if (isset($status[$object->{$export['key']}])) {
    $object->disabled = $status[$object->{$export['key']}];
  }

  $object->type = t('Default');
  $object->export_type = EXPORT_IN_CODE;
  $object->in_code_only = TRUE;

  return $object;
}

/**
 * Call the hook to get all default objects of the given type from the
 * export. If configured properly, this could include loading up an API
 * to get default objects.
 */
function _ctools_export_get_defaults($table, $export) {
  static $cache = array();

  if (!isset($cache[$table])) {
    $cache[$table] = array();

    if ($export['default hook']) {
      if (!empty($export['api'])) {
        ctools_include('plugins');
        $info = ctools_plugin_api_include($export['api']['owner'], $export['api']['api'],
          $export['api']['minimum_version'], $export['api']['current_version']);
        $modules = array_keys($info);
      }
      else {
        $modules = module_implements($export['default hook']);
      }

      foreach ($modules as $module) {
        $function = $module . '_' . $export['default hook'];
        if (function_exists($function)) {
          if (empty($export['api'])) {
            $cache[$table] += (array) $function($export);
          }
          else {
            foreach ((array) $function($export) as $name => $object) {
              // If version checking is enabled, ensure that the object can be used.
              if (isset($object->api_version) &&
                $object->api_version >= $export['api']['minimum_version'] &&
                $object->api_version <= $export['api']['current_version']) {
                $cache[$table][$name] = $object;
              }
            }
          }
        }
      }

      drupal_alter($export['default hook'], $cache[$table]);
    }
  }

  return $cache[$table];
}

/**
 * Unpack data loaded from the database onto an object.
 *
 * @param $schema
 *   The schema from drupal_get_schema().
 * @param $data
 *   The data as loaded by db_fetch_object().
 * @param $object
 *   If an object, data will be unpacked onto it. If a string
 *   an object of that type will be created.
 */
function _ctools_export_unpack_object($schema, $data, $object = 'stdClass') {
  if (is_string($object)) {
    if (class_exists($object)) {
      $object = new $object;
    }
    else {
      $object = new stdClass;
    }
  }

  // Go through our schema and build correlations.
  foreach ($schema['fields'] as $field => $info) {
    $object->$field = empty($info['serialize']) ? $data->$field : unserialize(db_decode_blob($data->$field));
  }

  return $object;
}

/**
 * Unpack data loaded from the database onto an object.
 *
 * @param $table
 *   The name of the table this object represents.
 * @param $data
 *   The data as loaded by db_fetch_object().
 */
function ctools_export_unpack_object($table, $data) {
  $schema = ctools_export_get_schema($table);
  return _ctools_export_unpack_object($schema, $data, $schema['export']['object']);
}

/**
 * Export a field.
 *
 * This is a replacement for var_export(), allowing us to more nicely
 * format exports. It will recurse down into arrays and will try to
 * properly export bools when it can, though PHP has a hard time with
 * this since they often end up as strings or ints.
 */
function ctools_var_export($var, $prefix = '') {
  if (is_array($var)) {
    if (empty($var)) {
      $output = 'array()';
    }
    else {
      $output = "array(\n";
      foreach ($var as $key => $value) {
        $output .= "  '$key' => " . ctools_var_export($value, '  ') . ",\n";
      }
      $output .= ')';
    }
  }
  else if (is_object($var) && get_class($var) === 'stdClass') {
    // var_export() will export stdClass objects using an undefined
    // magic method __set_state() leaving the export broken. This
    // workaround avoids this by casting the object as an array for
    // export and casting it back to an object when evaluated.
    $output .= '(object) ' . ctools_var_export((array) $var);
  }
  else if (is_bool($var)) {
    $output = $var ? 'TRUE' : 'FALSE';
  }
  else {
    $output = var_export($var, TRUE);
  }

  if ($prefix) {
    $output = str_replace("\n", "\n$prefix", $output);
  }

  return $output;
}

/**
 * Export an object into code.
 */
function ctools_export_object($table, $object, $indent = '', $identifier = NULL, $additions = array(), $additions2 = array()) {
  $schema = ctools_export_get_schema($table);
  if (!isset($identifier)) {
    $identifier = $schema['export']['identifier'];
  }

  $output = $indent . '$' . $identifier . ' = new ' . get_class($object) . ";\n";

  if ($schema['export']['can disable']) {
    $output .= $indent . '$' . $identifier . '->disabled = FALSE; /* Edit this to true to make a default ' . $identifier . ' disabled initially */' . "\n";
  }
  if (!empty($schema['export']['api']['current_version'])) {
    $output .= $indent . '$' . $identifier . '->api_version = ' . $schema['export']['api']['current_version'] . ";\n";
  }

  // Put top additions here:
  foreach ($additions as $field => $value) {
    $output .= $indent . '$' . $identifier . '->' . $field . ' = ' . ctools_var_export($value, $indent) . ";\n";
  }

  // Go through our schema and build correlations.
  foreach ($schema['fields'] as $field => $info) {
    if (!empty($info['no export'])) {
      continue;
    }
    if (!isset($object->$field)) {
      if (isset($info['default'])) {
        $object->$field = $info['default'];
      }
      else {
        $object->$field = '';
      }
    }

    if (!empty($info['export callback']) && function_exists($info['export callback'])) {
      $output .= $indent . '$' . $identifier . '->' . $field . ' = ' . $info['export callback']($object, $field, $value, $indent) . ";\n";
    }
    else {
      $value = $object->$field;
      if ($info['type'] == 'int') {
        $value = (isset($info['size']) && $info['size'] == 'tiny') ? (bool) $value : (int) $value;
      }

      $output .= $indent . '$' . $identifier . '->' . $field . ' = ' . ctools_var_export($value, $indent) . ";\n";
    }
  }

  // And bottom additions here
  foreach ($additions2 as $field => $value) {
    $output .= $indent . '$' . $identifier . '->' . $field . ' = ' . ctools_var_export($value, $indent) . ";\n";
  }

  return $output;
}

/**
 * Get the schema for a given table.
 *
 * This looks for data the export subsystem needs and applies defaults so
 * that it's easily available.
 */
function ctools_export_get_schema($table) {
  $schema = drupal_get_schema($table);

  if (!isset($schema['export'])) {
    $schema['export'] = array();
  }

  // Add some defaults
  $schema['export'] += array(
    'key' => 'name',
    'object' => 'stdClass',
    'status' => 'default_' . $table,
    'default hook' => 'default_' . $table,
    'can disable' => TRUE,
    'identifier' => $table,
    'bulk export' => TRUE,
    'export callback' => "$schema[module]_export_{$table}",
    'list callback' => "$schema[module]_{$table}_list",
    'to hook code callback' => "$schema[module]_{$table}_to_hook_code",
  );

  return $schema;
}

/**
 * Gets the schemas for all tables with ctools object metadata.
 */
function ctools_export_get_schemas($for_export = FALSE) {
  static $export_tables;
  if (is_null($export_tables)) {
    $export_tables = array();
    $schemas = drupal_get_schema();
    foreach ($schemas as $table => $schema) {
      if (!isset($schema['export'])) {
        unset($schemas[$table]);
        continue;
      }
      $export_tables[$table] = ctools_export_get_schema($table);
    }
  }
  return $for_export ? array_filter($export_tables, '_ctools_export_filter_export_tables') : $export_tables;
}

function _ctools_export_filter_export_tables($export) {
  return empty($export['bulk export']);
}

function ctools_export_get_schemas_by_module($modules = array(), $for_export = FALSE) {
  $export_tables = array();
  $list = ctools_export_get_schemas($for_export);
  foreach ($list as $table => $schema) {
    $export_tables[$schema['module']][$table] = $schema;
  }
  return empty($modules) ? $export_tables : array_keys($export_tables, $modules);
}

/**
 * Set the status of a default $object as a variable.
 *
 * The status, in this case, is whether or not it is 'disabled'.
 * This function does not check to make sure $object actually
 * exists.
 */
function ctools_export_set_status($table, $name, $new_status = TRUE) {
  $schema = ctools_export_get_schema($table);
  $status = variable_get($schema['export']['status'], array());

  $status[$name] = $new_status;
  variable_set($schema['export']['status'], $status);
}

/**
 * Set the status of a default $object as a variable.
 *
 * This is more efficient than ctools_export_set_status because it
 * will actually unset the variable entirely if it's not necessary,
 * this saving a bit of space.
 */
function ctools_export_set_object_status($object, $new_status = TRUE) {
  $table = $object->table;
  $schema = ctools_export_get_schema($table);
  $export = $schema['export'];
  $status = variable_get($schema['export']['status'], array());

  // Compare
  if (!$new_status && $object->export_type & EXPORT_IN_DATABASE) {
    unset($status[$object->{$export['key']}]);
  }
  else {
    $status[$object->{$export['key']}] = $new_status;
  }

  variable_set($schema['export']['status'], $status);
}

/**
 * Provide a form for displaying an export.
 *
 * This is a simple form that should be invoked like this:
 * @code
 *   $output = drupal_get_form('ctools_export_form', $code, $object_title);
 * @endcode
 */
function ctools_export_form(&$form_state, $code, $title = '') {
  $lines = substr_count($code, "\n");
  $form['code'] = array(
    '#type' => 'textarea',
    '#title' => $title,
    '#default_value' => $code,
    '#rows' => $lines,
  );

  return $form;
}

/**
 * Create a new object based upon schema values.
 *
 * Because 'default' has ambiguous meaning on some fields, we will actually
 * use 'object default' to fill in default values if default is not set
 * That's a little safer to use as it won't cause weird database default situations.
 */
function ctools_export_new_object($table, $set_defaults = TRUE) {
  $schema = ctools_export_get_schema($table);
  $export = $schema['export'];

  $object = new $export['object'];
  foreach ($schema['fields'] as $field => $info) {
    if (isset($info['object default'])) {
      $object->$field = $info['object default'];
    }
    else if (isset($info['default'])) {
      $object->$field = $info['default'];
    }
    else {
      $object->$field = NULL;
    }
  }

  if ($set_defaults) {
    // Set some defaults so this data always exists.
    $object->export_type = EXPORT_IN_DATABASE;
    $object->type = t('Local');
  }
  return $object;
}

/**
 * Convert a group of objects to code based upon input and return this as a larger
 * export.
 */
function ctools_export_to_hook_code(&$code, $table, $names = array(), $name = 'foo') {
  $schema = ctools_export_get_schema($table);
  $export = $schema['export'];
  // Use the schema-specified function for generating hook code, if one exists
  if (function_exists($export['to hook code callback'])) {
    $output = $export['to hook code callback']($names, $name);
  }
  // Otherwise, the following code generates basic hook code
  else {
    $objects = ctools_export_load_object($table, 'names', $names);
    if ($objects) {
      $output = "/**\n";
      $output .= " * Implementation of hook_{$export['default hook']}()\n";
      $output .= " */\n";
      $output .= "function " . $name . "_{$export['default hook']}() {\n";
      $output .= "  \${$export['identifier']}s = array();\n\n";
      foreach ($objects as $object) {
        $output .= $export['export callback']($object, '  '); // if this function does not exist, better to error out than fail silently
        $output .= "  \${$export['identifier']}s['" . check_plain($object->$export['key']) . "'] = \${$export['identifier']};\n\n";
      }
      $output .= "  return \${$export['identifier']}s;\n";
      $output .= "}\n";
    }
  }

  if (!empty($output)) {
    if (isset($export['api'])) {
      if (isset($code[$export['api']['owner']][$export['api']['api']]['version'])) {
        $code[$export['api']['owner']][$export['api']['api']]['version'] = max($code[$export['api']['owner']][$export['api']['api']]['version'], $export['api']['minimum_version']);
      }
      else {
        $code[$export['api']['owner']][$export['api']['api']]['version'] = $export['api']['minimum_version'];
        $code[$export['api']['owner']][$export['api']['api']]['code'] = '';
      }
      $code[$export['api']['owner']][$export['api']['api']]['code'] .= $output;
    }
    else {
      if (empty($code['general'])) {
        $code['general'] = '';
      }
      $code['general'] .= $output;
    }
  }
}
