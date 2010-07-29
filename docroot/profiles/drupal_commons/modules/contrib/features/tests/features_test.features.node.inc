<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _features_test_node_info() {
  $items = array(
    'features_test' => array(
      'name' => t('Testing: Features'),
      'module' => 'features',
      'description' => t('Content type provided for Features tests.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
