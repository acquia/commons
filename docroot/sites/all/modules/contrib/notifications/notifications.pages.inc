<?php
// $Id: notifications.pages.inc,v 1.1.2.8.2.8 2009/09/22 11:49:07 jareyero Exp $
/**
 * @file
 * User pages for Notifications
 */

/**
 * Menu callback. Overview page for user subscriptions.
 * 
 * We create the page as a form so it can be altered
 */
function notifications_user_overview($form_state, $account) {
  $form['account'] = array('#type' => 'value', '#value' => $account);
  
  $path = 'user/' . $account->uid;
  
  // Status, send method, interval
  $count = db_query("SELECT status, COUNT(*) AS num FROM {notifications} WHERE uid = %d GROUP BY status", $account->uid);
  $status_list = _notifications_subscription_status();
  while ($current = db_fetch_object($count)) {
    $status[$current->status] = t('You have %count @status subscriptions.', array('%count' => $current->num, '@status' => $status_list[$current->status]));
  }
  if (empty($status)) {
    $status['none'] = t('You don\'t have any subscriptions yet.');
  }
  $send_intervals = _notifications_send_intervals();
  $send_methods = _notifications_send_methods($account);
  if ($method = notifications_user_setting('send_method', $account)) {
    if (isset($send_methods[$method])) {      
      $status['method'] = t('Your default sending method for new subscriptions is @send_method', array('@send_method' => $send_methods[$method]));
    }
  }
  $interval = notifications_user_setting('send_interval', $account);
  if (isset($send_intervals[$interval])) {      
    $status['interval'] = t('Your default sending interval for new subscriptions is @send_interval', array('@send_interval' => $send_intervals[$interval]));
  }
  
  $form['status'] = array('#type' => 'item', '#weight' => 10, '#title' => t('Current status'), '#value' => theme('item_list', $status));
  
  // Build shortcut tips
  if (notifications_access_user($account, 'manage')) {
    $tips['admin'] = l(t('Administer your subscriptions'), "$path/notifications/subscriptions");
  }
  $tips['edit'] = l(t('Edit your notifications settings'), "$path/edit");
  
  // Enable / disable all subscriptions
  if (notifications_access_user($account, 'maintain')) {
    if (!empty($status[NOTIFICATIONS_SUBSCRIPTION_ACTIVE])) {
      $tips['disable'] = l(t('Temporarily disable all your subscriptions'), "$path/notifications/update/disable");
    }
    if (!empty($status[NOTIFICATIONS_SUBSCRIPTION_INACTIVE]) || !empty($status[NOTIFICATIONS_SUBSCRIPTION_BLOCKED])) {
      $tips['enable'] = l(t('Enable all your subscriptions'), "$path/notifications/update/enable");
    }    
  }
  $link = notifications_get_link('unsubscribe', array('uid' => $account->uid, 'destination' => TRUE));
  $tips['cancel'] = l(t('Cancel all your subscriptions'), $link['href'], $link['options']);
  
  //$output .= theme('item_list', $tips, t('You can'));
  $form['tips'] = array('#type' => 'item', '#weight' => 20, '#title' => t('You can'), '#value' => theme('item_list', $tips));
   
  return $form;  
}

/**
 * Form for creating new subscriptions
 */
