<?php
// $Id: features.export.inc,v 1.1.2.47 2010/02/02 16:21:34 yhahn Exp $

/**
 * @param $items
 * @param $module_name
 * @return
 */
function features_populate($items, $module_name) {
  // Sanitize items.
  $items = array_filter($items);

  // Populate stub
  $stub = array('features' => array(), 'dependencies' => array(), 'conflicts' => array());
  $export = _features_populate($items, $stub, $module_name);
  $export['dependencies'] = _features_export_minimize_dependencies($export['dependencies'], $module_name);

  // Clean up and standardize order
  foreach (array_keys($export['features']) as $k) {
    ksort($export['features'][$k]);
  }
  ksort($export['features']);
  ksort($export['dependencies']);

  return $export;
}

/**
 * Iterate and descend into a feature definition to extract module
 * dependencies and feature definition. Calls hook_features_export for modules
 * that implement it.
 *
 * @param $pipe
 *  Associative of array of module => info-for-module
 * @param $export
 *  Associative array of items, and module dependencies which define a feature.
 *  Passed by reference.
 *
 * @return fully populated $export array.
 */
function _features_populate($pipe, &$export, $module_name = '') {
  features_include();
  foreach ($pipe as $component => $data) {
    if (features_hook($component, 'features_export')) {
      // Pass module-specific data and export array.
      // We don't use features_invoke() here since we need to pass $export by reference.
      $function = "{$component}_features_export";
      $more = $function($data, $export, $module_name);
      // Allow for export functions to request additional exports.
      if (!empty($more)) {
        _features_populate($more, $export, $module_name);
      }
    }
  }
  return $export;
}

/**
 * Iterates over a list of dependencies and kills modules that are
 * captured by other modules 'higher up'.
 */
function _features_export_minimize_dependencies($dependencies, $module_name = '') {
  // Ensure that the module doesn't depend upon itself
  if (!empty($module_name) && !empty($dependencies[$module_name])) {
    unset($dependencies[$module_name]);
  }

  // Do some cleanup:
  // - Remove modules required by Drupal core.
  // - Protect against direct circular dependencies.
  // - Remove "intermediate" dependencies.
  $required = drupal_required_modules();
  foreach ($dependencies as $k => $v) {
    if (empty($v) || in_array($v, $required)) {
      unset($dependencies[$k]);
    }
    else {
      $module = features_get_modules($v);
      if ($module && !empty($module->info['dependencies'])) {
        // If this dependency depends on the module itself, we have a circular dependency.
        // Don't let it happen. Only you can prevent forest fires.
        if (in_array($module_name, $module->info['dependencies'])) {
          unset($dependencies[$k]);
        }
        // Iterate through the dependency's dependencies and remove any dependencies
        // that are captured by it.
        else {
          foreach ($module->info['dependencies'] as $j => $dependency) {
            if (array_search($dependency, $dependencies) !== FALSE) {
              $position = array_search($dependency, $dependencies);
              unset($dependencies[$position]);
            }
          }
        }
      }
    }
  }
  return drupal_map_assoc(array_unique($dependencies));
}

/**
 * Iterates over a list of dependencies and maximize the list of modules.
 */
function _features_export_maximize_dependencies($dependencies, $module_name = '', $first = TRUE) {
  $maximized = $dependencies;
  foreach ($dependencies as $k => $v) {
    $module = features_get_modules($v);
    if ($module && !empty($module->info['dependencies'])) {
      $maximized = array_merge($maximized, _features_export_maximize_dependencies($module->info['dependencies'], $module_name, FALSE));
    }
  }
  return array_unique($maximized);
}

/**
 * Preserve existing dependencies.
 */
function _features_export_preserve_dependencies($dependencies, $module_name = NULL, $existing = array()) {
  if (!empty($module_name)) {
    $feature = feature_load($module_name);
    $existing = !empty($feature->info['dependencies']) ? $feature->info['dependencies'] : array();
  }
  $merged = array_merge($existing, $dependencies);
  $merged = array_unique($merged);
  ksort($merged);
  return $merged;
}

