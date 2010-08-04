<?php
// $Id: token_user.inc,v 1.3.4.7 2010/06/05 16:45:58 davereid Exp $

/**
 * @file
 * Implementations of token module hooks for the core user module.
 *
 * The token module requires specific hooks to be added to modules
 * so that those modules can return data about their objects to the
 * token API.  Until and unless token becomes a part of core, the
 * implementations of the token hooks for core modules are provided
 * in the token module itself.
 *
 * @ingroup token
 */

/**
 * Implementation of hook_token_values().
 */
function user_token_values($type, $object = NULL, $options = array()) {
  $values = array();
  switch ($type) {
    case 'user':
      if (isset($object)) {
        $account = $object;
      }
      else {
        global $user;
        $account = user_load(array('uid' => $user->uid));
      }

      // Adjust for the anonymous user name.
      if (!$account->uid && !$account->name) {
        $account->name = variable_get('anonymous', 'Anonymous');
      }

      $values['user']           = check_plain($account->name);
      $values['user-raw']       = $account->name;
      $values['uid']            = $account->uid;
      $values['mail']           = $account->uid ? $account->mail : '';
      $values['reg-date']       = $account->uid ? format_date($account->created, 'small') : '';
      $values['reg-since']      = $account->uid ? format_interval(time() - $account->created) : '';
      $values['log-date']       = $account->uid ? format_date($account->access, 'small') : '';
      $values['log-since']      = $account->uid ? format_interval(time() - $account->access) : '';
      $values['date-in-tz']     = $account->uid ? format_date(time(), 'small', '', $account->timezone) : '';
      $values['account-url']    = $account->uid ? url("user/$account->uid") : '';
      $values['account-edit']   = $account->uid ? url("user/$account->uid/edit") : '';

      break;
  }
  return $values;
}

/**
 * Implementation of hook_token_list().
 */
function user_token_list($type = 'all') {
  if ($type == 'user' || $type == 'all') {
    $tokens['user']['user']           = t("User's name");
    $tokens['user']['user-raw']       = t("User's unfiltered name.");

    $tokens['user']['uid']            = t("User's ID");
    $tokens['user']['mail']           = t("User's email address");

    $tokens['user']['reg-date']       = t("User's registration date");
    $tokens['user']['reg-since']      = t("User's registration date in 'time-since' format. (40 years 2 months)");
    $tokens['user']['log-date']       = t("User's last login date");
    $tokens['user']['log-since']      = t("User's last login date in 'time-since' format. (40 years 2 months)");
    $tokens['user']['date-in-tz']     = t("The current date in the user's timezone");
    $tokens['user']['account-url']    = t("The URL of the user's profile page.");
    $tokens['user']['account-edit']   = t("The URL the user's account editing page.");

    return $tokens;
  }
}
