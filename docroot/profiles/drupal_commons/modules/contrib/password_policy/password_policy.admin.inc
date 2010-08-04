<?php
// $Id: password_policy.admin.inc,v 1.17 2010/04/16 14:15:16 deekayen Exp $

/**
 * @file
 * Admin page callback file for the password_policy module.
 */

//////////////////////////////////////////////////////////////////////////////
// Password policy admin settings

/**
 * Settings form display.
 */
function password_policy_admin_settings() {
  $form['expiration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expiration settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['expiration']['password_policy_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Admin (UID=1) password expires.'),
    '#default_value' => PASSWORD_POLICY_ADMIN,
    '#description' => t('Admin account password will obey expiration policy.'),
  );
  $form['expiration']['password_policy_begin'] = array(
    '#type' => 'radios',
    '#title' => t('Beginning of password expirations'),
    '#default_value' => PASSWORD_POLICY_BEGIN,
    '#options' => array('0' => t('After expiration time from setting a default policy (all passwords are valid during the expiration time from setting the default policy, and after that older than expiration time passwords expire).'), '1' => t('Setting a default policy (passwords older than expiration time expire after setting the default policy, retroactive behaviour).')),
  );
  $form['expiration']['password_policy_block'] = array(
    '#type' => 'radios',
    '#title' => t('Blocking expired accounts'),
    '#default_value' => PASSWORD_POLICY_BLOCK,
    '#options' => array('0' => t('Expired accounts are blocked. Only administrators can unblock them.'), '1' => t('The user with expired account is not blocked, but sent to a change password page. If the password is not changed, the account is blocked and the user cannot login again.')),
  );

  // Visibility
  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['visibility']['password_policy_show_restrictions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show restrictions on password change page.'),
    '#default_value' => PASSWORD_POLICY_SHOW_RESTRICTIONS,
    '#description' => t('Should password restrictions be listed on the password change page. A javascript warning block will be shown anyways if ithe typed in password does not meet the restrictions.'),
  );

  // E-mail notification settings.
  $form['email'] = array(
    '#type' => 'fieldset',
    '#title' => t('E-mail notification settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );
  $form['email']['password_policy_warning_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject of warning e-mail'),
    '#default_value' => _password_policy_mail_text('warning_subject'),
    '#maxlength' => 180,
    '#description' => t('Customize the subject of the warning e-mail message, which is sent to remind of password expiration.') .' '. t('Available variables are:') .' !username, !site, !uri, !uri_brief, !mailto, !date, !login_uri, !edit_uri, !days_left.',
  );
  $form['email']['password_policy_warning_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body of warning e-mail'),
    '#default_value' => _password_policy_mail_text('warning_body'),
    '#rows' => 15,
    '#description' => t('Customize the body of the warning e-mail message, which is sent to remind of password expiration.') .' '. t('Available variables are:') .' !username, !site, !uri, !uri_brief, !mailto, !date, !login_uri, !edit_uri, !days_left.',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
  );

  return $form;
}

/**
 * Submit hook for the settings form.
 */
function password_policy_admin_settings_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  switch ($op) {
    case t('Save configuration'):
      variable_set('password_policy_admin', $form_state['values']['password_policy_admin']);
      variable_set('password_policy_begin', $form_state['values']['password_policy_begin']);
      variable_set('password_policy_block', $form_state['values']['password_policy_block']);
      variable_set('password_policy_show_restrictions', $form_state['values']['password_policy_show_restrictions']);
      variable_set('password_policy_warning_subject', $form_state['values']['password_policy_warning_subject']);
      variable_set('password_policy_warning_body', $form_state['values']['password_policy_warning_body']);
      drupal_set_message(t('The configuration options have been saved.'));
      break;
    case t('Reset to defaults'):
      variable_del('password_policy_admin');
      variable_del('password_policy_begin');
      variable_del('password_policy_block');
      variable_del('password_policy_show_restrictions');
      variable_del('password_policy_warning_subject');
      variable_del('password_policy_warning_body');
      drupal_set_message(t('The configuration options have been reset to their default values.'));
      break;
  }
}

