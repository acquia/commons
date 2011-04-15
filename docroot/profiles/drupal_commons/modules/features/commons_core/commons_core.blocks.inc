<?php

/**
 * @file
 *   All block-related functions of commons_core
 */

/**
 * Callback for hook_block()
 */
function _commons_core_block($op = 'list', $delta = 0, $edit = array()) {
  if ($op == 'list') {
    return _commons_core_block_list();
  }
  else if ($op == 'configure') {
    $func = "_commons_core_{$delta}_block_configure";
    if (function_exists($func)) {
      return $func(); 
    }
  }
  else if ($op == 'save') {
    $func = "_commons_core_{$delta}_block_save";
    if (function_exists($func)) {
      return $func($edit); 
    }
  }
  else if ($op == 'view') {
    $func = "_commons_core_{$delta}_block";
    return $func();
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
    'info' => t('Drupal Commons information'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['header_login'] = array(
    'info' => t('Header login block'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['join_learn'] = array(
    'info' => t('Join & learn more'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['group_menu'] = array(
    'info' => t('Group actions menu'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['group_create_content'] = array(
    'info' => t('Group create content selector'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['group_activity'] = array(
    'info' => t('Group activity'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['group_members'] = array(
    'info' => t('Group members and admins'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['create_group'] = array(
    'info' => t('Create a group'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  return $blocks;
}

/**
 * Display a block with global user statistics
 */
function _commons_core_user_statistics_block() {
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
function _commons_core_commons_info_block() {
  return array(
    'subject' => '',
    'content' => theme('commons_core_info_block'),
  );
}

/**
 * Display our custom login block for the header
 */
function _commons_core_header_login_block() {
  global $user;
  
  $block = array('subject' => '', 'content' => '');
  
  // Only anonymous users can log in
  if ($user->uid) {
    return NULL;
  }
  
  // No login needed if we're on the login page
  if (arg(0) == 'user') {
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
function _commons_core_join_learn_block() {
  // Check access
  if (!user_register_access()) {
    return NULL;
  }
  
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
function _commons_core_group_menu_block() {
  // Detect group context
  if ($group = commons_core_get_group_context()) {
    // Get the standard group details block
    $details = og_block_details();
    if (isset($details['content'])) {
      return array(
        'subject' => l(t('Actions'), "node/{$group->nid}", array('attributes' => array('title' => t('Return to !group', array('!group' => $group->title))))),
        'content' => $details['content']
      );
    }
  }
  
  return NULL;
}

/**
 * Display the dropdown group create content selector
 */
function _commons_core_group_create_content_block() {
  // If we're inside a group
  if ($group = commons_core_get_group_context()) {
    // Make sure the current user is a group member
    if (!og_is_group_member($group->nid)) {
      return NULL;
    }
  }

  return array(
    'subject' => '',
    'content' => drupal_get_form('commons_core_group_create_content_block_form'),
  );
}

/**
 * Provide the form for the group create content selector
 */
function commons_core_group_create_content_block_form(&$form_state) {
  $form = array();
  $types = array();

  // If we're in a group context, the content types will be 
  // gathered based on the group
  if ($group = commons_core_get_group_context()) {
    // Gather group node type links
    $links = module_invoke_all('og_create_links', $group);
  
    // Allow og_features to alter them
    // We avoid allowing any module to alter them, because the alter 
    // hook is often used to add non-node links
    og_features_og_links_alter($links);
    
    // Turn the links into node types
    foreach($links as $key => $link) {
      // Extract the node type
      if ($type = str_replace('create_', '', $key)) {
        // Load the node type
        if ($type = node_get_types('type', $type)) {
          // Add the type
          $types[$type->type] = $type->name;
        }
      }
    }
  }
  else {
    // Iterate all available node types
    foreach (node_get_types() as $id => $type) {
      // Check that this is a group post type
      if (og_is_group_post_type($id)) {
        // Check create permissions
        if (node_access('create', $id)) {
          $types[$id] = $type->name;
        } 
      }
    }
  }

  // Make sure we have at least one type
  if (empty($types)) {
    return NULL;
  }
  
  // Provide the selector
  $form['node_type'] = array(
    '#type' => 'select',
    '#options' => $types,
  );
  
  // Determine the default node type for the selector based on the path
  if (arg(0) == 'node' && is_numeric(arg(1))) {
    // Viewing a node
    if (!arg(2)) {
      $arg = arg(1);
    }
    // Viewing a group content tab
    else if (arg(2) == 'content' && arg(3)) {
      $arg = arg(3);
    }
  }
  // Viewing a global content page
  else if (arg(0) == 'content' && arg(1)) {
    $arg = arg(1);
  }
  
  if ($arg) {
    switch ($arg) {
      // Known content-type paths within Commons
      case 'polls':
        $form['node_type']['#default_value'] = 'poll';
        break;
      case 'discussions':
        $form['node_type']['#default_value'] = 'discussion';
        break;
      case 'documents':
        $form['node_type']['#default_value'] = 'document';
        break;
      case 'blogs':
        $form['node_type']['#default_value'] = 'blog';
        break;
      case 'wikis':
        $form['node_type']['#default_value'] = 'wiki';
        break;
      case 'events':
      case 'calendar':
        $form['node_type']['#default_value'] = 'event';
        break;
      default:
        // If numeric, try to load the nid to determine the node type
        // currently being viewed
        if (is_numeric($arg)) {
          if ($node = node_load($arg)) {
            $form['node_type']['#default_value'] = $node->type;
            break;
          }
        }
        // Try to account for any additional content types added
        else {
          foreach ($types as $type => $name) {
            // Try for a match (accounting for a trailing 's')
            if (strstr($arg, substr($type, 0, strlen($type) - 1))) {
              $form['node_type']['#default_value'] = $type;
              break;
            }
          }
        }
    }
  }
  
  // Store the group
  $form['group'] = array(
    '#type' => 'value',
    '#value' => $group ? $group : NULL,
  );
  
  // Submit button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create'),
  );
  
  return $form;
}

/**
 * Submit handler for the group create content selector
 */
function commons_core_group_create_content_block_form_submit(&$form, $form_state) {
  // Extract the group
  $group = $form_state['values']['group'];
  
  // Extract the node type
  $type = $form_state['values']['node_type'];
  
  // Add a link query for the group, if there is one
  $options = $group ? array('gids' => array($group->nid)) : NULL;
  
  // Redirect to the node form
  drupal_goto("node/add/{$type}", $options);
}

/**
 * Display the recent group activity block
 */
function _commons_core_group_activity_block() {
  // Gather the activity from Heartbeat
  $block = heartbeat_block('view', 'ogheartbeat');
  
  if (isset($block['content'])) {
    // Alter the title
    $block['subject'] = t('Latest group activity');
    return $block;
  }
  
  return NULL;
}

/**
 * Display the "Group members" block
 */
function _commons_core_group_members_block() {
  // Detect the group context
  if ($group = commons_core_get_group_context()) {
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
    $link .= l(t('View all members'), "og/users/{$group->nid}/faces");
    
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
function _commons_core_create_group_block() {
  // Check permissions
  if (user_access('create group content')) {
    return array(
      'subject' => '',
      'content' => drupal_get_form('commons_core_create_group_form'),
    );
  }

  return NULL;
}

/**
 * Provide the form for the "create a group" block
 */
function commons_core_create_group_form() {
  $form = array();
  $form['#action'] = url('node/add/group');
  $form['create'] = array(
    '#type' => 'submit',
    '#value' => t('Create a group'),
  );
  return $form;
}
