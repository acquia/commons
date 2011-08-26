<?php

/**
 * @file
 *   Handles admin pages for the Facebook-style Micropublisher module.
 */

/**
 * Settings form.
 */
function fbsmp_admin($form_state) {  
  $plugins = fbsmp_get_plugins(TRUE);
  $disabled_plugins = variable_get('fbsmp_disabled_plugins', array());
  
  $form['#submit'] = array('fbsmp_admin_form_submit');
  $yesno = array(1 => t('Yes'), 0 => t('No'));
  
  //General settings.
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => FALSE,
  );
  $form['general']['ignore_sdefault'] = array(
    '#type' => 'checkbox',
    '#title' => t('Ignore default text'),
    '#prefix' => '<div class="fbsmp-checkboxes">',
    '#suffix' => '</div>',  
    '#default_value' => variable_get('fbsmp_ignore_sdefault', 0),
    '#description' => t('You can set the status update box to contain default text -- usually the previous status.')
      .' '. t('If you enable this setting, statuses saved with this default text will be saved as if the status text was blank.')
      .' '. t('This only applies when the relevant status has an attachment.'),
  );
  
  //Plugins settings.
  $form['fbsmp_plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plugin settings'),
    '#collapsible' => FALSE,
    '#description' => t('Enable one or more FBSMP plugins to publish content such as photos, links, videos, etc along with the FBSS statuses. Once a plugin is disabled, no content of this plugin type can be created and in the stream, only status text will be shown for this plugin type.'),
    '#tree' => TRUE,
    '#header' => array(t('Name'), t('Description'), t('Operations'), t('Enabled')),
    '#plugins' => $plugins,
    '#theme' => 'fbsmp_admin_plugins_overview',
  );
    
  foreach ($plugins as $plugin => $info) {
    $name = isset($info['name']) ? $info['name'] : $plugin;
    $description = isset($info['description']) ? $info['description'] : '';
    $admin_form = fbsmp_load_function($plugin, 'admin_settings_form');
    
    $form['fbsmp_plugins'][$plugin] = array(
      'label' => array('#value' => $name),
      'description' => array('#value' => $description),
      'configure' => $admin_form ? array('#value' => l(t('Configure'), 'admin/settings/fbsmp/plugins/'. $plugin)) : '',
      'enabled' => array('#type' => 'checkbox', '#default_value' => !in_array($plugin, $disabled_plugins)),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration')
  );
  
  return $form;
}

/**
 * Settings form submit function.
 */
function fbsmp_admin_form_submit(&$form, &$form_state) {
  $plugins = $form['fbsmp_plugins']['#plugins'];
  $plugin_values = $form_state['values']['fbsmp_plugins'];
  $disabled_plugins = array();
  foreach ($plugins as $key => $info) {
    $enabled = $plugin_values[$key]['enabled'];
    if (!isset($enabled) || !$enabled) {
      $disabled_plugins[] = $key;
    }
  }
  variable_set('fbsmp_disabled_plugins', $disabled_plugins);
  variable_set('fbsmp_ignore_sdefault', $form_state['values']['ignore_sdefault']);
  drupal_set_message(t('The configuration options have been saved.'));
}

function fbsmp_admin_plugin_form(&$form_state, $plugin) {
  drupal_add_css(drupal_get_path('module', 'fbsmp') .'/fbsmp.admin.css');
  $form = array();
  if ($function = fbsmp_load_function($plugin, 'admin_settings_form')) {
    $form += $function($form_state);
    
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
      '#validate' => array('fbsmp_admin_plugin_form_validate'),
      '#submit' => array('fbsmp_admin_plugin_form_submit'),
    );
    $form['ac_plugin'] = array(
      '#type' => 'value',
      '#value' => $plugin,
    );
  }
  else {
    $form['message'] = array(
      '#value' => '<div class="no-admin-settings-message">'. t('@name plugin does not provide any configuration settings.', array('@name' => $plugin)) .'</div>',
    );
  }
  return $form;
}

function fbsmp_admin_plugin_form_validate(&$form, &$form_state) {
  $plugin = $form_state['values']['ac_plugin'];
  if ($function = fbsmp_load_function($plugin, 'admin_settings_form_validate')) {
    $function($form, $form_state);
  }
}

function fbsmp_admin_plugin_form_submit(&$form, &$form_state) {
  $plugin = $form_state['values']['ac_plugin'];
  if ($function = fbsmp_load_function($plugin, 'admin_settings_form_submit')) {
    $function($form, $form_state);
  }
  drupal_set_message(t('The configuration options have been saved.'));
}

function theme_fbsmp_admin_plugins_overview($element) {
  //Iterate through all plugins and build a table.
  $rows = array();
  foreach ($element['#plugins'] as $plugin => $info) {
    $row = array();
    foreach (element_children($element[$plugin]) as $col) {
      $row[$col] = array(
        'data' => drupal_render($element[$plugin][$col]),
      );
    }
    $rows[] = array(
      'data' => $row,
    );
  }
  $output = '';
  if (count($rows)) {
    $output .= theme('table', $element['#header'], $rows, array('class' => 'fbsmp-admin-plugins'));
  }
  $output .= drupal_render($element);
  return $output;
}