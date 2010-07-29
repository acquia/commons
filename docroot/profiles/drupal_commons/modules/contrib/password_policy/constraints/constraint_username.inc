<?php
// $Id: constraint_username.inc,v 1.2 2008/07/13 23:16:45 miglius Exp $
/**
 * @file
 * Password policy constraint callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// Constraint API

/**
 * Description of the constraint.
 */
function password_policy_constraint_username_description() {
  return array('name' => t('Username'), 'description' => t('Password must differ from the username. Put any positive number to enforce this policy.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_username_error($constraint) {
  return t('Password must differ from the username.');
}

/**
 * Password validation.
 */
function password_policy_constraint_username_validate($password, $constraint, $uid) {
  $account = user_load(array('uid' => $uid));
  return drupal_strtolower($account->name) != drupal_strtolower($password);
}

/**
 * Javascript portion.
 */
function password_policy_constraint_username_js($constraint, $uid) {
  $account = user_load(array('uid' => $uid));
  $s = '';
  $s .= "  var username='". $account->name ."';\n";
  $s .= "  if (username.toLowerCase() == value.toLowerCase()) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_username);\n";
  $s .= "  }\n";
  return $s;
}