function _password_policy_admin_list_roles($pid) {
  $roles = array();
  $result = db_query('SELECT name FROM {role} r INNER JOIN {password_policy_role} p ON r.rid = p.rid WHERE p.pid = %d', $pid);
  while ($row = db_fetch_object($result)) {
    $roles[] = $row->name;
  }
  return $roles;
}

/**
 * The list of the password policies.
 */
function password_policy_admin_list() {
  $form = array();
  $options = array();
  $enabled = array();
  $result = db_query('SELECT pid, name, enabled, description, created, weight FROM {password_policy} ORDER BY weight');
  while ($row = db_fetch_array($result)) {
    $pid = $row['pid'];
    $options[$pid] = $row['enabled'] ? format_date($row['created'], 'medium') : '';
    if ($row['enabled']) {
      $enabled[] = $pid;
    }
    $form[$pid]['name'] = array('#value' => $row['name']);
    $form[$pid]['roles'] = array('#value' => theme('item_list', _password_policy_admin_list_roles($pid)));
    $form['weight'][$pid] = array('#type' => 'weight', '#default_value' => $row['weight']);
    $form[$pid]['view'] = array('#value' => l(t('view'), 'admin/settings/password_policy/'. $pid));
    $form[$pid]['edit'] = array('#value' => l(t('edit'), 'admin/settings/password_policy/'. $pid .'/edit'));
    $form[$pid]['delete'] = array('#value' => l(t('delete'), 'admin/settings/password_policy/delete/'. $pid));
  }
  $form['weight']['#tree'] = TRUE;
  $form['enabled'] = array('#type' => 'checkboxes', '#options' => $options, '#default_value' => $enabled);
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save changes'));
  return $form;
}

/**
 * Submit hook for the form on the default list view for the password policy module.
 */
function password_policy_admin_list_submit($form, &$form_state) {
  foreach ($form_state['values']['enabled'] as $pid => $enabled) {
    db_query("UPDATE {password_policy} SET weight = %d WHERE pid = %d", $form_state['values']['weight'][$pid], $pid);
    // Ensure we don't reset the timestamp on policies that are already enabled.
    if ($enabled) {
      db_query("UPDATE {password_policy} SET enabled = 1, created = %d WHERE pid = %d AND enabled = 0", time(), $pid);
    }
    else {
      db_query("UPDATE {password_policy} SET enabled = 0 WHERE pid = %d", $pid);
    }
  }

  drupal_set_message(t('The changes have been saved.'));
}

/**
 * The default view for the password policy.
 */
function password_policy_admin_view($policy) {
  $output = check_plain($policy['description']);
  $header = array(t('Name'), t('Constraint'));
  $rows = array();
  $roles = _password_policy_admin_list_roles($policy['pid']);
  if (!empty($roles)) {
    $rows[] = array(t('Roles'), theme('item_list', $roles));
  }
  if (!empty($policy['expiration'])) {
    $rows[] = array(t('Expiration'), $policy['expiration']);
  }
  if (!empty($policy['warning'])) {
    $rows[] = array(t('Warning'), $policy['warning']);
  }
  foreach ($policy['policy'] as $key => $val) {
    $desc = _password_policy_constraint_description($key);
    $rows[] = array($desc['name'], $val);
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No policies defined.'), 'colspan' => 2));
  }
  $output .= theme('table', $header, $rows);

  return $output;
}

/**
 * Form display for new or to be edited password policies.
 */
