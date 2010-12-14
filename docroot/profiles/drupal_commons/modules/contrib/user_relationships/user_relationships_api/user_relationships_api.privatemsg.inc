<?php
// $Id: user_relationships_api.privatemsg.inc,v 1.1.2.8 2010/09/12 19:09:40 alexk Exp $
/**
 * @file Integration with Privatemsg module
 * @author mansspams http://drupal.org/user/293179
 * @author alex.k http://drupal.org/user/183217
 */

/**
 * Fills new Privatemsg autocomplete To: field with friends only.
 */
function user_relationships_api_privatemsg_sql_autocomplete_alter(&$fragments, $search, $names) {
  global $user;
  // Check if $author needs to be restricted.
  if (!variable_get('user_relationships_privatemsg_autocomplete_alter', 0) || !user_relationships_api_privatemsg_restrict($user)) {
    return;
  }
  $fragments['inner_join'][] = "INNER JOIN {user_relationships} ur ON u.uid = ur.requestee_id";
  $fragments['where'][] = "ur.approved = 1";
  $fragments['where'][] = "ur.requester_id = %d";
  $fragments['query_args']['where'][] = $user->uid;
}


/**
 * Blocks messages to users that are not in relationships with sender.
 * @see hook_privatemsg_block_message()
 */
function user_relationships_api_privatemsg_block_message($author, $recipients) {
  // Check if $author needs to be restricted.
  if (!user_relationships_api_privatemsg_restrict($author)) {
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

function user_relationships_api_privatemsg_restrict($author) {
    //#522078 admin killswitch, always ignore this for user 1.
  if (variable_get('user_relationships_restrict_privatemsg', 'all') == 'all' || $author->uid == 1) {
    return FALSE;
  }

  $exlude_roles = array_filter(variable_get('user_relationships_privatemsg_role_exclusions', array()));
  // First, make sure that we have a user object with roles, and then check if
  // the users does have any of the exluded roles.
  if (!empty($author->roles) || $author = user_load($author->uid)) {
    $is_excluded = array_intersect(array_keys($author->roles), $exlude_roles);
    if (!empty($is_excluded)) {
      return FALSE;
    }
  }
  return TRUE;
}
