<?php

/**
 * @file
 * Commons Utility Links hooks implemented by the Commons Utility Links module.
 */

/**
 * Implements hook_commons_utility_links().
 */
function commons_utility_links_commons_utility_links() {
  if (user_is_logged_in()) {
    global $user;
    $account = $user;
    $links['name'] = array(
      'href' => 'user',
      'title' => format_username($account),
    );
    $links['logout'] = array(
      'href' => 'user/logout',
      'title' => t('Logout'),
    );
  }
  else {
    if (variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)) {
      $links['signup'] = array(
        'href' => 'user/register',
        'title' => t('Signup'),
      );
    }
    $links['login'] = array(
      'href' => 'user/login',
      'title' => t('Login'),
    );
  }

  return $links;
}
