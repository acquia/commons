<?php

/**
 * @file
 * Rules actions for sending Mime-encoded emails.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implementation of hook_rules_action_info().
 */
function mimemail_rules_action_info() {
  return array(
    'mimemail_rules_action_mail_to_user' => array(
      'label' => t('Send an HTML mail to a user'),
      'arguments' => array(
        'user' => array('type' => 'user', 'label' => t('Recipient')),
      ),
      'module' => 'Mime Mail',
      'eval input' => array('sender', 'from', 'to', 'cc', 'bcc', 'subject', 'message_html', 'message_plaintext', 'attachments'),
    ),
    'mimemail_rules_action_mail' => array(
      'label' => t('Send an HTML mail to an arbitrary mail address'),
      'module' => 'Mime Mail',
      'eval input' => array('sender', 'from', 'to', 'cc', 'bcc', 'subject', 'message_html', 'message_plaintext', 'attachments'),
    ),
    'mimemail_rules_action_mail_to_users_of_role' => array(
      'label' => t('Send an HTML mail to all users of a role'),
      'module' => 'Mime Mail',
      'eval input' => array('sender', 'from', 'to', 'cc', 'bcc', 'subject', 'message_html', 'message_plaintext', 'attachments'),
    ),
  );
}

/**
 * Action Implementation: Send a mail to a user and to an arbitrary mail address.
 */
function mimemail_rules_action_mail_to_user($user, $settings) {
  global $language;

  // Set the sender name and from address.
  if (empty($settings['sender']) && empty($settings['from'])) {
    $from = NULL;
  }
  else {
    $from = array(
      'name' => $settings['sender'],
      'mail' => $settings['from'],
    );
  }

  // If recipient field is empty send it to given user object.
  $to = empty($settings['to']) ? $user->mail : $settings['to'];

  // Prepare the message but not send.
  $message = drupal_mail('mimemail', 'rules_action_mail', $to, $language, $settings, $from, FALSE);

  $format = variable_get('mimemail_format', FILTER_FORMAT_DEFAULT);
  $message['body'] = check_markup($message['body'], $format, FALSE);

  // Send the prepared message.
  $message = mimemail(
    $message['from'],
    $message['to'],
    $message['subject'],
    $message['body'],
    NULL,
    $message['headers'],
    $message['params']['plaintext'],
    $message['params']['attachments'],
    $message['id']
  );

  if ($message['result']) {
    if (!empty($settings['bcc'])) $to .= ", " . $settings['bcc'];
    if (!empty($settings['cc'])) $to .= ", " . $settings['cc'];
    watchdog('rules', 'HTML mail successfully sent to %recipient', array('%recipient' => $to));
  }
}

/**
 * Action Implementation: rules_action_mail
 * This action makes use of the rules_action_mail_to_user action implementation.
 */
function mimemail_rules_action_mail($settings) {
  mimemail_rules_action_mail_to_user(NULL, $settings);
}

/**
 * Action: Send mail to all users of a specific role group(s).
 */
function mimemail_rules_action_mail_to_users_of_role($settings) {
  $recipients = array_filter(array_keys(array_filter($settings['recipients'])));

  // All authenticated users, which is everybody.
  if (in_array(DRUPAL_AUTHENTICATED_RID, $recipients)) {
    $result = db_query('SELECT mail FROM {users} WHERE uid > 0');
  }
  else {
    $rids = implode(',', $recipients);
    // Avoid sending emails to members of two or more target role groups.
    $result = db_query('SELECT DISTINCT u.mail FROM {users} u INNER JOIN {users_roles} r ON u.uid = r.uid WHERE r.rid IN ('. $rids .')');
  }

  // Set the sender name and from address.
  if (empty($settings['sender']) && empty($settings['from'])) {
    $from = NULL;
  }
  else {
    $from = array(
      'name' => $settings['sender'],
      'mail' => $settings['from'],
    );
  }

  while (($account = db_fetch_object($result))) {
    // Prepare the message but not send.
    $message = drupal_mail('mimemail', 'rules_action_role_mail',  $account->mail, user_preferred_language($account), $settings, $from, FALSE);

    $format = variable_get('mimemail_format', FILTER_FORMAT_DEFAULT);
    $message['body'] = check_markup($message['body'], $format, FALSE);

    // Send the prepared message.
    $message = mimemail(
      $message['from'],
      $message['to'],
      $message['subject'],
      $message['body'],
      NULL ,
      $message['headers'],
      $message['params']['plaintext'],
      $message['params']['attachments'],
      $message['id']
    );
  }

  if ($message['result']) {
    $roles = array_intersect_key(user_roles(TRUE), drupal_map_assoc($recipients));
    watchdog('rules', 'HTML mail successfully sent to role(s) %roles.', array('%roles' => implode(', ', $roles)));
  }
}

/**
 * @}
 */