function notifications_add_subscription_form($form_state, $account, $type, $destination = NULL) {
  $destination = $destination ? $destination : 'user/' . $account->uid . '/notifications';
  $info = notifications_subscription_types($type);
  $form['account'] = array('#type' => 'value', '#value' => $account);
  $form['type'] = array('#type' => 'value', '#value' => $type);

  // Display general information
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create @type subscription', array('@type' => $info['title'])),
    '#description' => !empty($info['description']) ? $info['description'] : '',
  );
  // Build subscription fields
  $form['info']['fields']['#tree'] = TRUE;  
  foreach ($info['fields'] as $fid => $field_type) {
    $field = notifications_subscription_fields($field_type);
    $form['info']['fields'][$fid]['type'] = array('#type' => 'value', '#value' => $field_type);
    $form['info']['fields'][$fid]['value'] = notifications_subscription_form_field($field_type, NULL, $type);
    $form['info']['fields'][$fid]['value'] += array(
      '#title' => $field['name'],
      '#required' => TRUE,   
    ); 
  }
  // Add generic subscription information for notifications
  $form['notifications'] = array(
    '#type' => 'fieldset',
    '#title' => t('Notifications'),
    '#description' => t('How often and by which channel do you want to get notifications for this subscription.')
  );
  $form['notifications']['send_interval'] = array(
    '#type' => 'select',
    '#title' => t('Send interval'),
    '#options' => _notifications_send_intervals(),
    '#default_value' => notifications_user_setting('send_interval', $account),
  );
  $send_methods = _notifications_send_methods($account);
  $form['notifications']['send_method'] = array(
    '#type' => 'select',
    '#title' => t('Send method'),
    '#options' => $send_methods,
    '#default_value' => notifications_user_setting('send_method', $account),
  );
  // Other form parameters and buttons
  $form['#redirect'] = $destination;
  $form['buttons']['save'] = array('#type' => 'submit', '#value' => t('Create subscription'));  
  $form['buttons']['cancel'] = array('#value' => l(t('Cancel'), $destination));
  
  return $form;    
}

/**
 * Validate new subscription, compute actual field values
 */
function notifications_add_subscription_form_validate($form, &$form_state) {
  $field_values = array();
  foreach ($form_state['values']['fields'] as $fid => $field){
    // We may need additional validation or field - value mappging for some fields
    $value = $field['value'];
    if ($callback = notifications_subscription_fields($field['type'], 'value callback')) {
      if ($args = notifications_subscription_fields($field['type'], 'value callback args')) {
        $value = call_user_func($callback, $value, "fields][$fid][value", $form_state['values']['type'], $args);
      } else {
        $value = call_user_func($callback, $value, "fields][$fid][value", $form_state['values']['type']);
      }
    }
    // If we still have a value (mapping may have failed, go and save)
    if ($value) {
      $field_values[$fid] = array('type' => $field['type'], 'value' => $value);
    }
    else {
      // We don't have a value, error message
      form_set_error("fields][$fid][value", t('You must set a value for this field.'));
    }
   
  }
  // Final check, we should have some valid field/value pairs
  if ($field_values) {
    $form_state['field_values'] = $field_values;
  }
  else {
    form_set_error('', t('You must provide valid values for all fields.'));
  } 
}

/**
 * Submit new subscription
 */
function notifications_add_subscription_form_submit($form, &$form_state) {
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
  if ($op == t('Create subscription')) {
    $subscription = array(
      'type' => $form_state['values']['type'],
      'uid' => $form_state['values']['account']->uid,
      'send_method' => $form_state['values']['send_method'],
      'send_interval' => $form_state['values']['send_interval'],
      'fields' => $form_state['field_values'],
    );
    $result = notifications_save_subscription($subscription);
    if ($result === SAVED_NEW) {
      drupal_set_message(t('Your subscription has been created.'));
    } else {
      drupal_set_message(t('Your subscription cannot be created.'), 'error');
    }
  }
}

/**
 * Menu callback add subscription
 * 
 * Presents confirmation page or not depending on confirm parameter
 */
