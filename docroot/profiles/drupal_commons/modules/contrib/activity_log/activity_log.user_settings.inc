<?php

/**
 * @file
 *   Form handlers for user settings.
 */

/**
 * Builds the form that allows disabling seeing certain activity types.
 *
 * @param $account
 *   The user whose form should be built.
 * @return
 *   A Form API array representing the form.
 */
function _activity_log_user_form($account) {
  $form = array();
  $result = db_query("SELECT * FROM {activity_log_action_names} WHERE public_name <> ''");
  $types = array();
  $default_values = array();
  while ($row = db_fetch_object($result)) {
    $types[$row->pid] = t($row->public_name);
    $default_values[$row->pid] = $row->pid;
  }
  if (empty($types)) {
    return;
  }
  $result = db_query("SELECT pid FROM {activity_log_disabled_types} WHERE uid = %d", $account->uid);
  $disabled = array();
  while ($row = db_fetch_object($result)) {
    $default_values[$row->pid] = 0;
    $disabled[] = $row->pid;
  }
  $form['activity_log'] = array(
    '#type' => 'fieldset',
    '#title' => t('Activity stream settings'),
    '#description' => t('Enable or disable the types of activity you would like to see when you view your activity stream.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['activity_log']['activity_log_types'] = array(
    '#type' => 'checkboxes',
    '#options' => $types,
    '#default_value' => $default_values,
  );
  $form['activity_log']['activity_log_types_all_values'] = array(
    '#type' => 'value',
    '#value' => array_keys($types),
  );
  $form['activity_log']['activity_log_types_disabled_values'] = array(
    '#type' => 'value',
    '#value' => $disabled,
  );
  return $form;
}

/**
 * Saves the form that allows disabling seeing certain activity types.
 */
function _activity_log_user_form_submit($edit) {
  $all = $edit['activity_log_types_all_values'];
  $disabled = $edit['activity_log_types_disabled_values'];
  $values = array_filter($edit['activity_log_types']);
  $delete = array();
  $add = array();
  foreach ($all as $type) {
    // Previously disabled, now enabled; delete record of it being disabled
    if (in_array($type, $disabled) && in_array($type, $values)) {
      $delete[] = $type;
    }
    // Previously enabled, now disabled; add record of it being disabled
    elseif (!in_array($type, $disabled) && !in_array($type, $values)) {
      $add[] = $type;
    }
  }
  if (!empty($delete)) {
    db_query("DELETE FROM {activity_log_disabled_types} WHERE pid IN (". db_placeholders($delete) .")", $delete);
  }
  if (!empty($add)) {
    $subquery = array();
    $args = array();
    foreach ($add as $type) {
      $subquery[] = "(%d, %d)";
      $args[] = $account->uid;
      $args[] = $type;
    }
    db_query("INSERT INTO {activity_log_disabled_types} (uid, pid) VALUES". implode(',', $subquery), $args);
  }
}
