<?php

class commons_trusted_contacts_handler_send_message extends views_handler_field {

  function render($values) {
    global $user;

    return l(t('Send private message'), 'user/' . $user->uid . '/contacts/messages/popup/' . $values->og_membership_etid);
  }
}
