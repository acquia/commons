<?php
/**
 * @file
 * Commons module integration for the Commons Groups module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_groups_commons_entity_integration() {
  return array(
    'node' => array(
      'group' => array(
        'is_group_content' => FALSE,
        'is_group' => TRUE,
        'exclude_commons_follow' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_commons_bw_group_widget().
 */
function commons_groups_commons_bw_group_widget() {
  return array(
    'commons_all' => array(
      'title' => t('All'),
      'type' => 'view',
      'vid' => 'commons_bw_all',
      'display' => 'default',
      'weight' => -10,
      'default' => 1,
      'bundle' => 'post',
    ),
  );
}
