<?php
// $Id: notifications.manage.inc,v 1.1.2.3.2.5 2009/11/13 14:10:49 jareyero Exp $

/**
 * @file
 *   Common functions for bulk management of subscriptions
 */

/**
 * Menu callback: subscriptions administration.
 */
function notifications_manage_admin_subscriptions($form_state) {
  module_load_include('inc', 'notifications', 'notifications.admin');
  if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
    return notifications_multiple_delete_confirm($form_state, array_filter($form_state['values']['subscriptions']));
  }
  $form = notifications_subscriptions_filter_form(TRUE);

  $form['#theme'] = 'notifications_subscriptions_filter_form';
  $form['admin']  = notifications_manage_subscriptions_form();

  return $form;
}

/**
 * Menu callback: user subscriptions management
 */
function notifications_manage_user_subscriptions($form_state, $account) {
  module_load_include('inc', 'notifications', 'notifications.pages');
  if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
    $form = notifications_multiple_delete_confirm($form_state, array_filter($form_state['values']['subscriptions']));
    return $form;
  }
  $form = notifications_subscriptions_filter_form();
  $form['filters']['#title'] = t('Filter');
  // Display collapsed only when no filters set
  $form['filters'] += array('#collapsible' => TRUE, '#collapsed' => empty($_SESSION['subscriptions_overview_filter']));
  $form['#theme'] = 'notifications_subscriptions_filter_form';
  $form['admin']  = notifications_manage_subscriptions_form($account);

  return $form;
}

/**
 * Check access for current user to manage subscriptions
 * 
 * @param $sids
 *   Array of subscription ids
 */
function notifications_manage_subscriptions_access($sids) {
  global $user;
  
  if (user_access('administer notifications') || user_access('manage all subscriptions')) {
    return TRUE;
  }
  else {
    $params = array_merge(array($user->uid), array_values($sids));
    $count = db_result(db_query("SELECT COUNT(*) FROM {notifications} WHERE uid = %d AND sid IN (" . db_placeholders($sids) . ')', $params));
    return $count == count($sids);
  }
} 

/**
 * Administer user subscriptions
 */
function notifications_manage_subscriptions_form($account = NULL, $full = TRUE) {
  $filter = notifications_subscriptions_build_filter_query($account);
  
  if ($account) {
    $result = pager_query('SELECT n.* FROM {notifications} n '. $filter['join'] . $filter['where'] .' ORDER BY n.sid DESC', 50, 0, NULL, $filter['args']);
  } else {
    $result = pager_query('SELECT n.*, u.name FROM {notifications} n '. $filter['join'] .' INNER JOIN {users} u ON n.uid = u.uid '. $filter['where'] .' ORDER BY n.sid DESC', 50, 0, NULL, $filter['args']);
  }
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );
  $options = array();
  foreach (notifications_subscriptions_operations($account) as $operation => $array) {
    if (!empty($array['parent'])) {
      $options[$array['parent']][$operation] = $array['label'];
    } else {  
      $options[$operation] = $array['label'];
    }
  }
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => 'approve',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#validate' => array('notifications_manage_subscriptions_form_validate'),
    '#submit' => array('notifications_manage_subscriptions_form_submit'),
  );

  $destination = drupal_get_destination();
  $subscriptions = array();
  $status = _notifications_subscription_status();
  $send_methods = messaging_method_info(NULL, 'name');
  $send_intervals = _notifications_send_intervals();
  while ($sub = db_fetch_object($result)) {
    $subscriptions[$sub->sid] = '';
    // Naming for this specific subscription, formatted strings    
    $form['type'][$sub->sid] = array('#value' => notifications_subscription_types($sub->type, 'title'));
    // If full loading, load full subscription and add description
    if ($full) {
      $sub = notifications_load_subscription($sub);
      $format = notifications_format_subscription($sub, 'array');
      $form['description'][$sub->sid] = array('#value' => $format['name']);
    }    
    if (!$account) {
      $form['username'][$sub->sid] = array('#value' => theme('username', $sub));
    }
    $form['send_method'][$sub->sid] = array('#value' => !empty($send_methods[$sub->send_method]) ? $send_methods[$sub->send_method] : $sub->send_method);
    $form['send_interval'][$sub->sid] = array('#value' => !empty($send_intervals[$sub->send_interval]) ? $send_intervals[$sub->send_interval] : $sub->send_interval);  
    $form['status'][$sub->sid] =  array('#value' => $status[$sub->status]);
    $operations = array(
      l(t('edit'), 'notifications/subscription/' . $sub->sid, array('query' => $destination)),
      l(t('drop'), 'notifications/unsubscribe/sid/' . $sub->sid, array('query' => $destination)),
    );
    $form['operations'][$sub->sid] = array('#value' => implode(', ', $operations));
  }
  $form['subscriptions'] = array('#type' => 'checkboxes', '#options' => $subscriptions);
  $form['pager'] = array('#value' => theme('pager', NULL, 50, 0));
  $form['#theme'] = 'notifications_manage_subscriptions';
  return $form;
}

