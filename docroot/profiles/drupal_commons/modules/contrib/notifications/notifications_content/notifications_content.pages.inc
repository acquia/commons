<?php
// $Id: notifications_content.pages.inc,v 1.1.2.3.2.2 2009/11/12 19:23:29 jareyero Exp $
/**
 * @file
 * Subscriptions to content events
 */
 
/**
 * Admin settings form
 */
function notifications_content_settings_form() {
  // Build check boxes table with content types x subscription types
  $form['content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enabled subscription types'),
    '#weight' => -10,
    '#collapsible' => TRUE,
    '#description' => t('Check the subscription types that will be enabled. You can use the global settings here or set different options for each content type. On this second case these will be the defaults for new content types.'),
  );
  $form['content']['notifications_content_per_type'] = array(
    '#type' => 'radios',
    '#default_value' => variable_get('notifications_content_per_type', 0),
    '#options' => array(
      t('Use global settings on this page for all content types'),
      t('Set up for each content type on <a href="@content-type-settings">Administer Content Types</a>.', array('@content-type-settings' => url('admin/content/types'))),
    ),
  );  
  $form['content']['notifications_content_type'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Global options'),
    '#options' => _notifications_content_type_options(),
    '#default_value' => variable_get('notifications_content_type', array()),
    '#description' => t('Define the available subscription types that will be enabled globally'),
  );

  return system_settings_form($form);
}

/**
 * Theme content type settings
 */
function theme_notifications_content_type_settings(&$elements) {
  $output = '';
  $options = _notifications_content_type_options();
  $header = array_merge(array(''), array_values($options));
  $rows = array();
  foreach (element_children($elements) as $key) {
    $row = array($elements[$key]['#title']);
    unset($elements[$key]['#title']);
    foreach (array_keys($options) as $index) {
      unset($elements[$key][$index]['#title']);
      $row[] = drupal_render($elements[$key][$index]);
    }
    $rows[] = $row;
  }
  $output .= theme('table', $header, $rows);
  $output .= drupal_render($elements);
  return $output;
}

/**
 * Subscriptions page callback: List thread subscriptions
 */
function notifications_content_page_thread($account = NULL) {
  global $user;
  if (is_null($account)) {
    $account = $user;
  }
  // query string for node subscriptions
  $query = "SELECT s.*, f.value AS nid, n.type AS node_type, n.title FROM {notifications} s 
    INNER JOIN {notifications_fields} f ON s.sid = f.sid LEFT JOIN {node} n ON f.intval = n.nid
    WHERE s.uid = %d AND s.type = 'thread' AND s.event_type = 'node' AND s.conditions = 1 AND f.field = 'nid'
    ORDER BY node_type, n.title";
  $results = pager_query($query, NOTIFICATIONS_CONTENT_PAGER, 0, NULL, $account->uid);

  $subscriptions = $list = array();
  $content_types = notifications_content_types('name');
  while ($sub = db_fetch_object($results)) {
    $subscriptions[$sub->nid] = $sub;
    $list[$sub->nid] = '['. $content_types[$sub->node_type] .'] '. l($sub->title, 'node/'. $sub->nid);
  }

  if (!$subscriptions) {
    $output = t('You are not currently subscribed to any active threads');
  }
  else {
    $output = t('You are currently subscribed to the following threads:');
    $defaults = array('type' => 'thread', 'event_type' => 'node');
    $options = array('title' => t('Title'));
    $output .= drupal_get_form('notifications_user_form', $account, 'thread', $subscriptions, $list, $defaults, $options);
    $output .= theme('pager', NULL, NOTIFICATIONS_CONTENT_PAGER);
  }
  return $output;
}

/**
 * User subscriptions to content types
 */
function notifications_content_page_nodetype($account = NULL) {
  global $user;
  if (!isset($account)) {
    $account = $user;
  }
  // List of all subscribed node types
  $subscriptions = notifications_get_subscriptions(array('type' => 'nodetype', 'uid' => $account->uid), array('type' => NULL), TRUE, 'value');
  
  $output = '';
  $types = notifications_content_types('name');
  if (!$types) {
    $output .= t('There are no active content types.');    
  }
  else {
    $defaults = array('type' => 'nodetype', 'event_type' => 'node');
    $options = array('title' => t('Type'));
    $output .= drupal_get_form('notifications_user_form', $account, 'nodetype', $subscriptions, $types, $defaults, $options);
  
  }
  return $output;
}

/**
 * User subscriptions to content types
 */