/**
 * Prepare a feature export array into a finalized info array.
 */
function features_export_prepare($export, $module_name, $reset = FALSE) {
  $existing = features_get_modules($module_name, $reset);

  // Prepare info string -- if module exists, merge into its existing info file
  $defaults = $existing ? $existing->info : array('core' => '6.x', 'package' => 'Features', 'project' => $module_name);
  $export = array_merge($defaults, $export);

  // Cleanup info array
  foreach ($export['features'] as $component => $data) {
    $export['features'][$component] = array_keys($data);
  }
  if (isset($export['dependencies'])) {
    $export['dependencies'] = array_values($export['dependencies']);
  }
  if (isset($export['conflicts'])) {
    unset($export['conflicts']);
  }
  ksort($export);
  return $export;
}

/**
 * Generate an array of hooks and their raw code.
 */
function features_export_render_hooks($export, $module_name, $reset = FALSE) {
  features_include();
  $code = array();

  // Sort components to keep exported code consistent
  ksort($export['features']);

  foreach ($export['features'] as $component => $data) {
    if (!empty($data)) {
      // Sort the items so that we don't generate different exports based on order
      asort($data);
      if (features_hook($component, 'features_export_render')) {
        $hooks = features_invoke($component, 'features_export_render', $module_name, $data, $export);
        $code[$component] = $hooks;
      }
    }
  }
  return $code;
}

/**
 * Render feature export into an array representing its files.
 *
 * @param $export
 *  An exported feature definition.
 * @param $module_name
 *  The name of the module to be exported.
 * @param $reset
 *  Boolean flag for resetting the module cache. Only set to true when
 *  doing a final export for delivery.
 *
 * @return array of info file and module file contents.
 */
function features_export_render($export, $module_name, $reset = FALSE) {
  $code = array();

  // Generate hook code
  $component_hooks = features_export_render_hooks($export, $module_name, $reset);
  $components = features_get_components();

  // Group component code into their respective files
  foreach ($component_hooks as $component => $hooks) {
    $file = array('name' => 'defaults', 'stub' => true);
    if (isset($components[$component]['default_file'])) {
      switch ($components[$component]['default_file']) {
        case FEATURES_DEFAULTS_INCLUDED:
          $file['name'] = "features.$component";
          break;
        case FEATURES_DEFAULTS_CUSTOM:
          $file['name'] = $components[$component]['default_filename'];
          $file['stub'] = false;
          break;
      }
    }

    if (!isset($code[$file['name']])) {
      $code[$file['name']] = array();
    }

    foreach ($hooks as $hook_name => $hook_code) {
      if ($file['stub']) {
        if (!isset($code['features'])) {
          $code['features'] = array();
        }
        $code['features'][$hook_name] = features_export_render_features($module_name, $hook_name, $file['name']);
      }
      $code[$file['name']][$hook_name] = features_export_render_defaults($module_name, $hook_name, $hook_code);
    }
  }

  // Finalize strings to be written to files
  foreach ($code as $filename => $contents) {
    $code[$filename] = "<?php\n\n". implode("\n\n", $contents) ."\n";
  }

  // Generate info file output
  $export = features_export_prepare($export, $module_name, $reset);
  $code['info'] = features_export_info($export);

  // Prepare the module
  // If module exists, let it be and include it in the files
  $existing = features_get_modules($module_name, TRUE);
  if ($existing) {
    $code['module'] = file_get_contents($existing->filename);
  }
  // Add a stub module to include the defaults
  else if (!empty($code['features'])) {
    $code['module'] = "<?php\n\ninclude_once('{$module_name}.features.inc');\n";
  }
  return $code;
}

/**
 * Detect differences between DB and code components of a feature.
 */
