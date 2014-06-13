<?php
/**
 * @file
 * Commons module integration for the Commons Posts module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_posts_commons_entity_integration() {
  return array(
    'node' => array(
      'post' => array(
        'media' => TRUE,
        'is_group_content' => TRUE,
      ),
    ),
  );
}
