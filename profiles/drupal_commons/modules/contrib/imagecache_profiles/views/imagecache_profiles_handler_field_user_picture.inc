<?php
// $Id: imagecache_profiles_handler_field_user_picture.inc,v 1.1.2.7 2010/03/24 15:28:43 andypost Exp $

class imagecache_profiles_handler_field_user_picture extends views_handler_field_user_picture {
  function option_definition() {
    $options = parent::option_definition();
    $options['imagecache_preset'] = array(
      'default' => variable_get('user_picture_imagecache_profiles_default', ''),
      'translatable' => FALSE
    );
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
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

  function render($values) {
    // Fake an account object.
    $options = $this->options;
    $account = new stdClass();
    $account->uid = $values->{$this->aliases['uid']};
    $account->name = $values->{$this->aliases['name']};
    $account->mail = isset($values->{$this->aliases['mail']}) ? $values->{$this->aliases['mail']} : '';
    $account->picture = $values->{$this->field_alias};

    if ($options['imagecache_preset']) {
      $account->imagecache_preset = $options['imagecache_preset'];
    }

    return theme('user_picture', $account);
  }
}
