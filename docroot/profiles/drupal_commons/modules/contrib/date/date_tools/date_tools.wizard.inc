<?php
// $Id: date_tools.wizard.inc,v 1.1.2.4 2010/08/12 14:14:57 karens Exp $

function date_tools_wizard_form() {
  
  $form = array();
  $form['type'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content type'),
    );
  $form['type']['type_name'] = array(
    '#type' => 'textfield',
    '#default_value' => 'date',
    '#title' => t('Content type name'),
    '#description' => t('Machine-readable name. Allowed values: (a-z, 0-9, _). If this is not an existing content type, the content type will be created.'),
    ); 
  $form['type']['name'] = array(
    '#type' => 'textfield',
    '#default_value' => t('Date'),
    '#title' => t('Content type label'),
    '#description' => t('The human-readable name for this content type. Only needed when creating a new content type.'),
    ); 
  $form['type']['type_description'] = array(
    '#type' => 'textarea',
    '#default_value' => t('A date content type that is linked to a Views calendar.'),
    '#title' => t('Content type description'),
    '#description' => t('A description for the content type. Only needed when creating a new content type.'),
    );      
  $form['field'] = array(
    '#type' => 'fieldset',
    '#title' => t('Date field'),
    );
  $form['field']['field_name'] = array(
    '#type' => 'textfield',
    '#default_value' => 'date',
    '#field_prefix' => 'field_',
    '#title' => t('Date field name'),
    '#description' => t('Machine-readable name. Allowed values: (a-z, 0-9, _) Must not be an existing field name.'),
    );
  $form['field']['label'] = array(
    '#tree' => TRUE,
    '#type' => 'textfield',
    '#default_value' => t('Date'),
    '#title' => t('Date field label'),
    '#description' => t('The human-readable label for this field.'),
    );
  $form['field']['widget_type'] = array(
    '#type' => 'select',
    '#options' => date_tools_wizard_widget_types(),
    '#default_value' => 'date_select',
    '#title' => t('Date widget type'),
    );
  $form['field']['repeat'] = array(
    '#type' => 'select',
    '#default_value' => 0,
    '#options' => array(0 => t('No'), 1 => t('Yes')),
    '#title' => t('Show repeating date options'),
    '#access' => module_exists('date_repeat'),
    );  
  $form['field']['advanced'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Advanced options'),
    );
  $form['field']['advanced']['field_type'] = array(
    '#type' => 'select',
    '#options' => date_tools_wizard_field_types(),
    '#default_value' => 'datetime',
    '#title' => t('Date field type'),
    '#description' => t("The recommend type is Datetime, except for historical dates or dates with only year or month granularity. Older or incomplete dates should use the Date type (an ISO date)."),
    );
  $form['field']['advanced']['granularity'] = array(
    '#type' => 'select',
    '#options' => date_granularity_names(),
    '#default_value' => array('month', 'day', 'year', 'hour', 'minute'),
    '#title' => t('Granularity'),
    '#multiple' => TRUE,
    );  
  $form['field']['advanced']['tz_handling'] = array(
    '#type' => 'select',
    '#options' => date_tools_wizard_tz_handling(),
    '#default_value' => 'site',
    '#title' => t('Date timezone handling'),
    '#description' => t("Timezone handling should be set to 'none' for granularity without time elements.")
    );
  $form['calendar'] = array(
    '#type' => 'select',
    '#default_value' => 1,
    '#options' => array(0 => t('No'), 1 => t('Yes')),
    '#title' => t('Create a calendar for this date field'),
    '#access' => module_exists('calendar'),
    ); 
  $form['blocks'] = array(
    '#type' => 'select',
    '#options' => array(0 => t('No'), 1 => t('Yes')),
    '#default_value' => 0,
    '#title' => t('Add calendar blocks to the current theme'),
    '#access' => module_exists('calendar'),
    );   
     
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    );      
  return $form;
}

