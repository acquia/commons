<?php
/**
 * @file
 * Commons module integration for the Commons Wikis module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_wikis_commons_entity_integration() {
  return array(
    'node' => array(
      'wiki' => array(
        'auto_title_instance' => FALSE,
        'is_group_content' => TRUE,
      ),
    ),
  );
}
