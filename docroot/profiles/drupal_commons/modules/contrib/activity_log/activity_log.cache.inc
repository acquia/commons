<?php

/**
 * @file
 *   React to changes in entities by invalidating caches or deleting messages.
 */

/**
 * Clears the cache on related activity messages when an entity is updated.
 *
 * @param $id
 *   The ID of the related entity.
 * @param $type
 *   The type of the related entity. Valid types include those returned by
 *   activity_log_get_rules_data_types().
 * @param $extra_where
 *   An array of additional conditions to add to the WHERE clause of the query
 *   that finds events related to the entity.
 * @param $extra_args
 *   An array of additional arguments corresponding to the %-placeholders in
 *   the $extra_where parameter.
 */
function _activity_log_update_related($id, $type, $extra_where = array(), $extra_args = array(), $timestamp = NULL) {
  $bump = variable_get('activity_log_comments_bump', array('status' => 'status'));
  $query = "SELECT aid FROM {activity_log_events} WHERE (target_id = %d AND target_type = '%s')";
  $args = array($id, $type);
  foreach ($extra_where as $clause) {
    $query .= " OR $clause";
  }
  $result = db_query($query, array_merge($args, $extra_args));
  $query = "UPDATE {activity_log_messages} SET cached = ''";
  $where = array("(stream_owner_id = %d AND stream_owner_type = '%s')");
  $args = array($id, $type);
  if (!empty($timestamp)) {
    if (($type == 'facebook_status' && !empty($bump['status'])) || ($type == 'node' && !empty($bump['node']))) {
      $query .= " AND last_updated = %d";
      $args[] = $timestamp;
    }
  }
  while ($row = db_fetch_object($result)) {
    $where[] = "aids LIKE '%%,%d,%%'";
    $args[] = $row->aid;
  }
  if (!empty($where)) {
    $query .= " WHERE ". implode(" OR ", $where);
    db_query($query, $args);
  }
}

/**
 * Deletes Activity Log records related to an entity.
 *
 * @param $id
 *   The ID of the related entity.
 * @param $type
 *   The type of the related entity. Valid types include those returned by
 *   activity_log_get_rules_data_types().
 * @param $extra_where
 *   An array of additional conditions to add to the WHERE clause of the query
 *   that finds events related to the entity.
 * @param $extra_args
 *   An array of additional arguments corresponding to the %-placeholders in
 *   the $extra_where parameter.
 */
function _activity_log_delete_related($id, $type, $extra_where = array(), $extra_args = array()) {
  $query = "SELECT aid FROM {activity_log_events} WHERE (target_id = %d AND target_type = '%s')";
  $args = array($id, $type);
  foreach ($extra_where as $clause) {
    $query .= " OR $clause";
  }
  $result = db_query($query, array_merge($args, $extra_args));
  $query = "UPDATE {activity_log_messages} SET cached = '', ";
  $set = $where = $args = $aids = array();
  while ($row = db_fetch_object($result)) {
    $set[] = "aids = REPLACE(aids, '%s', ',')";
    $args[] = ",$row->aid,";
    $where[] = "aids LIKE '%%,%d,%%'";
    $aids[] = $row->aid;
  }
  if (!empty($where)) {
    $query .= implode(", ", $set);
    $query .= " WHERE ";
    $query .= implode(" OR ", $where);
    db_query($query, array_merge($args, $aids));
  }
  db_query("
    DELETE FROM {activity_log_messages}
    WHERE (stream_owner_id = %d AND stream_owner_type = '%s') OR aids = ','
  ", $id, $type);
}

//=============================================================================
// DELETE OR INVALIDATE CACHE FOR RELATED ACTIVITY RECORDS ON ENTITY DELETION.
//=============================================================================

/**
 * Invalidate Activity Log caches on messages related to a user.
 */
function _activity_log_user_update($uid) {
  _activity_log_update_related($uid, 'user', array("acting_uid = %d"), $extra_args = array($uid));
}

/**
 * Deletes Activity Log records related to a user.
 */
function _activity_log_user_delete($uid) {
  _activity_log_delete_related($uid, 'user', array("acting_uid = %d"), $extra_args = array($uid));
  db_query("DELETE FROM {activity_log_disabled_types} WHERE uid = %d", $uid);
}

/**
 * Implementation of hook_nodeapi().
 */
function activity_log_nodeapi(&$node, $op, $a3 = NULL, $a4 = NULL) {
  if ($op == 'update') {
    _activity_log_update_related($node->nid, 'node');
  }
  elseif ($op == 'delete') {
    _activity_log_delete_related($node->nid, 'node');
  }
}

/**
 * Implementation of hook_taxonomy().
 */
function activity_log_taxonomy($op, $type, $array = NULL) {
  if ($type == 'term') {
    if ($op == 'update') {
      _activity_log_update_related($array['tid'], 'taxonomy_term');
    }
    elseif ($op == 'delete') {
      _activity_log_delete_related($array['tid'], 'taxonomy_term');
    }
  }
}

/**
 * Implementation of hook_comment().
 */
function activity_log_comment($a1, $op) {
  $comment = (object) $a1;
  if ($op == 'insert') {
    _activity_log_update_related($comment->nid, 'node', array(), array(), $comment->timestamp);
  }
  elseif ($op == 'update') {
    _activity_log_update_related($comment->cid, 'comment');
  }
  elseif ($op == 'delete') {
    _activity_log_delete_related($comment->cid, 'comment');
  }
}

/**
 * Implementation of hook_facebook_status_save().
 */
function activity_log_facebook_status_save($status, $context, $edit, $options) {
  if ($edit) {
    _activity_log_update_related($status->sid, 'facebook_status');
  }
}

/**
 * Implementation of hook_facebook_status_delete().
 */
function activity_log_facebook_status_delete($status, $meta = array()) {
  _activity_log_delete_related($status->sid, 'facebook_status');
  if (module_exists('fbss_comments')) {
    $comments = fbss_comments_get_comments($status->sid);
    foreach ($comments as $comment) {
      _activity_log_delete_related($comment->cid, 'fbss_comment');
    }
  }
}

/**
 * Implementation of hook_fbss_comments_after_save().
 */
function activity_log_fbss_comments_after_save($comment, $edit) {
  if ($edit) {
    _activity_log_update_related($comment->cid, 'fbss_comment');
  }
  else {
    _activity_log_update_related($comment->sid, 'facebook_status', array(), array(), $comment->created);
  }
}

/**
 * Implementation of hook_fbss_comments_delete().
 */
function activity_log_fbss_comments_delete($cid) {
  _activity_log_delete_related($cid, 'fbss_comment');
}

/**
 * Implementation of hook_flag().
 */
function activity_log_flag($event, $flag, $content_id, $account) {
  _activity_log_update_related($content_id, $flag->content_type);
}