function date_tools_wizard_form_validate(&$form, &$form_state) {
  $type_name = $form_state['values']['type_name'];
  $field_name = 'field_'. $form_state['values']['field_name'];
  if (db_result(db_query("SELECT type FROM {node_type} WHERE type='%s'", $type_name))) {
    drupal_set_message(t('This content type name already exists, adding new field to existing content type.'));
  }
  if (!preg_match('!^[a-z0-9_]+$!', $type_name)) {
    form_set_error('type_name', t('The machine-readable name must contain only lowercase letters, numbers, and underscores.'));
  }
  if (db_result(db_query("SELECT field_name FROM {content_node_field_instance} WHERE field_name='%s' AND type_name='%s'", $field_name, $type_name))) {
    form_set_error('field_name', t('This field name already exists.'));
  }
  if (!date_has_time($form_state['values']['granularity']) && $form_state['values']['tz_handling'] != 'none') {
    form_set_error('tz_handling', t('Timezone handling must be none for granularity without time.'));
  }
}

function date_tools_wizard_form_submit(&$form, &$form_state) {
  $view_name = date_tools_wizard_build($form_state['values']);
  menu_rebuild();
  if (!empty($view_name)) {
    drupal_set_message(t('Change the calendar as needed and save the view.'), 'error');
    $form['#redirect'] = 'admin/build/views/edit/'. $view_name;
  }
  else {
    $form['#redirect'] = 'admin/content/node-type/'. str_replace('_', '-', $form_state['values']['type_name']) .'/fields';
  }
}

function date_tools_wizard_build($form_values) {
  extract($form_values);
  
  $field_name = 'field_'. $field_name;
  
  if (!empty($repeat)) {
    $widget_type .= '_repeat';
  }
  
  // Create a node type if it doesn't already exist.
  // This makes it possible to add additional date fields to 
  // an existing type.
  $types = node_get_types('names');
  $type_settings = array();
  if (!array_key_exists($type_name, $types)) {
    date_tools_wizard_create_content_type($name, $type_name, $type_description, $type_settings);
  }
  else {
    $types = node_get_types();
    $type = $types[$type_name];
    if (!empty($type_settings)) {
      foreach ($type_settings as $key => $setting) {
        $type->$key = $setting;
      }
      node_type_save($type);
    }
    $name = $type->name;
  }
  
  $field_settings = array(
    'field_name' => $field_name,
    'label' => $label,
    'type_name' => $type_name,
    'type' => $field_type,
    'widget_type' => $widget_type,
    'granularity' => $granularity,
    'tz_handling' => $tz_handling,
    'repeat' => $repeat,
    'multiple' => $repeat,
    );

  $field_settings['widget']['label'] = $label;
  $field_settings['widget']['type'] = $widget_type;
    
  $date_field = date_tools_wizard_create_date_field($field_type, $widget_type, $tz_handling, $field_settings);
  
  $view_name = '';
  if (!empty($calendar)) {
    $view_name = date_tools_wizard_create_calendar($name, $type_name, $date_field);
    if (!empty($blocks)) {
      date_tools_wizard_create_blocks($type_name);  
    }
  }
  return $view_name;
  
}

function date_tools_wizard_include() {
  module_load_include('inc', 'node', 'content_types');
  module_load_include('inc', 'node', 'node.pages');
  module_load_include('inc', 'content', 'includes/content.admin');
  module_load_include('inc', 'content', 'includes/content.crud');
  module_load_include('inc', 'date', 'date_admin');
}

function date_tools_wizard_options($options = array()) {
  $default_options = array();
  if (module_exists('date_popup')) {
    $default_options[] = 'popups';
  } 
  if (module_exists('date_repeat')) {
    $default_options[] = 'repeat';
  } 
  if (module_exists('calendar')) {
    $default_options[] = 'linked';
  }

  // Allow override of default options.
  if (!empty($options)) {
    return $options;
  }
  else {
    return $default_options;
  }
}

/**
 * Return an array of the modules needed by this wizard.
 */
function date_tools_wizard_required_modules($options = array()) {
  $options = date_tools_wizard_options($options);
  $modules = array(
    'date_timezone', 'date_api', 'content', 'date', 
  );
  if (module_exists('calendar')) {
    $modules = array_merge($modules, array('calendar', 'views', 'views_ui'));
  }  
  if (in_array('popups', $options)) {
    $modules = array_merge($modules, array('date_popup', 'jcalendar'));
  }
  if (in_array('repeat', $options)) {
    $modules = array_merge($modules, array('date_repeat'));
  }
  return $modules;
}

