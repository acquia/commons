<?php

/**
 * @file
 *   Page callbacks and functions for the Facebook-style Statuses Notifications module.
 */

function fbss_notifications_autocomplete_uid_to_username($uid) {
  if ($account = user_load(array('uid' => $uid))) {
    return check_plain($account->name) .' [uid:'. $uid .']';
  }
  return t('Not found');
}

function fbss_notifications_autocomplete_uid($string = '') {
  $matches = array();
  if ($string) {
    $result = db_query_range("SELECT name FROM {users} WHERE LOWER(name) LIKE LOWER('%s%%')", $string, 0, 10);
    while ($user = db_fetch_object($result)) {
      $matches[$user->name] = check_plain($user->name);
    }
  }

  drupal_json($matches);
}
