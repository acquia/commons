<?php

/**
 * @file
 *   Handling for cross-posting.
 */

/**
 * Shows either the status owner (if the status was posted to one's own profile)
 * or the status owner and status poster (if the status was posted elsewhere).
 * Also shows the user picture.
 */
class facebook_status_views_handler_field_cross_pic extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    if (module_exists('imagecache_profiles')) {
      $options['imagecache_preset'] = array(
        'default' => variable_get('user_picture_imagecache_profiles_default', ''),
        'translatable' => FALSE,
      );
    }
    return $options;
  }
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    if (module_exists('imagecache_profiles')) {
      $presets = imagecache_presets();
      $opt = array('' => '');
      foreach ($presets as $preset) {
        $opt[$preset['presetname']] = check_plain($preset['presetname']);
      }
      $options = $this->options;
      $form['imagecache_preset'] = array(
        '#title' => t('Imagecache preset'),
        '#type'  => 'select',
        '#options' => $opt,
        '#default_value' => $options['imagecache_preset'],
      );
    }
  }
  function construct() {
    parent::construct();
    $this->additional_fields['recipient'] = 'recipient';
    $this->additional_fields['type'] = 'type';
  }
  function render($values) {
    $recipient_id = $values->{$this->aliases['recipient']};
    $sender_id = $values->{$this->field_alias};
    $sender = _facebook_status_user_load($sender_id);
    $type = $values->{$this->aliases['type']};
    $options = $this->options;
    if ($sender_id == $recipient_id && $type == 'user') {
      if (isset($options['imagecache_preset']) && $options['imagecache_preset']) {
        $sender->imagecache_preset = $options['imagecache_preset'];
      }
      return t('!picture !user', array(
        '!picture' => '<span class="facebook-status-sender-picture">'. facebook_status_display_user_picture($sender) .'</span>',
        '!user' => '<span class="facebook-status-sender">'. theme('username', $sender) .'</span>'
      ));
    }
    elseif ($type == 'user') {
      $recipient = _facebook_status_user_load($recipient_id);
      if (isset($options['imagecache_preset']) && $options['imagecache_preset']) {
        $sender->imagecache_preset = $options['imagecache_preset'];
        $recipient->imagecache_preset = $options['imagecache_preset'];
      }
      $args = array(
        '!sender' => '<span class="facebook-status-sender">'. theme('username', $sender) .'</span>',
        '!recipient' => '<span class="facebook-status-recipient">'. theme('username', $recipient) .'</span>',
        '!sender-picture' => '<span class="facebook-status-sender-picture">'. facebook_status_display_user_picture($sender) .'</span>',
        '!recipient-picture' => '<span class="facebook-status-recipient-picture">'. facebook_status_display_user_picture($recipient) .'</span>',
      );
      return t('!sender-picture !sender &raquo; !recipient-picture !recipient', $args);
    }
    else {
      $context = facebook_status_determine_context($type);
      $recipient = $context['handler']->load_recipient($recipient_id);
      if (isset($options['imagecache_preset']) && $options['imagecache_preset']) {
        $sender->imagecache_preset = $options['imagecache_preset'];
        $recipient->imagecache_preset = $options['imagecache_preset'];
      }
      $args = array(
        '!sender' => '<span class="facebook-status-sender">'. theme('username', $sender) .'</span>',
        '!recipient' => '<span class="facebook-status-recipient">'. $context['handler']->recipient_link($recipient) .'</span>',
        '!sender-picture' => '<span class="facebook-status-sender-picture">'. facebook_status_display_user_picture($sender) .'</span>',
      );
      return t('!sender-picture !sender &raquo; !recipient', $args);
    }
  }
}
