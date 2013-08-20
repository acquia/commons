<?php
/**
 * @file
 * Action to set the state of a user in a group.
 */

function commons_trusted_contacts_set_state_active_action_info() {
  return array('commons_trusted_contacts_set_state_active_action' => array(
    'type' => 'og_membership',
    'label' => t('Set Membership state to Active'),
    'configurable' => FALSE,
  ));
}

function commons_trusted_contacts_set_state_active_action($og_membership) {
  if ($og_membership->state == OG_STATE_ACTIVE) {
    return;
  }

  // Don't process the group manager, if exists.
  $group = entity_load_single($og_membership->group_type, $og_membership->gid);
  if (!empty($group->uid) && $group->uid == $og_membership->etid && $og_membership->entity_type == 'user') {
    return;
  }

  $og_membership->state = OG_STATE_ACTIVE;
  $og_membership->save();
}

