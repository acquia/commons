<?php
// $Id: features.menu.inc,v 1.1.2.6 2009/11/18 04:36:36 yhahn Exp $

/**
 * Implementation of hook_features_api().
 */
function menu_features_api() {
  return array(
    'menu' => array(
      'name' => t('Menu items'),
      'default_hook' => 'menu_default_items',
    ),
  );
}

/**
 * Implementation of hook_features_export_options().
 */
function menu_features_export_options() {
  $options = array();
  $result = db_query("SELECT * FROM {menu_links} WHERE menu_name = 'features' AND depth = 1");
  while ($row = db_fetch_array($result)) {
    $options[$row['link_path']] = $row['link_title'];
  }
  return $options;
}

/**
 * Implementation of hook_features_export().
 */
function menu_features_export($data, &$export) {
  $pipe = array();
  // Default hooks are provided by the feature module so we need as a to add
  // it as a dependency.
  $export['dependencies']['features'] = 'features';

  foreach ($data as $path) {
    // Query for links in the features table... if they exist, add to export object.
    $result = db_query("SELECT * FROM {menu_links} WHERE link_path = '%s' AND menu_name = 'features'", $path);
    while ($row = db_fetch_array($result)) {
      $export['features']['menu'][$path] = $path;
      break;
    }
    // We could add menu module as a dependency here but it's not actually necessary...
  }

  return $pipe;
}

/**
 * Implementation of hook_features_export_render()
 */
function menu_features_export_render($module = 'foo', $data) {
  $code = array();
  $code[] = '  $items = array();';
  $code[] = '';

  $translatables = array();

  foreach ($data as $path) {
    // Query for links only in the features table
    $result = db_query("SELECT * FROM {menu_links} WHERE link_path = '%s' AND menu_name = 'features'", $path);
    while ($row = db_fetch_array($result)) {
      $link = array(
        'title' => $row['link_title'],
        'path' => $row['link_path'],
        'weight' => $row['weight'],
      );
      $translatables[] = $row['link_title'];

      // Add in description field
      $options = unserialize($row['options']);
      if (!empty($options['attributes']['title'])) {
        $link['description'] = $options['attributes']['title'];
        $translatables[] = $options['attributes']['title'];
      }

      $code[] = "  \$items[] = ". features_var_export($link, '  ') .";";
      break;
    }
  }
  if (!empty($translatables)) {
    $code[] = features_translatables_export($translatables, '  ');
  }

  $code[] = '';
  $code[] = '  return $items;';
  $code = implode("\n", $code);
  return array('menu_default_items' => $code);
}
