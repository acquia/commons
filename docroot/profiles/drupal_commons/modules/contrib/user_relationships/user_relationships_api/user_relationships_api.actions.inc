<?php
// $Id: user_relationships_api.actions.inc,v 1.1.2.7 2009/11/07 19:17:26 alexk Exp $

/**
 * @file *Incomplete* Actions implementation
 * TODO: check what else this file is for except for hook_hook_info impl
 * 
 * Implementation of hook_hook_info().
 */
function user_relationships_api_hook_info() {
  return array(
    'user_relationships_api' => array(
      'user_relationships_api' => array(
        'type_presave' => array(
          'runs when' => t('When either saving a new relationship type or updating an existing relationship type'),
        ),
        'type_insert'  => array(
          'runs when' => t('After saving a new relationship type'),
        ),
        'type_update'  => array(
          'runs when' => t('After saving an existing relationship type'),
        ),
        'type_delete'  => array(
          'runs when' => t('After deleting a relationship type'),
        ),
        'type_load'    => array(
          'runs when' => t('When a relationship type is loaded'),
        ),
        'presave'     => array(
          'runs when' => t('When either saving a new relationship or updating an existing relationship'),
        ),
        'request'     => array(
          'runs when' => t('After a new relationship has been requested'),
        ),
        'cancel'      => array(
          'runs when' => t('When a relationship has been removed (specifically cancelled)'),
        ),
        'update'      => array(
          'runs when' => t('After saving an existing relationship'),
        ),
        'approve'     => array(
          'runs when' => t('After approving a relationship'),
        ),
        'disapprove'  => array(
          'runs when' => t('When a relationship has been removed (specifically disapproved)'),
        ),
        'remove'      => array(
          'runs when' => t('When a relationship has been removed'),
        ),
      ),
    ),
  );
}


/*
 * Implementation of hook_action_info().
 *
function user_relationships_api_action_info() {
  return array(
    'user_relationships_api_request_action' => array(
      'type'          => 'user_relationships_api',
      'description'   => t('Request a relationship'),
      'configurable'  => TRUE,
      'hooks'         => array(
        'user' => array('insert')
      ),
    ),
    'user_relationships_api_remove_action' => array(
      'type'          => 'user_relationships_api',
      'description'   => t('Remove a relationship'),
      'configurable'  => TRUE,
//      'hooks'         => array('any' => TRUE),
    ),
    'user_relationship_cancel_action' => array(
      'type'          => 'user_relationships_api',
      'description'   => t('Cancel a relationship request'),
      'configurable'  => FALSE,
//      'hooks'         => array('any' => TRUE),
    ),
    'user_relationship_approve_action' => array(
      'type'          => 'user_relationship',
      'description'   => t('Approve a relationship request'),
      'configurable'  => FALSE,
//      'hooks'         => array('any' => TRUE),
    ),
    'user_relationship_disapprove_action' => array(
      'type'          => 'user_relationship',
      'description'   => t('Disapprove a relationship request'),
      'configurable'  => FALSE,
//      'hooks'         => array('any' => TRUE),
    ),
  );
}

function user_relationship_approve_action(&$relationship) {
  $relationship->approved = TRUE;
  user_relationships_save_relationship($relationship, 'approve');
}

function user_relationship_disapprove_action(&$relationship) {
  $deleted_by = user_load($relationship->requestee_id);
  user_relationships_delete_relationship($relationship, $deleted_by, 'disapprove');
}

function user_relationship_cancel_action(&$relationship) {
  $deleted_by = user_load($relationship->requester_id);
  user_relationships_delete_relationship($relationship, $deleted_by, 'cancel');  
}

function user_relationship_remove_action(&$relationship, &$deleted_by, $reason) {
  user_relationships_delete_relationship($relationship, $deleted_by, $reason);
}

function user_relationship_request_action($user, $context) {
  $user = $context['account'];

  if ($context['users_role'] == 'requester') {
    $requester = $user->uid;
    $requestee = $context['relatee'];
  }
  else {
    $requester = $context['relatee'];    
    $requestee = $user->uid;
  }

  user_relationships_request_relationship($requester, $requestee, $context['rtype'], $context['approved']);
}

function user_relationship_request_action_form($context) {
  if (isset($context['relatee'])) {
    $other_user = db_result(db_query('SELECT name FROM {users} WHERE uid = %d', $context['relatee']));
  }

  $rtypes = user_relationships_types_load();
  foreach ($rtypes as $rtid => $rtype) {
    $rtypes[$rtid] = $rtype->name;
  }

  $form['rtype'] = array(
    '#type'               => 'select',
    '#title'              => t('Relationship Type'),
    '#options'            => $rtypes,
    '#description'        => t('The relationship type'),
    '#default_value'      => $context['rtype'],
  );
  $form['approved'] = array(
    '#type'               => 'checkbox',
    '#title'              => t('Approved'),
    '#description'        => t('Whether the relationship is already approved or not'),
    '#default_value'      => $context['approved'],
  );
  $form['users_role'] = array(
    '#type'               => 'select',
    '#title'              => t("User's Role"),
    '#options'            => array('requester' => t('Requester'), 'requestee' => t('Requestee')),
    '#description'        => t('Is the user the Requester or Requestee'),
    '#default_value'      => $context['users_role'],
    '#autocomplete_path'  => 'user/autocomplete',
  );
  $form['relatee'] = array(
    '#type'               => 'textfield',
    '#title'              => t('Relatee'),
    '#description'        => t('The username of the user with whom to request the relationship'),
    '#default_value'      => $other_user,
    '#autocomplete_path'  => 'user/autocomplete',
  );

  return $form;
}

function user_relationship_request_action_validate($form, $form_state) {
  $count = db_result(db_query("SELECT COUNT(*) FROM {users} WHERE name = '%s'", $form_state['values']['relatee']));
  if (empty($form_state['values']['relatee']) || intval($count) != 1) {
    form_set_error('relatee', t('Please enter a valid username.'));
  }
}

function user_relationship_request_action_submit($form, $form_state) {
  $return = array();

  $return['relatee'] = db_result(db_query("SELECT uid FROM {users} WHERE name = '%s'", $form_state['values']['relatee']));

  foreach (array('approved', 'rtype') as $field) {
    $return[$field] = $form_state['values'][$field];
  }

  return $return;
}
*/