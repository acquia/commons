<?php
// $Id: features.views.inc,v 1.1.2.16 2009/12/21 22:25:52 yhahn Exp $

/**
 * Implementation of hook_features_api().
 */
function views_features_api() {
  return array(
    'views' => array(
      'name' => t('Views'),
      'feature_source' => TRUE,
      'default_hook' => 'views_default_views',
      'default_file' => FEATURES_DEFAULTS_INCLUDED,
    ),
  );
}

/**
 * Implementation of hook_features_export_options().
 */
function views_features_export_options() {
  $enabled_views = array();
  $views = views_get_all_views();
  foreach ($views as $view) {
    if (!isset($views[$view->name]->disabled) || !$views[$view->name]->disabled) {
      $enabled_views[$view->name] = $view->name;
    }
  }
  ksort($enabled_views);
  return $enabled_views;
}

/**
 * Implementation of hook_features_export_render().
 */
function views_features_export_render($module = 'foo', $data) {
  $code = array();
  $code[] = '  $views = array();';
  $code[] = '';

  // Build views & add to export array
  foreach ($data as $view_name) {
    // Build the view
    $view = views_get_view($view_name, TRUE);
    if ($view) {
      $code[] = '  // Exported view: '. $view_name;
      $code[] = $view->export('  ');
      $code[] = '  $views[$view->name] = $view;';
      $code[] = '';
    }
  }
  $code[] = '  return $views;';
  $code = implode("\n", $code);
  return array('views_default_views' => $code);
}

/**
 * Implementation of hook_features_export().
 */
function views_features_export($data, &$export, $module_name = '') {
  views_include('view');

  if (!isset($export['features']['views'])) {
    $export['features']['views'] = array();
  }

  // Build views & add to export array
  $views = array();
  foreach ($data as $view_name) {
    // Add to exports
    $export['features']['views'][$view_name] = $view_name;

    // Build the view
    $view = views_get_view($view_name, TRUE);
    if ($view) {
      $view->build();
      $views[$view_name] = $view;
    }
  }

  // Add views as a dependency
  $export['dependencies']['views'] = 'views';

  // Discover module dependencies
  // We need to find dependencies based on:
  // 1. handlers
  // 2. plugins (style plugins, display plugins)
  // 3. other... (e.g. imagecache display option for CCK imagefields) : (

  // Handlers
  $handlers = array('fields', 'filters', 'arguments', 'sort', 'relationships');
  $handler_dependencies = views_handler_dependencies();

  // Plugins
  // For now we only support dependency detection for a subset of all views plugins
  $plugins = array('display', 'style', 'row', 'access');
  $plugin_dependencies = views_plugin_dependencies();

  foreach ($views as $view) {
    foreach ($view->display as $display) {
      if (is_object($display->handler) && method_exists($display->handler, 'get_option')) {

        // Handlers
        foreach ($handlers as $handler) {
          $items = $display->handler->get_option($handler);
          if (!empty($items)) {
            foreach ($items as $item) {
              $module = $handler_dependencies[$item['table']];
              $export['dependencies'][$module] = $module;
            }
          }
        }

        // Plugins
        foreach ($plugins as $plugin_type) {
          switch ($plugin_type) {
            case 'display':
              $plugin_name = $display->display_plugin;
              break;
            case 'access':
              $access = $display->handler->get_option("access");
              if (!empty($access['type']) && $access['type'] != 'none') {
                $plugin_name = $access['type'];
              }
              else {
                $plugin_name = '';
              }
              break;
            default:
              $plugin_name = $display->handler->get_option("{$plugin_type}_plugin");
              break;
          }
          if (!empty($plugin_name)) {
            $module = $plugin_dependencies[$plugin_type][$plugin_name];
            $export['dependencies'][$module] = $module;
          }
        }
      }
    }
  }

  // It's possible that a module provides the view for us so we need to
  // detect this and prevent elusive array_merge_recusive bugs.
  // To do so we do two things:
  //   1. remove any views in the export that are default views.
  //   2. add as a dependency the module that provides the view.
  //
  // If the view in question is overridden, the user needs to take action
  // to resolve the conflict. We display a message in this situation.
  views_include_default_views();
  $modules = module_implements('views_default_views');
  $conflicts = array();
  foreach ($modules as $m) {
    $m_default_views = module_invoke($m, 'views_default_views');
    if (is_array($m_default_views)) {
      foreach ($m_default_views as $view_name => $view) {
        if (array_key_exists($view_name, $export['features']['views']) && ($m != $module_name)) {
          $v = views_get_view($view_name);
          if ($v) {
            // If view is overridden we display an error message and bail.
            if ($v->type == 'Overridden') {
              $conflicts[$m] = $view_name;
              unset($export['features']['views'][$view_name]);
            }
            // If view is default, we add the providing module as a dependency and exclude it from the Views export
            else if ($v->type == 'Default') {
              unset($export['features']['views'][$view_name]);
              $tokens = array('!view_name' => $view_name, '!module' => $m);
              $export['conflicts']['status'][] = t('The view <strong>!view_name</strong> will not be exported with your feature because it is provided by <strong>!module</strong> which has been added as a dependency.', $tokens);
              $export['dependencies'][$m] = $m;
            }
          }
        }
      }
    }
  }
  if ($conflicts) {
    $message = '<p>A conflict was detected with the following overridden view(s):</p>';
    $message .= '<ul><li><strong>Views</strong>: !views</li><li><strong>Providing modules</strong>: !modules</li></ul>';
    $message .= '<p>To resolve this problem you should either:</p>';
    $message .= '<ol><li>Revert each overridden view</li><li>Clone each view so that the modified version(s) can be exported with your feature</li></ol>';
    $tokens = array('!views' => implode(', ', $conflicts), '!modules' => implode(', ', array_keys($conflicts)));
    $export['conflicts']['error'][] = t($message, $tokens);
  }
}

/**
 * Provides an array that maps hook_views_data() tables to modules.
 */
function views_handler_dependencies() {
  views_include_handlers();

  static $map;
  if (!isset($map)) {
    $map = array();
    foreach (module_implements('views_data') as $module) {
      $tables = module_invoke($module, 'views_data');
      foreach ($tables as $table => $info) {
        if (isset($info['table'])) {
          $map[$table] = $module;
        }
        else if (!isset($map[$table])) {
          $map[$table] = $module;
        }
      }
    }
  }
  return $map;
}

/**
 * Provides an array that maps hook_views_plugins() to modules.
 */
function views_plugin_dependencies() {
  views_include_handlers();

  static $map;
  if (!isset($map)) {
    $map = array();
    foreach (module_implements('views_plugins') as $module) {
      $plugins = module_invoke($module, 'views_plugins');
      if (!empty($plugins)) {
        foreach ($plugins as $type => $items) {
          if (is_array($items)) {
            foreach (array_keys($items) as $plugin_name) {
              $map[$type][$plugin_name] = $module;
            }
          }
        }
      }
    }
  }
  return $map;
}

/**
 * Implementation of hook_features_revert().
 *
 * @param $module
 * name of module to revert content for
 */
function views_features_revert($module = NULL) {
  views_include('view');

  // Get default views from feature
  if (module_hook($module, 'views_default_views')) {
    $default_views = module_invoke($module, 'views_default_views');

    // Delete Normal / Overridden views that are defined in code
    foreach ($default_views as $default_view) {
      if ($current_view = views_get_view($default_view->name)) {
        $current_view->delete();
      }
    }
  }
  else {
    drupal_set_message(t('Could not load default views.'), 'error');
    return FALSE;
  }
  return TRUE;
}
