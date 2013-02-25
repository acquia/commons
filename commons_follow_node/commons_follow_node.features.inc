<?php
/**
 * @file
 * commons_follow_node.features.inc
 */

/**
 * Implements hook_views_api().
 */
function commons_follow_node_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function commons_follow_node_flag_default_flags() {
  $flags = array();
  // Exported flag: "Other content you follow".
  $flags['commons_follow_node'] = array(
    'content_type' => 'node',
    'title' => 'Other content',
    'global' => '0',
    'types' => array(
    ),
    'flag_short' => 'Follow',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Following',
    'unflag_long' => '',
    'unflag_message' => 'Not following',
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
    'weight' => '-10',
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'module' => 'commons_follow_node',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  // Exported flag: "Email content".
  $flags['email_node'] = array(
    'content_type' => 'node',
    'title' => 'Email content',
    'global' => '0',
    'types' => array(
    ),
    'flag_short' => 'Send Email',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Don\'t send Email',
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
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'commons_follow_node',
    'api_version' => 2,
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
