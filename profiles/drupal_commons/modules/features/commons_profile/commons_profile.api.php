<?php

/**
 * Implementation of hook_commons_profile_action_links_alter()
 *
 * Alter, or add to, the profile links residing under the profile image
 * 
 * @param &$links
 *   An array of links, passed by reference.
 * @param $account
 *   The user whose profile is being view, NOT the current user.
 */
function hook_commons_profile_action_links_alter(&$links, $account) {
  global $user;
  
  // If we're viewing our own profile
  if ($user->uid == $account->uid) {
    // Add a link to view notification messages
    if (messaging_simple_access($account)) {
      // Count the available messages for this account
      $sql = "SELECT COUNT(uid) FROM {messaging_store} WHERE uid = %d";
      $count = db_result(db_query($sql, $account->uid));
      $links['notification_messages'] = array(
        'title' => t('Messages') . (($count > 0) ? " ($count)" : ''),
        'href' => "user/{$account->uid}/messages",
      );
    }
    
    // Add a link to edit notification settings
    if (notifications_access_user($account)) {
      $links['notification_settings'] = array(
        'title' => t('Notification settings'),
        'href' => "user/{$account->uid}/notifications",
      );
    }
  }
}
