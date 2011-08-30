<?php

/**
 * @file
 *   Functions used to convert Drupal data into chart format
 */

/**
 * Generate chart data for a multiple data point over
 * a time period
 * 
 * @see quant_build_data()
 */
function _quant_build_data_multiple(&$quant) {
  $data = array();
  $dates = array();
  // Extract the days
  $days = $quant->days;
  // Extract the period
  $period = $quant->period;
  // Determine when the starting time is
  $start = is_array($period) ? $period[1] : time();
  // The date() format to use. We compare by month if there are more than 96 days.
  $format = ($days > 75) ? QUANT_DATE_MONTH_FORMAT : QUANT_DATE_DAY_FORMAT;
  // Whether or not to jump by day or month
  $interval = ($days > 75) ? 2629743 : 86400;
  // Possibly convert days to months
  $steps = ($days > 75) ? ($days / 30) : $days;
  // Extract the field
  $field = $quant->field;
  // Extract the group field
  $group = $quant->group;
  
  // Place the items into an array for initial grouping by $group
  // For example: $data['page'] = array('May 10', 'May 18');
  while ($item = db_fetch_object($quant->items)) {
    $data[$item->$group][] = date($format, $item->$field);
  }
  
  // Iterate through each group of items and calculate the amount of
  // items for each time period
  foreach ($data as $type => $values) {
    // Create a new array that's preformatted with a key for
    // every single time period
    $dates[$type] = _quant_build_date_array($start, $steps, $interval, $format);

    // Increment for each time period
    foreach ($values as $value) {
      if (isset($dates[$type][$value])) {
        $dates[$type][$value]++;
      }
    }
    
    // Set in ascending order
    $dates[$type] = array_reverse($dates[$type]);
  }
  
  // Remove the database resource
  unset($quant->items);
  
  $quant->data = $dates;
}

/**
 * Generate chart data for a singular data point across
 * a time period
 * 
 * @see quant_build_data()
 */
function _quant_build_data_single(&$quant) {
  // Extract the days
  $days = $quant->days;
  // Extract the period
  $period = $quant->period;
  // Determine when the starting time is
  $start = is_array($period) ? $period[1] : time();
  // The date() format to use. We compare by month if there are more than 183 days.
  $format = ($days > 183) ? QUANT_DATE_MONTH_FORMAT : QUANT_DATE_DAY_FORMAT;
  // Whether or not to jump by day or month
  $interval = ($days > 183) ? 2629743 : 86400;
  // Possibly convert days to months
  $steps = ($days > 183) ? ($days / 30) : $days;
  // Extract the database field
  $field = $quant->field;

  // Create a new array that's preformatted with a key for
  // every single time period
  $dates = _quant_build_date_array($start, $steps, $interval, $format); 
 
  // Calculate the amount of occurrences per time period
  while ($item = db_fetch_object($quant->items)) {
    if (isset($dates[date($format, $item->$field)])) {
      $dates[date($format, $item->$field)]++;
    }
  }
  
  // Set in ascending order
  $dates = array_reverse($dates);
  
  // Remove the database resource
  unset($quant->items);
  
  $quant->data = $dates;
}

/**
 * Generate chart data for an aggregate (count) data point 
 * across a time period
 * 
 * @see quant_build_data()
 */
function _quant_build_data_count(&$quant) {
  $quant->data = array();

  while($item = db_fetch_array($quant->items)) {
    $quant->data[$item[$quant->count]] = $item["COUNT({$quant->count})"]; 
  }
  
  // Remove the database resource
  unset($quant->items);
}

/**
 * Build the date array for charts to fill plotted data on
 * 
 * @param $start
 *   A timestamp representing the day to begin
 * @param $steps
 *   The number of steps (days/months) to go back
 * @param $interval
 *   A numeric value representing the step size in seconds
 * @param $format
 *   The date format to be used in date()
 * @return
 *   An array keyed with the date formatted by format. All values are 
 *   initially set to 0.
 */
function _quant_build_date_array($start, $steps, $interval, $format) {
  $dates = array();
  for ($i = 0; $i < $steps; $i++) {
    $dates[date($format, $start)] = 0;
    $start -= $interval; // Backtrack a period
  }
  return $dates;
}
