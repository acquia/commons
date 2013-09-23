<?php
/**
 * @file
 * commons_content_moderation.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function commons_content_moderation_user_default_roles() {
  $roles = array();

  // Exported role: content moderator.
  $roles['content moderator'] = array(
    'name' => 'content moderator',
    'weight' => 2,
  );

  return $roles;
}
