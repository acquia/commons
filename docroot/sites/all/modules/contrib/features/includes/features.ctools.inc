<?php
// $Id: features.ctools.inc,v 1.1.2.16 2010/02/06 02:16:45 yhahn Exp $

/**
 * This is a wild hack, but effective.
 * Dynamically declare functions under a ctools component's namespace if they are not already declared.
 */
foreach (_ctools_features_get_info() as $component => $info) {
  $code = '';
  if (!function_exists("{$info['module']}_features_api")) {
    $code .= 'function '. $info['module'] .'_features_api() { return ctools_component_features_api("'. $info['module'] .'"); }';
  }
  if (!function_exists("{$component}_features_export")) {
    $code .= 'function '. $component .'_features_export($data, &$export, $module_name = "") { return ctools_component_features_export("'. $component .'", $data, $export, $module_name); }';
  }
  if (!function_exists("{$component}_features_export_options")) {
    $code .= 'function '. $component .'_features_export_options() { return ctools_component_features_export_options("'. $component .'"); }';
  }
  if (!function_exists("{$component}_features_export_render")) {
    $code .= 'function '. $component .'_features_export_render($module = "foo", $data) { return ctools_component_features_export_render("'. $component .'", $module, $data); }';
  }
  if (!function_exists("{$component}_features_revert")) {
    $code .= 'function '. $component .'_features_revert($module = "foo") { return ctools_component_features_revert("'. $component .'", $module); }';
  }
  eval($code);
}

/**
 * Implementation of hook_features_api().
 */
function ctools_features_api() {
  return array(
    'ctools' => array(
      'name' => 'CTools export API',
      'default_hook' => 'ctools_plugin_api',
      'feature_source' => TRUE,
      'duplicates' => FEATURES_DUPLICATES_ALLOWED,
    ),
  );
}

/**
 * Implementation of hook_features_export().
 * Adds references to the ctools mothership hook, ctools_plugin_api().
 */
function ctools_features_export($data, &$export, $module_name = '') {
  // Add ctools dependency
  $export['dependencies']['ctools'] = 'ctools';

  // Add the actual ctools components which will
  // need to be accounted for in hook_ctools_plugin_api().
  foreach ($data as $component) {
    $export['features']['ctools'][$component] = $component;
  }

  return array();
}

/**
 * Implementation of hook_features_export_render().
 * Adds the ctools mothership hook, ctools_plugin_api().
 */
function ctools_features_export_render($module = 'foo', $data) {
  $info = _ctools_features_get_info();

  $code = array();
  $code[] = '  $args = func_get_args();';
  $code[] = '  $module = array_shift($args);';
  $code[] = '  $api = array_shift($args);';

  $first = TRUE;
  foreach ($data as $component) {
    $module = $info[$component]['module'];
    $api = $info[$component]['api'];
    $version = $info[$component]['current_version'];

    $if = $first ? 'if' : 'else if';
    $code[] = '  '. $if .' ($module == "'. $module .'" && $api == "'. $api .'") {';
    $code[] = '    return array("version" => '. $version .');';
    $code[] = '  }';

    $first = FALSE;
  }
  return array('ctools_plugin_api' => implode("\n", $code));
}

/**
 * Master implementation of hook_features_api() for all ctools components.
 *
 * Note that this master hook does not use $component like the others, but uses the
 * component module's namespace instead.
 */
function ctools_component_features_api($module_name) {
  $api = array();
  foreach (_ctools_features_get_info() as $component => $info) {
    if ($info['module'] === $module_name) {
      $api[$component] = $info;
    }
  }
  return $api;
}

/**
 * Master implementation of hook_features_export_options() for all ctools components.
 */