function features_detect_overrides($module) {
  static $cache;
  if (!isset($cache)) {
    $cache = array();
  }
  if (!isset($cache[$module->name])) {
    // Make necessary inclusions
    if (module_exists('views')) {
      views_include('view');
    }

    // Rebuild feature from .info file description and prepare an export from current DB state.
    $export = features_populate($module->info['features'], $module->name);
    $export['dependencies'] = _features_export_preserve_dependencies($export['dependencies'], $module->name);
    $export = features_export_prepare($export, $module->name);

    $overridden = array();

    // Compare feature info
    _features_sanitize($module->info);
    _features_sanitize($export);

    $compare = array('normal' => features_export_info($export), 'default' => features_export_info($module->info));
    if ($compare['normal'] !== $compare['default']) {
      $overridden['info'] = $compare;
    }

    // Collect differences at a per-component level
    $states = features_get_component_states(array($module->name), FALSE);
    foreach ($states[$module->name] as $component => $state) {
      if ($state != FEATURES_DEFAULT) {
        $normal = features_get_normal($module->name, $component);
        $default = features_get_default($module->name, $component);
        _features_sanitize($normal);
        _features_sanitize($default);

        $compare = array('normal' => features_var_export($normal), 'default' => features_var_export($default));
        if (_features_linetrim($compare['normal']) !== _features_linetrim($compare['default'])) {
          $overridden[$component] = $compare;
        }
      }
    }
    $cache[$module->name] = $overridden;
  }
  return $cache[$module->name];
}

/**
 * Gets the available default hooks keyed by components.
 */
function features_get_default_hooks() {
  static $hooks;
  if (!isset($hooks)) {
    $hooks = array();
    features_include();
    foreach (module_implements('features_api') as $module) {
      $info = module_invoke($module, 'features_api');
      foreach ($info as $k => $v) {
        if (isset($v['default_hook'])) {
          $hooks[$k] = $v['default_hook'];
        }
      }
    }
  }
  return $hooks;
}

/**
 * Return a code string representing an implementation of a module hook.
 * Includes the module's defaults .inc and calls the private helper function.
 *
 * @param $module
 *   The name of the module being generated
 * @param $hook
 *   The name of the hook, without the "hook_" prefix. "hook_node_info" should
 *   be "node_info"
 * @param $filename
 *   Name of the include file. For a module 'foo', and filename'defaults'
 *   becomes 'foo.defaults.inc'.
 */
function features_export_render_features($module, $hook, $filename = 'defaults') {
  $output = array();
  $output[] = "/**";
  $output[] = " * Implementation of hook_{$hook}().";
  $output[] = " */";
  $output[] = "function {$module}_{$hook}() {";
  $output[] = "  module_load_include('inc', '{$module}', '{$module}.{$filename}');";
  $output[] = '  $args = func_get_args();';
  $output[] = "  return call_user_func_array('_{$module}_{$hook}', ".'$args'.");";
  $output[] = "}";
  return implode("\n", $output);
}

/**
 * Return a code string representing an implementation of a defaults module hook.
 */
function features_export_render_defaults($module, $hook, $code) {
  $output = array();
  $output[] = "/**";
  $output[] = " * Helper to implementation of hook_{$hook}().";
  $output[] = " */";
  $output[] = "function _{$module}_{$hook}() {";
  $output[] = $code;
  $output[] = "}";
  return implode("\n", $output);
}

/**
 * Generate code friendly to the Drupal .info format from a structured array.
 *
 * @param $info
 *   An array or single value to put in a module's .info file.
 * @param $parents
 *   Array of parent keys (internal use only).
 *
 * @return
 *   A code string ready to be written to a module's .info file.
 */
function features_export_info($info, $parents = array()) {
  $output = '';
  if (is_array($info)) {
    foreach ($info as $k => $v) {
      $child = $parents;
      $child[] = $k;
      $output .= features_export_info($v, $child);
    }
  }
  else if (!empty($info) && count($parents)) {
    $line = array_shift($parents);
    foreach ($parents as $key) {
      $line .= is_numeric($key) ? "[]" : "[{$key}]";
    }
    $line .=  " = \"{$info}\"\n";
    return $line;
  }
  return $output;
}

