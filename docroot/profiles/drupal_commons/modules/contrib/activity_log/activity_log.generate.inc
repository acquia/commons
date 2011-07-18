<?php

/**
 * @file
 *   Provides functions that regenerate activity messages.
 */

define(ACTIVITY_LOG_GENERATE_COUNT, 50);

/**
 * Implementation of hook_activity_log_regenerate_info().
 */
function activity_log_activity_log_regenerate_info() {
  $path = drupal_get_path('module', 'activity_log') .'/activity_log.generate.inc';
  $items = array(
    'comment_insert' => array(
      'callback' => 'activity_log_regenerate_comments',
      'file' => $path,
    ),
    'node_insert' => array(
      'callback' => 'activity_log_regenerate_nodes',
      'file' => $path,
    ),
    'taxonomy_term_insert' => array(
      'callback' => 'activity_log_regenerate_taxonomy_terms',
      'file' => $path,
    ),
    'user_insert' => array(
      'callback' => 'activity_log_regenerate_users',
      'file' => $path,
    ),
    'facebook_status_tags_user_was_tagged' => array(
      'callback' => 'activity_log_regenerate_fbss_mentions',
      'file' => $path,
    ),
    'fbss_comments_save' => array(
      'callback' => 'activity_log_regenerate_fbss_comments',
      'file' => $path,
    ),
    'facebook_status_save' => array(
      'callback' => 'activity_log_regenerate_statuses',
      'file' => $path,
    ),
    'og_user_insert' => array(
      'callback' => 'activity_log_regenerate_og_join',
      'file' => $path,
    ),
  );
  if (module_exists('flag')) {
    foreach (flag_get_flags() as $flag) {
      $items['flag_flagged_'. $flag->name] = array(
        'callback' => 'activity_log_regenerate_flag',
        'arguments' => array($flag),
        'file' => $path,
      );
    }
  }
  return $items;
}

/**
 * Triggers the comment_insert Rules event for each relevant comment.
 */
function activity_log_regenerate_comments($age, $offset) {
  return _activity_log_regenerate_object('comment_insert', "SELECT * FROM {comments} WHERE status = 0 AND timestamp > %d", $age, $offset);
}

/**
 * Triggers the node_insert Rules event for each relevant node.
 */
function activity_log_regenerate_nodes($age, $offset) {
  return _activity_log_regenerate_object('node_insert', "SELECT * FROM {node} WHERE status = 1 AND created > %d", $age, $offset);
}

/**
 * Triggers the taxonomy_term_insert Rules event for each relevant term.
 */
function activity_log_regenerate_taxonomy_terms($age, $offset) {
  return _activity_log_regenerate_object('taxonomy_term_insert', "", 0, $offset, "SELECT * FROM {term_data}");
}

/**
 * Triggers the user_insert Rules event for each relevant user.
 */
function activity_log_regenerate_users($age, $offset) {
  return _activity_log_regenerate_object('user_insert', "SELECT * FROM {users} WHERE status = 1 AND created > %d", $age, $offset);
}

/**
 * Triggers the facebook_status_tags_user_was_tagged Rules event for @mentions.
 */
function activity_log_regenerate_fbss_mentions($age, $offset) {
  return _activity_log_regenerate_object(
    'facebook_status_tags_user_was_tagged', "
      SELECT f.*, t.rid
      FROM {facebook_status_tags} t
      INNER JOIN {facebook_status} f
        ON t.sid = f.sid
      WHERE t.type = 'user' AND f.created > %d
  ", $age, $offset);
}

/**
 * Triggers the fbss_comments_save Rules event for relevant status comments.
 */
function activity_log_regenerate_fbss_comments($age, $offset) {
  return _activity_log_regenerate_object('fbss_comments_save', "SELECT * FROM {fbss_comments} WHERE created > %d", $age, $offset);
}

/**
 * Triggers the facebook_status_save Rules event for each relevant status.
 */
function activity_log_regenerate_statuses($age, $offset) {
  return _activity_log_regenerate_object('facebook_status_save', "SELECT * FROM {facebook_status} WHERE created > %d", $age, $offset);
}

/**
 * Triggers the og_user_insert Rules event for group joins.
 */
function activity_log_regenerate_og_join($age, $offset) {
  return _activity_log_regenerate_object('og_user_insert', "SELECT nid, uid FROM {og_uid} WHERE is_active = 1 AND created > %d", $age, $offset);
}

/**
 * Triggers the flag_flagged_$flag Rules event for flagging.
 */
function activity_log_regenerate_flag($age, $offset, $flag) {
  return _activity_log_regenerate_object('flag_flagged_'. $flag->name, "
    SELECT c.content_id, c.uid, f.*
    FROM {flag_content} c
    LEFT JOIN {flags} f
      ON c.fid = f.fid
    WHERE timestamp > %d
  ", $age, $offset);
}

/**
 * Trigger events for historical data.
 */
function _activity_log_regenerate_object($event, $query, $age, $offset, $timeless_query = NULL) {
  if (!$age && $timeless_query) {
    $result = db_query_range($timeless_query, $offset, ACTIVITY_LOG_GENERATE_COUNT);
  }
  else {
    $result = db_query_range($query, $age, $offset, ACTIVITY_LOG_GENERATE_COUNT);
  }
  $count = 0;
  while ($object = db_fetch_object($result)) {
    if ($event == 'user_insert') {
      $object = array('account' => $object);
    }
    elseif (strpos($event, 'flag_flagged_') === 0) {
      $object = array('flag' => $object, 'flag_content_id' => $object->content_id, 'flagging_user' => activity_log_user_load($object->uid));
    }
    if ($event == 'facebook_status_tags_user_was_tagged') {
      $account = activity_log_user_load($object->rid);
      rules_invoke_event('facebook_status_tags_user_was_tagged', $object, $account);
    }
    elseif ($event == 'og_user_insert') {
      rules_invoke_event('og_user_insert', $object->uid, $object->nid);
    }
    else {
      rules_invoke_event($event, $object);
    }
    $count++;
  }
  if ($count < ACTIVITY_LOG_GENERATE_COUNT) {
    drupal_set_message(format_plural(
      'One activity message generated for the event %event.',
      '!count activity messages generated for the event %event.',
      array('!count' => $offset + $count, '%event' => $event)
    ));
  }
  elseif ($count == ACTIVITY_LOG_GENERATE_COUNT) {
    return $offset + ACTIVITY_LOG_GENERATE_COUNT;
  }
}
