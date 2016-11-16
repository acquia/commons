<?php
/**
 * @file
 * commons_follow_term.features.inc
 */

/**
 * Implements hook_views_api().
 */
function commons_follow_term_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function commons_follow_term_flag_default_flags() {
  $flags = array();

  // Exported flag: "Topics you follow".
  $flags['commons_follow_term'] = array(
    'entity_type' => 'taxonomy_term',
    'title' => 'Topics',
    'global' => 0,
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
    'weight' => -8,
    'show_on_form' => 0,
    'access_author' => '',
    'show_in_links' => array(
      'diff_standard' => TRUE,
      'full' => TRUE,
      'token' => TRUE,
    ),
    'module' => 'commons_follow_term',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );

  return $flags;
}

/**
 * Implements hook_flag_default_flags_alter().
 */
function commons_follow_term_flag_default_flags_alter(&$flags) {
  // Enable the default email_term flag provided by Message Subscribe Email.
  if (!empty($flags['email_term'])) {
    $flags['email_term']['status'] = TRUE;
  }
}
