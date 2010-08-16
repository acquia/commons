<?php
// $Id$

/*** FORMS ***/

// Provide a simple form to change time periods
function quant_time_form() {
  $form = array();
  
  $options = array(
    '1_week' => t('1 week'),
    '2_weeks' => t('2 weeks'),
    '1_month' => t('1 month'),
    '3_months' => t('3 months'),
    '6_months' => t('6 months'),
    '1_year' => t('1 year'),
    '2_years' => t('2 years'),
  );
  
  $period = filter_xss($_GET['period']);
  if (!$period || !array_key_exists($period, $options)) {
    $period = '1_month'; // Default value
  }
  
  $form['filter'] = array(
    '#type' => 'fieldset',
    '#description' => t('Select a timeframe and click Update to see what\'s happening on your site during that time, as well as a total for all the activity during that timeframe.'),
  );
  
  $form['filter']['period'] = array(
    '#type' => 'select',
    '#title' => t('Timeframe'),
    '#options'=> $options,
    '#default_value' => $period, 
  ); 
  
  $form['filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );
  
  return $form;
}

function quant_time_form_submit(&$form, $form_state) {
  // Add a query to the URL which will be used to determine the query
  drupal_goto('analytics', 'period=' . $form_state['values']['period']); 
}

/*
 * Provide admin settings form
 */
function quant_admin_settings() {
  $form = array();
  
  // Get available quants
  $options = array();
  $quants = quant_get();
  foreach ($quants as $quant) {
    $options[$quant->id] = $quant->label;
  }
  
  // Generate default quant selection
  $default = array();
  if (!($default = variable_get('quant_visible', array()))) {
    if (empty($default)) {
      foreach ($options as $id => $label) {
        $default[] = $id;
      }
    }
  }
  
  $form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['display']['quant_visible'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Show analytics for the following site items'),
    '#default_value' => $default,
    '#options' => $options,
    '#description' => t('The checked objects will be shown on the analytics page.'),
  );
  $form['display']['quant_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Chart width'),
    '#default_value' => variable_get('quant_width', 500),
    '#size' => 6,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#description' => t('Specify the graph width in pixels. The Chart API will reject charts that are too wide.'),
  );
  $form['display']['quant_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Chart height'),
    '#default_value' => variable_get('quant_height', 200),
    '#size' => 6,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#description' => t('Specify the graph height in pixels. The Chart API will reject charts that are too tall.'),
  );
  
  // Generate the color palette
  $palette = quant_load_palette();
  
  $form['color'] = array(
    '#type' => 'fieldset',
    '#title' => t('Color settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Specify the colors that the charts will be rendered in.'),
  );
  
  for ($i = 0; $i < QUANT_PALETTE_AMOUNT; $i++) {
    $form['color']['quant_palette_color_' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Color #' . ($i + 1)),
      '#default_value' => $palette[$i],
      '#field_prefix' => '#',
      '#size' => 10,
      '#maxlength' => 6,
    );
  }
 
  return system_settings_form($form); 
}

function quant_admin_settings_validate(&$form, &$form_state) {
  // Check width
  if (!is_numeric($form_state['values']['quant_width']) ||
   strlen($form_state['values']['quant_width']) > 4 ||
   strlen($form_state['values']['quant_width']) < 2) {
    form_set_error('quant_width', t('The width must be a number that is between 2 and 4 digits'));
  }
  
  // Check height
  if (!is_numeric($form_state['values']['quant_height']) ||
   strlen($form_state['values']['quant_height']) > 4 ||
   strlen($form_state['values']['quant_height']) < 2) {
    form_set_error('quant_height', t('The height must be a number that is between 2 and 4 digits'));
  }
  
  // Iterate through colors
  $colors = array(); // Store all colors in a single array
  for ($i = 0; $i < QUANT_PALETTE_AMOUNT; $i++) {
    $color = $form_state['values']['quant_palette_color_' . $i];
    // If color exists, make sure it's valid
    if ($color) { 
      $colors[] = strtoupper($color);
      // Remove form value to avoid multiple color variables
      unset($form_state['values']['quant_palette_color_' . $i]);
    }
  }
  
  // Make sure we at least have one color
  if (empty($colors)) {
    form_set_error('color', t('You need to enter at least one color.')); 
  }
  else {
    // Save colors in a single variable
    variable_set('quant_palette', $colors);
  }
}
