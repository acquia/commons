<?php

/**
 * Invite accept link.
 */
class views_handler_field_invite_accept_link extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['reg_code'] = 'reg_code';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $text = !empty($this->options['text']) ? check_plain($this->options['text']) : t('link');
    $reg_code = $values->{$this->aliases['reg_code']};
    return l($text, 'invite/accept/' . $reg_code);
  }
}
