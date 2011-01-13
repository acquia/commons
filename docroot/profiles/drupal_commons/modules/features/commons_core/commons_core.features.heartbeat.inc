<?php

/**
 * Implementation of hook_heartbeat_message_info().
 */
function commons_core_heartbeat_message_info() {
  $messages = array();

  // Exported heartbeat message: heartbeat_join_group
  $messages[] = array (
    'message' => '!username joined the group !group_title',
    'message_concat' => '',
    'message_id' => 'heartbeat_join_group',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
    ),
    'description' => 'User joins a group, save user activity',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
      '@username' => '[account:user-name-url]',
      '@group_title' => '[group:title-link]',
    ),
  );

  // Exported heartbeat message: heartbeat_leave_group
  $messages[] = array (
    'message' => '!username has left the group !group_name',
    'message_concat' => '',
    'message_id' => 'heartbeat_leave_group',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
    ),
    'description' => 'User leaves a group, save user activity',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
      '@username' => '[account:user-name-url]',
      '@group_name' => '[group:title-link]',
    ),
  );

  // Exported heartbeat message: heartbeat_flag_content
  $messages[] = array (
    'message' => '!username bookmarked the !type !node_title',
    'message_concat' => '',
    'message_id' => 'heartbeat_flag_content',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
    ),
    'description' => 'User flagged content, save user activity',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
      '@username' => '[flagging_user:user-name-url]',
      '@type' => '[node:type-name]',
      '@node_title' => '[node:title-link]',
    ),
  );

  // Exported heartbeat message: heartbeat_create_user
  $messages[] = array (
    'message' => 'The user account !user_name has been created',
    'message_concat' => '',
    'message_id' => 'heartbeat_create_user',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
    ),
    'description' => 'User is created, log activity',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
      '@user_name' => '[account:account-url]',
    ),
  );

  // Exported heartbeat message: heartbeat_delete_user
  $messages[] = array (
    'message' => 'The user !user_name has been deleted',
    'message_concat' => '',
    'message_id' => 'heartbeat_delete_user',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
    ),
    'description' => 'User account is deleted, save activity',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
      '@user_name' => '[account:user]',
    ),
  );

  // Exported heartbeat message: heartbeat_delete_content
  $messages[] = array (
    'message' => '!user_name deleted the !type "!node_title"',
    'message_concat' => '',
    'message_id' => 'heartbeat_delete_content',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
    ),
    'description' => 'User deleted content item, save activity',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
      '@user_name' => '[user:user-name-url]',
      '@type' => '[node:type-name]',
      '@node_title' => '[node:title]',
      '@types' => '[node:type-name]s',
    ),
  );

  // Exported heartbeat message: heartbeat_delete_comment
  $messages[] = array (
    'message' => '!username deleted the comment !comment_title from !node_title',
    'message_concat' => '',
    'message_id' => 'heartbeat_delete_comment',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
    ),
    'description' => 'User deletes a comment, save activity',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
      '@username' => '[user:user-name-url]',
      '@comment_title' => '[comment:comment-title]',
      '@node_title' => '[node:title-link]',
    ),
  );

  // Exported heartbeat message: heartbeat_friend_removed
  $messages[] = array (
    'message' => '!userA and !userB are no longer !relationship_type',
    'message_concat' => '',
    'message_id' => 'heartbeat_friend_removed',
    'concat_args' => 
    array (
      'type' => 'single',
      'group_by' => 'none',
      'group_target' => '',
      'group_by_target' => '',
      'group_num_max' => '',
      'merge_separator' => '',
      'merge_end_separator' => '',
      'roles' => 
      array (
        0 => '0',
        1 => '0',
        2 => '0',
      ),
    ),
    'description' => 'Two users are no longer friends',
    'perms' => '1',
    'custom' => 1,
    'variables' => 
    array (
      '@userA' => '[requester:user-name-url]',
      '@userB' => '[requestee:user-name-url]',
      '@relationship_type' => '[relationship:relationship-name]s',
    ),
  );


  return $messages;
}
