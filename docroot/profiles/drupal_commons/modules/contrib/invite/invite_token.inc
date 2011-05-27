<?php

/**
 * @file
 * Token integration functions for invite module.
 */

/**
 * Implementation of hook_token_values().
 */
function invite_token_values($type = 'all', $object = NULL) {
  $values = array();
  if ($type == 'invite' && is_object($object)) {
    $values['inviter']            = check_plain($object->inviter->name);
    $values['inviter-raw']        = $object->inviter->name;
    $values['invite-mail']        = $object->email;
    $values['invite-message']     = check_plain($object->data['message']);
    $values['invite-message-raw'] = $object->data['message'];
    $values['join-link']          = url('invite/accept/'. $object->code, array('absolute' => TRUE));
  }
  return $values;
}

/**
 * Implementation of hook_token_list().
 */
function invite_token_list($type = 'all') {
  if ($type == 'invite' || $type == 'all') {
    $tokens['invite']['inviter']            = t('The user name of the inviter.');
    $tokens['invite']['inviter-raw']        = t('The user name of the inviter. WARNING - raw user input.');
    $tokens['invite']['invite-mail']        = t('The e-mail address of the invited user.');
    $tokens['invite']['invite-message']     = t('The personal message for the invitee.');
    $tokens['invite']['invite-message-raw'] = t('The personal message for the invitee as unfiltered text. WARNING - raw user input.');
    $tokens['invite']['join-link']          = t('The link to the registration page, including the invitation code.');
    return $tokens;
  }
}

/**
 * For a given context, builds a formatted list of tokens and descriptions
 * of their replacement values.
 *
 * @param type
 *   The token types to display documentation for. Defaults to 'all'.
 * @param prefix
 *   The prefix your module will use when parsing tokens. Defaults to '['
 * @param suffix
 *   The suffix your module will use when parsing tokens. Defaults to ']'
 * @return
 *   An HTML table containing the formatting docs.
 */
function theme_invite_token_help($type = 'all', $prefix = '[', $suffix = ']') {
  token_include();

  // @see http://drupal.org/node/127072
  $full_list = array();
  foreach ((array)$type as $t) {
    $full_list = array_merge($full_list, token_get_list($t));
  }

  $headers = array(t('Token'), t('Replacement value'));
  $rows = array();
  foreach ($full_list as $key => $category) {
    $rows[] = array(array('data' => drupal_ucfirst($key) .' '. t('tokens'), 'class' => 'region', 'colspan' => 2));
    foreach ($category as $token => $description) {
      $row = array();
      $row[] = $prefix . $token . $suffix;
      $row[] = $description;
      $rows[] = $row;
    }
  }

  $output = theme('table', $headers, $rows, array('class' => 'description'));
  return $output;
}