/**
 * Tar creation function. Written by dmitrig01.
 *
 * @param $files
 *   A keyed array where the key is the filepath and the value is the
 *   string contents of the file.
 *
 * @return
 *   A string of the tar file contents.
 */
function features_tar_create($files) {
  $tar = '';
  foreach ($files as $name => $contents) {
    $binary_data_first = pack("a100a8a8a8a12A12",
      $name,
      '100644 ', // File permissions
      '   765 ', // UID,
      '   765 ', // GID,
      sprintf("%11s ", decoct(strlen($contents))), // Filesize,
      sprintf("%11s", decoct(time())) // Creation time
    );
    $binary_data_last = pack("a1a100a6a2a32a32a8a8a155a12", '', '', '', '', '', '', '', '', '', '');

    $checksum = 0;
    for ($i = 0; $i < 148; $i++) {
      $checksum += ord(substr($binary_data_first, $i, 1));
    }
    for ($i = 148; $i < 156; $i++) {
      $checksum += ord(' ');
    }
    for ($i = 156, $j = 0; $i < 512; $i++, $j++) {
      $checksum += ord(substr($binary_data_last, $j, 1));
    }

    $tar .= $binary_data_first;
    $tar .= pack("a8", sprintf("%6s ", decoct($checksum)));
    $tar .= $binary_data_last;

    $buffer = str_split($contents, 512);
    foreach ($buffer as $item) {
      $tar .= pack("a512", $item);
    }
  }
  if (function_exists('gzencode')) {
    $tar = gzencode($tar);
  }
  return $tar;
}

/**
 * Export var function -- from Views.
 */
function features_var_export($var, $prefix = '', $init = TRUE) {
  if (is_object($var)) {
    $output = method_exists($var, 'export') ? $var->export() : features_var_export((array) $var);
  }
  else if (is_array($var)) {
    if (empty($var)) {
      $output = 'array()';
    }
    else {
      $output = "array(\n";
      foreach ($var as $key => $value) {
        $output .= "  '$key' => " . features_var_export($value, '  ', FALSE) . ",\n";
      }
      $output .= ')';
    }
  }
  else if (is_bool($var)) {
    $output = $var ? 'TRUE' : 'FALSE';
  }
  else if (is_string($var) && strpos($var, "\n") !== FALSE) {
    // Replace line breaks in strings with a token for replacement
    // at the very end. This protects whitespace in strings from
    // unintentional indentation.
    $var = str_replace("\n", "***BREAK***", $var);
    $output = var_export($var, TRUE);
  }
  else {
    $output = var_export($var, TRUE);
  }

  if ($prefix) {
    $output = str_replace("\n", "\n$prefix", $output);
  }

  if ($init) {
    $output = str_replace("***BREAK***", "\n", $output);
  }

  return $output;
}

/**
 * Helper function to return an array of t()'d translatables strings.
 * Useful for providing a separate array of translatables with your
 * export so that string extractors like potx can detect them.
 */
function features_translatables_export($translatables, $prefix = '') {
  sort($translatables);
  $translatables = array_unique($translatables);

  $output = $prefix . "// Translatables\n";
  $output .= $prefix . "array(\n";
  foreach ($translatables as $string) {
    $output .= $prefix . "  t('" . strtr($string, array("'" => "\'")) . "'),\n";
  }
  $output .= $prefix . ");\n";
  return $output;
}

/**
 * Get a summary storage state for a feature.
 */
function features_get_storage($module_name) {
  // Get component states, and array_diff against array(FEATURES_DEFAULT).
  // If the returned array has any states that don't match FEATURES_DEFAULT,
  // return the highest state.
  $states = features_get_component_states(array($module_name), FALSE);
  $states = array_diff($states[$module_name], array(FEATURES_DEFAULT));
  $storage = !empty($states) ? max($states) : FEATURES_DEFAULT;
  return $storage;
}

