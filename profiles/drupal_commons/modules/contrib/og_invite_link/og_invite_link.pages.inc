<?php

/**
 * @file
 * 	Contains the page callback functions for this module
 */
define('OG_INVITE_LINK_MAX_INVITES_PER_FORM', 20);

/**
 * Form constructor for inviting members into groups.
 */
function og_invite_link_invite_page_form($form_state = array(), $node) {
  // Set the page title (needed because it's a local task)
  drupal_set_title(t('Invite members to this group'));

  $form = array();
  $form['group'] = array(
    '#type' => 'value',
    '#value' => $node,
  );
  $form['invitees'] = array(
    '#type' => 'textfield',
    '#title' => t('Invitees'),
    '#maxlength' => 1024,
    '#required' => TRUE,
    '#autocomplete_path' => 'og_invite_link/autocomplete',
    '#description' => t('Add one or more usernames in order to invite users in this group. Multiple usernames should be separated by a comma. A maximum of !max invites can be sent out at a time.', array('!max' => OG_INVITE_LINK_MAX_INVITES_PER_FORM)),
  );
  $form['additional_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional message'),
    '#description' => t('Insert an additional message to be sent to the users.')
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Invite'),
  );
  return $form;
}

/**
 * Validation handler for the invite form
 */
function og_invite_link_invite_page_form_validate($form, &$form_state) {
  $invitees = array();

  // Extract the user names to send invites to
  $names = explode(',', $form_state['values']['invitees']);

  // Add them to an array, filtering out whitespace entries
  // in order to get a real count
  foreach ($names as $name) {
    $name = trim($name);
    if ($name) {
      $invitees[] = trim($name);
    }
  }

  // Make sure we have no more than the max amount of invites
  if (count($invitees) > OG_INVITE_LINK_MAX_INVITES_PER_FORM) {
    form_set_error('invitees', t('You can only send !max invitations at a time', array('!max' => OG_INVITE_LINK_MAX_INVITES_PER_FORM)));
  }
}

/**
 * Submit handler for the invite form
 */
function og_invite_link_invite_page_form_submit($form, &$form_state) {
  // Extract the group from the form
  $group = $form_state['values']['group'];
  // Extract the additional message from the form
  $message = filter_xss($form_state['values']['additional_message']);
  // Extract the user names to send invites to
  $names = explode(',', $form_state['values']['invitees']);
  // Track the valid invitees
  $invitees = array();
  // Track the invalid invitees
  $invalid = array();
  // Track the valid invitees that are already group members
  $in_group = array();

  // Attempt to load the users based on names, to determine which are real
  // users and which are not. We need to load each user individually instead
  // of using a single query because we need to determine which groups each
  // user belongs to in order to avoid inviting them to a group of theirs
  foreach ($names as $name) {
    // Trim and sanitize the name
    $name = trim(filter_xss(strip_tags($name)));

    // Make sure we have a name to invite after the filtering
    if ($name == '') {
      continue;
    }

    // Check for duplicates
    if (in_array($name, $invitees) || in_array($name, $invalid) || in_array($name, $in_group)) {
      continue;
    }

    // Attempt to load the user and make sure he is a valid one
    $user = user_load(array('name' => $name));
    if ($user->status) {
      // See if the user is already a member
      // Don't use og_is_group_member() because it's horrible
      if (isset($user->og_groups[$group->nid])) {
        $in_group[] = theme('username', $user);
      }
      else {
        // Invite the user
        og_invite_link_send_invite($user, $group, $message);
        $invitees[] = theme('username', $user);
      }
    }
    else {
      // Store the invalid user
      $invalid[] = $name;
    }
  }

  // Set a message for the invited users
  if (!empty($invitees)) {
    drupal_set_message(t('An invite has been sent to !users', array('!users' => implode(', ', $invitees))));
  }

  // Set a message for the invitees already in the group
  if (!empty($in_group)) {
    drupal_set_message(t('The following invitees are already members: !users', array('!users' => implode(', ', $in_group))), 'warning');
  }

  // Set a message for the invalid invitees
  if (!empty($invalid)) {
    drupal_set_message(t('The following invitees are not users: !users', array('!users' => implode(', ', $invalid))), 'error');
  }
}

/**
 * Page callback for joining a group
 *
 * @param object $group
 *   The group object
 * @param object $account
 *   The account in the invitation link
 * @param string $token
 *   The invitation token
 */