function password_policy_admin_form($form_state, $policy = NULL) {
  $form['policy']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $policy['name'],
    '#maxlength' => 64,
    '#required' => TRUE,
  );
  $form['policy']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $policy['description'],
  );

  $form['roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Roles'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['roles']['roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#options' => user_roles(TRUE),
    '#default_value' => isset($policy['roles']) ? $policy['roles'] : array(),
    '#description' => t('Select the roles that this policy will apply to.'),
  );

  $form['expiration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expiration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['expiration']['expiration'] = array('#type' => 'textfield',
    '#title' => t('Password Expiration'),
    '#default_value' => $policy['expiration'],
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('The passwords will expire after this number of days. The users with expired passwords will be blocked. Leaving this field empty won\'t put any password expiration constraints.'),
  );
  $form['expiration']['warning'] = array('#type' => 'textfield',
    '#title' => t('Password Expiration Warning'),
    '#default_value' => $policy['warning'],
    '#size' => 10,
    '#description' => t('The comma separated list of days. The warning about expiration of the password will be sent out on those days before the expiration. Leaving this field empty won\'t send out or display any warnings.'),
  );

  $form['constraints'] = array(
    '#type' => 'fieldset',
    '#title' => t('Constraints'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );

  foreach (_password_policy_constraints() as $constraint) {
    $desc = _password_policy_constraint_description($constraint);
    $form['constraints']['constraint_'. $constraint] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#default_value' => isset($policy['policy'][$constraint]) ? $policy['policy'][$constraint] : NULL,
      '#maxlength' => 2,
      '#title' => $desc['name'],
      '#description' => $desc['description'],
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => is_array($policy) ? t('Save') : t('Create'),
  );

  if ($policy) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
    $form['pid'] = array(
      '#type' => 'hidden',
      '#value' => $policy['pid'],
    );
  }

  return $form;
}

/**
 * Form validation hook for new or edited password policies.
 */
function password_policy_admin_form_validate($form, &$form_state) {
  $roles = array_filter($form_state['values']['roles']);
  if (empty($roles)) {
    form_set_error('roles', t('You must select at least one role for a policy to apply to.'));
  }
}

/**
 * Form submission hook for new or edited password policies.
 */
function password_policy_admin_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];

  if ($op == t('Delete')) {
    drupal_goto('admin/settings/password_policy/delete/'. $form_state['values']['pid']);
  }

  $policy = array();
  foreach ($form_state['values'] as $key => $value) {
    // If we have no form value, then we have no constraint to set.
    if (!is_array($value)) { //dodge issues with roles array
      $value = trim($value);
      if ($value != "" && preg_match("/^constraint_/", $key)) {
        $policy[substr($key, 11)] = $value;
      }
    }
  }

  // If we have an pid, update, else save.
  if (isset($form_state['values']['pid'])) {
    db_query("UPDATE {password_policy} SET name = '%s', description = '%s', policy = '%s', expiration = %d, warning = '%s' WHERE pid = %d", $form_state['values']['name'], $form_state['values']['description'], serialize($policy), trim($form_state['values']['expiration']), str_replace(' ', '', $form_state['values']['warning']), $form_state['values']['pid']);
    drupal_set_message(t('Policy %name has been updated.', array('%name' => $form_state['values']['name'])));
    watchdog('password_policy', 'Policy %name updated.', array('%name' => $form_state['values']['name']), WATCHDOG_NOTICE, l(t('edit'), 'admin/settings/password_policy/'. $form_state['values']['pid'] .'/edit'));
    $pid = $form_state['values']['pid'];
    db_query("DELETE FROM {password_policy_role} WHERE pid = %d", $pid);
  }
  else {
    db_query("INSERT INTO {password_policy} (name, description, enabled, policy, expiration, warning) VALUES ('%s', '%s', %d, '%s', %d, '%s')", $form_state['values']['name'], $form_state['values']['description'], 0, serialize($policy), trim($form_state['values']['expiration']), str_replace(' ', '', $form_state['values']['warning']));
    $pid = db_last_insert_id('password_policy', 'pid');
    drupal_set_message(t('Policy %name has been created.', array('%name' =>  $form_state['values']['name'])));
    watchdog('password_policy', 'New policy %name created.', array('%name' => $form_state['values']['name']), WATCHDOG_NOTICE, l(t('edit'), 'admin/settings/password_policy/'. $pid .'/edit'));
  }

  foreach (array_filter($form_state['values']['roles']) as $rid => $enabled) {
    db_query("INSERT INTO {password_policy_role} (pid, rid) VALUES (%d, %d)", $pid, $rid);
  }

  drupal_goto('admin/settings/password_policy/list');
}

/**
 * Confirmation form for the deletion of a password policy.  Deletion takes place
 * in password_policy_admin_delete_submit().
 */
