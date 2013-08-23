<?php

/**
 * Implements hook_views_data().
 */
function commons_trusted_contacts_views_data() {
  $data['og_membership']['send_message'] = array(
    'title' => t('Send Message'),
    'help' => t('Views handler.'),
    'real field' => 'etid',
    'field' => array(
      'handler' => 'commons_trusted_contacts_handler_send_message',
    ),
  );

  return $data;
}
