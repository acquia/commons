<?php

/**
 * @file
 *   Admin configuration pages
 */

/**
 * The admin settings form
 */
function og_features_admin_settings() {
  $form = array();
  $types = array();
  
  // Fetch the feature registry
  $registry = og_features_get_registry();
  
  // If the registy is empty, there is nothing to configure
  if (empty($registry)) {
    return array(
      'empty' => array(
        '#type' => 'item',
        '#value' => t('There are currently no OG features to configure.'),
      ),
    );
  }
  
  // Fetch all available group types
  foreach (node_get_types() as $type) {
    if (og_is_group_type($type->type)) {
      $types[$type->type] = $type->name;
    }
  }
  
  // Make sure we have at least one group type
  if (empty($types)) {
    return array(
      'empty' => array(
        '#type' => 'item',
        '#value' => t('There are currently no group node types to configure.'),
      ),
    );
  }
  
  // Provide a configuration for each group
  foreach ($types as $type => $name) {
    // Build the fieldset for this node type
    $form["node-{$type}"] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => $name,
    );
    
    // Attempt to load the defaults for this node type
    $defaults = og_features_get_node_type_settings($type);
    
    foreach ($registry as $id => $feature) {
      $form["node-{$type}"]["{$type}--{$id}"] = array(
        '#type' => 'radios',
        '#title' => $feature->name,
        '#description' => $feature->description,
        '#default_value' => isset($defaults[$id]) ? $defaults[$id] : OG_FEATURES_ADMIN_TOGGLE_ENABLED,
        '#options' => array(
          OG_FEATURES_ADMIN_TOGGLE_ENABLED => t('Toggle (Enabled by default)'),
          OG_FEATURES_ADMIN_TOGGLE_DISABLED => t('Toggle (Disabled by default)'),
          OG_FEATURES_ADMIN_ENABLED => t('Always enabled'),
          OG_FEATURES_ADMIN_DISABLED => t('Always disabled'),
        ),
      );
    }
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  
  return $form;
}

/**
 * Submit handler for the admin settings form
 */
function og_features_admin_settings_submit(&$form, &$form_state) {
  $types = array();
  
  // Iterate the form values
  foreach ($form_state['values'] as $key => $value) {
    // See if this is a value we are looking for
    if (strstr($key, '--')) {
      // Determine the delimeter position
      $pos = strpos($key, '--');
      // Extract the group type
      if ($type = substr($key, 0, $pos)) {
        // Extract the feature name
        if ($feature = substr($key, $pos + 2)) {
          // Store the setting
          $types[$type][$feature] = $value;
        }
      }
    }
  }
  
  // Iterate over the group node types
  foreach ($types as $type => $settings) {
    // Save a variable for each
    variable_set("og_features_node_type_{$type}", $settings);
  }
  
  // Status message
  drupal_set_message(t('Your settings have been saved.'));
}
