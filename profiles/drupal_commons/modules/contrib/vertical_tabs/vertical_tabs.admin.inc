<?php
// $Id: vertical_tabs.admin.inc,v 1.1.2.2 2010/02/03 19:06:46 davereid Exp $

function vertical_tabs_settings_form() {
  $form['vertical_tabs_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include new fieldsets in vertical tabs by default.'),
    '#default_value' => variable_get('vertical_tabs_default', 1),
  );
  $form['vertical_tabs_minimum'] = array(
    '#type' => 'select',
    '#title' => t('Minimum number of tabified fieldsets to show vertical tabs'),
    '#description' => t('Non-tabified fieldsets do not count towards this minimum.'),
    '#options' => array(1 => t('No minimum')) + drupal_map_assoc(range(2, 10)),
    '#default_value' => variable_get('vertical_tabs_minimum', 1),
  );
  $form['vertical_tabs_node_type_settings'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expose vertical tabs selection on the edit content type forms.'),
    '#description' => t('This feature will not work when adding a new content type and may not detect some fieldsets.'),
    '#default_value' => variable_get('vertical_tabs_node_type_settings', 0),
  );
  return system_settings_form($form);
}

function vertical_tabs_add_node_type_options(&$form, $node_type) {
  module_load_include('inc', 'node', 'node.pages');

  // Build a psuedo-node for a sample node form.
  $node = (object) array(
    'type' => $node_type,
    'name' => '',
    'vid' => 0,
    'language' => '',
  );

  // Build a sample node form to find fieldsets.
  $node_form_state = array('values' => array());
  $node_form_id = $node_type .'_node_form';
  $args = array(
    $node_form_id,
    $node_form_state,
    $node
  );
  $node_form = call_user_func_array('drupal_retrieve_form', $args);
  $node_form['#post'] = $node_form_state['values'];
  drupal_prepare_form($node_form_id, $node_form, $node_form_state);
  uasort($node_form, 'element_sort');

  // Find all fieldsets.
  $elements = vertical_tabs_get_form_elements($node_form);
  $config = vertical_tabs_get_config($node_type . '_node_form');

  // Merge default values and correct non-key-matching values.
  // @todo Keep settings for non-accessible fieldsets set by more priviledged users?
  $defaults = is_array($config) ? $config : array();
  $options = array();
  foreach ($elements as $key => $element) {
    $options[$key] = $element['#title'];
    if (!isset($defaults[$key]) && !empty($element['#group'])) {
      $defaults[$key] = $key;
    }
  }

  $form['vertical_tabs_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Vertical tabs'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('The selected fieldsets will be rendered as vertical tabs for this content type. The tabs are rendered in the same version as the original form\'s fieldsets.'),
    '#group' => 'additional_settings',
    '#tree' => TRUE,
  );
  $form['vertical_tabs_settings']['form_id'] = array(
    '#type' => 'value',
    '#value' => $node_form_id,
  );
  $form['vertical_tabs_settings']['fieldsets'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Include the following elements in the vertical tabs'),
    '#options' => $options,
    '#default_value' => $defaults,
  );

  array_unshift($form['#submit'], 'vertical_tabs_node_type_form_submit');
}

function vertical_tabs_node_type_form_submit($form, &$form_state) {
  if (isset($form_state['values']['vertical_tabs_settings'])) {
    $settings = $form_state['values']['vertical_tabs_settings'];
    vertical_tabs_save_config($settings['form_id'], $settings['fieldsets']);
    unset($form_state['values']['vertical_tabs_settings']);
  }
}
