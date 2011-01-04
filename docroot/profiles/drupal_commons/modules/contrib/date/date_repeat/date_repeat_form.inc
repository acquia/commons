<?php
// $Id: date_repeat_form.inc,v 1.15.4.19 2010/10/30 10:42:51 karens Exp $
/**
 * @file
 * Code to add a date repeat selection form to a date field and create
 * an iCal RRULE from the chosen selections.
 *
 * Moved to a separate file since it is not used on most pages
 * so the code is not parsed unless needed.
 *
 * Currently implemented:
 * INTERVAL, UNTIL, EXDATE, RDATE, BYDAY, BYMONTHDAY, BYMONTH,
 * YEARLY, MONTHLY, WEEKLY, DAILY
 *
 * Currently not implemented:
 *
 * BYYEARDAY, MINUTELY, HOURLY, SECONDLY, BYMINUTE, BYHOUR, BYSECOND
 *   These could be implemented in the future.
 *
 * COUNT
 *   The goal of this module is to create a way we can parse an iCal
 *   RRULE and pull out just dates for a specified date range, for
 *   instance with a date that repeats daily for several years, we might
 *   want to only be able to pull out the dates for the current year.
 *
 *   Adding COUNT to the rules we create makes it impossible to do that
 *   without parsing and computing the whole range of dates that the rule
 *   will create. COUNT is left off of the user form completely for this
 *   reason.
 *
 * BYSETPOS
 *   Seldom used anywhere, so no reason to complicated the code.
 */
/**
 * Generate the repeat setting form.
 */