function password_policy_admin_delete($form_state, $pid) {
  if (is_numeric($pid) && $policy = _password_policy_load_policy_by_pid($pid)) {
    $form['pid'] = array('#type' => 'hidden', '#value' => $policy['pid']);

    return confirm_form($form, t('Are you sure you want to delete the policy %name?', array('%name' => $policy['name'])), 'admin/settings/password_policy/list', t('This action cannot be undone.'), t('Delete'), t('Cancel'));
  }
  else {
    drupal_not_found();
    exit;
  }
}

/**
 * Submit hook for the delete policy operation.
 */
function password_policy_admin_delete_submit($form, &$form_state) {
  $pid = $form_state['values']['pid'];
  $policy = _password_policy_load_policy_by_pid($pid);

  db_query("DELETE FROM {password_policy} WHERE pid = %d", $pid);
  db_query("DELETE FROM {password_policy_role} WHERE pid = %d", $pid);
  drupal_set_message(t('Password policy %policy was deleted.', array('%policy' => $policy['name'])));
  watchdog('password_policy', 'Policy %name was deleted.', array('%name' => $policy['name']), WATCHDOG_NOTICE);
  drupal_goto('admin/settings/password_policy/list');
}

/**
 * Forced password change form.
 */
function password_policy_password_change_settings() {
  $form['password_policy_new_login_change'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force password change on first-time login'),
    '#default_value' => variable_get('password_policy_new_login_change', 0),
  );
  $roles = user_roles(TRUE);
  $form['password_policy_force_change_roles'] = array(
    '#type' => 'checkboxes',
    '#options' => $roles,
    '#title' => t('Force users in the following roles to change their password'),
    '#description' => t('Users who are not signed in will be required to change their password immediately upon sign in. Users who are currently signed in will be required to change their password upon their next page click, but after changing their password will be redirected back to the page they were attempting to access.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Submit hook for forced password change form.
 */
function password_policy_password_change_settings_submit($form, &$form_state) {
  global $user;
  $selected_roles = array();
  variable_set('password_policy_new_login_change', $form_state['values']['password_policy_new_login_change']);
  if ($form_state['values']['password_policy_new_login_change'] == 1) {
    watchdog('password policy', t('New user accounts must change password on new login enabled by !admin', array('!admin' => $user->name)), array(), WATCHDOG_NOTICE);
  }
  ($form_state['values']['password_policy_new_login_change']) ? drupal_set_message(t('New users will be required to change their password on first-time login.')) : drupal_set_message(t('New users will not be required to change their pasword on first-time login.'));
  foreach ($form_state['values']['password_policy_force_change_roles'] as $role) {
    // skip over null values returned by unselected roles
    if ($role == 0) {
      continue;
    }
    $uids = array();
    // special handling for authenticated users role
    // since this role makes no entries in the users_roles table
    if ($role == 2) {
      // no point in flagging Anonymous since they can't log in anyway
      $db_uids = db_query('SELECT uid FROM {users} WHERE uid <> 0');
    }
    else {
      $db_uids = db_query('SELECT uid FROM {users_roles} WHERE rid = %d', $role);
    }
    while ($uid = db_result($db_uids)) {
      if (($uid == 1 && PASSWORD_POLICY_ADMIN) || $uid > 1) {
        $uids[] = $uid;
      }
    }
    $sql = 'UPDATE {password_policy_force_change} SET force_change = 1 WHERE uid IN (' . db_placeholders($uids, 'int') . ')';
    db_query($sql, $uids);
    $selected_roles[] = $role;
  }
  if (count($selected_roles)) {
    $roles = user_roles(TRUE);
    $list = array();
    foreach ($selected_roles as $sr) {
      $list[] = $roles[$sr];
    }
    $list = implode(', ', $list);
    drupal_set_message(t('Users in the following roles will be required to immediately change their password: %list', array('%list' => $list)), 'status');
    watchdog('password policy', t('!admin has flagged users in the following roles to immediately change their password: %list', array('%list' => $list, '!admin' => $user->name)), array(), WATCHDOG_NOTICE);
  }
  else {
    drupal_set_message(t('No roles were selected.'));
  }
}

