<?php
// $Id: features.drush.inc,v 1.1.2.19 2010/02/07 05:20:16 yhahn Exp $

/**
 * @file
 *   Features module drush integration.
 */

/**
 * Implementation of hook_drush_command().
 * 
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function features_drush_command() {
  $items = array();

  $items['features'] = array(
    'callback' => 'features_command_list',
    'description' => "List all the available features for your site.",
  );
  $items['features-export'] = array(
    'callback' => 'features_command_export',
    'description' => "Export a feature from your site into a module.",
    'arguments' => array(
      'feature' => 'Feature name to export.',
    ),
  );
  $items['features-update'] = array(
    'callback' => 'features_command_update',
    'description' => "Update a feature module on your site.",
    'arguments' => array(
      'feature' => 'A space delimited list of features.',
    ),
  );
  $items['features-revert'] = array(
    'callback' => 'features_command_revert',
    'description' => "Revert a feature module on your site.",
    'arguments' => array(
      'feature' => 'A space delimited list of features.',
    ),
    'options' => array(
      '--force' => "Force revert even if Features assumes components' state are default.",
    ),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function features_drush_help($section) {
  switch ($section) {
    case 'drush:features':
      return dt("List all the available features for your site.");
    case 'drush:features export':
      return dt("Export a feature from your site into a module.");
  }
}

/**
 * Get a list of all feature modules.
 */
function features_command_list() {
  module_load_include('inc', 'features', 'features.export');
  $rows = array(array(dt('Name'), dt('Feature'), dt('Status'), dt('State')));
  foreach (features_get_features() as $k => $m) {
    switch (features_get_storage($m->name)) {
      case FEATURES_DEFAULT:
      case FEATURES_REBUILDABLE:
        $storage = '';
        break;
      case FEATURES_OVERRIDDEN:
        $storage = dt('Overridden');
        break;
      case FEATURES_NEEDS_REVIEW:
        $storage = dt('Needs review');
        break;
    }
    $rows[] = array(
      $m->info['name'],
      $m->name,
      $m->status ? dt('Enabled') : dt('Disabled'),
      $storage
    );
  }
  drush_print_table($rows, TRUE);
}

/**
 * Create a feature module based on a list of contexts.
 */
function features_command_export() {
  $args = func_get_args();

  if (count($args) == 1) {
    // Assume that the user intends to create a module with the same name as the
    // "value" of the component.
    list($source, $component) = explode(':', $args[0]);
    $stub = array($source => array($component));
    _features_command_export($stub, $component);
  }
  elseif (count($args) > 1) {
    // Assume that the user intends to create a new module based on a list of 
    // contexts. First argument is assumed to be the name.
    $name = array_shift($args);
    $stub = array();
    foreach ($args as $v) {
      list($source, $component) = explode(':', $v);
      $stub[$source][] = $component;
    }
    _features_command_export($stub, $name);
  }
  else {
    drush_print(dt('Available sources'));
    $rows = array(dt('Available sources'));
    foreach (features_get_components(TRUE) as $component => $info) {
      if ($options = features_invoke($component, 'features_export_options')) {
        foreach ($options as $key => $value) {
          $rows[] = array($component .':'. $key);
        }
      }
    }
    drush_print_table($rows, TRUE);
  }
}

/**
 * Create a feature module based on a list of contexts.
 */
function features_command_update() {
  if ($args = func_get_args()) {
    foreach ($args as $module) {
      if (($feature = feature_load($module, TRUE)) && module_exists($module)) {
        $stub = $feature->info['features'];
  
        // Construct the correct destination path
        $destination = dirname($feature->filename);
        $split = explode('/', $destination);
        if ($feature->name == array_pop($split)) {
          $destination = implode('/', $split);
        }
  
        _features_command_export($stub, $feature->name, $destination);
      }
      else if ($feature) {
        _features_drush_set_error($module, 'FEATURES_FEATURE_NOT_ENABLED');
      }
      else {
        _features_drush_set_error($module);
      }
    }
  }
  else {
    // By default just show contexts that are available.
    $rows = array(array(dt('Available features')));
    foreach (features_get_features(NULL, TRUE) as $name => $info) {
      $rows[] = array($name);
    }
    drush_print_table($rows, TRUE);
  }
}

