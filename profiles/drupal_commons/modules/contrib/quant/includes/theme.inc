<?php

/**
 * @file
 *   Theme wrappers
 */

/**
 * Theme wrapper for the quant analytics page
 *
 * @param $form
 *   The datepicker form, in HTML.
 * @param $charts
 *   An array of generated charts.
 */
function theme_quant_page($form, $charts) {
  $content = '';
  $content .= $form;
  if ($charts) {
    foreach ($charts as $chart) {
      $content .= $chart;
    }
  }
  return '<div id="quant-page">' . $content . '</div>';
}

/**
 * Theme wrapper for quant_time_form()
 */
function theme_quant_time_form($form) {
  $output = '';
  
  $output .= '<fieldset>';
  
  $output .= '<div class="description">';
  $output .= drupal_render($form['message']);
  $output .= '</div>';
  
  $output .= '<div class="quant-option-row">';
  $output .= drupal_render($form['option']['period']);
  $output .= drupal_render($form['period']);
  $output .= '</div>';
  
  $output .= '<div class="quant-option-row">';
  $output .= drupal_render($form['option']['custom']);
  $output .= '<span class="description">From:</span>';
  $output .= drupal_render($form['custom_from']);
  $output .= '<span class="description">To:</span>';
  $output .= drupal_render($form['custom_to']);
  $output .= '<span class="description"><i>Format MM/DD/YYYY</i></span>';
  $output .= '</div>';
  
  $output .= drupal_render($form);
  
  $output .= '</fieldset>';
  
  return $output;
}
