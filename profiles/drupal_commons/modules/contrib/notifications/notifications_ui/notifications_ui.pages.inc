<?php
// $Id: notifications_ui.pages.inc,v 1.1.2.3 2009/04/15 16:08:14 jareyero Exp $
/**
 * @file
 *   User pages for User Interface for subscriptions modules
 */
 
/**
 * User add subscription
 */
function notifications_ui_page_user_add($account, $type = NULL) {
  drupal_set_title(t('Add subscription'));
  if ($type && notifications_ui_access_user_add($account, $type)) {    
    module_load_include('inc', 'notifications', 'notifications.pages');
    return drupal_get_form('notifications_add_subscription_form', $account, $type);
  }
  else {    
    foreach (notifications_ui_subscription_types() as $key => $type) {
      if (notifications_ui_access_user_add($account, $key)) {
        $options[] = array(
          'title' => $type['title'],
          'href'  => "user/$account->uid/notifications/add/$key",
          'description' => !empty($type['description']) ? $type['description'] : '',
        );
      }
    }
    return theme('notifications_ui_add_list', $options);
  }  
}

/**
 *  Site-wide settings form.
 */
function notifications_ui_settings_form() {
  // Enable / disable for subscription types
  $form['notifications_ui_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Visible subscription types'),
    '#options' => _notifications_subscription_types('long'),
    '#default_value' => variable_get('notifications_ui_types', array()),
    '#description' => t('Check the subscription types the UI module should show. If not checked no options for this subscription type will be displayed at all.'),
  );

  $options = array(
    'page' => t('<strong>Tab</strong>. A full tab for some subscription types will be displayed for each enabled subscription type when available.'),
    'create' => t('<strong>Create</strong>. A create link and a custom page for adding subscriptions will be available for each enabled subscription type.'),
  
  );
  // UI elements on user account pages
  $form['users'] = array(
    '#title' => t('User account pages'),
    '#type' => 'fieldset',    
    '#collapsible' => TRUE,
    '#description' => t('Check elements to display on user account pages'),
  );
  $form['users']['notifications_ui_user'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Manage own subscriptions'),
    '#default_value' => notifications_ui_user_options(),
    '#options' => $options,
    '#description' => t('Check elements to display on user account tabs for site users to manage their own subscriptions'),  
  );
  $form['users']['notifications_ui_account_options'] = array(
    '#title' => t('Subscribe to other users'),
    '#type' => 'checkboxes',
    '#default_value' => variable_get('notifications_ui_account_options', array()),
    '#options' => _notifications_ui_account_options(),
    '#description' => t('Check elements to display on user account tabs for other users to subscribe to them'),     
  );

  // Several options to subscribe to content  
  $form['content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Subscribe to content'),
    '#collapsible' => TRUE,
    '#description' => t('You can use the global settings here or set different options for each content type. On this second case these will be the defaults for new content types.'),  
  );
  $form['content']['notifications_ui_per_type'] = array(
    '#type' => 'radios',
    '#default_value' => variable_get('notifications_ui_per_type', 0),
    '#options' => array(
      t('Use global settings on this page for all content types'),
      t('Set up for each content type on <a href="@content-type-settings">Administer Content Types</a>.', array('@content-type-settings' => url('admin/content/types'))),
    ),
  );  
  $form['content']['notifications_ui_node'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Global settings'),
    '#default_value' => variable_get('notifications_ui_node', array()),
    '#options' => _notifications_ui_node_options(),
    '#description' => t('Check elements to display on each node for users to subscribe / unsubscribe.'),
       
  );  
  return system_settings_form($form);
}

/**
 * Format subscription type settings
 */
function theme_notifications_ui_subscription_types(&$elements) {
  $output = '';
  $header = array('', t('Enabled'), t('Show user account page'), t('Show create subscription page'));
  $rows = array();
  foreach (element_children($elements) as $key) {
    $rows[] = array(
      drupal_render($elements[$key]['title']),
      drupal_render($elements[$key]['enabled']),
      drupal_render($elements[$key]['page']),
      drupal_render($elements[$key]['create']),
    );
  }
  $output .= theme('table', $header, $rows);
  $output .= drupal_render($elements);
  return $output;
}

function theme_notifications_ui_content_types(&$elements) {
  $output = '';
  $options = _notifications_ui_node_type_options();
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
 * Display the list of available subscription types for creation
 *
 * @ingroup themeable
 */
function theme_notifications_ui_add_list($content) {
  $output = '';

  if ($content) {
    $output = '<dl class="subscriptions-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>'. l($item['title'], $item['href']) .'</dt>';      
      $output .= '<dd>'. filter_xss_admin($item['description']) .'</dd>';
    }
    $output .= '</dl>';
  }
  return $output;
}