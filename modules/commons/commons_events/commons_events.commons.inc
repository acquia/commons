<?php
/**
 * @file
 * Commons module integration for the Commons Events module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_events_commons_entity_integration() {
  return array(
    'node' => array(
      'event' => array(
        'is_group_content' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_commons_bw_create_all_widget().
 */
function commons_events_commons_bw_create_all_widget($group) {
  if (og_user_access('node', $group->nid, 'create event content')) {
    $link = l(t('List an event'), 'node/add/event',
      array(
        'attributes' => array('class' => 'commons-events-create'),
        'query' => array('og_group_ref' => $group->nid),
      )
    );

    return array(
      'commons_events' => array(
        'link' => $link,
        'text' => t('Create in-person or online meetups'),
        '#weight' => 6,
      ),
    );
  }
}
