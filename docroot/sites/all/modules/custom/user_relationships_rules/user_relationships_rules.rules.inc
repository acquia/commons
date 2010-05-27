<?php
// $Id$


/**
 * @file rules integration for the system module
 */


/**
 * Implementation of hook_rules_action_info().
 * @ingroup rules
 */
function user_relationships_rules_rules_action_info() {
  return array(
    'user_relationships_rules_action_create_relationship' => array(
      'label' => t('Request, create or approve relationships between users'),
      'module' => 'User Relationships',
      'eval input' => array('requester', 'requestee'),
    ),
    'user_relationships_rules_action_delete_relationship' => array(
      'label' => t('Delete, cancel or disapprove relationships between users'),
      'module' => 'User Relationships',
      'eval input' => array('requester', 'requestee'),
    ),
  );
}

/**
* Implementation of hook_rules_condition_info().
* @ingroup rules
*/
function user_relationships_rules_rules_condition_info() {
  return array(
    'user_relationships_rules_condition_relationship_has_type' => array(
      'label' => t('Relationship has type'),
      'arguments' => array(
        'requester' => array('type' => 'user', 'label' => t('User who initiated the request')),
        'requestee' => array('type' => 'user', 'label' => t('User whose relationship is requested')),
        'relationship' => array('type' => 'relationship', 'label' => t('Relationship')),
      ),
      'module' => 'User Relationships',
    ),
    'user_relationships_rules_condition_messages_only_to_relationships' => array(
      'label' => t('Allow private messages only to relationships'),
      'arguments' => array(
        'user' => array('type' => 'user', 'label' => t('User whose setting you want to check')),
      ),
      'module' => 'User Relationships',
    ),
    'user_relationships_rules_condition_users_are_related' => array(
      'label' => t('Check if two users are related'),
      'arguments' => array(
        'user1' => array('type' => 'user', 'label' => t('User A')),
        'user2' => array('type' => 'user', 'label' => t('User B')),
      ),
      'module' => 'User Relationships',
    ),
  );
}

/**
* Implementation of hook_rules_event_info().
* @ingroup rules
*/
function user_relationships_rules_rules_event_info() {
  return array(
    'user_relationships_request' => array(
      'label' => t('A user relationship has been requested'),
      'module' => 'User Relationships',
      'arguments' => array(
        'requester' => array('type' => 'user', 'label' => t('User who initiated the request')),
        'requestee' => array('type' => 'user', 'label' => t('User whose relationship is requested')),
        'relationship' => array('type' => 'relationship', 'label' => t('The relationship object')),
      ),
    ),
    'user_relationships_cancel' => array(
      'label' => t('A user relationship has been cancelled'),
      'module' => 'User Relationships',
      'arguments' => array(
        'requester' => array('type' => 'user', 'label' => t('User who initiated the request')),
        'requestee' => array('type' => 'user', 'label' => t('User whose relationship is requested')),
        'relationship' => array('type' => 'relationship', 'label' => t('The relationship object')),
      ),
    ),    
    'user_relationships_approve' => array(
      'label' => t('A user relationship has been approved'),
      'module' => 'User Relationships',
      'arguments' => array(
        'requester' => array('type' => 'user', 'label' => t('User who initiated the request')),
        'requestee' => array('type' => 'user', 'label' => t('User whose relationship is requested')),
        'relationship' => array('type' => 'relationship', 'label' => t('The relationship object')),
      ),
    ),  
    'user_relationships_disapprove' => array(
      'label' => t('A user relationship has been denied'),
      'module' => 'User Relationships',
      'arguments' => array(
        'requester' => array('type' => 'user', 'label' => t('User who initiated the request')),
        'requestee' => array('type' => 'user', 'label' => t('User whose relationship is requested')),
        'relationship' => array('type' => 'relationship', 'label' => t('The relationship object')),
      ),
    ),
    'user_relationships_delete' => array(
      'label' => t('A user relationship request has expired'),
      'module' => 'User Relationships',
      'arguments' => array(
        'requester'   => array('type' => 'user',  'label' => t('User who initiated the request')),
        'requestee'   => array('type' => 'user',  'label' => t('User whose relationship is requested')),
        'relationship' => array('type' => 'relationship',  'label' => t('The relationship object'))
      )
    ),
    'user_relationships_remove' => array(
      'label' => t('A user relationship has been removed'),
      'module' => 'User Relationships',
      'arguments' => array(
        'requester'   => array('type' => 'user',  'label' => t('User who initiated the request')),
        'requestee'   => array('type' => 'user',  'label' => t('User whose relationship is requested')),
        'relationship' => array('type' => 'relationship',  'label' => t('The relationship object'))
      )
    ),
  );
}


/**
* Implementation of hook_rules_data_type_info().
*/
function user_relationships_rules_rules_data_type_info() {
  return array(
    'relationship' => array(
      'label' => t('Relationship'),
      'class' => 'rules_data_type_relationship',
      'savable' => FAlSE,
      'identifiable' => TRUE,
      'module' => 'User Relationships',
    ),
  );
}

/**
* Defines the rules relationship data type.
*/
class rules_data_type_relationship extends rules_data_type {
  function load($rid) {
    return user_relationships_load(array('rid' => $rid));
  }
  
  function get_identifier() {
    $relationship = &$this->get();
    return $relationship->rid;
  }
}

/**
 * Action Implementation: Request relationship.
 */
function user_relationships_rules_action_create_relationship($settings) {
  $existing = user_relationships_load(array('requester_id' => $settings['requester'], 'requestee_id' => $settings['requestee'], 'rtid' => $settings['relationship_type']));
  
  if (empty($existing)) {
    user_relationships_request_relationship($settings['requester'], $settings['requestee'], $settings['relationship_type'], $settings['approve']);
  }
  else if ($settings['approve']) {
    user_relationships_save_relationship(array_shift($existing), $op = 'approve');
  }
}

/**
 * Action Implementation: Delete relationship.
 */
function user_relationships_rules_action_delete_relationship($settings) {
  // setting $deleted_by
  $deleted_by = user_load(array('uid' => $settings['requester']));
  // getting relationship object
  $relationships = user_relationships_load(array('between' => array($settings['requester'], $settings['requestee']), 'rtid' => $settings['relationship_type']));
  // finding rid - this method can probably be made better
  $relationship_rid = array_keys($relationships);
  // preparing $relationship with rid
  $relationship = $relationships[$relationship_rid[0]];
  
  // voila...
  user_relationships_delete_relationship($relationship, $deleted_by, $op = 'remove');
}

/**
 * Condition Implementation: Relationship has type.
 */
function user_relationships_rules_condition_relationship_has_type($requester, $requestee, $relationship, $settings) {
  $relationship = array_shift($relationship);
  // checking if relationship exists
  return $relationship->rtid == $settings['relationship_type'];
}

/**
 * Condition Implementation: Private messages only to relationships.
 */
function user_relationships_rules_condition_messages_only_to_relationships($user, $settings) {
  return $user->user_relationships_allow_private_message == 'on in relations';
}

/**
 * Condition Implementation: Users are related.
 */
function user_relationships_rules_condition_users_are_related($user1, $user2, $settings) {
  // Get relationships between the two users
  $relationships = user_relationships_load(array('between' => array($user1->uid, $user2->uid)));
  
  // Unset unwanted relationship types
  if (!empty($relationships) && !empty($settings['relationship_types'])) {
    foreach ($settings['relationship_types'] as $rtid) {
      unset($relationships[$rtid]);
    }
  }
  return !empty($relationships);
}
