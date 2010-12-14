<?php
// $Id: quant.chart.inc,v 1.1.2.4 2010/09/16 15:40:33 mikestefff Exp $

/**
 * @file
 *   Chart building functions
 */

/**
 * Initialize a chart
 * 
 * This function returns a chart with it's type declared,
 * colors added, size and title set
 * 
 * @param $quant
 *   A quant object
 * @param $data
 *   The data array used to populate the chart
 * @return
 *   An initialized chart array
 */
function quant_init_chart($quant, $data) {
  $chart = '';
  
  switch ($quant->chartType) {
    case 'bar':
      $chart = quant_init_bar_chart($quant);
      break;
    case 'pie':
      $chart = quant_init_pie_chart($quant);
      break;
    case 'line':
    default:
      $chart = quant_init_line_chart($quant);
  }
  
  // Currently only supports adding item sum to title
  quant_override_title($chart, $quant, $data);
  // Give the chart color
  quant_chart_add_color($chart, $quant);
  // Set the size of the chart
  quant_chart_add_size($chart);
  
  return $chart;
}

/**
 * Optionally override a chart title
 */
function quant_override_title(&$chart, $quant, $data) {
  // If the quant wants the sum of item amounts in the title
  if ($quant->labelsum) {
    $sum = 0;
    foreach ($data as $value) {
      if ($quant->dataType == 'multiple') {
        foreach ($value as $amount) {
          $sum = $sum + $amount;
        }
      }
      else {
        $sum = $sum + $value;
      }
    }
    
    $chart['#title'] = chart_title($quant->label . ' (' . t('Total') . ": $sum)");
  }
}

function quant_load_palette($random = FALSE) {
  $palette = variable_get('quant_palette', array());
  
  if (!$palette) {
    $default_palette = _chart_color_schemes();
    $palette = $default_palette['default'];
  }
  
  // Random
  if ($random) {
    shuffle($palette);
  }
  
  return $palette;
}

function quant_chart_add_color(&$chart, $quant) {
  // Load the color palette
  $palette = quant_load_palette(TRUE); 
  
  // If quant is singular, add a random color
  if ($quant->dataType == 'single') {
    $chart['#data_colors'][] = $palette[rand(0, count($palette))];
  }
  else {
    for ($i = 0; $i < count($palette); $i++) {
      $chart['#data_colors'][] = $palette[$i];
    }
  }
}

function quant_chart_add_size(&$chart) {
  $chart['#size'] = chart_size(
    variable_get('quant_width', 500), 
    variable_get('quant_height', 200)
  ); 
}

// Initialize the creation of a line chart
function quant_init_line_chart($quant) {
  $chart = array(
    '#chart_id' => $quant->id,
    '#title' => chart_title($quant->label),
    '#type' => CHART_TYPE_LINE,
    '#adjust_resolution' => TRUE,
    '#chart_fill' => chart_fill('c', 'fff'),          
    '#grid_lines' => chart_grid_lines(20, 20, 1, 5), 
  );
    
  return $chart;
}

// Initialize the creation of a bar chart
function quant_init_bar_chart($quant) {
  $chart = array(
    '#chart_id' => $quant->id,
    '#title' => chart_title($quant->label),
    '#type' => CHART_TYPE_BAR_V,
    '#adjust_resolution' => TRUE,
    '#grid_lines' => chart_grid_lines(30, 20),
    '#bar_size' => chart_bar_size(45, 15), 
  );  
  
  return $chart;
}

// Initialize the creation of a bar chart
function quant_init_pie_chart($quant) {
  $chart = array(
    '#chart_id' => $quant->id,
    '#title' => chart_title($quant->label),
    '#type' => CHART_TYPE_PIE,
    '#adjust_resolution' => TRUE,
  );  
  
  return $chart;
}

function quant_x_label(&$chart, $label) {
  $chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][0][] = chart_mixed_axis_label($label);
}

function quant_y_range(&$chart, $min, $max) {
  $max = max($max, 1); // Prevent a max that's zero
  $chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_range_label($min, $max);
}
