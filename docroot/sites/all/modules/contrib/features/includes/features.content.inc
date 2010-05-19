<?php
// $Id: features.content.inc,v 1.1.2.11 2009/11/18 04:36:36 yhahn Exp $

/**
 * Implementation of hook_features_api().
 */
function content_features_api() {
  return array(
    'content' => array(
      'name' => t('CCK'),
      'default_hook' => 'content_default_fields',
    ),
  );
}

/**
 * Implementation of hook_features_export().
 */
function content_features_export($data, &$export, $module_name = '') {
  $pipe = array();

  // The content_default_fields() hook integration is provided by the
  // features module so we need to add it as a dependency.
  $export['dependencies']['features'] = 'features';

  // Collect a field to module map
  $map = array();
  $modules = module_implements('content_default_fields');
  foreach ($modules as $module) {
    $fields = module_invoke($module, 'content_default_fields');
    foreach ($fields as $field) {
      $map["{$field['type_name']}-{$field['field_name']}"] = $module;
    }
  }

  foreach ($data as $instance) {
    // If this field is already provided by another module, remove the field
    // and add the other module as a dependency.
    if (isset($map[$instance]) && $map[$instance] != $module_name) {
      if (isset($export['features']['content'][$instance])) {
        unset($export['features']['content'][$instance]);
      }
      $module = $map[$instance];
      $export['dependencies'][$module] = $module;
    }
    // If the field has not yet been exported, add it
    else {
      $split = explode('-', $instance);
      $type_name = $split[0];
      $field_name = $split[1];
      $field = content_fields($field_name, $type_name);

      if ($field) {
        // Add field item instance for later export.
        $export['features']['content'][$instance] = $instance;

        // Add module which provides field.
        $export['dependencies'][$field['module']] = $field['module'];

        // Add module which provides field widget.
        $export['dependencies'][$field['widget']['module']] = $field['widget']['module'];

        // Add modules which provide display.
        foreach (array('teaser', 'full') as $display) {
          $formatter = _content_get_formatter($field['display_settings'][$display]['format'], $field['type']);
          $export['dependencies'][$formatter['module']] = $formatter['module'];

          // TODO make this logic more generic, for now though we just handle
          // the imagecache presets.
          if ($formatter['module'] == 'imagecache') {
            $format = $field['display_settings'][$display]['format'];

            $parts = explode('_', $format);
            $style = array_pop($parts);
            $presetname = implode('_', $parts);

            $pipe[$formatter['module']][] = $presetname;
          }
        }
      }
    }
  }

  return $pipe;
}

/**
 * Implementation of hook_features_export_render().
 */
function content_features_export_render($module = 'foo', $data) {
  $translatables = $code = array();

  $code[] = '  $fields = array();';
  $code[] = '';
  foreach ($data as $instance) {
    $instance = explode('-', $instance);
    $type_name = $instance[0];
    $field_name = $instance[1];

    $field = content_fields($field_name, $type_name);
    unset($field['columns']);
    unset($field['locked']);
    unset($field['db_storage']);

    $code[] = '  // Exported field: '. $field_name;
    $code[] = '  $fields[] = '. features_var_export($field, '  ') .';';
    $code[] = '';

    // Add any labels to translatables array.
    if (!empty($field['widget']['label'])) {
      $translatables[] = $field['widget']['label'];
    }
  }
  if (!empty($translatables)) {
    $code[] = features_translatables_export($translatables, '  ');
  }
  $code[] = '  return $fields;';
  $code = implode("\n", $code);
  return array('content_default_fields' => $code);
}

/**
 * Implementation of hook_features_revert().
 */
function content_features_revert($module) {
  content_features_rebuild($module);
}

/**
 * Implementation of hook_features_rebuild().
 * Rebuilds CCK field definitions from code defaults.
 */
function content_features_rebuild($module) {
  $fields = module_invoke($module, 'content_default_fields');
  if (!empty($fields)) {
    module_load_include('inc', 'content', 'includes/content.crud');
    content_clear_type_cache(TRUE);

    foreach ($fields as $field) {
      $existing_field = content_fields($field['field_name']);
      $existing_instance = content_fields($field['field_name'], $field['type_name']);
      if ($existing_field && $existing_instance) {
        content_field_instance_update($field, FALSE);
      }
      else {
        content_field_instance_create($field, FALSE);
      }
      variable_set('menu_rebuild_needed', TRUE);
    }
  }
}
