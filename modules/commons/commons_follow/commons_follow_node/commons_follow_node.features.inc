<?php
/**
 * @file
 * commons_follow_node.features.inc
 */

/**
 * Implements hook_views_api().
 */
function commons_follow_node_views_api($module = NULL, $api = NULL) {
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
    'global' => 0,
    'types' => array(),
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
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => -10,
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

  return $flags;
}

/**
 * Implements hook_flag_default_flags_alter().
 */
function commons_follow_node_flag_default_flags_alter(&$flags) {
  // Enable the default email_node flag provided by Message Subscribe Email.
  if (!empty($flags['email_node'])) {
    $flags['email_node']['status'] = TRUE;
  }
}
