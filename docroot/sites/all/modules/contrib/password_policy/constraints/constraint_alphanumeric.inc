<?php
// $Id: constraint_alphanumeric.inc,v 1.3 2009/05/08 14:19:02 miglius Exp $
/**
 * @file
 * Password policy constraint callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// Constraint API

/**
 * Description of the constraint.
 */
function password_policy_constraint_alphanumeric_description() {
  return array('name' => t('Alphanumeric'), 'description' => t('Password must contain the specified minimum number of alphanumeric (letters or numbers) characters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_alphanumeric_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one alphanumeric (letter or number) character.', 'Password must contain at least @count alphanumeric (letter or number) characters.');
}

/**
 * Password validation.
 */
function password_policy_constraint_alphanumeric_validate($password, $constraint, $uid) {
  $length = drupal_strlen($password);
  $num = 0;
  for ($i = 0; $i < $length; $i++) {
    if (ctype_alnum($password[$i]))
      $num++;
  }
  return $num >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_alphanumeric_js($constraint, $uid) {
  $s = '';
  $s .= "  var i=0;\n";
  $s .= "  var num=0;\n";
  $s .= "  var chr=\"\";\n";
  $s .= "  while(i<value.length) {\n";
  $s .= "    chr=value.charAt(i);\n";
  $s .= "    if(chr.toUpperCase() != chr.toLowerCase() || \"1234567890\".indexOf(chr) != -1) {\n";
  $s .= "      num++;\n";
  $s .= "    }\n";
  $s .= "    i++;\n";
  $s .= "  }\n";
  $s .= "  if (num<$constraint) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_alphanumeric);\n";
  $s .= "  }\n";
  return $s;
}

