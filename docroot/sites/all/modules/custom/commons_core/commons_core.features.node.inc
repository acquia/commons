<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _commons_core_node_info() {
  $items = array(
    'discussion' => array(
      'name' => t('Discussion'),
      'module' => 'features',
      'description' => t('A item which allows the open discussion of a given topic.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'document' => array(
      'name' => t('Document'),
      'module' => 'features',
      'description' => t('A document item which contains a title, description, an unlimited amount of attached files.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'event' => array(
      'name' => t('Event'),
      'module' => 'features',
      'description' => t('An item that is used to provide details about an event. Events can be connected to multiple groups.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'group' => array(
      'name' => t('Group'),
      'module' => 'features',
      'description' => t('A group which members can be a part of.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'notice' => array(
      'name' => t('Notice'),
      'module' => 'features',
      'description' => t('A notice is an informative message that is meant to broadcast information to all of the users of the site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'wiki' => array(
      'name' => t('Wiki Page'),
      'module' => 'features',
      'description' => t('A wiki is used for information collaboration.'),
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
