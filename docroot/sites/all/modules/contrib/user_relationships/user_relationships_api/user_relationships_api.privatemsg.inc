<?php
// $Id: user_relationships_api.privatemsg.inc,v 1.1.2.6 2009/10/24 22:39:07 alexk Exp $
/**
 * @file Integration with Privatemsg module
 * @author mansspams http://drupal.org/user/293179
 * @author alex.k http://drupal.org/user/183217
 */
/**
 * Fills new Privatemsg autocomplete To: field with friends only.
 *
 */
function user_relationships_api_privatemsg_sql_autocomplete_alter(&$fragments, $search, $names) {
  //#522078 killswitch for autocomplete
  if (!variable_get('user_relationships_privatemsg_autocomplete_alter', 0)) {
    return;
  }

  global $user;
  
  static $uniqueprefix = 0;
  
  $fragments['inner_join'][] = "INNER JOIN {user_relationships} ur_$uniqueprefix ON u.uid = ur_$uniqueprefix.requestee_id";
  $fragments['where'][] = "ur_$uniqueprefix.approved = 1";
  $fragments['where'][] = "ur_$uniqueprefix.requester_id = %d";
  $fragments['query_args']['where'][] = $user->uid;
  
  $uniqueprefix++;
}


/**
 * Blocks messages to users that are not in relationships with sender.
 * @see hook_privatemsg_block_message()
 */
function user_relationships_api_privatemsg_block_message($author, $recipients) {
  //#522078 admin killswitch
  if (variable_get('user_relationships_restrict_privatemsg', 'all') == 'all') {
    return;
  }
  $blocked = array();
  foreach ($recipients as $recipient) {
    //block if user is only receiving pm's from his relationships, and author is not one of them
    if (
        (variable_get('user_relationships_restrict_privatemsg', 'all') == 'relationships' 
         || (variable_get('user_relationships_restrict_privatemsg', 'all') == 'all_overridable' 
             && $recipient->user_relationships_allow_private_message == 'on in relations')) 
        && !module_invoke_all('socnet_is_related', $author->uid, $recipient->uid)
     ) {
      $blocked[] = array(
        'uid' => $recipient->uid,
        'message' => t('!name is not a friend of yours.', array('!name' => theme('username', $recipient)))
      );
    }
  }
  return $blocked;
}
