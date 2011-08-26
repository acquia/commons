<?php

/**
 * @file
 *   User-controlled settings for the Activity Log Digests module.
 */

/**
 * Implementation of hook_form_alter().
 *
 * Use form_alter because it runs after form_FORM_ID_alter. Since Notifications
 * uses form_alter and we need to override what it does, we have to use
 * form_alter too.
 */
function digests_form_alter(&$form, $form_state, $form_id) {
  if ($form_id == 'user_profile_form') {
    $form['mimemail']['#collapsed'] = TRUE;
    $form['mimemail']['#title'] = t('Email delivery settings');
    if (isset($form['messaging'])) {
      $form['messaging']['#collapsed'] = TRUE;
      $form['messaging']['#title'] = t('Immediate notifications settings');
    }
  }
}

/**
 * The user settings for Activity Log Digests.
 */
function _digests_user_form($uid) {
  $form = array();
  $interval = db_result(db_query("SELECT send_interval FROM {digests} WHERE uid = %d", $uid));
  $form['digests_last_interval'] = array(
    '#type' => 'value',
    '#value' => $interval,
  );
  $form['digests'] = array(
    '#type' => 'fieldset',
    '#title' => t('Activity digest settings'),
    '#collapsible' => TRUE,
    '#weight' => 5,
  );
  $form['digests']['digests_interval'] = array(
    '#type' => 'select',
    '#title' => t('Receive digests of interesting activity'),
    '#default_value' => empty($interval) ? 86400 : $interval,
    '#options' => array(
      86400 => t('Daily'),
      604800 => t('Weekly'),
      0 => t('Never'),
    ),
  );
  return $form;
}

/**
 * Saves users' digest settings.
 */
function _digests_user_update(&$edit, $uid) {
  $v = $edit['digests_interval'];
  $lv = $edit['digests_last_interval'];
  unset($edit['digests_interval'], $edit['digests_last_interval']);
  if ($v !== $lv) {
    db_query("UPDATE {digests} SET send_interval = %d WHERE uid = %d", $v, $uid);
    if (db_affected_rows() <= 0) {
      $insert = (object) array(
        'uid' => $uid,
        'last_sent' => 0,
        'send_interval' => $v,
      );
      drupal_write_record('digests', $insert);
    }
  }
}
