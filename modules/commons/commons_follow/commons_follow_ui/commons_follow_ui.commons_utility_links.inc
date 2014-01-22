<?php

/**
 * @file
 * Commons Utility Links hooks implemented by the Commons Follow UI module.
 */

/**
 * Implements hook_commons_utility_links().
 */
function commons_follow_ui_commons_utility_links() {
  $links = array();

  if (user_is_logged_in()) {
    global $user;
    $account = $user;
    $links['settings']= array(
      'href' => 'user/' . $account->uid . '/notification-settings',
      'title' => t('Settings'),
      'weight' => 10,
    );
  }

  return $links;
}