/**
 * Wrapper around features_get_[storage] to return an md5hash of a normalized
 * defaults/normal object array. Can be used to compare normal/default states
 * of a module's component.
 */
function features_get_signature($state = 'default', $module_name, $component, $reset = FALSE) {
  switch ($state) {
    case 'cache':
      $codecache = variable_get('features_codecache', array());
      return isset($codecache[$module_name][$component]) ? $codecache[$module_name][$component] : FALSE;
    case 'default':
      $objects = features_get_default($module_name, $component, $reset);
      break;
    case 'normal':
      $objects = features_get_normal($module_name, $component, $reset);
      break;
  }
  if (!empty($objects)) {
    $objects = (array) $objects;
    _features_sanitize($objects);
    return md5(_features_linetrim(features_var_export($objects)));
  }
  return FALSE;
}

/**
 * Set the signature of a module/component pair in the codecache.
 */
function features_set_signature($module, $component, $signature = NULL) {
  $var_codecache = variable_get('features_codecache', array());
  $signature = isset($signature) ? $signature : features_get_signature('default', $module, $component, TRUE);
  $var_codecache[$module][$component] = $signature;
  variable_set('features_codecache', $var_codecache);
}

/**
 * Processing semaphore operations.
 */
function features_semaphore($op, $component) {
  // Note: we don't use variable_get() here as the inited variable
  // static cache may be stale. Retrieving directly from the DB narrows
  // the possibility of collision.
  $semaphore = db_result(db_query("SELECT value FROM {variable} WHERE name = 'features_semaphore'"));
  $semaphore = !empty($semaphore) ? unserialize($semaphore) : array();

  switch ($op) {
    case 'get':
      return isset($semaphore[$component]) ? $semaphore[$component] : FALSE;
    case 'set':
      $semaphore[$component] = time();
      variable_set('features_semaphore', $semaphore);
      break;
    case 'del':
      if (isset($semaphore[$component])) {
        unset($semaphore[$component]);
        variable_set('features_semaphore', $semaphore);
      }
      break;
  }
}

/**
 * Get normal objects for a given module/component pair.
 */
function features_get_normal($module_name, $component, $reset = FALSE) {
  static $cache;
  if (!isset($cache) || $reset) {
    $cache = array();
  }
  if (!isset($cache[$module_name][$component])) {
    features_include();
    $default_hooks = features_get_default_hooks();

    $module = features_get_features($module_name);
    $export = $module->info;
    if ($module && isset($module->info['features'][$component]) && features_hook($component, 'features_export_render') && $default_hook = $default_hooks[$component]) {
      $code = features_invoke($component, 'features_export_render', $module_name, $module->info['features'][$component], $export);
      $cache[$module_name][$component] = isset($code[$default_hook]) ? eval($code[$default_hook]) : FALSE;
    }

    // Clear out vars for memory's sake.
    unset($code);
    unset($module);
  }
  return isset($cache[$module_name][$component]) ? $cache[$module_name][$component] : FALSE;
}

/**
 * Get defaults for a given module/component pair.
 */
function features_get_default($module_name, $component, $reset = FALSE) {
  static $cache;
  if (!isset($cache) || $reset) {
    $cache = array();
  }
  if (!isset($cache[$module_name][$component])) {
    features_include();
    $default_hooks = features_get_default_hooks();
    if (isset($default_hooks[$component]) && module_hook($module_name, $default_hooks[$component])) {
      $cache[$module_name][$component] = module_invoke($module_name, $default_hooks[$component]);
    }
    else {
      $cache[$module_name][$component] = FALSE;
    }
  }
  return isset($cache[$module_name][$component]) ? $cache[$module_name][$component] : FALSE;
}

/**
 * Retrieve an array of features/components and their current states.
 */