function og_invite_link_join($group, $account, $token) {
  global $user;

  // Load the invitation from the token
  $invitation = og_invite_link_get_invitation_by_token($token);

  // Determine if this is a valid invitation
  if (!$invitation) {
    drupal_set_message(t('This invitation is not valid or has expired.'), 'error');
    drupal_goto('<front>');
  }

  // Make sure this invitation was intended for the account
  // included in the invitation link
  if ($account->uid != $invitation->uid) {
    drupal_set_message(t('This is not a valid invitation.'), 'error');
    drupal_goto('<front>');
  }

  // Make sure the invitation is meant for this group
  if ($group->nid != $invitation->group_nid) {
    drupal_set_message(t('This is not a valid invitation.'), 'error');
    drupal_goto('<front>');
  }

  // If the user is logged in, make sure the invitation is meant for them
  if ($user->uid && $user->uid != $invitation->uid) {
    drupal_set_message(t('This is not a valid invitation.'), 'error');
    drupal_goto('<front>');
  }

  // See if the invitation has expired
  if ($invitation->accepted_timestamp) {
    drupal_set_message(t('This invitation has expired.'), 'error');
    drupal_goto('<front>');
  }

  // Log the user in if not yet logged in
  if (!$user->uid) {
    // Make sure the invited user is active and exists
    if ($account->uid && $account->status) {
      // Load the user in
      $user = $account;
    }
  }

  // If we don't have a logged in user by now, the invitation is invalid
  if (!$user->uid) {
    drupal_set_message(t('This is not a valid invitation.'), 'error');
    drupal_goto('<front>');
  }

  // See if the user is already in the group
  $is_member = og_is_group_member($invitation->group_nid, FALSE, $invitation->uid);
  if ($is_member) {
    drupal_set_message(t('You are already a member of this group.'));
    // Remove any pending invitations for this user and this group
    db_query("DELETE FROM {og_invite} WHERE uid = %d AND group_nid = %d AND accepted_timestamp = 0", $invitation->uid, $invitation->group_nid, $invitation->token);
  }
  else {
    // Determine the moderation status of the invitation
    if ($moderated = $invitation->moderated) {
      switch ($group->og_selective) {
        // If the group is open, no moderation needed
        case OG_OPEN:
          $moderated = 0;
          break;

        // If moderated and the group is now closed, this is no
        // longer a valid invitation
        case OG_CLOSED:
          // Alert the user
          drupal_set_message(t('This invitation is no longer valid.'), 'error');
          // Delete this invitation (should we?)
          db_query("DELETE FROM {og_invite} WHERE token = '%s'", $invitation->token);
          // Redirect home
          drupal_goto('<front>');
          break;
      }
    }

    // Update the invitation to mark it as accepted
    db_query("UPDATE {og_invite} SET accepted_timestamp = %d WHERE token = '%s'", time(), $invitation->token);

    // Remove any other pending invitations for this user and group
    db_query("DELETE FROM {og_invite} WHERE uid = %d AND group_nid = %d AND token <> '%s'", $invitation->uid, $invitation->group_nid, $invitation->token);

    // Create a group subscription for the user
    og_save_subscription($invitation->group_nid, $invitation->uid, array('is_active' => $moderated ? 0 : 1));

    // Set a message based on the moderation status
    if ($moderated) {
      drupal_set_message(t('You have requested access to join the group. A group administrator must first approve your request before you can join the group.'), 'warning');
      // Go to the home page if this group is private
      if ($group->og_private) {
        drupal_goto('<front>');
      }
    }
    else {
      drupal_set_message(t('You are a member of this group now.'));
    }
  }

  drupal_goto("node/{$invitation->group_nid}");
}

/**
 * Helper function for autocompletion
 * @see taxonomy_autocomplete()
 *
 * @todo A good thing would be to avoid returning
 * usernames that are already members in the group.
 * For that, the group id has to be sent as a parameter.
 */
function og_invite_link_autocomplete($string = '') {
  // The user enters a comma-separated list of names. We only autocomplete the last name.
  $array = drupal_explode_tags($string);

  // Fetch last name
  $last_string = trim(array_pop($array));
  $matches = array();
  if ($last_string != '') {
    $result = db_query_range("SELECT name FROM {users} WHERE LOWER(name) LIKE LOWER('%s%%')", $last_string, 0, 10);

    $prefix = count($array) ? implode(', ', $array) .', ' : '';

    while ($name = db_fetch_object($result)) {
      $n = $name->name;
      // Commas and quotes in usernames are special cases, so encode 'em.
      //(Although the usernames should not have such characters).
      if (strpos($name->name, ',') !== FALSE || strpos($name->name, '"') !== FALSE) {
        $n = '"'. str_replace('"', '""', $name->name) .'"';
      }
      $matches[$prefix . $n] = check_plain($name->name);
    }
  }

  drupal_json($matches);
}
