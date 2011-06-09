<?php

/**
 * @file
 *   Provides Rules integration for Facebook-style Micropublisher.
 */

/**
 * Implementation of hook_rules_event_info().
 */
function fbsmp_rules_event_info() {
  return array(
    'fbsmp_delete_status' => array(
      'label' => t('User deletes a FBSS status which has a FBSMP attachment'),
      'module' => 'Facebook-style Micropublisher',
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The FBSS status object')),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The FBSMP attachment object')),
      ),
    ),
    'fbsmp_edit_status' => array(
      'label' => t('User edits a FBSS status which has a FBSMP attachment'),
      'module' => 'Facebook-style Micropublisher',
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The old FBSS status object.')),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The old FBSMP attachment object')),
      ),
    ),
    'fbsmp_add_status' => array(
      'label' => t('User adds a FBSS status which has a FBSMP attachment'),
      'module' => 'Facebook-style Micropublisher',
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The FBSS status object')),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The FBSMP attachment object')),
      ),
    ),
  );
}

/**
 * Implementation of hook_rules_condition_info().
 */
function fbsmp_rules_condition_info() {
  
  $plugins = fbsmp_get_plugins();
  $items = array();
  
  foreach ($plugins as $plugin => $info) {
    $name = isset($info['name']) ? $info['name'] : $plugin;
    $items['fbsmp_attachment_is_'. $plugin] = array(
      'label' => t('The FBSS status has !pluginobject attachment', array('!pluginobject' => $name)),
      'arguments' => array(
        'plugin' => array('type' => 'value', 'default value' => $plugin),
        'attachment' => array('type' => 'fbsmp', 'label' => t('The FBSMP attachment object.')),
      ),
      'base' => 'fbsmp_check_attachment_condition',
      'module' => 'Facebook-style Micropublisher',
    );
  }
  
  return $items;
}

/**
 * Checks if the attachment is of given plugin type.
 */
function fbsmp_check_attachment_condition($plugin, $attachment) {
  return ($plugin == $attachment->type);
}

/**
 * Implementation of hook_rules_action_info().
 */
function fbsmp_rules_action_info() {
  return array(
    'fbsmp_load_action' => array(
      'label' => t('Load a FBSMP attachment object'),
      'new variables' => array(
        'attachment_loaded' => array('type' => 'fbsmp', 'label' => t('The loaded FBSMP attachment')),
      ),
      'help' => t('Enter the Status ID of the status for which attachment should be loaded.'),
      'module' => 'Facebook-style Micropublisher',
      'eval input' => array('sid'),
    ),
  );
}

/**
 * Builds the form for loading a status.
 */
function fbsmp_load_action_form($settings, &$form) {
  $settings += array('sid' => '');
  $form['settings']['sid'] = array(
    '#type' => 'textfield',
    '#title' => t('Status ID'),
    '#default_value' => $settings['sid'],
    '#required' => TRUE,
  );
}

/**
 * Loads a status.
 */
function fbsmp_load_action($settings) {
  return array('attachment_loaded' => fbsmp_load($settings['sid']));
}

/**
 * Implementation of hook_rules_data_type_info().
 */
function fbsmp_rules_data_type_info() {
  return array(
    'fbsmp' => array(
      'label' => t('FBSMP attachment to FBSS status'),
      'class' => 'rules_data_type_fbsmp',
      'savable' => FALSE,
      'identifiable' => TRUE,
      'use_input_form' => FALSE,
      'module' => 'Facebook-style Micropublisher',
    ),
  );
}

/**
 * Defines the rules node data type.
 */
class rules_data_type_fbsmp extends rules_data_type {
  function load($sid) {
    return fbsmp_load($sid);
  }
  function get_identifier() {
    $attachment = &$this->get();
    return $attachment->sid;
  }
}