/**
 * Validate notifications_admin_subscriptions form submissions.
 * 
 * Check if any items have been selected to perform the chosen
 * 'Update option' on.
 */
function notifications_manage_subscriptions_form_validate($form, &$form_state) {
  $items = array_filter($form_state['values']['subscriptions']);
  if (count($items) == 0) {
    form_set_error('', t('No items selected.'));
  }
  else if (!notifications_manage_subscriptions_access(array_keys($items))) {
    form_set_error('', t('You don\'t have permissions to manage these subscriptions'));
  }
}

/**
 * Handle manage form submissions, run batch operations
 */
function notifications_manage_subscriptions_form_submit($form, &$form_state) {
  $operations = notifications_subscriptions_operations();
  $operation = $operations[$form_state['values']['operation']];
  // Filter out unchecked subscriptions
  $items = array_filter($form_state['values']['subscriptions']);
 
  if ($function = $operation['callback']) {
    // Add in callback arguments if present.
    if (isset($operation['callback arguments'])) {
      $args = array_merge(array($items), $operation['callback arguments']);
    }
    else {
      $args = array($items);
    }
    call_user_func_array($function, $args);
  }
  else {
    // We need to rebuild the form to go to a second step.  For example, to
    // show the confirmation form for the deletion of subscriptions.
    $form_state['rebuild'] = TRUE;
  }
}
/**
 * Build query for node administration filters based on session.
 */
function notifications_subscriptions_build_filter_query($account = NULL) {
  $filters = notifications_subscriptions_filters();

  // Build query
  $where = $args = array();
  $join = '';
  // If account passed, will be the first condition
  if ($account) {
    $where[] = "n.uid = %d";
    $args[] = $account->uid;
  }
  foreach ($_SESSION['subscriptions_overview_filter'] as $index => $filter) {
    list($key, $value) = $filter;
    switch ($key) {
      case 'status':
      case 'send_interval':
        $where[] = "n.$key = %d";
        $args[] = $value;
        break;
      case 'send_method':
      case 'type':
        $where[] = "n.$key = '%s'";
        $args[] = $value;
        break;
    }
    $args[] = $value;
  }
  $where = count($where) ? 'WHERE '. implode(' AND ', $where) : '';

  return array('where' => $where, 'join' => $join, 'args' => $args);
}

/**
 * List node administration filters that can be applied.
 * 
 * @param $admin
 *   Whether this is for the site admin page, will display more options
 */
function notifications_subscriptions_filters($admin = FALSE) {
  global $user;

  $filters['status'] = array(
    'title' => t('status'),
    'options' => _notifications_subscription_status(),
  );
  $filters['type'] = array(
    'title' => t('type'),
    // If not admin page, check access to each type
    'options' => notifications_subscription_types(NULL, 'title', !$admin),
  );
  $filters['send_method'] = array(
    'title' => t('method'),
    // If not admin mode, filter for current user
    'options' => _notifications_send_methods($admin ? NULL : $user),
  );
  $filters['send_interval'] = array(
    'title' => t('interval'), 
    'options' => _notifications_send_intervals(),
  );
  // Take out the filters when only one option
  foreach ($filters as $key => $data) {
    if (empty($data['options']) || count($data['options']) == 1) {
      unset($filters[$key]);
    }
  }
  return $filters;
}

/**
 * Subscription mass operations.
 * 
 * @param $account
 *   User account if we are administering subscriptions for this user
 */
