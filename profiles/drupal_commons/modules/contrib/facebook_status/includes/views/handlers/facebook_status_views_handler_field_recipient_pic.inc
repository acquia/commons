<?php

/**
 * @file
 *   Handling for the recipient's picture in Views.
 */

/**
 * Shows the profile picture for the user that received the status, if applicable.
 */
class facebook_status_views_handler_field_recipient_pic extends views_handler_field {
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
    $this->additional_fields['type'] = 'type';
  }
  function render($values) {
    $type = $values->{$this->aliases['type']};
    if ($type == 'user') {
      $account = _facebook_status_user_load($values->{$this->field_alias});
      $options = $this->options;
      if (isset($options['imagecache_preset']) && $options['imagecache_preset']) {
        $account->imagecache_preset = $options['imagecache_preset'];
      }
      return '<span class="facebook-status-recipient-picture">'. facebook_status_display_user_picture($account) .'</span>';
    }
  }
}
