<?php
// $Id: constraint_history.inc,v 1.3 2009/05/08 14:19:02 miglius Exp $
/**
 * @file
 * Password policy constraint callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// Constraint API

/**
 * Description of the constraint.
 */
function password_policy_constraint_history_description() {
  return array('name' => t('History'), 'description' => t('Password must not match any of the user\'s previous X passwords.') .'<br/><b>'. t('Note: ') .'</b>'. t('This constraint can only compare a new password with the previous passwords recorded since the password policy module was enabled.  For example, if the number of previous passwords is set to 3, the module may have only recorded 2 password changes since the module was enabled.  If the recorded password history is not large enough to support the constraint history size, the history size for the constraint will be reduced (temporarily during the constraint check) to match the available recorded history. Also note that a history size of 1 means that the user is unable to change their password to their current password.  This can be useful in certain situations, but a setting of 2+ will likely be more useful.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_history_error($constraint) {
  return format_plural($constraint, 'Password must not match last password.', 'Password must not match last @count passwords.');
}

/**
 * Password validation.
 */
function password_policy_constraint_history_validate($password, $constraint, $uid) {
  return !in_array(md5($password), _password_policy_constraint_history_old_passwords($constraint, $uid));
}

/**
 * Javascript portion.
 */
function password_policy_constraint_history_js($constraint, $uid) {
  drupal_add_js(drupal_get_path('module', 'password_policy') .'/constraints/scripts/webtoolkit.md5.js');
  $pass = _password_policy_constraint_history_old_passwords($constraint, $uid);
  $s = '';
  $s .= "  var num=0;\n";
  $s .= "  var pass=new Array(\"". implode('","', $pass) ."\");\n";
  $s .= "  var i;\n";
  $s .= "  for (i=0;i<pass.length;i++) {\n";
  $s .= "    if (pass[i] == MD5(value)) {\n";
  $s .= "      num=1;\n";
  $s .= "    }\n";
  $s .= "  }\n";
  $s .= "  if (num>0) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_history);\n";
  $s .= "  }\n";
  return $s;
}

//////////////////////////////////////////////////////////////////////////////
// Auxiliary

/**
 * Gets old password hashes.
 */
function _password_policy_constraint_history_old_passwords($constraint, $uid) {
  $pass = array();
  if (!empty($uid)) {
    // note that we specify a limit of the window size, but may not get that if the history isn't there.
    $result = db_query("SELECT pass FROM {password_policy_history} WHERE uid = %d ORDER BY created DESC LIMIT %d", $uid, $constraint);
    while ($row = db_fetch_array($result)) {
      $pass[] = $row['pass'];
    }
  }
  return $pass;
}

