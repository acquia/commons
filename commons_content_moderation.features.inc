<?php
/**
 * @file
 * commons_content_moderation.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_content_moderation_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_content_moderation_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function commons_content_moderation_flag_default_flags() {
  $flags = array();
  // Exported flag: "Comment inappropriate".
  $flags['inappropriate_comment'] = array(
    'content_type' => 'comment',
    'title' => 'Comment inappropriate',
    'global' => '0',
    'types' => array(),
    'flag_short' => 'Flag as inappropriate',
    'flag_long' => 'Flag this content as inappropriate.',
    'flag_message' => '',
    'unflag_short' => 'Flag as non-inappropriate',
    'unflag_long' => 'Cancel reporting as inappropriate.',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'confirm',
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
    'show_on_comment' => 1,
    'flag_confirmation' => 'Are you sure you want to report this content as inappropriate?',
    'unflag_confirmation' => 'Are you sure you want to cancel reporting this content as inappropriate?',
    'api_version' => 2,
    'module' => 'commons_content_moderation',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Node inappropriate".
  $flags['inappropriate_node'] = array(
    'content_type' => 'node',
    'title' => 'Node inappropriate',
    'global' => '0',
    'types' => array(
      0 => 'event',
      1 => 'group',
      2 => 'page',
      3 => 'post',
      4 => 'wiki',
    ),
    'flag_short' => 'Report as inappropriate',
    'flag_long' => 'Report this content as inappropriate.',
    'flag_message' => '',
    'unflag_short' => 'Cancel report as inappropriate',
    'unflag_long' => 'Report this content as appropriate',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'confirm',
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
    'show_on_teaser' => 0,
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'flag_confirmation' => 'Are you sure you want to report this content as inappropriate?',
    'unflag_confirmation' => 'Are you sure you want cancel reporting this content as inappropriate?',
    'api_version' => 2,
    'module' => 'commons_content_moderation',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
