<?php

/**
 * @file
 * Radioactivity integration for the Flag module.
 */

/**
 * Implements hook_flag().
 *
 * Trigger radioactivity incidents when a user follows a node or group.
 */
function commons_radioactivity_flag($op, $flag, $content_id, $account, $fcid) {
  if (in_array($flag->name, array('commons_follow_node', 'commons_follow_group'))) {
    $node = node_load($content_id);

    if ($op == 'flag') {
      // A user following their own node should not increase radioactivity.
      if ($node->uid != $account->uid) {
        commons_radioactivity_incident_node($node,  COMMONS_RADIOACTIVITY_FLAG_NODE);
      }
    }

    if ($op == 'unflag') {
      // A user unfollowing their own node should not decrease radioactivity.
      if ($node->uid != $account->uid) {
        commons_radioactivity_incident_node($node,  -1 * COMMONS_RADIOACTIVITY_FLAG_NODE);
      }
    }
  }
}
