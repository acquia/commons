<?php
// $Id$


/**
 * @file Rules configuration forms for the system module
 */

 
 /**
 * Action create relationship configuration form.
 */
function user_relationships_rules_action_create_relationship_form($settings, &$form) {
  $settings += array('requester' => '', 'requestee' => '', 'relationship_type' => '', 'message' => '', 'confirmation' => '');

  $form['settings']['requester'] = array(
    '#type' => 'textfield',
    '#title' => t('Requester'),
    '#default_value' => $settings['requester'],
    '#description' => t('User ID of requester. Insert token here for dynamic action.'),
  );
  $form['settings']['requestee'] = array(
    '#type' => 'textfield',
    '#title' => t('Requestee'),
    '#default_value' => $settings['requestee'],
    '#description' => t('User ID of requestee. Insert token here for dynamic action.'),
  );
  $options = array();
  $relationship_types = user_relationships_types_load();
  foreach ($relationship_types as $relationship_type) {
    $options[$relationship_type->rtid] = $relationship_type->name;
  }
  
  $form['settings']['relationship_type'] = array(
    '#type' => 'select',
    '#title' => t('Relationship type'),
    '#default_value' => $settings['relationship_type'],
    '#options' => $options,
    '#description' => t('Select relationship type.'),
  );
  $form['settings']['approve'] = array(
    '#type' => 'checkbox',
    '#title' => t('Approve relationship'),
    '#default_value' => $settings['approve'],
    '#description' => t('Check if relationship should be approved.'),
  );
}

 /**
 * Action delete relationship configuration form.
 */
function user_relationships_rules_action_delete_relationship_form($settings, &$form) {
  $settings += array('requester' => '', 'requestee' => '', 'op' => '');

  $form['settings']['requester'] = array(
    '#type' => 'textfield',
    '#title' => t('Requester'),
    '#default_value' => $settings['requester'],
    '#description' => t('User ID of requester. Insert token here for dynamic action.'),
  );
  $form['settings']['requestee'] = array(
    '#type' => 'textfield',
    '#title' => t('Requestee'),
    '#default_value' => $settings['requestee'],
    '#description' => t('User ID of requestee. Insert token here for dynamic action.'),
  );
  $options = array();
  $relationship_types = user_relationships_types_load();
  foreach ($relationship_types as $relationship_type) {
    $options[$relationship_type->rtid] = $relationship_type->name;
  }
  
  $form['settings']['relationship_type'] = array(
    '#type' => 'select',
    '#title' => t('Relationship type'),
    '#default_value' => $settings['relationship_type'],
    '#options' => $options,
    '#description' => t('Select relationship type.'),
  );
  $form['settings']['op'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#default_value' => $settings['op'],
    '#options' => array(
      'remove' => t('Remove'),
      'cancel' => t('Cancel'),
      'disapprove' => t('Disapprove'),
    ),
    '#description' => t('Select the operation you wish to perform.'),
  );
}

/**
 * Action "Send a mail to a user" configuration form
 */
function messaging_action_message_to_user_form($settings = array(), &$form) {
  $settings += array('from' => '', 'to' => '', 'subject' => '', 'body' => '');
  $form['settings']['from'] = array(
    '#type' => 'textfield',
    '#title' => t('Sender'),
    '#default_value' => $settings['from'],
    '#description' => t("Not used. Current user used instead. Message senders user ID."),
  );
  $form['settings']['to'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient'),
    '#default_value' => $settings['to'],
    '#description' => t("Message receivers user ID."),
  );
  $form['settings']['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => $settings['subject'],
    '#description' => t("The message subject."),
  );
  $form['settings']['body'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#default_value' => $settings['body'],
    '#description' => t("The message body."),
  );
}

/**
 * Condition relationship has type configuration form.
 */
function user_relationships_rules_condition_relationship_has_type_form($settings, &$form) {
  $settings += array('relationship_type' => '');

  $options = array();
  $relationship_types = user_relationships_types_load();
  foreach ($relationship_types as $relationship_type) {
    $options[$relationship_type->rtid] = $relationship_type->name;
  }
  $form['settings']['relationship_type'] = array(
    '#type' => 'select',
    '#title' => t('Relationship type'),
    '#default_value' => $settings['relationship_type'],
    '#options' => $options,
    '#description' => t('Select relationship type you want to check for.'),
  );
}

/**
 * Condition relationship has type configuration form.
 */
function user_relationships_rules_condition_users_are_related_form($settings, &$form) {
  $settings += array('relationship_types' => '');

  $options = array();
  $relationship_types = user_relationships_types_load();
  foreach ($relationship_types as $relationship_type) {
    $options[$relationship_type->rtid] = $relationship_type->name;
  }
  $form['settings']['relationship_types'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Relationship types'),
    '#default_value' => $settings['relationship_types'],
    '#options' => $options,
    '#description' => t('Select a special relationship type you want to check for. Leave empty to check for all.'),
  );
}