/**
 * Write a module to the site dir.
 *
 * @param $requests
 *   An array of the context requested in this export.
 * @param $module_name
 *  Optional. The name for the exported module, it omitted will be generated
 *  from the first listed context.
 */
function _features_command_export($stub, $module_name = NULL, $destination = 'sites/all/modules') {
  drupal_flush_all_caches();

  module_load_include('inc', 'features', 'features.export');
  $export = features_populate($stub, $module_name);
  if ($feature = feature_load($module_name)) {
    $export['dependencies'] = _features_export_preserve_dependencies($export['dependencies'], $module_name);
  }
  else {
    $export['name'] = $module_name;
  }
  $files = features_export_render($export, $module_name, TRUE);

  if ($root = drush_locate_root()) {
    $directory = "$destination/{$module_name}";
    if (is_dir($directory)) {
      drush_print(dt('Module appears to already exist in !dir', array('!dir' => $directory)));
      if (!drush_confirm(dt('Do you really want to continue?'))) {
        drush_die('Aborting.');
      }
    }
    else {
      drush_op('mkdir', $directory);
    }
    foreach ($files as $extension => $file_contents) {
      if (!in_array($extension, array('module', 'info'))) {
        $extension .= '.inc';
      }
      drush_op('file_put_contents', "{$directory}/{$module_name}.$extension", $file_contents);
    }
    drush_log(dt("Created module: !module in !directory", array('!module' => $module_name, '!directory' => $directory)), 'ok');
  }
  else {
    drush_die(dt('Couldn\'t locate site root'));
  }
}

/**
 * Revert a feature to it's code definition.
 */
function features_command_revert() {
  if ($args = func_get_args()) {
    // Determine if revert should be forced.
    $force = drush_get_option('force');
    foreach ($args as $module) {
      if (($feature = feature_load($module, TRUE)) && module_exists($module)) {
        // Find all overridden items
        module_load_include('inc', 'features', 'features.export');
  
        $components = array();
        $states = features_get_component_states(array($feature->name), FALSE);
        foreach ($states[$feature->name] as $component => $state) {
          if ($force || (in_array($state, array(FEATURES_OVERRIDDEN, FEATURES_NEEDS_REVIEW)) && features_hook($component, 'features_revert'))) {
            $components[] = $component;
          }
        }
  
        if (empty($components)) {
          drush_log(dt('Current state already matches defaults, aborting.'), 'ok');
        }
        else {
          foreach ($components as $component) {
            if (drush_confirm(dt('Do you really want to revert !component?', array('!component' => $component)))) {
              features_revert(array($module => array($component)));
              drush_log(dt('Reverted !component.', array('!component' => $component)), 'ok');
            }
            else {
              drush_log(dt('Skipping !component.', array('!component' => $component)), 'ok');
            }
          }
        }
      }
      else if ($feature) {
        _features_drush_set_error($module, 'FEATURES_FEATURE_NOT_ENABLED');
      }
      else {
        _features_drush_set_error($module);
      }
    }
  }
  else {
    features_command_list();
    return;
  }
}

/**
 * Helper function to call drush_set_error().
 *
 * @param $feature
 *   The string name of the feature.
 * @param $error
 *   A text string identifying the type of error.
 * @return 
 *   FALSE.  See drush_set_error().
 */
function _features_drush_set_error($feature, $error) {
  $args = array('!feature' => $feature);

  switch ($error) {
    case 'FEATURES_FEATURE_NOT_ENABLED':
      $message = 'The feature !feature is not enabled.';
      break;
    default:
      $error = 'FEATURES_FEATURE_NOT_FOUND';
      $message = 'The feature !feature could not be found.';
  }

  return drush_set_error($error, dt($message, $args));
}
