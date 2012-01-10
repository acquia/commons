<?php

/**
 * @file
 *   Block functions
 */

/**
 * Callback for hook_block_view()
 */
function _commons_profile_block($op = 'list', $delta = 0, $edit = array()) {
  switch ($op) {
    case 'list':
      $function = "_commons_profile_block_list";
      break;
    case 'view':
    case 'configure':
    case 'save':
      $function = "_commons_profile_{$delta}_block_{$op}";
      break;
  }
  
  if ($function && function_exists($function)) {
    return call_user_func($function, $edit); 
  }
}

/**
 * Declare all available blocks
 */
function _commons_profile_block_list() {
  $blocks = array();
  $blocks['find_new_friends'] = array(
    'info' => t('Find new friends'),
    'cache' => BLOCK_CACHE_GLOBAL,
  );
  $blocks['image_links'] = array(
    'info' => t('Profile image and action links'),
    'cache' => BLOCK_NO_CACHE,
  );
  return $blocks;
}

/**
 * Render the "find new friends" block
 */
function _commons_profile_find_new_friends_block_view() {
  // Check access required to use this block
  if (user_access('search content') && user_access('access user profiles')) {
    module_load_include('inc', 'commons_profile', 'commons_profile.form');
    return array(
      'subject' => t('Find new friends'),
      'content' => drupal_get_form('commons_profile_friend_search_form'),
    );
  }
  
  return NULL;
}

/**
 * Generate the profile image and action links block
 */
function _commons_profile_image_links_block_view() {
  global $user;
  
  // Make sure we're viewing a user
  if (!($account = _commons_profile_get_current_user())) {
    return NULL;
  }
  
  // Fetch the profile image
  $account->imagecache_preset = variable_get('user_picture_imagecache_profiles', '');
  $picture = theme('user_picture', $account);
  
  // Generate a list of action links
  $links = array();
  
  // The links depend on whether or not the user is viewing
  // their own profile
  if ($user->uid == $account->uid) {
    // Provide a link to edit your profile
    $links['edit_profile'] = array(
      'title' => t('Edit my profile'),
      'href' => "user/{$account->uid}/edit",
    );
    
    // See if you have friend requests
    if (user_access('maintain own relationships')) {
      $requests = user_relationships_load(array('requestee_id' => $account->uid, 'approved' => FALSE));
      if (count($requests)) {
        // Provide a link to see the requests
        $links['friend_requests'] = array(
          'title' => t('Friend requests (!count)', array('!count' => count($requests))),
          'href' => variable_get('user_relationships_requests_link', 'relationships/requests'),
        );
      }
    }
    
    // Add a link to view your bookmarks
    $links['bookmarks'] = array(
      'title' => t('My bookmarks'),
      'href' => "user/{$account->uid}/bookmarks",
    );
  }
  else {
    // Provide relationship links/messages
    if (user_access('maintain own relationships')) {
      // For the Commons "Follower" relatinoship, hide controls to 
      // make another user unfollow the present user.
      $actions = _user_relationships_ui_actions_between($user, $account);
      static $rids_exclude;
      if (empty($rids_exclude[$user->uid])) {
        $rids_exclude[$user->uid] = array();
        $query = db_query("SELECT rid FROM {user_relationships} WHERE rtid = 1 AND requester_id != %d AND requestee_id = %d", $user->uid, $user->uid);
        while ($result = db_fetch_object($query)) {
          $rids_exclude[$user->uid][$result->rid] = $result->rid;
        }  
      }
      foreach ($actions as $key => $action) {
        if (in_array($key, $rids_exclude[$user->uid])) {
          continue;
        }
        $links["ur_action_$key"] = array(
          'title' => $action,
          // No href because this is the best that UR can offer
          'html' => TRUE,
          'attributes' => array('class' => 'ur_action'),
        );
      }
    }

    // If the current user has access to, provide a link
    // to edit the viewed user's profile
    if (user_access('administer users')) {
      $links['edit_profile'] = array(
        'title' => t('Edit !user\'s profile', array('!user' => $account->name)),
        'href' => "user/{$account->uid}/edit",
      );
    }
    
    // Provide link to contact the user
    if (_contact_user_tab_access($account)) {
      $links['contact'] = array(
        'title' => t('Contact !user', array('!user' => $account->name)),
        'href' => "user/{$account->uid}/contact",
      );
    }
  }
  
  // Allow other modules to alter the list of links
  drupal_alter('commons_profile_action_links', $links, $account);

  return array(
    'subject' => '',
    'content' => theme('commons_profile_image_action_links_block', $picture, $links, $account),
  );
}