function features_get_component_states($features = array(), $rebuild_only = TRUE, $reset = FALSE) {
  static $cache;
  if (!isset($cache) || $reset) {
    $cache = array();
  }

  $features = !empty($features) ? $features : array_keys(features_get_features(NULL, TRUE));

  // Retrieve only rebuildable components if requested.
  features_include();
  $components = array_keys(features_get_components());
  if ($rebuild_only) {
    foreach ($components as $k => $component) {
      if (!features_hook($component, 'features_rebuild')) {
        unset($components[$k]);
      }
    }
  }

  foreach ($features as $feature) {
    $cache[$feature] = isset($cache[$feature]) ? $cache[$feature] : array();
    if (module_exists($feature)) {
      foreach ($components as $component) {
        if (!isset($cache[$feature][$component])) {
          $normal = features_get_signature('normal', $feature, $component, $reset);
          $default = features_get_signature('default', $feature, $component, $reset);
          $codecache = features_get_signature('cache', $feature, $component, $reset);
          $semaphore = features_semaphore('get', $component);

          // DB and code states match, there is nothing more to check.
          if ($normal == $default) {
            $cache[$feature][$component] = FEATURES_DEFAULT;

            // Stale semaphores can be deleted.
            features_semaphore('del', $component);

            // Update code cache if it is stale, clear out semaphore if it stale.
            if ($default != $codecache) {
              features_set_signature($feature, $component, $default);
            }
          }
          // Component properly implements exportables.
          else if (!features_hook($component, 'features_rebuild')) {
            $cache[$feature][$component] = FEATURES_OVERRIDDEN;
          }
          // Component does not implement exportables.
          else {
            if (empty($semaphore)) {
              // Code has not changed, but DB does not match. User has DB overrides.
              if ($codecache == $default) {
                $cache[$feature][$component] = FEATURES_OVERRIDDEN;
              }
              // DB has no modifications to prior code state (or this is initial install).
              else if ($codecache == $normal || empty($codecache)) {
                $cache[$feature][$component] = FEATURES_REBUILDABLE;
              }
              // None of the states match. Requires user intervention.
              else if ($codecache != $default) {
                $cache[$feature][$component] = FEATURES_NEEDS_REVIEW;
              }
            }
            else {
              // Semaphore is still within processing horizon. Do nothing.
              if ((time() - $semaphore) < FEATURES_SEMAPHORE_TIMEOUT) {
                $cache[$feature][$component] = FEATURES_REBUILDING;
              }
              // A stale semaphore means a previous rebuild attempt did not complete.
              // Attempt to complete the rebuild.
              else {
                $cache[$feature][$component] = FEATURES_REBUILDABLE;
              }
            }
          }
        }
      }
    }
  }

  // Filter cached components on the way out to ensure that even if we have
  // cached more data than has been requested, the return value only reflects
  // the requested features/components.
  $return = $cache;
  $return = array_intersect_key($return, array_flip($features));
  foreach ($return as $k => $v) {
    $return[$k] = array_intersect_key($return[$k], array_flip($components));
  }
  return $return;
}

/**
 * Helper function to eliminate whitespace differences in code.
 */
function _features_linetrim($code) {
  $code = explode("\n", $code);
  foreach ($code as $k => $line) {
    $code[$k] = trim($line);
  }
  return implode("\n", $code);
}

/**
 * "Sanitizes" an array recursively, performing two key operations:
 * - Sort an array by its keys (assoc) or values (non-assoc)
 * - Remove any null or empty values for associative arrays (array_filter()).
 */
function _features_sanitize(&$array) {
  if (is_array($array)) {
    $is_assoc = (array_keys($array) != range(0, count($array) - 1));
    if ($is_assoc) {
      ksort($array);
      $array = array_filter($array);
    }
    else {
      sort($array);
    }
    foreach ($array as $k => $v) {
      if (is_array($v)) {
        _features_sanitize($array[$k]);
      }
    }
  }
}
