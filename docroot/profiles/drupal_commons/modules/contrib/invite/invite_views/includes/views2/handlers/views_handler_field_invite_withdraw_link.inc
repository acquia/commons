<?php

/**
 * Invite withdraw link.
 */
class views_handler_field_invite_withdraw_link extends views_handler_field_invite_accept_link {
  function render($values) {
    $text = !empty($this->options['text']) ? check_plain($this->options['text']) : t('link');
    $reg_code = $values->{$this->aliases['reg_code']};
    return l($text, 'invite/withdraw/' . $reg_code);
  }
}