function notifications_page_subscribe($account, $type, $fields, $values, $send_interval = NULL, $send_method = NULL) {
  global $user;

  // Check signature if present
  $params = array('subscribe', $account->uid, $type, $fields, $values);
  $signed = !empty($_GET['signature']) && $_GET['signature'] == _notifications_signature($params, !empty($_GET['confirm']));

  // Build subscriptions object
  $subscription = (object)array(
    'uid' => $account->uid,
    'type' => $type,
    'fields' => notifications_field_args($fields, $values),
    'send_interval' => $send_interval ? $send_interval : notifications_user_setting('send_interval', $account),
    'send_method' => $send_method ? $send_method : notifications_user_setting('send_method', $account),
    'event_type' => notifications_subscription_types($type, 'event_type'),
  );      
  if (notifications_user_allowed('subscription', $account, $subscription)) {
    // Display subscription information
    if (!empty($_GET['confirm']) && $signed) {
      // Subscribe, no confirmation
      notifications_save_subscription($subscription);
      drupal_set_message(t('Your subscription was activated.'));
      drupal_goto();
    }
    else {
      // Ask for confirmation
      drupal_set_title(t('Confirm your subscription'));
      return drupal_get_form('notifications_form_subscribe_confirm', $subscription, $account);
    }
  }
  else {
    drupal_set_message(t('Subscription type or parameters not allowed'), 'error');
    drupal_goto();
  }
    
  drupal_access_denied();
}

/**
 * Form for subscription confirmation
 */
function notifications_form_subscribe_confirm($form_state, $subscription, $account) {
  // Pass on simple values
  foreach (array('sid', 'uid', 'type', 'fields', 'event_type') as $field) {
    $form[$field] = array('#type' => 'value', '#value' => isset($subscription->$field) ? $subscription->$field : '');
  }
  // The subscription description will be added here
  $form['info'] = notifications_subscription_info_field($subscription); 
  // Additional parameters
  $form['send_interval'] = array(
    '#type' => 'select',
    '#title' => t('Send interval'),
    '#options' => _notifications_send_intervals(),
    '#default_value' => $subscription->send_interval,
  );
  $send_methods = _notifications_send_methods($account);
  $form['send_method'] = array(
    '#type' => 'select',
    '#title' => t('Send method'),
    '#options' => $send_methods,
    '#default_value' => $subscription->send_method,
    '#disabled' => count($send_methods) < 2,
  );

  $form['confirm'] = array('#type' => 'submit', '#value' => t('Subscribe'));
  $form['cancel'] = array('#type' => 'submit', '#value' => t('Cancel'));
  return $form;
}

/**
 * Process form submission
 */
function notifications_form_subscribe_confirm_submit($form, &$form_state) {
  $subscription = (object)$form_state['values'];
  switch ($form_state['values']['op']) {
    case t('Subscribe'):
      notifications_save_subscription($subscription);
      drupal_set_message(t('Your subscription was activated.'));
      $form_state['redirect'] = 'notifications/subscription/' . $subscription->sid;
      break;
    case t('Cancel'):
      drupal_set_message(t('Your subscription was cancelled'));
      $form_state['redirect'] = 'user/'. $subscription->uid .'/notifications';
      break;
  }  
}

/**
 * Process arguments and return an array of field/value pairs
 */
function notifications_field_args($fields, $values) {
  $names = explode(',', $fields);
  $params = explode(',', $values);
  return array_combine($names, $params);  
}

/**
 * Menu callback for unsubscribe page
 * 
 * @param $type
 *   Either 'sid' or 'uid' (for unsubscribe all)
 * @param $id
 *   Subscription id or user id, depending on type
 */
function notifications_page_unsubscribe($type, $id) {
  global $user;
  
  // Check signature if present
  $signed = !empty($_GET['signature']) && $_GET['signature'] == _notifications_signature(array('unsubscribe', $type, $id), !empty($_GET['confirm']));
  
  // Determine subscription and user depending on type
  if ($type == 'sid' && is_numeric($id) && ($subscription = notifications_load_subscription($id))) {
    $account = NULL;
    $uid = $subscription->uid;
  }
  elseif ($type == 'uid' && is_numeric($id) && ($account = user_load($id)) && $account->uid) {
    $subscription = NULL;
    $uid = $account->uid;
  }
  
  // Check permissions and present confirmation form or not depending on parameters
  if (($account || $subscription) && $uid && 
      (user_access('administer notifications') || ($user->uid == $uid) || $signed)) {
    // Skip confirmation page when requested and the signature is ok
    if (!empty($_GET['confirm']) && $signed) {
      if ($subscription) {
        notifications_delete_subscription($subscription->sid);
        drupal_set_message(t('Your subscription has been removed.'));
      }
      elseif ($account) {
        notifications_delete_subscriptions(array('uid' => $account->uid));
        drupal_set_message(t('All your subscriptions have been removed.'));
      }
      drupal_goto();
    } 
    elseif ($account && !db_result(db_query("SELECT COUNT(*) FROM {notifications} WHERE uid = %d", $account->uid))) {
      return t("You don't have any subscription on this site.");
    }
    else {
      // Display confirmation form
      return drupal_get_form('notifications_form_unsubscribe_confirm', $subscription, $account);
    }
  }
  drupal_access_denied();
}