function notifications_subscriptions_operations($account = NULL) {
  $operations = array(
    'activate' => array(
      'label' => t('Activate'),
      'callback' => 'notifications_subscriptions_mass_update',
      'callback arguments' => array('updates' => array('status' => NOTIFICATIONS_SUBSCRIPTION_ACTIVE)),
    ),
    'deactivate' => array(
      'label' => t('Deactivate'),
      'callback' => 'notifications_subscriptions_mass_update',
      'callback arguments' => array('updates' => array('status' => NOTIFICATIONS_SUBSCRIPTION_INACTIVE)),
    ),
    'delete' => array(
      'label' => t('Delete'),
      'callback' => NULL,
    ),
  );
  // Block option only for administrators
  if (user_access('administer notifications') || user_access('manage all subscriptions')) {
    $operations['block'] = array(
      'label' => t('Block'),
      'callback' => 'notifications_subscriptions_mass_update',
      'callback arguments' => array('updates' => array('status' => NOTIFICATIONS_SUBSCRIPTION_BLOCKED)),
    );
  }
  // Sending methods
  $parent = t('Change send method to');
  foreach (_notifications_send_methods($account) as $key => $name) {
    $operations['send_method-' . $key] = array(
      'label' => $name,
      'parent' => $parent,
      'callback' => 'notifications_subscriptions_mass_update',
      'callback arguments' => array('updates' => array('send_method' => $key)),
    );
  }
  $parent = t('Change send interval to');
  foreach (_notifications_send_intervals() as $key => $name) {
    $operations['send_method-' . $key] = array(
      'label' => $name,
      'parent' => $parent,
      'callback' => 'notifications_subscriptions_mass_update',
      'callback arguments' => array('updates' => array('send_interval' => $key)),
    );
  }

  // Intervals
  return $operations;
}

/**
 * Make mass update of subscriptions, changing all nodes in the $nodes array
 * to update them with the field values in $updates.
 *
 * IMPORTANT NOTE: This function is intended to work when called
 * from a form submit handler. Calling it outside of the form submission
 * process may not work correctly.
 *
 * @param array $subscriptions
 *   Array of subscriptions nid to update.
 * @param array $updates
 *   Array of key/value pairs with node field names and the
 *   value to update that field to.
 */
function notifications_subscriptions_mass_update($subscriptions, $updates) {
  foreach ($subscriptions as $id) {
    _notifications_subscriptions_mass_update_helper($id, $updates);
  }
  drupal_set_message(t('The update has been performed.'));
}

function _notifications_subscriptions_mass_update_helper($sid, $updates) {
  $subs = notifications_load_subscription($sid);
  foreach ($updates as $name => $value) {
    $subs->$name = $value;
  }
  notifications_save_subscription($subs);
  return $subs;  
}

/**
 * Form for multiple delete. When account passed check that all subscriptions belong to the user account
 */
function notifications_multiple_delete_confirm(&$form_state, $items, $destination = NULL) {
  $destination = $destination ? $destination : $_GET['q'];
  if (notifications_manage_subscriptions_access(array_keys($items))) {
    $form['items'] = array('#prefix' => '<ul>', '#suffix' => '</ul>', '#tree' => TRUE);
    // array_filter returns only elements with TRUE values
    foreach ($items as $id => $value) {
      // Load the subscription to display a friendly name
      $subscription = notifications_load_subscription($id);      
      $title = notifications_format_subscription($subscription, 'long');
      $form['items'][$id] = array(
        '#type' => 'hidden',
        '#value' => $id,
        '#prefix' => '<li>',
        '#suffix' => $title ."</li>\n",
      );
    }    
    $form['operation'] = array('#type' => 'hidden', '#value' => 'delete');
    $form['#submit'][] = 'notifications_multiple_delete_confirm_submit';
    $form['#validate'][] = 'notifications_multiple_delete_confirm_validate';
    $form['#redirect'] = $destination;
    return confirm_form($form,
                      t('Are you sure you want to delete these items?'),
                      $destination, t('This action cannot be undone.'),
                      t('Delete all'), t('Cancel'));
  }
  else {
    drupal_set_message(t('Validation error. You don\'t have permission to delete some of these subscriptions'), 'error');
    drupal_access_denied();
  }
}

/**
 * Validate permissions to delete all the subscriptions
 */
function notifications_multiple_delete_confirm_validate($form, &$form_state) {
  if (!notifications_manage_subscriptions_access(array_keys($form_state['values']['items']))) {
    form_set_error('', t('You don\'t have permission to manage all these subscriptions'));
  }
}

/**
 * Submit multiple delete from
 */
function notifications_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    foreach ($form_state['values']['items'] as $id => $value) {
      notifications_delete_subscription($id);
    }
    drupal_set_message(t('The subscriptions have been deleted.'));
  }
  return;
}

/**
 * Return form for node administration filters.
 * 
 * @param $admin
 *   Whether this is for the site admin page, will display more options
 */
