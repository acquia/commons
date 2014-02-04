<?php

/**
 * @file
 * Commons Utility Links hooks implemented by the Commons Trusted Contacts module.
 */

/**
 * Implements hook_commons_utility_links().
 */
function commons_trusted_contacts_commons_utility_links() {
  $links = array();

  if (user_is_logged_in()) {
    global $user;
    $account = $user;

    // Check for unread invitations.
    $unread_invitations = count(commons_trusted_contacts_get_pending_invitations($account->uid));

    // Check for unread messages.
    $unread_messages = privatemsg_unread_count($account);

    // Provide a default mailbox icon pointing to the private messages UI when
    // there are no unread messages or invitations.
    if (empty($unread_invitations) && empty($unread_messages)) {
      $links['no-unread-messages'] = array(
        'href' => 'user/' . $user->uid . '/contacts',
        'query' => array('qt-commons_trusted_contacts' => 'messages'),
        'title' => t('No unread messages'),
        'weight' => -9,
      );
    }

    // Add a link to the user's invitations.
    if ($unread_invitations) {
      $links['unread-invitations']= array(
        'href' => 'user/' . $user->uid . '/contacts',
        'query' => array('qt-commons_trusted_contacts' => 'invitations'),
        'title' => format_plural($unread_invitations, '1 invitation', '@count invitations'),
        'weight' => -8,
      );
    }

    // Add a link to the user's unread messages.
    if ($unread_messages) {
      $links['unread-messages']= array(
        'href' => 'user/' . $user->uid . '/contacts',
        'query' => array('qt-commons_trusted_contacts' => 'messages'),
        'title' => format_plural($unread_messages, '1 message', '@count messages'),
        'weight' => -7,
      );
    }
  }

  return $links;
}
