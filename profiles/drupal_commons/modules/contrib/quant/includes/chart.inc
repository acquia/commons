<?php

/**
 * @file
 *   Chart building functions
 */
   
/**
 * Wrapper for chart generation functions
 */
function quant_generate_chart(&$quant) {
  // Initialize the chart
  $function = "_quant_init_{$quant->chartType}_chart";
  $function($quant);
  // Currently only supports adding item sum to title
  quant_override_title($quant);
  // Give the chart color
  quant_chart_add_color($quant);
  // Set the size of the chart
  quant_chart_add_size($quant);
  // Generate and return the chart
  $function = "_quant_generate_chart_{$quant->dataType}";
  $function($quant);
}

/**
 * Optionally override a chart title
 */
function quant_override_title(&$quant) {
  // If the quant wants the sum of item amounts in the title
  if ($quant->labelsum) {
    $sum = 0;
    foreach ($quant->data as $value) {
      if ($quant->dataType == 'multiple') {
        foreach ($value as $amount) {
          $sum = $sum + $amount;
        }
      }
      else {
        $sum = $sum + $value;
      }
    }
    
    $quant->chart['#title'] = chart_title($quant->label . ' (' . t('Total') . ": $sum)");
  }
}

function _quant_load_palette($random = FALSE) {
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

function quant_chart_add_color(&$quant) {
  // Load the color palette
  $palette = _quant_load_palette(TRUE); 
  
  // If quant is singular, add a random color
  if ($quant->dataType == 'single') {
    $quant->chart['#data_colors'][] = $palette[rand(0, count($palette))];
  }
  else {
    for ($i = 0; $i < count($palette); $i++) {
      $quant->chart['#data_colors'][] = $palette[$i];
    }
  }
}

function quant_chart_add_size(&$quant) {
  $quant->chart['#size'] = chart_size(
    variable_get('quant_width', 500), 
    variable_get('quant_height', 200)
  ); 
}

// Initialize the creation of a line chart
function _quant_init_line_chart(&$quant) {
  $quant->chart = array(
    '#chart_id' => $quant->id,
    '#title' => chart_title($quant->label),
    '#type' => CHART_TYPE_LINE,
    '#adjust_resolution' => TRUE,
    '#chart_fill' => chart_fill('c', 'fff'),          
    '#grid_lines' => chart_grid_lines(20, 20, 1, 5), 
  );
}

// Initialize the creation of a bar chart
function _quant_init_bar_chart(&$quant) {
  $quant->chart = array(
    '#chart_id' => $quant->id,
    '#title' => chart_title($quant->label),
    '#type' => CHART_TYPE_BAR_V,
    '#adjust_resolution' => TRUE,
    '#grid_lines' => chart_grid_lines(30, 20),
    '#bar_size' => chart_bar_size(45, 15), 
  );  
}

// Initialize the creation of a bar chart
function _quant_init_pie_chart(&$quant) {
  $quant->chart = array(
    '#chart_id' => $quant->id,
    '#title' => chart_title($quant->label),
    '#type' => CHART_TYPE_PIE,
    '#adjust_resolution' => TRUE,
  );
}

/**
 * Take formatted data for a count chart and convert to 
 * a format that the charts can understand
 */
function _quant_generate_chart_count(&$quant) {
  $max = 0; // Determine the highest available value on y-axis
  
  foreach ($quant->data as $key => $value) {
    $quant->chart['#data'][] = $value;
    
    // If pie chart, let's add the numeric value to the label
    if ($quant->chartType == 'pie') {
      quant_x_label($quant, $key . ' (' . $value . ')');
    }
    else {
      quant_x_label($quant, $key);
    }
    
    $max = max($max, $value);
  }
  
  quant_y_range($quant, 0, $max);

  $quant->render = chart_render($quant->chart);
}

/**
 * Take formatted data for a single-point chart and convert to 
 * a format that the charts can understand
 */
function _quant_generate_chart_single(&$quant) {
  $max = 0; // Determine the highest available value on y-axis
  $interval = 0; // Counter to help break the x-axis label
  $period = ceil(count($data) / 10); // Period when to break x-axis

  foreach ($quant->data as $date => $value) {
    // Only show the X label every calculated period
    if(!$interval) {
      quant_x_label($quant, $date);
      $interval = $period;
    }
    $quant->chart['#data'][] = $value;
    $max = max($max, $value);
    $interval--;
  }
  
  quant_y_range($quant, 0, $max);

  $quant->render = chart_render($quant->chart);
}

/**
 * Take formatted data for a multi-point chart and convert to 
 * a format that the charts can understand
 */
function _quant_generate_chart_multiple(&$quant) {
  $max = 0; // Determine the highest available value on y-axis
  $interval = 0; // Counter to help break the x-axis label
  $x = FALSE; // Only register the x-axis labels once
  
  foreach ($quant->data as $type => $values) {
    // Set type as a legend
    $quant->chart['#legends'][] = $type; 
    // Period when to break x-axis
    $period = ceil(count($data[$type]) / 10);
    
    foreach ($values as $date => $value) {
      $quant->chart['#data'][$type][] = $value;
      $max = max($max, $value);
      
      if (!$x) { // Only set x-axis labels once
        if(!$interval) {
          quant_x_label($quant, $date);
          $interval = $period;
        }
        $interval--;
      }
    }
    
    $x = TRUE; // x-axis labels have been set
  }
  
  quant_y_range($quant, 0, $max);

  $quant->render = chart_render($quant->chart);
}

/**
 * Add an x-axis label to the chart
 * 
 * @param &$quant
 *   A quant object
 * @param $label
 *   The label for the x-axis
 */
function quant_x_label(&$quant, $label) {
  $quant->chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][0][] = chart_mixed_axis_label($label);
}

/**
 * Add an y-axis range to the chart
 * 
 * @param &$quant
 *   A quant object
 * @param $min
 *   The minimum value for the y-axis
 * @param $max
 *   The maximum value for the y-axis
 */
function quant_y_range(&$quant, $min, $max) {
  $max = max($max, 1); // Prevent a max that's zero
  $quant->chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_range_label($min, $max);
}
