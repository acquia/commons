<?php

/**
 * Invite resend link.
 */
class views_handler_field_invite_resend_link extends views_handler_field_invite_accept_link {
  function render($values) {
    $text = !empty($this->options['text']) ? check_plain($this->options['text']) : t('link');
    $reg_code = $values->{$this->aliases['reg_code']};
    return l($text, 'invite/resend/' . $reg_code);
  }
}
