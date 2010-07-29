<?php
// $Id: constraint_punctuation.inc,v 1.3 2009/05/08 14:19:02 miglius Exp $
/**
 * @file
 * Password policy constraint callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// Constraint API

/**
 * Description of the constraint.
 */
function password_policy_constraint_punctuation_description() {
  return array('name' => t('Punctuation'), 'description' => t('Password must contain the specified minimum number of punctuation (not whitespace or an alphanumeric) characters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_punctuation_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one punctuation (not whitespace or an alphanumeric) character.', 'Password must contain at least @count punctuation (not whitespace or an alphanumeric) characters.');
}

/**
 * Password validation.
 */
function password_policy_constraint_punctuation_validate($password, $constraint, $uid) {
  $length = drupal_strlen($password);
  $num = 0;
  for ($i = 0; $i < $length; $i++) {
    if (ctype_punct($password[$i]))
      $num++;
  }
  return $num >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_punctuation_js($constraint, $uid) {
  $s = '';
  $s .= "  var i=0;\n";
  $s .= "  var num=0;\n";
  $s .= "  var chr=\"\";\n";
  $s .= "  while(i<value.length) {\n";
  $s .= "    chr=value.charAt(i);\n";
  $s .= "    if(chr.toUpperCase() == chr.toLowerCase() && \"1234567890\".indexOf(chr) == -1 && chr != ' ') {\n";
  $s .= "      num++;\n";
  $s .= "    }\n";
  $s .= "    i++;\n";
  $s .= "  }\n";
  $s .= "  if (num<$constraint) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_punctuation);\n";
  $s .= "  }\n";
  return $s;
}

