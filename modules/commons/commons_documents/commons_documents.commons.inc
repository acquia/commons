<?php
/**
 * @file
 * Commons module integration for the Commons Documents module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_documents_commons_entity_integration() {
  return array(
    'node' => array(
      'document' => array(
        'is_group_content' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_commons_bw_group_widget().
 */
function commons_documents_commons_bw_group_widget() {
  return array(
    'commons_documents' => array(
      'title' => t('Docs'),
      'type' => 'view',
      'vid' => 'commons_bw_documents',
      'display' => 'default',
      'weight' => 6,
      'bundle' => 'document',
    ),
  );
}
