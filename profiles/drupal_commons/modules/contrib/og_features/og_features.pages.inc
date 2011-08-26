<?php

/**
 * Group feature selection form
 */
function og_features_feature_form(&$form_state, $group) {
  $form = array();
  // Fetch the og features registry
  $registry = og_features_get_registry();
  
  // Iterate all the available features to provide a toggle switch
  foreach ($registry as $key => $feature) {
    // Make sure this feature can be toggled by this group
    if (!og_features_feature_can_toggle($group, $key)) {
      continue;  
    }
    
    $form["feature-{$key}"]["name-{$key}"] = array(
      '#type' => 'item',
      '#value' => $feature->name,
    );
    $form["feature-{$key}"]["description-{$key}"] = array(
      '#type' => 'item',
      '#value' => $feature->description,
    );
    $form["feature-{$key}"]["toggle-{$key}"] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($group->features_disabled[$key]) ? 0 : 1,
    );
  }
  
  // Store the group
  $form['group'] = array(
    '#type' => 'value',
    '#value' => $group,
  );
  
  // Submit button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 * Submit the group features form
 */
function og_features_feature_form_submit(&$form, &$form_state) {
  // Extract the group
  $group = $form_state['values']['group'];
  
  // Collect the disabled features
  $features = array();
  foreach ($form_state['values'] as $key => $value) {
    if (substr($key, 0, 7) == 'toggle-') {
      $feature = substr($key, 7);
      $features[$feature] = $value;
    }
  }
  
  // Save the new settings
  if (!og_features_save_feature_settings($group, $features)) {
    drupal_set_message(t('An error occurred while trying to save your settings. Please try again.'), 'error');
    watchdog('og_features', t('An error occurred while trying to save feature settings for group !nid', array('!nid' => $group->nid)), array(), WATCHDOG_ERROR);
    return;
  }
  
  // Alert other modules about the change
  module_invoke_all('og_features_toggle', $group, $features);
  
  // Set a message
  drupal_set_message(t('Your settings have been saved successfully'));
}
