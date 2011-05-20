<?php

/**
 * @file
 *   Form building and altering functions
 */
 
/**
 * The "find a new friend" search form
 */
function commons_profile_friend_search_form(&$form_state) {
  $form['search_message'] = array(
    '#value' => t('Search for other site users'),
  );
  
  $form['search_text'] = array(
    '#type' => 'textfield',
	  '#autocomplete_path' => 'user/findfriends/autocomplete', 
  );
    
  $form['search_button'] = array(
    '#type' => 'submit',
    '#value' => t('Search')
  );
  
  return $form;
}

/**
 * Submit handler for the "find a friend" search form
 */
function commons_profile_friend_search_form_submit($form_id, &$form_state) {
  // Extract and filter the input
  if ($name = check_plain($form_state['values']['search_text'])) {
    // Try to match a user name
    $sql = "SELECT uid FROM {users} WHERE name = '%s'";
    $uid = db_result(db_query($sql, $name));
    
    // Redirect based on what we found
    if ($uid) {
      // Go to the user's profile
      drupal_goto("user/{$uid}");
    }
    else {
      // Search for the input provided
      drupal_goto("search/user/{$name}");
    }
  }
}
