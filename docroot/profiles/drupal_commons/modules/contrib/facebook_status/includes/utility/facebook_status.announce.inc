<?php

/**
 * @file
 *   Allows sending a status message to every user.
 */

/**
 * Admin form callback.
 */
function facebook_status_announce_admin(&$form_state) {
  $form = array();
  drupal_set_message(t('<span class="error">Warning</span>: this can be very slow on sites with lots of users.'), 'warning');
  $form['from'] = array(
    '#type' => 'textfield',
    '#title' => t('Sender'),
    '#description' => t('The username of the user from whom the messages will be sent.'),
    '#autocomplete_path' => 'user/autocomplete',
    '#required' => TRUE,
  );
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#required' => TRUE,
  );
  /*
  // Unfortunately we have to use the default format because we don't have any
  // way to keep track of which format to use at display time.
  $formats = filter_formats();
  $f = array();
  foreach ($formats as $format) {
    $f[$format->format] = filter_xss($format->name);
  }
  $form['format'] = filter_form();
   */
  $form['send'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );
  return $form;
}

/**
 * Admin form submit callback.
 */
function facebook_status_announce_admin_submit($form, &$form_state) {
  $v = $form_state['values'];
  $from = _facebook_status_user_load_by_name($v['from']);
  if (!$from->uid) {
    $from = FALSE;
  }
  if (!isset($v['format'])) {
    $v['format'] = NULL;
  }

  $count = db_result(db_query("SELECT COUNT(*) FROM {users} WHERE status = 1"));
  $batch = array(
    'operations' => array(
      array('facebook_status_announce_generate_status', array($v['message'], $from, $count, $v['format'])),
    ),
    'finished' => 'facebook_status_announce_batch_finished',
    'title' => t('Sending message to all users'),
    'file' => drupal_get_path('module', 'facebook_status') .'includes/utility/facebook_status.announce.inc',
  );
  batch_set($batch);
}

/**
 * Sends the status message to users.
 *
 * @param $message
 *   The message that will be sent.
 * @param $from
 *   The $user object of the status poster.
 * @param $count
 *   The number of active users.
 * @param $format
 *   The ID of the input format to use for the message.
 */
function facebook_status_announce_generate_status($message, $from, $count, $format, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
  }
  $uid = db_result(db_query_range("SELECT uid FROM {users} WHERE status = 1", $context['sandbox']['progress'], 1));
  // Caching here is actually slower than not caching because we should only load each user once.
  // So we use user_load() instead of _facebook_status_user_load().
  $to = user_load(array('uid' => $uid));
  facebook_status_save_status($to, 'user', $message, $from);
  $context['message'] = t('Sending message to %user (@current of @total)',
    array('%user' => $to->name, '@current' => $context['sandbox']['progress'], '@total' => $count));
  $context['sandbox']['progress']++;
  $context['results'][] = check_plain($to->name);
  $context['finished'] = $context['sandbox']['progress'] / $count;
}

/**
 * Batch finished callback.
 */
function facebook_status_announce_batch_finished($success, $results, $operations) {
  if ($success) {
    $count = count($results);
    if ($count < 50) {
      drupal_set_message(format_plural(count($results),
        'Sent message to 1 user: !list',
        'Sent message to @count users: !list',
        array('!list' => theme('item_list', $results))
      ));
    }
    else {
      drupal_set_message(t('Sent message to @count users.', array('@count' => $count)));
    }
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing %error_operation with arguments: @arguments',
      array(
        '%error_operation' => $error_operation[0],
        '@arguments' => print_r($error_operation[1], TRUE)
      )
    ));
  }
}
