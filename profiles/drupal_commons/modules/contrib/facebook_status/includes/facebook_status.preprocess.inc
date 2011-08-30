<?php

/**
 * @file
 *   Preprocess functions for the Facebook-style Statuses theme templates.
 */
function template_preprocess_facebook_status_item(&$vars) {
  $status = $vars['status'];
  $options = $vars['options'];
  $context = facebook_status_determine_context($status->type);
  $vars['context'] = $context;
  $vars['sid'] = $status->sid;
  $vars['self'] = $status->type == 'user' && $status->sender == $status->recipient;
  $vars['page'] = $options['page'];
  $vars['type'] = $status->type;
  $vars['message'] = _facebook_status_run_filter($status->message);
  if (variable_get('facebook_status_nl2br', 0)) {
    $vars['message'] = nl2br($vars['message']);
  }
  $vars += array(
    'recipient' => '', 'recipient_name' => '', 'recipient_picture' => '',
    'meta' => '', 'links' => '',
  );
  if (module_exists('imagecache_profiles')) {
    $preset = variable_get('facebook_status_imagecache_preset', variable_get('user_picture_imagecache_profiles_default', ''));
  }
  $vars['recipient'] = $context['handler']->load_recipient($status->recipient);
  $vars['recipient_name'] = check_plain($context['handler']->recipient_name($vars['recipient']));
  $vars['recipient_link'] = $context['handler']->recipient_link($vars['recipient']);
  if ($status->type == 'user') {
    if (isset($preset)) {
      $vars['recipient']->imagecache_preset = $preset;
    }
    $vars['recipient_picture'] = theme('user_picture', $vars['recipient']);
  }
  $vars['sender'] = _facebook_status_user_load($status->sender);
  if (isset($preset)) {
    $vars['sender']->imagecache_preset = $preset;
  }
  $vars['sender_name'] = check_plain($vars['sender']->name);
  $vars['sender_link'] = theme('username', $vars['sender']);
  $vars['sender_picture'] = theme('user_picture', $vars['sender']);
  if ($options['cacheable']) {
    $vars['created'] = format_date($status->created, 'small');
  }
  else {
    $vars['created'] = theme('facebook_status_time', $status->created);
    if ($status->type == 'user') {
      if ($status->sender != $status->recipient) {
        $vars['meta'] = t('to !recipient', array('!recipient' => $vars['recipient_link']));
      }
    }
    elseif (!empty($vars['recipient_name'])) {
      $vars['meta'] = t('on !entity', array('!entity' => $vars['recipient_link']));
    }
    if ($options['links']) {
      $vars['links'] = !empty($status->links) ? theme('links', $status->links, array('class' => 'links inline')) : '';
    }
  }
  $vars['status_url'] = url('statuses/'. $status->sid, array('absolute' => TRUE));
}

/**
 * Returns themed HTML for a status.
 * @see facebook_status_show()
 */
function _facebook_status_show($status, $options) {
  if (!facebook_status_user_access('view', $status)) {
    return;
  }
  $options += array(
    'links' => TRUE,
    'page' => FALSE,
    'cacheable' => FALSE,
    'extras' => TRUE,
  );
  if ($options['links']) {
    $status->links = module_invoke_all('link', 'facebook_status', $status);
    drupal_alter('facebook_status_link', $status->links, $status);
    uasort($status->links, '_facebook_status_links_sort');
  }
  $message = trim($status->message);
  if ($options['page']) {
    $title = '';
    if (empty($message)) {
      drupal_not_found();
      return;
    }
    $sender = _facebook_status_user_load($status->sender);
    if ($status->type == 'user' && $status->sender == $status->recipient) {
      $title = t('@sender: @message', array('@sender' => $sender->name, '@message' => $message));
    }
    else {
      $context = facebook_status_determine_context($status->type);
      $recipient = $context['handler']->load_recipient($status->recipient);
      $recipient_name = $context['handler']->recipient_name($recipient);
      //"\xC2\xBB" is the unicode escape sequence for the HTML entity &raquo; (a double right angle bracket)
      $title = t("@sender \xC2\xBB @recipient: @message",
        array('@sender' => $sender->name, '@recipient' => $recipient_name, '@message' => $message)
      );
    }
    if (drupal_strlen($title) > 80) {
      //"\xE2\x80\xA6" is the unicode escape sequence for the HTML entity &hellip; (an ellipsis)
      $title = drupal_substr($title, 0, 79) ."\xE2\x80\xA6";
    }
    drupal_set_title($title);
  }
  drupal_add_css(drupal_get_path('module', 'facebook_status') .'/resources/facebook_status.css');
  return theme('facebook_status_item', $status, $options);
}

/**
 * Helps sort links by weight.
 */
function _facebook_status_links_sort($a, $b) {
  if (!isset($a['weight'])) {
    $a['weight'] = 0;
  }
  if (!isset($b['weight'])) {
    $b['weight'] = 0;
  }
  return $a['weight'] > $b['weight'] ? 1 : ($a['weight'] < $b['weight'] ? -1 : 0);
}
