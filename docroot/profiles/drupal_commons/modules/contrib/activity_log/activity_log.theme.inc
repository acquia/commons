<?php

/**
 * @file
 *   Functions that help theme activity messages.
 */

//==================
// THEME FUNCTIONS.
//==================

/**
 * Renders an individual activity log message.
 *
 * @param $record
 *   A fully qualified activity record.
 * @param $reset
 *   Whether to reset the cache for this record.
 * @return
 *   The themed activity message.
 */
function theme_activity_log_item($record, $reset = FALSE) {
  static $user_lang;
  if (!isset($user_lang)) {
    $user_lang = user_preferred_language($GLOBALS['user'])->language;
  }
  if ($reset || empty($record->cacheable) || empty($record->cached) || empty($record->cached[$user_lang])) {
    if (empty($record->template)) {
      // If we can't find the template, make sure we have all of them available.
      _activity_log_rebuild_templates();
      watchdog('activity_log', 'The Activity Log templates were rebuilt for missing template ID @id', array('@id' => $record->tid), WATCHDOG_WARNING);
      return;
    }
    $classes = array();
    $classes[] = 'activity-log-display-type-'. $record->display_type;
    $classes[] = 'activity-log-template-'. $record->tid;
    $classes[] = 'activity-log-rule-'. $record->rule;
    //$classes[] = 'activity-log-action-'. drupal_strtolower(preg_replace('%[^\w\-]%', '', str_replace(' ', '_', $record->action_label)));
    if (count($record->events) === 1) {
      $classes[] = 'activity-message-single';
    }
    else {
      $classes[] = 'activity-message-grouped';
    }
    $message = '<div id="activity-log-item-'. $record->mid .'" class="activity-log-message '. implode(' ', $classes) .'">'. activity_log_evaluate_record($record) .'</div>';
    $record->cached[$user_lang] = $message;
    db_query("UPDATE {activity_log_messages} SET cached = '%s' WHERE mid = %d", serialize($record->cached), $record->mid);
    return $message;
  }
  else {
    if (!empty($record->resources['css'])) {
      foreach ($record->resources['css'] as $resource) {
        drupal_add_css($resource);
      }
    }
    if (!empty($record->resources['js'])) {
      foreach ($record->resources['js'] as $resource) {
        drupal_add_js($resource);
      }
    }
    return $record->cached[$user_lang];
  }
}

/**
 * Collapses an array to a string summarizing its elements.
 *
 * Depending on the number of elements in the collection, the result could be
 * in one of the following formats:
 * - [nothing]
 * - Joe
 * - Jack and Jill
 * - Jack, Jill, and Joe
 * - Jane, Jim, and N other people
 *
 * @param $collection
 *   An array of strings to collapse into a single string.
 * @param $method
 *   The method to use to collapse the collection. Should be the name of a
 *   function that takes the collection array and the number of items in that
 *   array as arguments.
 * @return
 *   A string representing the collapsed collection array.
 */
function theme_activity_log_collapse($collection = array(), $method = 'activity_log_collapse_inline') {
  $count = count($collection);
  if ($count == 0) {
    return;
  }
  elseif ($count === 1) {
    $output = $collection[0];
  }
  else {
    $output = $method($collection, $count);
  }
  return '<span class="activity-log-collection activity-log-collection-method-'. $method .'">'. $output .'</span>';
}

//================================
// COLLECTION COLLAPSING METHODS.
//================================

/**
 * Collapses an array of strings into the format "A, B, and 3 others."
 */
function activity_log_collapse_inline($collection, $count) {
  if ($count == 2) {
    $output = t('!first and !second', array('!first' => $collection[0], '!second' => $collection[1]));
  }
  elseif ($count == 3) {
    $output = t('!first, !second, and !third', array(
      '!first' => $collection[0],
      '!second' => $collection[1],
      '!third' => $collection[2],
    ));
  }
  else {
    $path = drupal_get_path('module', 'activity_log');
    drupal_add_css($path .'/activity_log.css');
    drupal_add_js($path .'/activity_log.js');
    $first = array_pop($collection);
    $second = array_pop($collection);
    $output = t('!first, !second, and <a class="activity-log-collection-more" href="!here">@count others</a>', array(
      '!first' => $first,
      '!second' => $second,
      '!here' => url($_GET['q'], array('absolute' => TRUE)),
      '@count' => $count - 2,
    ));
    $collection[] = $second;
    $output .= '<div class="activity-log-collection-more-expand">'.
      t('!collection, and !last', array('!collection' => implode(', ', $collection), '!last' => $first))
    .'</div>';
  }
  return $output;
}

