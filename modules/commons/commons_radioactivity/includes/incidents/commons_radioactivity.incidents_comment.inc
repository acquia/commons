<?php

/**
 * @file
 * Radioactivity integration for the Comment module.
 */

/**
 * Implements hook_comment_insert().
 *
 * Increase a node's radioactivity when a comment is added.
 */
function commons_radioactivity_comment_insert($comment) {
  // Adding a comment that wasn't published shouldn't affect radioactivity.
  if ($comment->status == COMMENT_PUBLISHED) {
    $node = node_load($comment->nid);

    // A user adding a comment to their own node should not increase
    // radioactivity.
    if ($node->uid != $comment->uid) {
      commons_radioactivity_incident_node($node, COMMONS_RADIOACTIVITY_COMMENT);
    }
  }
}

/**
 * Implements hook_comment_delete().
 *
 * Decrease a node's radioactivity when a comment is removed.
 */
function commons_radioactivity_comment_delete($comment) {
  // Removing a comment that wasn't published shouldn't affect radioactivity.
  if ($comment->status == COMMENT_PUBLISHED) {
    $node = node_load($comment->nid);

    // A user removing a comment from their own node should not decrease
    // radioactivity.
    if ($node->uid != $comment->uid) {
      commons_radioactivity_incident_node($node, -1 * COMMONS_RADIOACTIVITY_COMMENT);
    }
  }
}

/**
 * Implements hook_comment_publish().
 *
 * Increase a node's radioactivity when a comment is published.
 */
function commons_radioactivity_comment_publish($comment) {
  $node = node_load($comment->nid);

  // Publishing a user's comment on their own node should not increase
  // radioactivity.
  if ($node->uid != $comment->uid) {
    commons_radioactivity_incident_node($node, COMMONS_RADIOACTIVITY_COMMENT);
  }
}

/**
 * Implements hook_comment_unpublish().
 *
 * Decrease a node's radioactivity when a comment is unpublished.
 */
function commons_radioactivity_comment_unpublish($comment) {
  $node = node_load($comment->nid);

  // Unpublishing a user's comment on their own node should not decrease
  // radioactivity.
  if ($node->uid != $comment->uid) {
    commons_radioactivity_incident_node($node, -1 * COMMONS_RADIOACTIVITY_COMMENT);
  }
}
