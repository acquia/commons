<?php
/**
 * @file
 * Action to set the state of a user in a group.
 */

function commons_trusted_contacts_mark_as_read_action_info() {
  return array('commons_trusted_contacts_mark_as_read_action' => array(
    'type' => 'privatemsg_message',
    'label' => t('Mark as read'),
    'configurable' => FALSE,
  ));
}

function commons_trusted_contacts_mark_as_read_action($privatemsg_message) {
  db_update('pm_index')
    ->fields(array('is_new' => PRIVATEMSG_READ))
    ->condition('mid', $privatemsg_message->mid)
    ->execute();
}

