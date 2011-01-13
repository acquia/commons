<?php
// $Id: custom.heartbeat_filters.inc,v 1.1.2.2 2010/02/21 12:31:33 stalski Exp $

/**
 * @file
 *   custom.heartbeat_filters.inc
 */

/*
 * Created on 10-okt-09
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */

/**
 * Heartbeat filter implementation for cusom filters.
 */
function heartbeat_filter_friends_and_groups(&$messages, HeartbeatAccess $stream) {
  global $user;

  $filtered_messages = array();
  foreach ($messages as $key => $message) {
    if ($message->nid > 0) {
      // the node is a group
      $node = node_load($message->nid);
      if (og_is_group_member($node->nid)) {
        $filtered_messages[$key] = $message;
      }
      // or the node is a group post, check its group
      elseif (isset($node->og_groups)) {
        foreach (array_keys($node->og_groups) as $gid) {
          // On group pages, we could check the current group
          // to block/allow messages to be "this-group" specific
          if (og_is_group_member($gid)) {
            $filtered_messages[$key] = $message;
            break;
          }
        }
      }

      // the target node is a group (nid is group post most of the time)
      if ($message->nid_target > 0) {
        if (og_is_group_member($message->nid_target)) {
          $filtered_messages[$key] = $message;
        }
      }
    }

    // if the actor of the message is a friend of the current user
    if (in_array($message->uid, $stream->stream->user_relations)) {
      $filtered_messages[$key] = $message;
    }
    // or if the message is addressed too the user
    if ($user->uid == $message->uid_target && $message->nid > 0) {
      $filtered_messages[$key] = $message;
    }
  }

  return $filtered_messages;
}

/**
 * Heartbeat filter implementation for cusom filters.
 */
function heartbeat_filter_articles(&$messages, HeartbeatAccess $stream) {
  $filtered_messages = array();
  foreach ($messages as $key => $message) {
    if ($message->nid > 0) {
      $node = node_load($message->nid);
      if ($node->type == 'article') {
        $filtered_messages[$key] = $message;
      }
    }
  }

  return $filtered_messages;
}

/**
 * Heartbeat filter implementation for cusom filters.
 */
function heartbeat_filter_reports(&$messages, HeartbeatAccess $stream) {
  $filtered_messages = array();

  foreach ($messages as $key => $message) {
  }

  return $filtered_messages;
}

/**
 * Heartbeat filter implementation for cusom filters.
 */
function heartbeat_filter_announcements(&$messages, HeartbeatAccess $stream) {

  $filtered_messages = array();

  foreach ($messages as $key => $message) {
  }

  return $filtered_messages;
}

/**
 * Heartbeat filter implementation for cusom filters.
 */
function heartbeat_filter_events(&$messages, HeartbeatAccess $stream) {

  $filtered_messages = array();

  foreach ($messages as $key => $message) {
  }

  return $filtered_messages;
}