function _date_repeat_rrule_process($element, $edit, $form_state, $form) {
  require_once('./'. drupal_get_path('module', 'date_api') .'/date_api_ical.inc');
  
  if (empty($element['#date_repeat_widget'])) {
    $element['#date_repeat_widget'] = module_exists('date_popup') ? 'date_popup' : 'date_select';
  }
  if (is_array($element['#value'])) {
    $element['#value'] = date_repeat_merge($element['#value'], $element);
    $rrule = date_api_ical_build_rrule($element['#value']);
  }
  else {
    $rrule = $element['#value'];
  }
  // Empty the original string value of the RRULE so we can create
  // an array of values for the form from the RRULE's contents.
  $element['#value'] = '';

  $parts = date_repeat_split_rrule($rrule);
  $rrule = $parts[0];
  $exceptions = $parts[1];
  $additions = $parts[2];
  
  $timezone = !empty($element['#date_timezone']) ? $element['#date_timezone'] : date_default_timezone_name();
  $merged_values = date_repeat_merge($rrule, $element);
  
  $UNTIL = '';
  if (!empty($merged_values['UNTIL']['datetime'])) {
    $until_date = date_make_date($merged_values['UNTIL']['datetime'], $merged_values['UNTIL']['tz']);
    date_timezone_set($until_date, timezone_open($timezone));
    $UNTIL = date_format($until_date, DATE_FORMAT_DATETIME);
  }
  $parent_collapsed = !empty($rrule['INTERVAL']) || !empty($rrule['FREQ']) ? 0 : (!empty($element['#date_repeat_collapsed']) ? $element['#date_repeat_collapsed'] : 0);
  $element['#type'] = 'fieldset';
  $element['#title'] = t('Repeat');
  $element['#description'] = theme('advanced_help_topic', 'date_api', 'date-repeat-form') . t('Choose a frequency and period to repeat this date. If nothing is selected, the date will not repeat.');
  $element['#collapsible'] = TRUE;
  $element['#collapsed'] = $parent_collapsed;
  
  // Make sure we don't get floating parts where we don't want them.
  $element['#prefix'] = '<div class="date-clear">';
  $element['#suffix'] = '</div>';
  
  $element['INTERVAL'] = array(
    '#type' => 'select',
    //'#title' => t('Interval'),
    '#default_value' => (!empty($rrule['INTERVAL']) ? $rrule['INTERVAL'] : 0),
    '#options' => INTERVAL_options(),
    '#prefix' => '<div class="date-repeat-input">',
    '#suffix' => '</div>',
  );

  $element['FREQ'] = array(
    '#type' => 'select',
    //'#title' => t('Frequency'),
    '#default_value' => !empty($rrule['FREQ']) ? $rrule['FREQ'] : 'NONE',
    '#options' => FREQ_options(),
    '#prefix' => '<div class="date-repeat-input">',
    '#suffix' => '</div>',
  );

  $element['UNTIL'] = array(
    '#tree' => TRUE,
    '#prefix' => '<div class="date-clear">',
    '#suffix' => '</div>',
    'datetime' => array(
      '#type' => $element['#date_repeat_widget'],
      '#title' => t('Until'),
      '#description' => t('Date to stop repeating this item.'),
      '#default_value' => $UNTIL,
      '#date_timezone' => $timezone,
      '#date_format' => !empty($element['#date_format']) ? date_limit_format($element['#date_format'], array('year', 'month', 'day')) : 'Y-m-d',
      '#date_text_parts'  => !empty($element['#date_text_parts']) ? $element['#date_text_parts'] : array(),
      '#date_year_range'  => !empty($element['#date_year_range']) ? $element['#date_year_range'] : '-3:+3',
      '#date_label_position' => !empty($element['#date_label_position']) ? $element['#date_label_position'] : 'within',
      ),
    'tz' => array('#type' => 'hidden', '#value' => $element['#date_timezone']),
    'all_day' => array('#type' => 'hidden', '#value' => 1),
    'granularity' => array('#type' => 'hidden', '#value' => serialize(array('year', 'month', 'day'))),
    );
  
  $collapsed = TRUE;
  if (!empty($merged_values['BYDAY']) || !empty($merged_values['BYMONTH'])) {
    $collapsed = FALSE;
  }
	// start the advanced fieldset
  $element['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapsed,
    '#description' => t("If no advanced options are selected, the date will repeat on the day of week of the start date for weekly repeats, otherwise on the month and day of the start date. Use the options below to override that behavior to select specific months and days to repeat on. Use the 'Except' box to input dates that should be omitted from the results.") .' ',
    '#prefix' => '<div class="date-clear">',
    '#suffix' => '</div>',
    );

  $element['advanced']['BYMONTH'] = array(
    '#type' => 'select',
    '#title' => date_t('Month', 'datetime'),
    '#default_value' => !empty($rrule['BYMONTH']) ? $rrule['BYMONTH'] : '',
    '#options' => array('' => t('-- Any')) + date_month_names(TRUE),
    '#multiple' => TRUE,
    '#size' => 10,
    '#prefix' => '<div class="date-repeat-input">',
    '#suffix' => '</div>',
  );

  $element['advanced']['BYMONTHDAY'] = array(
    '#type' => 'select',
    '#title' => t('Day of Month'),
    '#default_value' => !empty($rrule['BYMONTHDAY']) ? $rrule['BYMONTHDAY'] : '',
    '#options' => array('' => t('-- Any')) + drupal_map_assoc(range(1, 31)) + drupal_map_assoc(range(-1, -31)),
    '#multiple' => TRUE,
    '#size' => 10,
    '#prefix' => '<div class="date-repeat-input">',
    '#suffix' => '</div>',
  );

  $element['advanced']['BYDAY'] = array(
    '#type' => 'select',
    '#title' => t('Day of Week'),
    '#default_value' => !empty($rrule['BYDAY']) ? $rrule['BYDAY'] : '',
    '#options' => array('' => t('-- Any')) + date_repeat_dow_options(),
    //'#attributes' => array('size' => '5'),
    '#multiple' => TRUE,
    '#size' => 10,
    '#prefix' => '<div class="date-repeat-input">',
    '#suffix' => '</div>',
  );

  $element['exceptions'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => empty($exceptions) ? TRUE : FALSE,
    '#title' => t('Except'),
    '#description' => t('Dates to omit from the list of repeating dates.'),
    '#prefix' => '<div id="date-repeat-exceptions" class="date-repeat">',
    '#suffix' => '</div>',
    );
  $max = !empty($exceptions) ? sizeof($exceptions) : 0;
  for ($i = 0; $i <= $max; $i++) {
    $EXCEPT = '';
    if (!empty($exceptions[$i]['datetime'])) {
      $EXCEPT = $exceptions[$i]['datetime'];
    }
    $element['exceptions']['EXDATE'][$i] = array(
      '#tree' => TRUE,
      'datetime' => array(
        '#type' => $element['#date_repeat_widget'],
        '#default_value' => $EXCEPT,
        '#date_timezone' => !empty($element['#date_timezone']) ? $element['#date_timezone'] : date_default_timezone_name(),
        '#date_format' => !empty($element['#date_format']) ? date_limit_format($element['#date_format'], array('year', 'month', 'day')) : 'Y-m-d',
        '#date_text_parts'  => !empty($element['#date_text_parts']) ? $element['#date_text_parts'] : array(),
        '#date_year_range'  => !empty($element['#date_year_range']) ? $element['#date_year_range'] : '-3:+3',
        '#date_label_position' => !empty($element['#date_label_position']) ? $element['#date_label_position'] : 'within',
        ),
      'tz' => array('#type' => 'hidden', '#value' => $element['#date_timezone']),
      'all_day' => array('#type' => 'hidden', '#value' => 1),
      'granularity' => array('#type' => 'hidden', '#value' => serialize(array('year', 'month', 'day'))),
      );
  }
  
  // collect additions in the same way as exceptions - implements RDATE.
  $element['additions'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => empty($additions) ? TRUE : FALSE,
    '#title' => t('Additional'),
    '#description' => t('Dates to add to the list of repeating dates.'),
    '#prefix' => '<div id="date-repeat-additions" class="date-repeat">',
    '#suffix' => '</div>',
    );
  $max = !empty($additions) ? sizeof($additions) : 0;
  for ($i = 0; $i <= $max; $i++) {
    $RDATE = '';
    if (!empty($additions[$i]['datetime'])) {
      $RDATE = $additions[$i]['datetime'];
    }
    $element['additions']['RDATE'][$i] = array(
      '#tree' => TRUE,
      'datetime' => array(
        '#type' => $element['#date_repeat_widget'],
        '#default_value' => $RDATE,
        '#date_timezone' => !empty($element['#date_timezone']) ? $element['#date_timezone'] : date_default_timezone_name(),
        '#date_format' => !empty($element['#date_format']) ? date_limit_format($element['#date_format'], array('year', 'month', 'day')) : 'Y-m-d',
        '#date_text_parts'  => !empty($element['#date_text_parts']) ? $element['#date_text_parts'] : array(),
        '#date_year_range'  => !empty($element['#date_year_range']) ? $element['#date_year_range'] : '-3:+3',
        '#date_label_position' => !empty($element['#date_label_position']) ? $element['#date_label_position'] : 'within',
        ),
      'tz' => array('#type' => 'hidden', '#value' => $element['#date_timezone']),
      'all_day' => array('#type' => 'hidden', '#value' => 1),
      'granularity' => array('#type' => 'hidden', '#value' => serialize(array('year', 'month', 'day'))),
      );
  }

  // Create an "Add another" button for the exceptions.
  $field_name = $element['#parents'][0];
  $element['exceptions']['exceptions_addmore'] = array(
    '#type' => 'button',
    '#value' => t('Add more exceptions'),
    '#ahah' => array(
      'event' => 'click',
      'path' => 'date_repeat_get_exception_form_ajax/exceptions/' . $field_name,
      'wrapper' => 'date-repeat-exceptions',
      'method' => 'replace',
      'effect' => 'fade'
    )
  );
  // Create an "Add another" button for the additions.
  $field_name = $element['#parents'][0];
  $element['additions']['additions_addmore'] = array(
    '#type' => 'button',
    '#value' => t('Add more additions'),
    '#ahah' => array(
      'event' => 'click',
      'path' => 'date_repeat_get_exception_form_ajax/additions/' . $field_name,
      'wrapper' => 'date-repeat-additions',
      'method' => 'replace',
      'effect' => 'fade'
    )
  );
  
  return $element;
}

