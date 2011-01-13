<?php
// $Id: user_relationships-pending_block.tpl.php,v 1.1.2.12 2010/01/03 19:19:11 alexk Exp $
/**
 * @file
 * Template for relationships requests block
 * List all pending requests and provide links to the actions that can be taken on those requests
 */
if ($relationships) {
  $list = array();
  foreach ($relationships as $rtid => $relationship) {
    $tt_rel_name = ur_tt("user_relationships:rtid:$rtid:name", $relationship->name);
    $tt_rel_plural_name = ur_tt("user_relationships:rtid:$rtid:plural_name", $relationship->plural_name);
    if ($user->uid == $relationship->requester_id) {
      $relation_to =& $relationship->requestee;
      $controls = theme('user_relationships_pending_request_cancel_link', $user->uid, $relationship->rid);
      $line = t('@rel_name to !username (!controls)', array('@rel_name' => $tt_rel_name, '!username' => theme('username', $relation_to), '!controls' => $controls));
      $key = t('Sent requests');
    }
    else {
      $relation_to =& $relationship->requester;
      $controls =
        theme('user_relationships_pending_request_approve_link', $user->uid, $relationship->rid).'|'.
        theme('user_relationships_pending_request_disapprove_link', $user->uid, $relationship->rid);
      $line = t('@rel_name from !username (!controls)', array('@rel_name' => $tt_rel_name, '!username' => theme('username', $relation_to), '!controls' => $controls));
      $key = t('Received requests');
    }
    $list[$key][] = $line;
  }

  $output = array();
  foreach ($list as $title => $users) {
    $output[] = theme('item_list', $users, $title);
  }
}

print isset($output) ? implode('', $output) : t('No Pending Requests');

?>
