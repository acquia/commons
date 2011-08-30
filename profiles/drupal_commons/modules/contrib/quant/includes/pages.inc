<?php

/**
 * @file
 *   Page callbacks
 */
 
/**
 * The analytics page callback
 */
function quant_page() {
  quant_include('forms');
  $charts = array();
  
  // Get time period or interval
  $period = _quant_get_time_from_url();
  
  // Fetch all available quants
  if ($period) {
    $quants = quant_get_quants();
    foreach ($quants as $quant) {
      // Check to see if this quant should be shown
      if ($allowed = variable_get('quant_visible', array())) {
        if (isset($allowed[$quant->id]) && !$allowed[$quant->id]) {
          continue;
        }
      }
      // Process the quant
      $charts[] = quant_process($quant, $period);
    }
  }
  else {
    drupal_set_message(t('Invalid timeframe arguments provided.'), 'error');
  }

  // Add externals
  drupal_add_css(drupal_get_path('module', 'quant') . '/theme/quant.css');
  
  // Theme and return the page
  return theme('quant_page', drupal_get_form('quant_time_form'), $charts);
}
