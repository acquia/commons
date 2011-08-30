<?php
// $Id$

/**
 * @file
 *   Rules integration.
 */

/**
 * Implementation of hook_rules_event_info().
 */
function fbss_rules_rules_event_info() {
  return array(
    'facebook_status_delete' => array(
      'label' => t('User deletes a status'),
      'module' => 'Facebook-style Statuses',
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status.')),
      ),
    ),
    'facebook_status_edit' => array(
      'label' => t('User edits a status'),
      'module' => 'Facebook-style Statuses',
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status.')),
        //'context' => array('type' => 'value', 'label' => t('The status context.')),
      ),
    ),
    'facebook_status_save' => array(
      'label' => t('User saves a status'),
      'module' => 'Facebook-style Statuses',
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status.')),
        //'context' => array('type' => 'value', 'label' => t('The status context.')),
      ),
    ),
  );
}

/**
 * Implementation of hook_rules_condition_info().
 */
function fbss_rules_rules_condition_info() {
  return array(
    'fbss_rules_is_self' => array(
      'label' => t('Status was posted to own profile'),
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
    'fbss_rules_can_post' => array(
      'label' => t('User has permission to send a status message'),
      'arguments' => array(
        'recipient' => array('type' => 'number', 'label' => t('The ID of the object to which the status will be posted.')),
        'sender' => array('type' => 'user', 'label' => t('Sender')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
    'fbss_rules_rules_condition_can_edit' => array(
      'label' => t('User has permission to edit a status'),
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
    'fbss_rules_rules_condition_can_delete' => array(
      'label' => t('User has permission to delete a status'),
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
    'fbss_rules_rules_condition_is_type' => array(
      'label' => t('Status recipient is a certain type'),
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
  );
}

/**
 * Checks if the status was posted to the user's own profile.
 */
function fbss_rules_is_self($status) {
  return $status->sender == $status->recipient && $status->type == 'user';
}

/**
 * Builds the form for the fbss_rules_can_post condition.
 */
function fbss_rules_can_post_form($settings, &$form) {
  $settings += array('type' => 'user');
  $contexts = module_invoke_all('facebook_status_context_info');
  $options = array('auto' => t('Automatically determined'));
  foreach ($contexts as $key => $context) {
    $options[$key] = $context['title'];
  }
  $form['settings']['type'] = array(
    '#type' => 'select',
    '#title' => t('Recipient type'),
    '#default_value' => $settings['type'],
    '#description' => t('The type of entity onto whose stream the status update will be posted.'),
    '#options' => $options,
  );
}

/**
 * Checks if the user is allowed to post a status.
 */
function fbss_rules_can_post($recipient, $sender, $settings) {
  if ($settings['type'] == 'auto') {
    $context = facebook_status_determine_context();
    $settings['type'] = $context['handler']->type();
  }
  return facebook_status_user_access('add', $recipient, $settings['type'], $sender);
}

/**
 * Builds the form for the fbss_rules_rules_condition_is_type condition.
 */
function fbss_rules_rules_condition_is_type_form($settings, &$form) {
  $settings += array('types' => array());
  $contexts = module_invoke_all('facebook_status_context_info');
  $options = array();
  foreach ($contexts as $key => $context) {
    $options[$key] = $context['title'];
  }
  $form['settings']['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Recipient type'),
    '#default_value' => $settings['types'],
    '#description' => t('The types of recipients allowed for this condition to be true.'),
    '#options' => $options,
  );
}

/**
 * Checks if the status recipient is one of a specified type.
 */
function fbss_rules_rules_condition_is_type($status, $settings) {
  if (empty($settings['types'])) {
    return FALSE;
  }
  return !empty($settings['types'][$status->type]);
}

/**
 * Checks if the current user can edit the status.
 */
function fbss_rules_rules_condition_can_edit($status) {
  facebook_status_user_access('edit', $status);
}

/**
 * Checks if the current user can delete the status.
 */
function fbss_rules_rules_condition_can_delete($status) {
  facebook_status_user_access('delete', $status);
}

/**
 * Implementation of hook_rules_action_info().
 */
function fbss_rules_rules_action_info() {
  return array(
    'fbss_rules_load_action' => array(
      'label' => t('Load a status'),
      'new variables' => array(
        'status_loaded' => array('type' => 'facebook_status', 'label' => t('Loaded status')),
      ),
      'help' => t('Enter the Status ID of a status to load.'),
      'module' => 'Facebook-style Statuses',
      'eval input' => array('sid'),
    ),
    'fbss_rules_edit_action' => array(
      'label' => t('Edit a status'),
      'help' => t('Enter the Status ID of the status to edit and the text you wish to replace the status.'),
      'module' => 'Facebook-style Statuses',
      'eval input' => array('sid', 'message'),
    ),
    'fbss_rules_delete_action' => array(
      'label' => t('Delete a status'),
      'help' => t('Enter the Status ID of the status to delete.'),
      'module' => 'Facebook-style Statuses',
      'eval input' => array('sid'),
    ),
    'fbss_rules_add_action' => array(
      'label' => t('Add a status'),
      'help' => t('Enter the status text and the ID and type of the recipient to which the status will be posted.'),
      'module' => 'Facebook-style Statuses',
      'eval input' => array('sender', 'recipient', 'type', 'message'),
    ),
  );
}

/**
 * Builds the form for loading a status.
 */
function fbss_rules_load_action_form($settings, &$form) {
  $settings += array('sid' => '');
  $form['settings']['sid'] = array(
    '#type' => 'textfield',
    '#title' => t('Status ID'),
    '#default_value' => $settings['sid'],
    '#required' => TRUE,
  );
}

/**
 * Loads a status.
 */
function fbss_rules_load_action($settings) {
  return array('status_loaded' => facebook_status_load($settings['sid']));
}

/**
 * Builds the form for editing a status.
 */
function fbss_rules_edit_action_form($settings, &$form) {
  $settings += array('sid' => '', 'message' => '');
  $form['settings']['sid'] = array(
    '#type' => 'textfield',
    '#title' => t('Status ID'),
    '#default_value' => $settings['sid'],
    '#required' => TRUE,
  );
  $form['settings']['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Status message'),
    '#default_value' => $settings['message'],
    '#rows' => 3,
  );
}

/**
 * Edits a status.
 */
function fbss_rules_edit_action($settings) {
  facebook_status_edit_status(facebook_status_load($settings['sid']), $settings['message']);
}

/**
 * Builds the form for deleting a status.
 */
function fbss_rules_delete_action_form($settings, &$form) {
  $settings += array('sid' => '');
  $form['settings']['sid'] = array(
    '#type' => 'textfield',
    '#title' => t('Status ID'),
    '#default_value' => $settings['sid'],
    '#required' => TRUE,
  );
}

/**
 * Deletes a status.
 */
function fbss_rules_delete_action($settings) {
  facebook_status_delete_status($settings['sid']);
}

/**
 * Builds the form for adding a status.
 */
function fbss_rules_add_action_form($settings, &$form) {
  $settings += array('sender' => '', 'recipient' => '', 'type' => '', 'message' => '');
  $form['settings']['sender'] = array(
    '#type' => 'textfield',
    '#title' => t('Sender username'),
    '#autocomplete_path' => 'user/autocomplete',
    '#description' => t('If you leave this blank, the current user will be assumed.'),
    '#default_value' => $settings['sender'],
  );
  $form['settings']['recipient'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient ID'),
    '#default_value' => $settings['recipient'],
  );
  $form['settings']['type'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient type'),
    '#default_value' => $settings['type'],
  );
  $form['settings']['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Status message'),
    '#default_value' => $settings['message'],
    '#rows' => 3,
  );
}

/**
 * Validates the form for adding a status.
 */
function fbss_rules_add_action_validate($form, $form_state) {
  if (!$form_state['values']['settings']['recipient'] || !$form_state['values']['settings']['type']) {
    form_set_error('settings][recipient', t('You must enter an object ID and its type.'));
  }
}

/**
 * Adds a status.
 */
function fbss_rules_add_action($settings) {
  $type = $settings['type'];
  $context = facebook_status_determine_context($type);
  $recipient = $context['handler']->load_recipient($settings['recipient']);
  $message = $settings['message'];
  $sender = _facebook_status_user_load_by_name($settings['sender']);
  facebook_status_save_status($recipient, $type, $message, $sender);
}

/**
 * Implementation of hook_rules_data_type_info().
 */
function fbss_rules_rules_data_type_info() {
  return array(
    'facebook_status' => array(
      'label' => t('Facebook-style Status'),
      'class' => 'rules_data_type_facebook_status',
      'savable' => TRUE,
      'identifiable' => TRUE,
      'use_input_form' => FALSE,
      'module' => 'Facebook-style Statuses',
    ),
  );
}

/**
 * Defines the rules node data type.
 */
class rules_data_type_facebook_status extends rules_data_type {
  function save() {
    $status = &$this->get();
    $context = facebook_status_determine_context($status->type);
    $recipient = $context['handler']->load_recipient($status->recipient);
    $sender = _facebook_status_user_load($status->sender);
    facebook_status_save_status($recipient, $status->type, $status->message, $sender);
    return TRUE;
  }
  function load($sid) {
    return facebook_status_load($sid);
  }
  function get_identifier() {
    $status = &$this->get();
    return $status->sid;
  }
}
