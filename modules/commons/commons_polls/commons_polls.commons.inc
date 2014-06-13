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
