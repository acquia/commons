<?php
/**
 * @file
 * commons_follow_term.features.inc
 */

/**
 * Implements hook_views_api().
 */
function commons_follow_term_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function commons_follow_term_flag_default_flags() {
  $flags = array();
  // Exported flag: "Topics you follow".
  $flags['commons_follow_term'] = array(
    'content_type' => 'taxonomy_term',
    'title' => 'Topics',
    'global' => '0',
    'types' => array(
      0 => 'topics',
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
    'weight' => '-8',
    'show_on_entity' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'module' => 'commons_follow_term',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  // Exported flag: "Email term".
  $flags['email_term'] = array(
    'content_type' => 'taxonomy_term',
    'title' => 'Email term',
    'global' => '0',
    'types' => array(),
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
    'show_on_entity' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'module' => 'commons_follow_term',
    'api_version' => 2,
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
