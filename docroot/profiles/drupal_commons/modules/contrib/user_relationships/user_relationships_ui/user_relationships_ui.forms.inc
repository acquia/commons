<?php
// $Id: user_relationships_ui.forms.inc,v 1.1.2.23 2010/03/03 20:20:34 alexk Exp $

/**
 * @file
 * User Relationships forms
 */
module_load_include('inc', 'user_relationships_ui', 'user_relationships_ui.actions');

/**
 * Request new user to user relationship
 * @param $requester user object for the requesting user
 * @param $requestee user object for the target user
 * @param $form_values array $form['values'] when called from form_alter() 
 */
function user_relationships_ui_request_form($requester, $requestee, $form_values = NULL) {
  $relationships = _user_relationships_ui_get_requestable_rtypes($requester, $requestee);
  //try to find out desired relationship type
  if (isset($form_values['rtid'])) {//given through form
    $default_relationship = $form_values['rtid'];
  }
  elseif (is_numeric(arg(3)) && user_relationships_type_load(arg(3))) {//given through URL arguments, e.g. relationship/{uid}/request/{rtid}
    $default_relationship = arg(3);
  }
  elseif (count($relationships) == 1) {//preselect the only one.
    $rtids = array_keys($relationships);
    $default_relationship = $rtids[0];
  }
  //verify default relationship may be requested
  $default_relationship = $relationships[$default_relationship] ? $default_relationship : NULL;
  
  if (count($relationships)) {
    //hide control if the relationship is chosen
    if ($default_relationship && variable_get('user_relationships_show_direct_links', 1)) {
      $form['rtid'] = array(
        '#type' => 'hidden',
        '#default_value' => $default_relationship,
      );
    }
    else {
      $form['rtid'] = array(
        '#title'          => t('My relationship is'),
        '#type'           => 'radios',
        '#options'        => $relationships,
        '#default_value'  => $default_relationship,
      );
    }
  }
  $form['requester'] = array(
    '#type'   => 'value',
    '#value'  => $requester->uid,
  );
  $form['requestee'] = array(
    '#type'   => 'value',
    '#value'  => $requestee->uid,
  );

  return $form;
}

/**
 * Ajax handler function that is utilized to display the form
 * in a popup rather than having the full page reload for the users
 */
function user_relationships_ui_request_ajax($requestee) {
  $form = drupal_get_form('user_relationships_ui_request', $requestee);
  if (isset($_GET['ajax'])) {
    die($form);
  }
  return $form;
}

/**
 * Request a new relationship with another user
 */
function user_relationships_ui_request(&$form_state, $requestee) {
  global $user;
  $requester = $user;

  $script = '<script type="text/javascript">setTimeout(\'Drupal.user_relationships_ui.hidePopup()\', 10000);</script>';
  if (empty($requestee->name)) {
    $form['error'] = array(
      '#type' => 'markup',
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#value' => user_relationships_ui_get_message('non_existent_user') . $script
    );
    return $form;
  }
  elseif (!user_access('can have relationships', $requestee)) {
    $form['error'] = array(
      '#type' => 'markup',
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#value' => user_relationships_ui_get_message('not_accepting_requests') . $script
    );
    return $form;
  }
  elseif ($user->uid == $requestee->uid) {
    $form['error'] = array(
      '#type' => 'markup',
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#value' => user_relationships_ui_get_message('self_request') . $script
    );
    return $form;
  }
  elseif (!variable_get('user_relationships_allow_multiple', TRUE) &&
           $relationships_count = user_relationships_load(array('between' => array($requester->uid, $requestee->uid)), array('count' => TRUE))) {
    $form['error'] = array(
      '#type' => 'markup',
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#value' => user_relationships_ui_get_message('too_many_relationships') . $script
    );
    return $form;
  }
  // This is the default which means we will display the form
  $form = user_relationships_ui_request_form($requester, $requestee, $form_state);
  if (!$form['rtid']) {
    $data['error'] = array(
      '#type' => 'markup',
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#value' => user_relationships_ui_get_message('too_many_relationships') . $script
    );
    return $data;
  }
  else {
    if ($form['rtid']['#default_value']) {
      $relationship = user_relationships_type_load($form['rtid']['#default_value']);
    }
    $form = confirm_form(
      $form,
      t('Request relationship'),
      "user/$requestee->uid",
      $relationship ?
      ($relationship->requires_approval 
       ? t('Are you sure you wish to send a new %rel_name request to !name?', array('%name' => $requestee->name, '%rel_name' => ur_tt("user_relationships:rtid:$relationship->rtid:name", $relationship->name), '%rel_plural_name' => ur_tt("user_relationships:rtid:$relationship->rtid:plural_name", $relationship->plural_name), '!name' => theme('username', $requestee))) 
       : t("Are you sure you want to become %name's %rel_name?", array('%name' => $requestee->name, '%rel_name' => ur_tt("user_relationships:rtid:$relationship->rtid:name", $relationship->name)))) :
      t('How do you relate to %name?', array('%name' => $requestee->name)),
      t('Send'), t('Cancel'),
      'user_relationships_request_confirm'
    );
    return $form;
  }
}