function notifications_content_page_author($account = NULL) {
  global $user;
  if (!isset($account)) {
    $account = $user;
  }
  // List of all author subscriptions, and build author list with the same query
  $subscriptions = $list = array();
  $sql = "SELECT n.*, f.intval, u.name FROM {notifications} n INNER JOIN {notifications_fields} f ON f.sid = n.sid INNER JOIN {users} u ON u.uid = f.intval ";
  $sql .= " WHERE n.uid = %d AND n.type = 'author'";
  $result = pager_query($sql, NOTIFICATIONS_CONTENT_PAGER, 0, NULL, $account->uid);
  while ($subs = db_fetch_object($result)) {
    $author = (object)array('uid' => $subs->intval, 'name' => $subs->name);
    $list[$author->uid] = theme('username', $author);
    $subs->fields['author'] = $subs->intval;
    $subscriptions[$subs->sid] = $subs;
  }
 
  if (!$subscriptions) {
    $output = t('There are no active author subscriptions.');    
  }
  else {
    $defaults = array('type' => 'author', 'event_type' => 'node');
    //$output = drupal_get_form('notifications_content_form', $account, $subscriptions, $list, 'author', t('Author'), $defaults);
    $options = array('title' => t('Author'));
    $output = drupal_get_form('notifications_user_form', $account, 'author', $subscriptions, $list, $defaults, $options);
    $output .= theme('pager', NULL, NOTIFICATIONS_CONTENT_PAGER);
  }
  return $output;
}

/**
 * Generic subscriptions content form
 */
function notifications_content_form($account, $subscriptions, $list, $field, $field_title, $defaults = array()) {
  // Complete defaults
  $defaults += array(
    'sid' => 0, 
    'send_interval' => notifications_user_setting('send_interval', $account), 
    'send_method' => notifications_user_setting('send_method', $account),
    'event_type' => 'node',
  );
  $form['defaults'] = array('#type' => 'value', '#value' => $defaults);  
  $form['account'] = array('#type' => 'value', '#value' => $account);
  $form['current'] = array('#type' => 'value', '#value' => $subscriptions);
  $form['subscription_fields'] = array('#type' => 'value', '#value' => array());
  $form['subscriptions'] = array(
    '#tree' => TRUE,
    '#theme' => 'notifications_form_table',
    '#header' => array('', $field_title, t('Send interval'), t('Send method'))
  );  
  foreach ($list as $key => $title) {
    $rowdefaults = isset($subscriptions[$key]) ? (array)($subscriptions[$key]) : $defaults;
    $rowdefaults += $rowdefaults;
    $form['subscriptions']['checkbox'][$key] = array(
      '#type' => 'checkbox',
      '#default_value' => $rowdefaults['sid'],
    );
    $form['subscriptions']['title'][$key] = array(
      '#value' => $title,
    );
    $form['subscriptions']['send_interval'][$key] = array(
      '#type' => 'select',
      '#options' => _notifications_send_intervals(),
      '#default_value' => $rowdefaults['send_interval'],
    );
    $form['subscriptions']['send_method'][$key] = array(
      '#type' => 'select',
      '#options' => _notifications_send_methods(),
      '#default_value' => $rowdefaults['send_method'],
    );
    // Pass on the fields for processing
    $form['subscription_fields']['#value'][$key] = array($field => $key);
  
  }
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));

  return $form; 
}

/**
 * Process generic form submission
 */
function notifications_content_form_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  $account = $form_values['account'];
  $current = $form_values['current'];
  $defaults = $form_values['defaults'];
  $defaults += array('type' => 'node', 'uid' => $account->uid);
  $fields = $form_values['subscription_fields'];
  $values = $form_values['subscriptions'];
  $check = 'checkbox';

  foreach ($values[$check] as $index => $value) {
    $subscription = NULL;
    if ($value) {
      // Checked, save only if new or changed
      if (!isset($current[$index])) {
        $subscription = $defaults;
      }
      elseif ($current[$index]->send_interval != $values['send_interval'][$index] || $current[$index]->send_method != $values['send_method'][$index]) {
        $subscription = (array)($current[$index]);        
      }
      // Complete and save
      if ($subscription) {
        $subscription['send_interval'] = $values['send_interval'][$index];
        $subscription['send_method'] = $values['send_method'][$index];
        $subscription['fields'] = $fields[$index];
        notifications_save_subscription($subscription);
      }
    }
    elseif (isset($current[$index])) {
      notifications_delete_subscription($current[$index]->sid);
    }
  }
  drupal_set_message(t('Your subscriptions have been updated.'));
}
