<?php

/**
 * @file
 *   Handles the conversation view.
 */

/**
 * Generates the title for the conversation page.
 */
function _facebook_status_conversation_title() {
  global $user;
  $args = explode(',', arg(2));
  $count = count($args);
  if (is_numeric($args[0]) && $count == 2 || ($count == 1 && $args[0] != $user->uid)) {
    if (empty($args[1])) {
      $recipient = _facebook_status_user_load($args[0]);
      if (!empty($recipient->uid)) {
        return t('Conversation between you and @recipient', array('@recipient' => $recipient->name));
      }
    }
    elseif (is_numeric($args[1])) {
      $account1 = _facebook_status_user_load($args[0]);
      $account2 = _facebook_status_user_load($args[1]);
      if (!empty($account1->uid) && !empty($account2->uid)) {
        return t('Conversation between @sender and @recipient', array('@sender' => $account1->name, '@recipient' => $account2->name));
      }
    }
  }
  return t('Conversation');
}

/**
 * Builds a page with a conversation view. A form to post a message to the other
 * user's profile may be at the top.
 */
function _facebook_status_conversation() {
  drupal_set_title(_facebook_status_conversation_title());
  global $user;
  $args = explode(',', arg(2));
  $count = count($args);
  if ($count > 2 || $count < 1 || ($count == 1 && $args[0] == $user->uid) || !is_numeric($args[0]) || ($count == 2 && !is_numeric($args[1]))) {
    drupal_not_found();
    return;
  }
  $key = array_search($user->uid, $args);
  if ($key === FALSE) {
    if ($count === 1) {
      $args[1] = $user->uid;
    }
    $arg = implode(',', $args);
    return views_embed_view('facebook_status_conversation', 'default', $arg, $arg);
  }
  $key = $key ? 0 : 1; //The recipient is not the current user.
  $recipient = _facebook_status_user_load($args[$key]);
  if (facebook_status_user_access('converse') && !empty($recipient->uid)) {
    return theme('facebook_status_form_display', $recipient, 'user');
  }
  drupal_not_found();
}
