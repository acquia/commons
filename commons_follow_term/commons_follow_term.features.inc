<?php
/**
 * @file
 * commons_follow_term.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function commons_follow_term_flag_default_flags() {
  $flags = array();
  // Exported flag: "Commons Follow (Taxonomy term)".
  $flags['commons_follow_term'] = array(
    'content_type' => 'taxonomy_term',
    'title' => 'Commons Follow (Taxonomy term)',
    'global' => '0',
    'types' => array(
      0 => 'topics',
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
    'show_on_entity' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'api_version' => 2,
    'module' => 'commons_follow_term',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;
}
