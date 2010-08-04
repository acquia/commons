<?php
// $Id: user_relationships_ui.actions.inc,v 1.1.2.16 2010/05/13 19:15:57 alexk Exp $

/**
 * @file
 * User Relationships Actions
 */


/**
 * Validate relationship request.
 */
function user_relationships_ui_request_validate($form, &$form_state) {
  $requester = user_load($form_state['values']['requester']);
  $requestee = user_load($form_state['values']['requestee']);
  $rtid = $form_state['values']['rtid'];
  
  if (user_access('can have relationships', $requestee)) {
    //check that a type has been chosen
    if (!$rtid || !($rtype = user_relationships_type_load($rtid))) {
      form_set_error('rtid', user_relationships_ui_get_message('relationship_type_not_set'));
      //need to handle requests from ajax forms separately
      if (isset($_GET['ajax'])) {
        drupal_goto();
      }
      else {
        return;
      }
    }
    $current_relationships = user_relationships_load(array('between' => array($requester->uid, $requestee->uid)), array('sort' => 'rtid'));
    //check for multiple relationships
    if (!variable_get('user_relationships_allow_multiple', TRUE) && count($current_relationships)) {
    form_set_error('rtid', user_relationships_ui_get_message('too_many_relationships'));
      if (isset($_GET['ajax'])) {
        drupal_goto();
      }
      else {
        return;
      }
    }
    //check user is allowed to request this type
    if (!user_relationships_api_can_request($requester, $rtype)) {
      $rtype->requester = $requester;
      $rtype->requestee = $requestee;
      form_set_error('rtid', user_relationships_ui_get_message('relationship_type_not_allowed', $rtype));
      if (isset($_GET['ajax'])) {
        drupal_goto();
      }
      else {
        return;
      }
    }

    //check user is allowed to receive this type
    if (!user_relationships_api_can_receive($requestee, $rtype)) {
      $rtype->requester = $requester;
      $rtype->requestee = $requestee;
      form_set_error('rtid', user_relationships_ui_get_message('relationship_type_not_allowed', $rtype));
      if (isset($_GET['ajax'])) {
        drupal_goto();
      }
      else {
        return;
      }
    }

    //check if this request contradicts existing relationships or requests of this type
    //gather rtid's of relationships that have already been requested from requester to requestee
    $test_relationships = array();
    foreach ($current_relationships as $key => $value) {
      foreach ($value as $val_rel) {
        //existing two way relationships count no matter the direction
        if (!$val_rel->is_oneway) {
          $test_relationships[$key]=$value;
          continue;
        }
        //if it's one way, but not reciprocal, then it counts no matter the direction
        if (!$val_rel->is_reciprocal) {
          $test_relationships[$key]=$value;
          continue;
        }
        //remaining case is a reciprocal relationship - it counts unless the request is in the opposite direction
        if ($requester->uid == $val_rel->requester_id) {
          $test_relationships[$key]=$value;
        }
      }
    }
    //check if there aren't any available (not yet used) types that can be established
    if (!db_result(db_query(
      'SELECT COUNT(*) FROM {user_relationship_types}' . 
      ($test_relationships ? ' WHERE rtid NOT IN ('. db_placeholders($test_relationships) .')' : ''),
      array_keys($test_relationships)
    ))) {
      drupal_set_message(user_relationships_ui_get_message('too_many_relationships'), 'error');
      drupal_goto();
    }
    //check if desided relationship type is among the unused ones
    elseif (isset($test_relationships[$rtid])) {
      $message_name = $test_relationships[$rtid]->approved ? 'existing_relationship' : 'existing_request';
      form_set_error('rtid', user_relationships_ui_get_message($message_name, NULL, array(
        '!requester'                => $requester->name,
        '!requestee'                => $requestee->name,
        '%relationship_name'        => $current_relationships[$rtid][0]->name,
        '%relationship_plural_name' => $current_relationships[$rtid][0]->plural_name
      )));
    }
  }
  else {
    drupal_set_message(user_relationships_ui_get_message('not_accepting_requests'));
    drupal_goto();
  }
}

/**
 * Process relationship request.
 */
function user_relationships_ui_request_submit($form, &$form_state) {
  //#578372 leave all form values in the object for other functions to use
  $relationship = (object) $form_state['values'];
  $relationship->requester = user_load($form_state['values']['requester']);
  $relationship->requestee = user_load($form_state['values']['requestee']);
  $relationship->type = user_relationships_type_load($form_state['values']['rtid']);

  $relationship = user_relationships_request_relationship($relationship);

  if ($relationship === FALSE) {
    drupal_set_message(user_relationships_ui_get_message('unknown_error', $relationship));
  }

  //Not sure why these were here, they just cause php notices
//  $relationship->requester = $requester;
//  $relationship->requestee = $requestee;
//  $relationship->type = $relationship_type;

  drupal_set_message(user_relationships_ui_get_message(($relationship->approved ? 'pre_approved' : 'submitted'), $relationship));

  $form_state['redirect'] = $_GET['destination'];
}


/**
 * Approve, Disapprove, or Cancel a relationship request
 */
function user_relationships_ui_pending_requested_submit($form, &$form_state) {
  global $user;

  $relationships = user_relationships_load(array('rid' => $form_state['values']['rid']), array('include_user_info' => TRUE));
  $relationship = $relationships[$form_state['values']['rid']];
  $requester    = $relationship->requester;
  $requestee    = $relationship->requestee;

  switch ($form_state['values']['action']) {
  case 'approve':
    if (!user_access('maintain own relationships') || (!user_access('administer user relationships') && $user->uid != $requestee->uid)) {
      drupal_access_denied();
      exit();
    }
    $relationship->approved = TRUE;
    user_relationships_save_relationship($relationship, $form_state['values']['action']);
    drupal_set_message(user_relationships_ui_get_message('accepted', $relationship));
    break;

  case 'cancel':
    if (!user_access('maintain own relationships') || (!user_access('administer user relationships') && $user->uid != $requester->uid)) {
      drupal_access_denied();
      exit();
    }
    user_relationships_delete_relationship($relationship, $user, $form_state['values']['action']);
    drupal_set_message(user_relationships_ui_get_message($form_state['values']['action'], $relationship));
    break;

  case 'disapprove':
    if (!user_access('maintain own relationships') || (!user_access('administer user relationships') && $user->uid != $requestee->uid)) {
      drupal_access_denied();
      exit();
    }
    user_relationships_delete_relationship($relationship, $user, $form_state['values']['action']);
    drupal_set_message(user_relationships_ui_get_message($form_state['values']['action'], $relationship));
    break;

  default:
    drupal_set_message(user_relationships_ui_get_message('default'));
  }

  $form_state['redirect'] = str_replace('destination=', '', drupal_get_destination());
}


/**
 * Remove a relationship
 */
function user_relationships_ui_remove_submit($form, &$form_state) {
  global $user;

  $relationship = user_relationships_load($form_state['values']['rid']);

  if (!user_access('maintain own relationships') || (!user_access('administer user relationships') && $user->uid != $relationship->requester_id && $user->uid != $relationship->requestee_id)) {
    drupal_access_denied();
    exit();
  }
  
  user_relationships_delete_relationship($relationship, $user);
  drupal_set_message(user_relationships_ui_get_message('removed', $relationship));

  return "user/{$form_state['values']['viewed_id']}/relationships";
}
