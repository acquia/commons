<?php

/**
* Implements hook_votingapi_insert().
*   Increase Radioactivity when a node receives a "Like."
*/
function commons_radioactivity_votingapi_insert($votes) {
  foreach ($votes as $vote) {
    if ($vote['tag'] == 'commons_like' && $vote['entity_type'] == 'node') {
      $node = node_load($vote['entity_id']);
      // A user's vote on her own node should not increase radioactivity.
      if ($node->uid != $vote['uid']) {
        commons_radioactivity_incident_node($node, COMMONS_RADIOACTIVITY_LIKE);
      }
    }  
  }
}

/**
* Implements hook_votingapi_insert().
*   Decrease Radioactivity when a "Like" is cancelled.
*/
function commons_radioactivity_votingapi_delete($votes) {
  foreach ($votes as $vote) {
    if ($vote['tag'] == 'commons_like' && $vote['entity_type'] == 'node') {
      $node = node_load($vote['entity_id']);
      // A user's vote on her own node did not increase radioactivity, so
      // we don't need to offset it when the vote is deleted.
      if ($node->uid != $vote['uid']) {
        commons_radioactivity_incident_node($node, -1 * COMMONS_RADIOACTIVITY_LIKE);
      }
    }  
  }
}