function date_tools_wizard_modules() {
  return array(
    'date' => t('Date'),
    'date_api' => t('Date API'),
    'date_timezone' => t('Date Timezone'),
    'content' => t('Content'),
    'calendar' => t('Calendar'),
    'calendar_ical' => t('Calendar iCal'),
    'date_repeat' => t('Date Repeat'),
    'date_popup' => t('Date Popup'),
    'jcalendar' => t('Calendar Popup'),
    'text' => t('Text'),
    'optionwidgets' => t('Optionwidgets'),
    'nodereference' => t('Nodereference'),
    'views' => t('Views'),
    'views_ui' => t('Views UI'),
    );
}

function date_tools_wizard_enabled_modules($options = array()) {
  $modules = date_tools_wizard_required_modules($options);
  $enabled = array();
  $names = date_tools_wizard_modules();
  foreach ($modules as $option) {
    if (module_exists($option)) {
      $enabled[$option] = $names[$option] .' (<span class="admin-enabled">'. t('enabled') .'</span>)';
    }
  }
  return $enabled;
}

function date_tools_wizard_disabled_modules($options = array()) {
  $modules = date_tools_wizard_required_modules($options);
  $enabled = array();
  $names = date_tools_wizard_modules();
  foreach ($modules as $option) {
    if (!module_exists($option)) {
      $enabled[$option] = $names[$option] .' (<span class="admin-disabled">'. t('disabled') .'</span>)';
    }
  }
  return $enabled;
}

function date_tools_wizard_field_types() {
  $field_types = array();  
  foreach (date_field_info() as $name => $info) {
    $field_types[$name] = $info['label']; //.' - '. $info['description'];
  }
  return $field_types;  
}

function date_tools_wizard_widget_types() {
  $widget_types = array();  
  foreach (date_widget_info() as $name => $info) {
    if (!strstr($name, '_repeat')) {
      $widget_types[$name] = $info['label'];
    }
  }
  return $widget_types;  
}

function date_tools_wizard_tz_handling() {
  include_once(drupal_get_path('module', 'date') .'/date_admin.inc');
  return date_timezone_handling_options();
}

function date_tools_wizard_create_content_type($name, $type_name, $description, $type_settings = array()) {
  
  date_tools_wizard_include();
  
  // Create the content type.
  $values  = array (
    'name' => $name,
    'type' => $type_name,
    'description' => $description,
    'title_label' => 'Title',
    'body_label' => 'Body',
    'min_word_count' => '0',
    'help' => '',
    'node_options' => 
    array (
      'status' => 1,
      'promote' => 1,
      'sticky' => 0,
      'revision' => 0,
    ),
    'language_content_type' => '0',
    'old_type' => $type_name,
    'orig_type' => '',
    'module' => 'node',
    'custom' => '1',
    'modified' => '1',
    'locked' => '0',
    'url_str' => str_replace('_', '-', $type_name),
  );
  
  // Allow overrides of these values.
  foreach ($type_settings as $key => $value) {
    $values[$key] = $value;
  }

  $type = (object) _node_type_set_defaults($values);
  node_type_save($type);
  
  if ($type == 'ical_feed') {
    // Default type to not be promoted and have comments disabled.
    variable_set('node_options_'. $type_name, array('status'));
    variable_set('comment_'. $type_name, COMMENT_NODE_DISABLED);

    // Don't display date and author information for this type by default.
    $theme_settings = variable_get('theme_settings', array());
    $theme_settings['toggle_node_info_'. $type_name] = FALSE;
    variable_set('theme_settings', $theme_settings);
  }
  
  // Update the menu router information.
  menu_rebuild();
  content_clear_type_cache();
  
}


