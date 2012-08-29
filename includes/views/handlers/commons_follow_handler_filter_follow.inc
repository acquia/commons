<?php

/**
 * Filter by what the user is following.
 */
class commons_follow_handler_filter_follow extends views_handler_filter {
  function can_expose() { return TRUE; }
  function query() {
    $table = $this->ensure_my_table();
      // Select for source translations (tnid = nid). Conditionally, also accept either untranslated nodes (tnid = 0).
    //@Todo: Allow other modules to return a list of mids to include for "The user is following."
    // Provide an API that lets other modules define these OR detect them automagically.
    // Query for NIDs, UIDs, and TIDs that the user is following based on what they have flagged.
    $user_flags = array();
    $user_flags += flag_get_user_flags('node');
    $user_flags += flag_get_user_flags('user');
    $user_flags += flag_get_user_flags('term');
    dpm($user_flags);
    $this->query->add_where_expression($this->options['group'], "$table.mid IN (17)");
  }
}

/**
 * Get all flagged content in a flag.
 *
 * @param
 *   The flag name for which to retrieve flagged content.
 */
function commons_activity_streams_get_flagged_content($account) {
  if (empty($account)) {
    global $user;
    $account = $user;
  }
  $return = array();
  $flag = flag_get_flag($flag_name);
  $result = db_select('flag_content', 'fc')
    ->fields('fc')
    ->condition('fid', $flag->fid)
    ->execute();
  foreach ($result as $row) {
    $return[] = $row;
  }
  return $return;
}