/**
 * Form for unsubscription confirmation
 * 
 * It works for both single subscription or account (all subscriptions)
 */
function notifications_form_unsubscribe_confirm($form_state, $subscription, $account = NULL) {

  // Pass on subscription values
  $form['subscription'] = array('#type' => 'value', '#value' => $subscription);
  $form['account'] = array('#type' => 'value', '#value' => $account);
  
  if ($subscription) {
    $message = t('Are you sure you want to delete this subscription?');
    // The subscription description will be added here
    $form['info'] = notifications_subscription_info_field($subscription);    
  }
  else {
    $message = t('Are you sure you want to remove all your subscriptions on this site?');
  }

  return confirm_form($form,
    $message,
    isset($_GET['destination']) ? $_GET['destination'] : '',
    t('This action cannot be undone.'),
    t('Unsubscribe'),
    t('Cancel')
  );
}

/**
 * Process form submission
 */
function notifications_form_unsubscribe_confirm_submit($form, &$form_state) {
  $subscription = $form_state['values']['subscription'];
  $account = $form_state['values']['account'];
  switch ($form_state['values']['op']) {
    case t('Unsubscribe'):
      if ($subscription) {
        notifications_delete_subscription($subscription->sid);
        drupal_set_message(t('Your subscription has been removed.'));
      }
      elseif ($account) {
        notifications_delete_subscriptions(array('uid' => $account->uid));
        drupal_set_message(t('All your subscriptions have been removed.'));
      }
      $form_state['redirect'] = '';
      break;
    case t('Cancel'):
      // Do nothing, not worth showing a message, just get back
      $form_state['redirect'] = '';
      break;
  }
}

/**
 * Edit subscription
 */
function notifications_subscription_form($form_state, $subscription) {
  // The subscription description will be added here
  $form['info'] = notifications_subscription_info_field($subscription);
  // Subscription values  
  $form['subscription'] = array('#type' => 'value', '#value' => $subscription);
  $form['send_interval'] = array(
    '#type' => 'select',
    '#title' => t('Send interval'),
    '#options' => _notifications_send_intervals(),
    '#default_value' => $subscription->send_interval,
  );
  $send_methods = _notifications_send_methods();
  $form['send_method'] = array(
    '#type' => 'select',
    '#title' => t('Send method'),
    '#options' => $send_methods,
    '#default_value' => $subscription->send_method,
  );
  // Status, show blocked only to administrators
  $status = _notifications_subscription_status();
  if (!user_access('administer notifications') && !user_access('manage all subscriptions')) {
    unset($status[NOTIFICATIONS_SUBSCRIPTION_BLOCKED]);
  }
  $form['status'] = array(
    '#type' => 'radios',
    '#title' => t('Status'),
    '#options' => $status,
    '#default_value' => $subscription->status,
    '#description' => t('You can temporarily disable this subscription for not getting notifications.')
  );

  $form['save'] = array('#type' => 'submit', '#value' => t('Save'));
  
  $form['delete'] = array('#type' => 'submit', '#value' => t('Delete'));
  
  return $form;  
}

/**
 * Bulk update all user subscriptions, confirmation form
 * 
 * @param $account
 *   User account
 * @param $operation
 *   Operation to perform: enable, disable
 */
