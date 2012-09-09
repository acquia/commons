<?php
/**
 * @file
 * commons_follow_node.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function commons_follow_node_flag_default_flags() {
  $flags = array();
  // Exported flag: "Commons Follow (Individual nodes)".
  $flags['commons_follow_node'] = array(
    'content_type' => 'node',
    'title' => 'Commons Follow (Individual nodes)',
    'global' => '0',
    'types' => array(
      0 => 'post',
    ),
    'flag_short' => 'Follow',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Following',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'commons_follow_node',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;
}
