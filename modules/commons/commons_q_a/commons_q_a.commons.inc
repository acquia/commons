<?php
/**
 * @file
 * Commons module integration for the Commons Q&A module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_q_a_commons_entity_integration() {
  return array(
    'node' => array(
      'question' => array(
        'media' => TRUE,
        'is_group_content' => TRUE,
      ),
      'answer' => array(
        'exclude_topics' => TRUE,
        'exclude_rate' => TRUE,
        'is_group_content' => TRUE,
      ),
    ),
  );
}