/**
 * Ajax callback to get the exceptions form.  This is needed to
 * implement the "Add another" button for the date repeat exceptions.
 * 
 * @param $type - 'exceptions' or 'additions'.
 * @param $field_name - The name of the date field.
 */
function date_repeat_get_exception_form_ajax($type, $field_name) {
  // Get the cached form.  
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  if( !($form = form_get_cache($_POST['form_build_id'], $form_state)) ) {
    drupal_json(array('status' => FALSE, 'data' => ''));
    exit();
  }

  // Set the form state values.
  $form_state = array_merge($form_state, array('values' => $_POST));

  // Set the new form rrule value.
  $form[$field_name]['rrule']['#value'] = $form_state['values'][$field_name]['rrule'];

  // Cache the new form state.
  form_set_cache($_POST['form_build_id'], $form, $form_state);

  // Rebuild the form.
  $form_state = array();
  $form['#post'] = array();
  $form = form_builder($form['form_id']['#value'] , $form, $form_state);

  // Force a rebuild of the Drupal.settings javascript object.
  //   - Borrowed from content.node_form.inc, content_add_more_js function
  $javascript = drupal_add_js(NULL, NULL);
  $output_js = isset($javascript['setting']) ? '<script type="text/javascript">jQuery.extend(Drupal.settings, '. drupal_to_js(call_user_func_array('array_merge_recursive', $javascript['setting'])) .');</script>' : '';

  // Create our output.
  $output = drupal_render($form[$field_name]['rrule'][$type]) . $output_js;

  // Set the new exceptions form.
  drupal_json(array('status' => TRUE, 'data' => $output));
  exit();
}

/**
 * Regroup values back into a consistant array, no matter what state it is in.
 */
