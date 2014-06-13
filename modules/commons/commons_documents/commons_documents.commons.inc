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