function date_tools_wizard_create_date_field($field_type, $widget_type, $tz_handling, $overrides = array()) {
  date_tools_wizard_include();
  
  $field_name = $overrides['field_name'];
  $type_name = $overrides['type_name'];
  
  // Create the date field.
  
  // Set overrides that apply to all date fields.  
  $base_overrides = array(
  
    'field_name' => $field_name,
    'type_name' => $type_name,
    
    // Can be set to 0 (none), 1 (unlimited or repeating), 
    // or 2-9 for a fixed number of values.
    'multiple' => 0, 
    
    // Set a display format that will show complete date information, 
    // to help test that values are correct.
    'default_format' => 'long',
    
    // Set the date granularity.
    'granularity' => array (
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
      'hour' => 'hour',
      'minute' => 'minute',
      ),
    
    // Shall this date include a 'To date'?, can be blank, 'optional', or 'required'  
    'todate' => 'optional',
    
   );    
  
   // Widget overrides:
   $widget_overrides = array(

    // Move the date right below the title.
    'weight' => -4,

    // Set default values to 'blank', 'now', or 'relative'. To dates can also use 'same'.
    'default_value' => 'now',
    'default_value_code' => '', // The code to use with 'relative', like '+1 day'. 
    'default_value2' => 'blank',
    'default_value_code2' => '', // The code to use with 'relative', like '+1 day'. 
    
    // Set format string to use for input forms, it controls order and type of date parts.
    // Input formats must have all date parts, including seconds.
    'input_format_custom' => variable_get('date_format_short', 'm/d/Y - H:i') .':s',
    
    // Increment for minutes and seconds, can be 1, 5, 10, 15, or 30.
    'increment' => 15,
    
    // Optional array of date parts that should be textfields in select widgets,
    // can be any combination of year, month, day, hour, minute, second.
    'text_parts' => array (),
    
    // The number of years to go back and forward in drop-down year selectors.
    'year_range' => '0:+1',
    
    // The place for the date part labels, can be 'above', 'within', or 'none'.
    'label_position' => 'above',
  );
  
  $overrides = array_merge($base_overrides, $overrides);
  $overrides['widget'] = array_merge($widget_overrides, $overrides['widget']);
    
  // Get field default values for this combination of field and widget type,
  // using a helper function in the Date module.
  $field = date_field_default_values($field_type, $widget_type, $tz_handling, $overrides);
    
  $field = content_field_instance_collapse($field);
  $field = content_field_instance_create($field);
  $field = content_field_instance_expand($field);
  
  return $field;
}

function date_tools_wizard_create_calendar($name, $type_name, $date_field) {
  
  $date_name = !empty($date_field) ? $date_field['field_name'] : '';
  $path = 'calendar-'. str_replace('field_', '', $date_name);
  
  // Add a default calendar for this content type.
  $calendar_options = variable_get('calendar_default_view_options', array());
  if (array_key_exists('calendar_'. $type_name, $calendar_options)) {
    unset($calendar_options['calendar_'. $type_name]);
  }
  $option = array(
    'name' => 'calendar_'. $type_name,
    'description' => 'An event calendar for '. $date_field['widget']['label'],
    'path' => $path,
    'types' => array($type_name => $name),
    'date_fields' => array($date_name),
    'display_fields' => array('title' => array(), $date_name => array()),
  );
  $calendar_options['calendar_'. $type_name] = $option;
  variable_set('calendar_default_view_options', $calendar_options);
  
  // Make sure menu items get rebuilt as necessary.
  menu_rebuild();

  // Clear the views cache.
  cache_clear_all('*', 'cache_views');

  // Clear the page cache.
  cache_clear_all();  
  
  // Remove this view from cache so we can edit it properly.
  views_object_cache_clear('view', 'calendar_'. $type_name);  

  // Force Views to empty its cache and find the new view.
  views_discover_default_views();

  return 'calendar_'. $type_name;
}

function date_tools_wizard_create_blocks($type_name) {
  // Add calendar blocks to the default theme.
  $current_theme = variable_get('theme_default', 'garland');
  
  // Legend block.
  $block = new stdClass();
  $block->theme = $current_theme;
  $block->status = 1;
  $block->weight = -1;
  $block->region = 'left';
  $block->title = '';
  $block->module = 'calendar';
  $block->delta = 0;
  date_tools_wizard_add_block($block);
  
  // Mini calendar block. 
  $block->module = 'views';
  $block->delta = 'calendar_'. $type_name .'-calendar_block_1';
  date_tools_wizard_add_block($block); 
  
  // Upcoming events block.
  $block->module = 'views';
  $block->delta = 'calendar_'. $type_name .'-block_1';
  date_tools_wizard_add_block($block);
  return;      
}

/**
 * Add a block.
 */
function date_tools_wizard_add_block($block) {
  $bid = db_result(db_query("SELECT bid FROM {blocks} WHERE module='%s' AND delta='%s' AND theme='%s'", $block->module, $block->delta, $block->theme));
  if (empty($bid)) {
    $block->bid = NULL;
    drupal_write_record('blocks', $block);
  }
  else {
    $block->bid = $bid;
    drupal_write_record('blocks', $block, 'bid');
  }
}