function date_repeat_merge($form_values, $element) {
  if (empty($form_values) || !is_array($form_values)) {
    return $form_values;
  }
  if (array_key_exists('advanced', $form_values) || array_key_exists('exceptions', $form_values) || array_key_exists('additions', $form_values)) {
    if (!array_key_exists('advanced', $form_values)) $form_values['advanced'] = array();
    if (!array_key_exists('exceptions', $form_values)) $form_values['exceptions'] = array();
    if (!array_key_exists('additions', $form_values)) $form_values['additions'] = array();
    $form_values = array_merge($form_values, (array) $form_values['advanced'], (array) $form_values['exceptions'], (array) $form_values['additions']);
    unset($form_values['advanced']);
    unset($form_values['exceptions']);
    unset($form_values['additions']);
  }
  if (array_key_exists('BYDAY', $form_values)) unset($form_values['BYDAY']['']);
  if (array_key_exists('BYMONTH', $form_values)) unset($form_values['BYMONTH']['']);
  if (array_key_exists('BYMONTHDAY', $form_values)) unset($form_values['BYMONTHDAY']['']);
      
  if (array_key_exists('UNTIL', $form_values) && is_array($form_values['UNTIL']['datetime'])) {
    $function = $element['#date_repeat_widget'] .'_input_value';
    $until_element = $element;
    $until_element['#value'] = $form_values['UNTIL']['datetime'];
    $until_element['#date_format'] = date_limit_format($element['#date_format'], array('year', 'month', 'day'));
    $form_values['UNTIL']['datetime'] = $function($until_element);
  }
  if (array_key_exists('EXDATE', $form_values) && is_array($form_values['EXDATE'])) {
    $function = $element['#date_repeat_widget'] .'_input_value';
    $exdate_element = $element;
    foreach ($form_values['EXDATE'] as $delta => $value) {
      if (is_array($value['datetime'])) {
        $exdate_element['#value'] = $form_values['EXDATE'][$delta]['datetime'];
        $exdate_element['#date_format'] = date_limit_format($element['#date_format'], array('year', 'month', 'day'));
        $form_values['EXDATE'][$delta]['datetime'] = $function($exdate_element);
      }
    }
  }
  if (array_key_exists('RDATE', $form_values) && is_array($form_values['RDATE'])) {
    $function = $element['#date_repeat_widget'] .'_input_value';
    $rdate_element = $element;
    foreach ($form_values['RDATE'] as $delta => $value) {
      if (is_array($value['datetime'])) {
        $rdate_element['#value'] = $form_values['RDATE'][$delta]['datetime'];
        $rdate_element['#date_format'] = date_limit_format($element['#date_format'], array('year', 'month', 'day'));
        $form_values['RDATE'][$delta]['datetime'] = $function($rdate_element);
      }
    }
  }
  return $form_values;
}

/**
 * Build a RRULE out of the form values.
 */
function date_repeat_rrule_validate($element, &$form_state) {
  require_once('./'. drupal_get_path('module', 'date_api') .'/date_api_ical.inc');
  $form_values = $form_state['values'];
  $field_name = $element['#parents'][0];
  $item = $form_values[$field_name]['rrule'];
  $item = date_repeat_merge($item, $element);
  if (!empty($item['UNTIL']['datetime'])) {
    $date = date_make_date($item['UNTIL']['datetime'], $element['#date_timezone']);
    date_time_set($date, 23, 59, 59);
    date_timezone_set($date, timezone_open('UTC'));
    $item['UNTIL']['datetime'] = date_format($date, DATE_FORMAT_DATETIME);
  }
  $rrule = date_api_ical_build_rrule($item);
  form_set_value($element, $rrule, $form_state);
}

/**
 * Theme the exception list as a table so the buttons line up
 */
function theme_date_repeat_current_exceptions($rows = array()) {
  $rows_info = array();
  foreach ($rows as $key => $value) {
    if (substr($key, 0, 1) != '#') {
      $rows_info[] = array(drupal_render($value['action']), drupal_render($value['display']));
    }
  }
  return theme('table', array(t('Delete'), t('Current exceptions')), $rows_info);
}

/**
 * Theme the exception list as a table so the buttons line up
 */
function theme_date_repeat_current_additions($rows = array()) {
  $rows_info = array();
  foreach ($rows as $key => $value) {
    if (substr($key, 0, 1) != '#') {
      $rows_info[] = array(drupal_render($value['action']), drupal_render($value['display']));
    }
  }
  return theme('table', array(t('Delete'), t('Current additions')), $rows_info);
}

/**
 * Themes the date repeat element.
 */
function theme_date_repeat($element) {
  return theme('form_element', $element, '<div class="container-inline">'. drupal_render($element). '</div>');
}