<?php

/**
* Implements hook_flag().
*   Trigger radioactivity incidents when a user follows a ndoe or group.
*/
function commons_radioactivity_flag($op, $flag, $content_id, $account, $fcid) {
  if (in_array($flag->name, array('commons_follow_node', 'commons_follow_group'))) {

    $node = node_load($content_id);

    if ($op == 'flag') {
      // A user following her own node shouldn't add to its radioactivity.
      if ($node->uid == $account->uid) {
        return;
      }
      commons_radioactivity_incident_node($node,  COMMONS_RADIOACTIVITY_FLAG_NODE);
    }

    if ($op == 'unflag') {
      // A user unfollowing her own node shouldn't add to its radioactivity.
      if ($node->uid == $account->uid) {
        return;
      }
      commons_radioactivity_incident_node($node,  -1 * COMMONS_RADIOACTIVITY_FLAG_NODE);
    }
  }
}