function notifications_subscriptions_filter_form($admin = FALSE) {
  $session = &$_SESSION['subscriptions_overview_filter'];
  $session = is_array($session) ? $session : array();
  $filters = notifications_subscriptions_filters($admin);

  $i = 0;
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only items where'),
    '#theme' => 'node_filters', // We reuse this theme from node admin pages
  );
  $form['#submit'][] = 'notifications_subscriptions_filter_form_submit';
  foreach ($session as $filter) {
    list($type, $value) = $filter;
    $value = $filters[$type]['options'][$value];
    $form['filters']['current'][] = array('#value' => t('<strong>%a</strong> is <strong>%b</strong>', array('%a' => $filters[$type]['title'], '%b' => $value)));
  }

  foreach ($filters as $key => $filter) {
    $names[$key] = $filter['title'];
    $form['filters']['status'][$key] = array('#type' => 'select', '#options' => $filter['options']);
  }

  $form['filters']['filter'] = array('#type' => 'radios', '#options' => $names, '#default_value' => 'status');
  $form['filters']['buttons']['submit'] = array('#type' => 'submit', '#value' => (count($session) ? t('Refine') : t('Filter')));
  if (count($session)) {
    $form['filters']['buttons']['undo'] = array('#type' => 'submit', '#value' => t('Undo'));
    $form['filters']['buttons']['reset'] = array('#type' => 'submit', '#value' => t('Reset'));
  }

  drupal_add_js('misc/form.js', 'core');

  return $form;
}

/**
 * Process result from node administration filter form.
 */
function notifications_subscriptions_filter_form_submit($form, &$form_state) {
  $filters = notifications_subscriptions_filters();
  switch ($form_state['values']['op']) {
    case t('Filter'):
    case t('Refine'):
      if (isset($form_state['values']['filter'])) {
        $filter = $form_state['values']['filter'];

        // Flatten the options array to accommodate hierarchical/nested options.
        $flat_options = form_options_flatten($filters[$filter]['options']);

        if (isset($flat_options[$form_state['values'][$filter]])) {
          $_SESSION['subscriptions_overview_filter'][] = array($filter, $form_state['values'][$filter]);
        }
      }
      break;
    case t('Undo'):
      array_pop($_SESSION['subscriptions_overview_filter']);
      break;
    case t('Reset'):
      $_SESSION['subscriptions_overview_filter'] = array();
      break;
  }
}

/**
 * Theme subscriptions management form
 *
 * @ingroup themeable
 */
function theme_notifications_manage_subscriptions($form) {
  // If there are rows in this form, then $form['title'] contains a list of
  // the title form elements.
  $has_posts = isset($form['type']) && is_array($form['type']);
  $select_header = $has_posts ? theme('table_select_header_cell') : '';
  $header = array($select_header);
  $header[] = t('Type');
  if (!empty($form['description'])) {
    $header[] = t('Description');
  }
  if (!empty($form['username'])) {
    $header[] = t('User');
  }
  $header[] = t('Send method');
  $header[] = t('Send interval');
  $header[] = t('Status');
  $header[] = t('Operations');
  $output = '';

  $output .= drupal_render($form['options']);
  if ($has_posts) {
    foreach (element_children($form['type']) as $key) {
      $row = array();
      $row[] = drupal_render($form['subscriptions'][$key]);
      $row[] = drupal_render($form['type'][$key]);
      if (!empty($form['description'])) {
        $row[] = drupal_render($form['description'][$key]);
      }
      if (!empty($form['username'])) {
        $row[] = drupal_render($form['username'][$key]);
      }
      $row[] = drupal_render($form['send_method'][$key]);
      $row[] = drupal_render($form['send_interval'][$key]);       
      $row[] = drupal_render($form['status'][$key]);
      $row[] = drupal_render($form['operations'][$key]);
      $rows[] = $row;
    }

  }
  else {
    $rows[] = array(array('data' => t('No subscriptions available.'), 'colspan' => '6'));
  }

  $output .= theme('table', $header, $rows);
  if ($form['pager']['#value']) {
    $output .= drupal_render($form['pager']);
  }

  $output .= drupal_render($form);

  return $output;
}

/**
 * Theme node administration filter form.
 *
 * @ingroup themeable
 */
function theme_notifications_subscriptions_filter_form($form) {
  $output = '';
  $output .= '<div id="notifications-admin-filter">';
  $output .= drupal_render($form['filters']);
  $output .= '</div>';
  $output .= drupal_render($form);
  return $output;
}