function ctools_component_features_export_options($component) {
  $options = array();

  ctools_include('export');
  $schema = ctools_export_get_schema($component);
  if ($schema && $schema['export']['bulk export']) {
    $export_key = $schema['export']['key'];
    // If a list callback is available use it, otherwise fallback to generating
    // options from ctools_export_load_object().
    if (function_exists($schema['export']['list callback'])) {
      $objects = $schema['export']['list callback']();
      $options = drupal_map_assoc(array_keys($objects));
    }
    else if ($objects = ctools_export_load_object($component, 'all')) {
      $options = drupal_map_assoc(array_keys($objects));
    }
  }
  ksort($options);
  return $options;
}

/**
 * Master implementation of hook_features_export() for all ctools components.
 */
function ctools_component_features_export($component, $data, &$export, $module_name = '') {
  // Add the actual implementing module as a dependency
  $info = _ctools_features_get_info();
  $export['dependencies'][$module] = $info[$component]['module'];

  // Add the components
  foreach ($data as $object_name) {
    if (ctools_export_load_object($component, 'names', array($object_name))) {
      $export['features'][$component][$object_name] = $object_name;
    }
  }

  // Let CTools handle API integration for this component.
  return array('ctools' => array($component));
}

/**
 * Master implementation of hook_features_export_render() for all ctools components.
 */
function ctools_component_features_export_render($component, $module = 'foo', $data) {
  ctools_include('export');

  $schema = ctools_export_get_schema($component);
  if (function_exists('page_manager_page_manager_handlers_list')) {
    page_manager_page_manager_handlers_list();
  }
  if (function_exists($schema['export']['to hook code callback'])) {
    $list = $schema['export']['list callback']();
    $export = $schema['export']['to hook code callback']($data, $module);
    $code = explode("{\n", $export);
    array_shift($code);
    $code = explode('}', implode($code, "{\n"));
    array_pop($code);
    $code = implode('}', $code);
  }
  else {
    $code = '  $export = array();'."\n";
    foreach ($data as $object) {
      $identifier = $schema['export']['identifier'];
      $objects = ctools_export_load_object($component, 'names', array($object));
      if (!empty($objects[$object])) {
        // Support objects that have a defined export callback, but fall back to.
        // ctools_export_object().
        if (function_exists($schema['export']['export callback'])) {
          $code .= $schema['export']['export callback']($objects[$object], '  ');
        }
        else {
          $code .= ctools_export_object($component, $objects[$object], '  ', $identifier);
        }
        $code .= "\n";
        $code .= '  $export[\''. $object .'\'] = $'. $identifier .';'."\n";
      }
    }
    $code .= '  return $export;';
  }

  return array($schema['export']['default hook'] => $code);
}

/**
 * Master implementation of hook_features_revert() for all ctools components.
 */
function ctools_component_features_revert($component, $module = 'foo') {
  $info = _ctools_features_get_info();
  $objects = module_invoke($module, $info[$component]['default_hook']);
  if (!empty($objects)) {
    $schema = ctools_export_get_schema($component);
    $export = $schema['export'];
    $names = db_placeholders(array_keys($objects), $schema['fields'][$export['key']]['type']);
    db_query("DELETE FROM {{$component}} WHERE {$export['key']} IN ({$names})", array_keys($objects));
  }
}

/**
 * Helper function to return various ctools information for components.
 */
function _ctools_features_get_info($reset = FALSE) {
  static $components;
  if (!isset($components) || $reset) {
    $components = array();
    $modules = features_get_info();
    ctools_include('export');
    foreach (ctools_export_get_schemas_by_module() as $module => $schemas) {
      foreach ($schemas as $table => $schema) {
        if ($schema['export']['bulk export']) {
          // Let the API owner take precedence as the owning module.
          $api_module = isset($schema['export']['api']['owner']) ? $schema['export']['api']['owner'] : $module;
          $components[$table] = array(
            'name' => isset($modules[$api_module]->info['name']) ? $modules[$api_module]->info['name'] : $api_module,
            'api' => $schema['export']['api']['api'],
            'default_hook' => $schema['export']['default hook'],
            'current_version' => $schema['export']['api']['current_version'],
            'module' => $api_module,
            'feature_source' => TRUE,
          );
        }
      }
    }
  }
  return $components;
}
