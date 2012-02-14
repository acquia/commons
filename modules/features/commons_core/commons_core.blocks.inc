<?php

/**
 * @file
 *   All block-related functions of commons_core
 */

/**
 * Callback for hook_block_view()
 */
function _commons_core_block($op = 'list', $delta = 0, $edit = array()) {
  switch ($op) {
    case 'list':
      $function = "_commons_core_block_list";
      break;
    case 'view':
    case 'configure':
    case 'save':
      $function = "_commons_core_{$delta}_block_{$op}";
      break;
  }
  
  if ($function && function_exists($function)) {
    return call_user_func($function, $edit); 
  }
}

/**
 * Declare a list of all the available blocks
 */
function _commons_core_block_list() {
  $blocks = array();
  $blocks['user_statistics'] = array(
    'info' => t('User statistics'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['commons_info'] = array(
    'info' => t('Commons information'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['header_login'] = array(
    'info' => t('Header login block'),
    'cache' => BLOCK_NO_CACHE,
  );
  $blocks['join_learn'] = array(
    'info' => t('Join & learn more'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['group_menu'] = array(
    'info' => t('Group menu'),
    'cache' => BLOCK_NO_CACHE,
  );
  $blocks['group_create_content'] = array(
    'info' => t('Group create content selector'),
    'cache' => BLOCK_NO_CACHE,
  );
  $blocks['group_members'] = array(
    'info' => t('Group members and admins'),
    'cache' => BLOCK_NO_CACHE,
  );
  $blocks['create_group'] = array(
    'info' => t('Create a group'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['create_notice'] = array(
    'info' => t('Create a notice'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['your_content'] = array(
    'info' => t('Your content'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  return $blocks;
}

function _commons_core_your_content_block_view() {
  $block = array();
  $block['subject'] = t('Your content');
  $block['content'] = l(t('Your posts and comments'), 'mycontent/mine', array('attributes' => array('class' => 'my-content')));
  $block['content'] .= l(t('Your bookmarks'), 'bookmarks', array('attributes' => array('class' => 'my-bookmarks')));
  return $block;
}
/**
 * Display a block with global user statistics
 */
function _commons_core_user_statistics_block_view() {
  $data = array();
  
  // Determine total users on the site
  $sql = "SELECT COUNT(uid) FROM {users} WHERE status = 1";
  $total = db_result(db_query($sql));
  $data[] = format_plural($total, '1 user', '@count users');
  
  // Determine recently joined users
  $sql = "SELECT COUNT(uid) FROM {users} WHERE status = 1 AND created > %d";
  $total = db_result(db_query($sql, strtotime('-' . variable_get('commons_recent_join_interval', '3 months'), time())));
  $data[] = format_plural($total, '1 recently joined member', '@count recently joined members');
  
  // Build the block
  $block = array(
    'subject' => t('User statistics'),
    'content' => theme('commons_core_user_stats_block', $data), 
  );
  
  return $block;
}

/**
 * Configure the basic user statistics block
 */
function _commons_core_user_statistics_block_configure() {
  $form['commons_recent_join_interval'] = array(
    '#type' => 'select',
    '#title' => t('Recent joins time-frame'),
    '#default_value' => variable_get('commons_recent_join_interval', t('3 months')),
    '#options' => array(
      '3 days' => t('3 days'),
      '1 week' => t('1 week'),
      '2 weeks' => t('2 weeks'),
      '1 month' => t('1 month'),
      '3 months' => t('3 months'),
      '6 months' => t('6 months'),
    ),
    '#description' => t('The !user_directory contains a block that indicates the amount of recently joined members. Select the time-frame to be used to calculate this value.', array('!user_directory' => l(t('user directory'), 'users'))),
  );
  return $form;
}

/**
 * Save the basic user statistics block
 */
function _commons_core_user_statistics_block_save($edit) {
  variable_set('commons_recent_join_interval', $edit['commons_recent_join_interval']);
}

/**
 * Display the Commons information block
 */
function _commons_core_commons_info_block_view() {
  return array(
    'subject' => '',
    'content' => theme('commons_core_info_block'),
  );
}

/**
 * Display our custom login block for the header
 */
function _commons_core_header_login_block_view() {
  global $user;
  
  $block = array('subject' => '', 'content' => '');
  
  // Only anonymous users can log in
  if ($user->uid) {
    return NULL;
  }
  
  // No login needed if we're on the login page
  if (arg(0) == 'user' && !is_numeric(arg(1))) {
    return NULL;
  }
  
  // Determine if we're on the front page
  if (drupal_is_front_page()) {
    // Only provide a link
    $block['content'] = t('Already a member? !login', array('!login' => l(t('Login'), 'user')));
  }
  else {
    // Provide the login form
    $block['content'] = drupal_get_form('user_login_block');
  }
  
  return $block;
}

/**
 * Display the "Join & learn more" registration block
 */
function _commons_core_join_learn_block_view() {
  // Check access
  if (!user_register_access()) {
    return NULL;
  }
  
  module_load_include('inc', 'commons_core', 'commons_core.form');
  
  // Build the block
  $block = array(
    'subject' => t('Join & learn more'),
    'content' => drupal_get_form('commons_core_join_form'), 
  );
  
  return $block;
}

/**
 * Display the customized group actions menu block
 */
function _commons_core_group_menu_block_view() {
  // Detect group context
  if ($group = og_features_get_group_context()) {
    // Get the standard group details block
    $details = og_block_details();
    if (isset($details['content'])) {
      return array(
        'subject' => t('Group menu'),
        'content' => $details['content'],
      );
    }
  }
  
  return NULL;
}

/**
 * Display the dropdown group create content selector
 */
function _commons_core_group_create_content_block_view() {
  // If we're inside a group
  if ($group = og_features_get_group_context()) {
    // Make sure the current user is a group member
    if (!og_is_group_member($group->nid)) {
      return NULL;
    }
  }

  module_load_include('inc', 'commons_core', 'commons_core.form');

  return array(
    'subject' => '',
    'content' => drupal_get_form('commons_core_group_create_content_block_form'),
  );
}

/**
 * Display the "Group members" block
 */
function _commons_core_group_members_block_view() {
  // Detect the group context
  if ($group = og_features_get_group_context()) {
    // Count the number of group members for the block title
    $sql = "SELECT count(uid) FROM {og_uid} WHERE nid = %d AND is_active = 1";
    $count = db_result(db_query($sql, $group->nid));
      
    // Load the group managers from the view
    if ($view = views_get_view('group_block_members')) {
      if ($output = $view->execute_display('block_1')) {
        $managers .= $output['content'];
      }
      $view->destroy();
    }
    
    // Load the group members from the view
    if ($view = views_get_view('group_block_members')) {
      if ($output = $view->execute_display('block_2')) {
        $members .= $output['content'];
      }
      $view->destroy();
    }
    
    // Add a link to view all the members
    $link = og_menu_access_picture($group->nid) ? l(t('View all members'), "og/users/{$group->nid}/faces") : NULL;
    
    return array(
      'subject' => t('Group members (!count)', array('!count' => $count)),
      'content' => theme('commons_core_group_members_block', $managers, $members, $link),
    );
  }
  
  return NULL;
}

/**
 * Display the "create a group" block
 */
function _commons_core_create_group_block_view() {
  // Check permissions
  if (node_access('create', 'group')) {
    module_load_include('inc', 'commons_core', 'commons_core.form');
    return array(
      'subject' => '',
      'content' => drupal_get_form('commons_core_create_group_form'),
    );
  }

  return NULL;
}

/**
 * Display the "create a notice" block
 */
function _commons_core_create_notice_block_view() {
  // Check permissions
  if (node_access('create', 'notice')) {
    module_load_include('inc', 'commons_core', 'commons_core.form');
    return array(
      'subject' => '',
      'content' => drupal_get_form('commons_core_create_notice_form'),
    );
  }

  return NULL;
}
