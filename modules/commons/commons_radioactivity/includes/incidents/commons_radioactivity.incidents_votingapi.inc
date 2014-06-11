<?php

/**
 * @file
 * Radioactivity integration for the Voting API module.
 */

/**
 * Implements hook_votingapi_insert().
 *
 * Increase radioactivity when a node is liked.
 */
function commons_radioactivity_votingapi_insert($votes) {
  foreach ($votes as $vote) {
    if ($vote['tag'] == 'commons_like' && $vote['entity_type'] == 'node') {
      $node = node_load($vote['entity_id']);

      // A user liking their own node should not increase radioactivity.
      if ($node->uid != $vote['uid']) {
        commons_radioactivity_incident_node($node, COMMONS_RADIOACTIVITY_LIKE);
      }
    }
  }
}

/**
 * Implements hook_votingapi_delete().
 *
 * Decrease radioactivity when a node is unliked.
 */
function commons_radioactivity_votingapi_delete($votes) {
  foreach ($votes as $vote) {
    // Information such as 'tag' may not be available when deleting a vote.
    // See https://drupal.org/node/2264643.
    if (isset($vote['tag']) && $vote['tag'] == 'commons_like' && $vote['entity_type'] == 'node') {
      $node = node_load($vote['entity_id']);

      // A user unliking their own node should not decrease radioactivity.
      if ($node->uid != $vote['uid']) {
        commons_radioactivity_incident_node($node, -1 * COMMONS_RADIOACTIVITY_LIKE);
      }
    }
  }
}