/**
 * Ajax handler function that is utilized to display the form
 * in a popup rather than having the full page reload for the users
 */
function user_relationships_ui_pending_requested_ajax($action, $account, $relationship) {
  $form = drupal_get_form('user_relationships_ui_pending_requested', $action, $account, $relationship);
  if (isset($_GET['ajax'])) {
    die($form);
  }
  return $form;
}

/**
 * Approve, Disapprove, or Cancel confirmation form
 */
function user_relationships_ui_pending_requested(&$form_state, $action, $account, $relationship) {
  $viewed_id = $account->uid;

  $form['rid'] = array(
    '#type'   => 'value',
    '#value'  => $relationship->rid
  );
  $form['action'] = array(
    '#type'   => 'value',
    '#value'  => $action
  );
  $form['viewed_id'] = array(
    '#type'   => 'value',
    '#value'  => $viewed_id
  );

  //pick the correct question message: approve and disapprove are requests to current user, cancel is a request from current user
  switch ($action) {
    case 'approve':
      $confirmation_message = t('Are you sure you want to approve the %relationship_name relationship request from !name?', array(
        '@action'             => $action,
        '%relationship_name'  => ur_tt("user_relationships:rtid:$relationship->rtid:name", $relationship->name),
        '!name'               => theme('username', user_load(array('uid' => ($viewed_id == $relationship->requester_id ? $relationship->requestee_id : $relationship->requester_id))))
      ));
      $action_message = t('Approve relationship');
      break;
    case 'disapprove':
      $confirmation_message = t('Are you sure you want to disapprove the %relationship_name relationship request from !name?', array(
        '@action'             => $action,
        '%relationship_name'  => ur_tt("user_relationships:rtid:$relationship->rtid:name", $relationship->name),
        '!name'               => theme('username', user_load(array('uid' => ($viewed_id == $relationship->requester_id ? $relationship->requestee_id : $relationship->requester_id))))
      ));
      $action_message = t('Disapprove relationship');
      break;
    default:
      $confirmation_message = t('Are you sure you want to cancel your %relationship_name relationship request to !name?', array(
        '@action'             => $action,
        '%relationship_name'  => ur_tt("user_relationships:rtid:$relationship->rtid:name", $relationship->name),
        '!name'               => theme('username', user_load(array('uid' => ($viewed_id == $relationship->requester_id ? $relationship->requestee_id : $relationship->requester_id))))
      ));
      $action_message = t('Cancel relationship');
  }

  global $user;
  $output = confirm_form(
    $form,
    $action_message,
    ($viewed_id == $user->uid ? 'relationships/requests' : "user/{$viewed_id}/relationships/requests"),
    $confirmation_message,
    t('Yes'), t('No'),
    'user_relationships_approve_confirm'
  );

  return $output;
}

/**
 * Ajax handler function that is utilized to display the form
 * in a popup rather than having the full page reload for the users
 */
function user_relationships_ui_remove_ajax($account, $relationship) {
  //#382668 makes sure a valid relationship id was supplied
  if (!$relationship->rid) {
    if (isset($_GET['ajax'])) {
      die();
    }
    drupal_goto();
  }
  $form = drupal_get_form('user_relationships_ui_remove', $account, $relationship);
  if (isset($_GET['ajax'])) {
    die($form);
  }
  return $form;
}

/**
 * Confirm relationship removal.
 */
function user_relationships_ui_remove(&$form_state, $account, $relationship) {
  global $user;

  $viewed_id = $account->uid;

  $form['rid'] = array(
    '#type'   => 'value',
    '#value'  => $relationship->rid
  );
  $form['viewed_id'] = array(
    '#type'   => 'value',
    '#value'  => $viewed_id
  );
  $output = confirm_form(
    $form,
    t('Remove relationship'),
    ($viewed_id == $user->uid ? 'relationships' : "user/{$viewed_id}/relationships/"),

    t("Are you sure you wish to delete the %relationship_name relationship with !name?", array(
      '%relationship_name'  => ur_tt("user_relationships:rtid:$relationship->rtid:name", $relationship->name),
      '!name'               => theme('username', user_load(array('uid' => ($viewed_id == $relationship->requester_id ? $relationship->requestee_id : $relationship->requester_id))))
    )),
    t('Yes'), t('No'),
    'user_relationships_remove_confirm'
  );

  return $output;
}