/**
 * Collapses an array of strings into a horizontal list, e.g. "A B C D".
 */
function activity_log_collapse_list_horizontal($collection, $count) {
  drupal_add_css(drupal_get_path('module', 'activity_log') .'/activity_log.css');
  return theme('item_list', $collection, NULL, 'ul', array('class' => 'activity-log-collection-list-horizontal'));
}

/**
 * Collapses an array of strings into a vertical list, e.g.:
 * - A
 * - B
 * - C
 * - D
 */
function activity_log_collapse_list_vertical($collection, $count) {
  drupal_add_css(drupal_get_path('module', 'activity_log') .'/activity_log.css');
  return theme('item_list', $collection, NULL, 'ul', array('class' => 'activity-log-collection-list-vertical'));
}

//===================
// HELPER FUNCTIONS.
//===================

/**
 * Evaluate the template for a given activity record.
 *
 * @param $record
 *   The activity record whose template should be evaluated.
 * @return
 *   The text of an activity message.
 */
function activity_log_evaluate_record($record) {
  $time = time();
  rules_include('rules');
  $user_lang = user_preferred_language($GLOBALS['user'])->language;
  $default_lang = language_default('language');
  // Get the stored data we need to apply the Rules input evaluators.
  $master_element = array('#settings' => array(
    'placeholder' => '',
    'grouping' => array(
      'group_summary' => $record->group_summary,
      'templates' => $record->group_template,
    ),
    'visibility' => array(
      'stream_owner_id' => '',
      'viewer_id' => '',
    ),
    'templates' => $record->template,
    'acting_uid' => '',
    'tid' => $record->tid,
    '#eval input' => $record->eval_input,
  ));
  // Evaluate all of our grouped events.
  $template = '';
  $group_template = '';
  $names = array();
  $collection = array();
  foreach ($record->events as $event) {
    $element = $master_element;
    // Reconstruct the Rules State as if the event was triggered just now.
    $state = $event->id_map['state'];
    foreach ($state['variables'] as $type => $info) {
      $info->data->_data = activity_log_get_variable($type, $event->id_map);
    }
    // Apply the Rules input evaluators.
    rules_apply_input_evaluators($element, $state);
    // Keep track of the evaluated templates.
    $templates = $element['#settings']['templates'];
    $template = empty($templates[$user_lang]['template']) ? $templates[$default_lang]['template'] : $templates[$user_lang]['template'];
    $group_templates = $element['#settings']['grouping']['templates'];
    $group_template = empty($group_templates[$user_lang]['template']) ? $group_templates[$default_lang]['template'] : $group_templates[$user_lang]['template'];
    // Compute the group template variables.
    if (strpos($group_template, '[names]') !== FALSE) {
      $acting_user = activity_log_user_load($event->acting_uid);
      $names[] = theme('username', $acting_user);
    }
    if (strpos($group_template, '[collection]') !== FALSE) {
      $collection[] = $element['#settings']['grouping']['group_summary'];
    }
  }
  if (count($record->events) === 1) {
    return $template;
  }
  $collection = array_unique($collection);
  return str_replace(
    array('[names]', '[collection]', '[count]'),
    array(
      theme('activity_log_collapse', array_unique($names)),
      theme('activity_log_collapse', $collection, $record->collapse_method),
      count($collection)
    ),
    $group_template
  );
}

/**
 * Load an object in its current state so that we can replace the old version.
 *
 * It is mostly important to do this so that Token executes the correct
 * replacements. We load the new objects by identifying their Rules class type
 * and executing its load() method.
 */
function activity_log_get_variable($type, $id_map) {
  if (class_exists($id_map[$type]['class'])) {
    $object = new $id_map[$type]['class'];
    return $object->load($id_map[$type]['id']);
  }
}
