<?php

/**
 * @file
 *   Provides edit/delete status forms.
 */

/**
 * The edit status form.
 */
function facebook_status_edit(&$form_state, $status) {
  $context = facebook_status_determine_context($status->type);
  $maxlength = variable_get('facebook_status_length', 140);
  $path = drupal_get_path('module', 'facebook_status') .'/resources';
  drupal_add_js($path .'/facebook_status.js');
  drupal_add_css($path .'/facebook_status.css');
  if (module_exists('modalframe')) {
    modalframe_child_js();
  }
  $intro = _facebook_status_get_edit_intro($status, $context);
  $self = '';
  if ($status->type == 'user' && $status->sender == $status->recipient) {
    $self = ' facebook-status-form-self-update';
  }
  $form['intro'] = array(
    '#value' => '<div class="clear-block facebook-status-update facebook-status-form-type-'. $status->type . $self .'">'.
      '<span class="facebook-status-intro">'. $intro .'</span>',
    '#weight' => -45,
  );
  $form['fbss-status'] = array(
    '#type' => 'textarea',
    '#rows' => variable_get('facebook_status_box_rows', 2),
    '#default_value' => $status->message,
    '#attributes' => array('class' => 'facebook-status-text'),
    '#resizable' => FALSE,
    '#weight' => -40,
  );
  if ($maxlength > 0) {
    $form['chars'] = array(
      '#value' => '<span class="facebook-status-chars">'. t('%chars characters allowed', array('%chars' => $maxlength)) .'</span>',
      '#weight' => -38,
    );
  }
  $form['sid'] = array(
    '#type' => 'value',
    '#value' => $status->sid,
    '#weight' => -35,
  );
  $form['fbss-submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array('class' => 'facebook-status-submit'),
    '#suffix' => '</div>',
    '#weight' => -25,
  );
  // @todo: This is bad. It should be in the CSS but that doesn't seem to be working.
  $form['#attributes'] = array('style' => 'margin-bottom: 0;');
  return $form;
}

/**
 * Validate function for the status update form.
 */
function facebook_status_edit_validate($form, &$form_state) {
  $maxlen = variable_get('facebook_status_length', 140);
  if (drupal_strlen($form_state['values']['fbss-status']) > $maxlen && $maxlen != 0) {
    form_set_error('status', t('The status must be no longer than %chars characters.', array('%chars' => $maxlen)));
  }
}

/**
 * Submit function for the status update form.
 */
function facebook_status_edit_submit($form, &$form_state) {
  facebook_status_edit_status(facebook_status_load($form_state['values']['sid']), $form_state['values']['fbss-status']);
  $form_state['redirect'] = empty($_GET['destination']) ? array('statuses/share') : array($_GET['destination']);
  drupal_set_message(t('Status has been successfully edited.'));
  // Modal Frame integration.
  if (module_exists('modalframe')) {
    modalframe_close_dialog();
  }
}

/**
 * The delete status confirmation form.
 */
function _facebook_status_delete(&$form_state, $status) {
  if (module_exists('modalframe')) {
    modalframe_child_js();
  }
  $form['infotext'] = array('#value' => '<p>'. t('Are you sure you want to permanently delete the status %status?', array('%status' => $status->message)) .'</p>');
  $form['confirm'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm'),
    '#submit' => array('_facebook_status_delete_confirm'),
  );
  $form['back'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('_facebook_status_delete_cancel'),
  );
  $form['status-sid'] = array(
    '#type' => 'value',
    '#value' => $status->sid,
  );
  return $form;
}

/**
 * Deletes a status.
 */
function _facebook_status_delete_confirm($form, &$form_state) {
  $status = facebook_status_load($form_state['values']['status-sid']);
  facebook_status_delete_status($status);
  drupal_set_message(t('Status deleted.'));
  if ($_GET['destination']) {
    $form_state['redirect'] = $_GET['destination'];
  }
  else {
    $form_state['redirect'] = ($status->type == 'user' ? 'user' : '<front>');
  }
  if (module_exists('modalframe')) {
    modalframe_close_dialog();
  }
}

/**
 * Cancels status deletion.
 */
function _facebook_status_delete_cancel($form, &$form_state) {
  $status = facebook_status_load($form_state['values']['status-sid']);
  if ($_GET['destination']) {
    $form_state['redirect'] = $_GET['destination'];
  }
  else {
    $form_state['redirect'] = ($status->type == 'user' ? 'user' : '<front>');
  }
  if (module_exists('modalframe')) {
    modalframe_close_dialog();
  }
}

/**
 * Determines what text to display above the edit status form.
 *
 * @param $status
 *   A status object.
 * @param $context
 *   A context array.
 * @return
 *   A translated string to display above the edit status form.
 */
function _facebook_status_get_edit_intro($status, $context) {
  global $user;
  $orig = nl2br(check_plain($status->message));
  if ($status->type == 'user') {
    if ($user->uid == $status->sender && $status->sender == $status->recipient) {
      $intro = '<strong>'. t('Original status: !status', array('!status' => $orig)) .' </strong>';
    }
    elseif ($user->uid == $status->sender) {
      $intro = '<strong>'. t('Original message from you to !recipient: !status', array(
        '!recipient' => theme('username', _facebook_status_user_load($status->recipient)),
        '!status' => $orig
      )) .'</strong>';
    }
    elseif ($user->uid == $status->recipient) {
      $intro = '<strong>'. t('Original message from !sender to you: !status', array(
        '!sender' => theme('username', _facebook_status_user_load($status->sender)),
        '!status' => $orig
      )) .'</strong>';
    }
    elseif ($status->sender == $status->recipient) {
      $intro = '<strong>'. t('Original status by !creator: !status', array(
        '!creator' => theme('username', _facebook_status_user_load($status->sender)),
        '!status' => $orig
      )) .'</strong>';
    }
    else {
      $intro = '<strong>'. t('Original message from !sender to !recipient: !status', array(
        '!sender' => theme('username', _facebook_status_user_load($status->sender)),
        '!recipient' => theme('username', _facebook_status_user_load($status->recipient)),
        '!status' => $orig
      )) .'</strong>';
    }
  }
  else {
    if ($status->sender == $user->uid) {
      $intro = '<strong>'. t('Original message from you to !recipient: !status', array(
        '!recipient' => $context['handler']->recipient_link($context['handler']->load_recipient($status->recipient)),
        '!status' => $orig
      )) .'</strong>';
    }
    else {
      $intro = '<strong>'. t('Original message from !sender to !recipient: !status', array(
        '!sender' => theme('username', _facebook_status_user_load($status->sender)),
        '!recipient' => $context['handler']->recipient_link($context['handler']->load_recipient($status->recipient)),
        '!status' => $orig
      )) .'</strong>';
    }
  }
  return $intro;
}
