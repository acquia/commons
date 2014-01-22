<?php

/**
 * @file
 * Commons Utility Links hooks implemented by the Commons Notify module.
 */

/**
 * Implements hook_commons_utility_links_alter().
 */
function commons_notify_commons_utility_links_alter(&$links) {
  if (user_is_logged_in()) {
    global $user;
    $account = $user;

    // Create an array of new links which will replace any existing links.
    $new_links = array();

    // Include the existing user name link if it's available.
    if (isset($links['name'])) {
      $new_links['name'] = $links['name'];
    }

    // Check for unread invitations.
    $unread_invitations = 0;
    if (module_exists('commons_trusted_contacts')) {
      $unread_invitations = count(commons_trusted_contacts_get_pending_invitations($account->uid));
    }

    // Check for unread messages.
    $unread_messages = 0;
    if (module_exists('privatemsg')) {
      $unread_messages = privatemsg_unread_count($account);
    }

    // Provide a default mailbox icon pointing to the private messages UI when
    // there are no unread messages or invitations.
    if (empty($unread_invitations) && empty($unread_messages)) {
      $new_links['no-unread-messages'] = array(
        'href' => 'user/' . $user->uid . '/contacts',
        'query' => array('qt-commons_trusted_contacts' => 'messages'),
        'title' => t('No unread messages'),
      );
    }

    // Add a link to the user's invitations.
    if ($unread_invitations) {
      $new_links['unread-invitations']= array(
        'href' => 'user/' . $user->uid . '/contacts',
        'query' => array('qt-commons_trusted_contacts' => 'invitations'),
        'title' => format_plural($unread_invitations, '1 invitation', '@count invitations'),
      );
    }

    // Add a link to the user's unread messages.
    if ($unread_messages) {
      $new_links['unread-messages']= array(
        'href' => 'user/' . $user->uid . '/contacts',
        'query' => array('qt-commons_trusted_contacts' => 'messages'),
        'title' => format_plural($unread_messages, '1 message', '@count messages'),
      );
    }

    // Include the existing logout link if it's available.
    if (isset($links['logout'])) {
      $new_links['logout'] = $links['logout'];
    }

    // Include the existing settings link if it's available.
    if (isset($links['settings'])) {
      $new_links['settings'] = $links['settings'];
    }

    // Override all existing links with the new links.
    $links = $new_links;
  }
}