function notifications_update_user_subscriptions($form_state, $account, $operation) {
  $form['account'] = array('#type' => 'value', '#value' => $account);
  $form['operation'] = array('#type' => 'value', '#value' => $operation);  
  $destination = 'user/' . $account->uid . '/notifications';
  $form['#redirect'] = $destination;
  if ($operation == 'enable') {
    return confirm_form($form,
                      t('Are you sure you want to enable all your subscriptions?'),
                      $destination, t('You will get notifications again for all of them.'),
                      t('Enable'), t('Cancel'));
  }
  elseif ($operation == 'disable') {
    return confirm_form($form,
                      t('Are you sure you want to disable all your subscriptions?'),
                      $destination, t('You will stop getting notifications until you enable them again.'),
                      t('Disable'), t('Cancel'));    
  }
  else {
    drupal_access_denied();
  }
}

function notifications_update_user_subscriptions_submit($form, $form_state) {
  $account = $form_state['values']['account'];
  
  switch ($form_state['values']['operation']) {
    case 'enable':
      // Enable also blocked subscriptions just in case there are some
      db_query('UPDATE {notifications} SET status = %d WHERE uid = %d', NOTIFICATIONS_SUBSCRIPTION_ACTIVE, $account->uid);
      drupal_set_message(t('All your subscriptions have been enabled.'));
      break;
    case 'disable':
      db_query('UPDATE {notifications} SET status = %d WHERE status = %d AND uid = %d', NOTIFICATIONS_SUBSCRIPTION_INACTIVE, NOTIFICATIONS_SUBSCRIPTION_ACTIVE, $account->uid);
      notifications_queue_clean(array('uid' => $account->uid));
      drupal_set_message(t('All your subscriptions have been disabled.'));
      break;
  }
}

/**
 * Save edited subscription
 */
function notifications_subscription_form_submit($form, $form_state) {
  // Rebuild subscription object
  $subscription = $form_state['values']['subscription'];
  foreach (array('send_interval', 'send_method', 'status') as $field) {
    if (isset($form_state['values'][$field])) {
      $subscription->$field = $form_state['values'][$field];
    }
  }
  switch($form_state['values']['op']) {
    case t('Save'):
      notifications_save_subscription($subscription);
      break;
    case t('Delete'):
      notifications_delete_subscription($subscription->sid);
      $form_state['redirect'] = 'user/'. $subscription->uid .'/notifications';
      break;
  }
}

/**
 * Subscription information field for several forms
 */
function notifications_subscription_info_field($subscription) {
  $info = notifications_subscription_types($subscription->type);
  $format = notifications_format_subscription($subscription, 'array');  
  if (!empty($info['name'])) {
    // This subscription type already have a name
    $value = $format['name'];
  }
  else if (empty($format['names'])) {
    // No name, maybe no fields it should be enough with the title
    $value = '';
  }
  elseif (count($format['names']) == 1) {
    // If the field is unique, we don't need a table nor a name for it
    $value = array_shift($format['values']);
  }
  else {
    // Multiple fields, format as a table
    foreach ($format['names'] as $index => $value) {
      $rows[] = array(
        $value,
        $format['values'][$index],
      );
    }
    $value = theme('table', array(), $rows);
  }
  // Build a form field
  $field = array(
    '#type' => 'item',
    '#title' => t('!type subscription', array('!type' => $format['type'])),
    '#value' => $value,
  );
  if (!empty($info['description'])) {
    $field['#description'] = $info['description'];
  }
  return $field;
}

/**
 * Theme function for fields in form
 */
function theme_notifications_subscription_fields($elements) {
  $header = array(t('Field type'), t('Value'));
  $rows = array();
  foreach (element_children($elements['name']) as $key) {
    $rows[] = array(
      drupal_render($elements['name'][$key]),
      drupal_render($elements['value'][$key]),
    );
  }
  $output = theme('table', $header, $rows);
  $output .= drupal_render($elements);
  return $output;
}