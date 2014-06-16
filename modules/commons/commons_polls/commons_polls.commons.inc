<?php
/**
 * @file
 * Commons module integration for the Commons Polls module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_polls_commons_entity_integration() {
  return array(
    'node' => array(
      'poll' => array(
        'media' => TRUE,
        'is_group_content' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_commons_bw_group_widget().
 */
function commons_polls_commons_bw_group_widget() {
  return array(
    'commons_polls' => array(
      'title' => t('Polls'),
      'type' => 'view',
      'vid' => 'commons_bw_polls',
      'display' => 'default',
      'weight' => 10,
      'bundle' => 'poll',
    ),
  );
}
