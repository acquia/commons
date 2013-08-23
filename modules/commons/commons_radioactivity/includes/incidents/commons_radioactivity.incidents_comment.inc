<?php

/**
* Implements hook_comment_insert().
*   Increase Radioactivity when a node recieves a comment.
*/
function commons_radioactivity_comment_insert($comment) {
  // Moderated comments should not add radioactivity.
  if (!$comment->status) {
    return;
  }
  $node = node_load($comment->nid);
  // A user's comment on her own node should not add radioactivity.
  if ($node->uid == $comment->uid) {
    return;
  }
  commons_radioactivity_incident_node($node, COMMONS_RADIOACTIVITY_COMMENT);
}

/**
* Implements hook_comment_insert().
*   Increase Radioactivity when a node recieves a comment.
*/
function commons_radioactivity_comment_delete($comment) {
  // Deleting a comment that wasn't published shouldn't affect radioactivity.
  if (!$comment->status) {
    return;
  }
  $node = node_load($comment->nid);
  // This comment didn't add radioactivity originally, so we don't need to
  // offset any with its deletion.
  if ($node->uid == $comment->uid) {
    return;
  }
  commons_radioactivity_incident_node($node, -1 * COMMONS_RADIOACTIVITY_COMMENT);
}

/**
* Implements hook_comment_update().
*   Change radioactivity when a comment is published or unpuiblished.
*/
function commons_radioactivity_comment_update($comment) {
  // $comment_change will be equal to 1 if we're changing the publishing status
  // of the comment.
  $comment_change = $comment->status + $comment->original->status;
  // Is this comment's published status changing?
  if ($comment_change == 1) {
    $node = node_load($comment->nid);
    switch ($comment->status) {
      // The comment is being unpublished.
      case 0:
        commons_radioactivity_comment_delete($comment);
        break;
      // The comment is being published.
      case 1;
        commons_radioactivity_comment_insert($comment);
        break;
    }
  }
}