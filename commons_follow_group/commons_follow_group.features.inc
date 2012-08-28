<?php
/**
 * @file
 * commons_follow_group.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function commons_follow_group_flag_default_flags() {
  $flags = array();
  // Exported flag: "Commons Follow (Groups)".
  $flags['commons_follow_group'] = array(
    'content_type' => 'node',
    'title' => 'Commons Follow (Groups)',
    'global' => '0',
    'types' => array(
      0 => 'group',
    ),
    'flag_short' => 'Follow',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Following',
    'unflag_long' => '',
    'unflag_message' => 'Follow',
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
    'module' => 'commons_follow_group',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;
}
