<?php
// $Id: constraint_digit_placement.inc,v 1.1 2009/06/04 21:48:39 deekayen Exp $

/**
 * @file
 * Restrict placement of digits in passwords.
 *
 * @link http://drupal.org/node/316768
 * @author David Kent Norman (http://deekayen.net/)
 */

//////////////////////////////////////////////////////////////////////////////
// Constraint API

/**
 * Description of the constraint.
 */
function password_policy_constraint_digit_placement_description() {
  return array('name' => t('Digit Placement'), 'description' => t('Minimum number of digits in the password to allow a digit in the first or last position in the password (e.g. 2abcdefg and abcdefg4 are unacceptable passwords, while 2qpcxrm3 and 99qpcxrm are allowed passwords when 2 is set here).'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_digit_placement_error($constraint) {
  return t('Password must have a minimum of %numChars %digits to place any digits at the start or end of the password.',
    array('%numChars' => $constraint,
        '%digits' => format_plural($constraint, t('digit'), t('digits'))));
}

/**
 * Password validation.
 */
function password_policy_constraint_digit_placement_validate($password, $constraint, $uid) {
  $number_of_digits = 0;
  for ($i=0; $i<10; $i++) {
    $number_of_digits += substr_count($password, "$i"); // help string count by sending it a string instead of an int
  }
  if ($number_of_digits < (int)$constraint) {
    return preg_match("/^(\d+)|(\d+)$/", $password) != 1;
  }
  return TRUE;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_digit_placement_js($constraint, $uid) {
  return <<<JSS
  function substr_count(haystack, needle) {
    var pos = 0, cnt = 0;

    haystack += '';
    needle += '';
    var offset = 0;
    var length = 0;
    offset--;

    while ((offset = haystack.indexOf(needle, offset+1)) != -1) {
      if (length > 0 && (offset+needle.length) > length) {
        return false;
      } else {
        cnt++;
      }
    }
    return cnt;
  }

  var i=0;
  var num=0;
  for (i=0;i<10;i++) {
    num += substr_count(value, i);
  }
  if (num<$constraint && value.match(/^(\d+)|(\d+)$/) != null) {
    strength="low";
    msg.push(translate.constraint_digit_placement);
  }
JSS;
}
