<?php

/**
 * @file
 *   Page callbacks for commons_profile
 */

/**
 * Autocomplete callback for the "find new friends" form
 */
function commons_profile_find_friends_autocomplete($string = '') {
  global $user;
  $matches = array();
  if ($string) {
    // Make sure the current user isn't returned in the autocomplete
    $ignore = array($user->uid);
    
    // Determine the user's current friends
    if ($user->uid) {
      $friends = user_relationships_load(array('user' => $user->uid));
      foreach ($friends as $friend) {
        // Add the friend to the ignore list
        $ignore[] = ($user->uid == $friend->requester_id) ? $friend->requestee_id : $friend->requester_id;
      }
    }
    
    // Build the query
    $sql = "SELECT name, picture";
    $sql .= " FROM {users}";
    $sql .= " WHERE LOWER(name) LIKE LOWER('%s%%')";
    $sql .= " AND status = 1";
    $sql .= " AND uid NOT IN (" . db_placeholders($ignore, 'int') . ")";
    
    // Add the string to the ignore list, so we can pass a single array
    // of query arguments in
    array_unshift($ignore, $string);
    
    // Retrieve the results
    $result = db_query_range($sql, $ignore, 0, 10);
    while ($match = db_fetch_object($result)) {
      $matches[$match->name] = theme('commons_profile_friend_autocomplete_item', check_plain($match->name), $match->picture);
    }
  }

  drupal_json($matches);
}
