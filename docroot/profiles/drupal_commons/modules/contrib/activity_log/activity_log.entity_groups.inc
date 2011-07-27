<?php

/**
 * @file
 *   Entity group definitions and callbacks for the Activity Log module.
 */

/**
 * Defines the default entity groups.
 */
function activity_log_entity_groups($stream_owner = TRUE) {
  $og = module_exists('og');
  $ur = module_exists('user_relationships_api');
  $co = module_exists('comments');
  $fc = module_exists('fbss_comments');
  $ft = module_exists('facebook_status_tags');
  $fb = module_exists('facebook_status');
  $tx = module_exists('taxonomy');
  if ($ur) {
    $ur = $ur && (db_result(db_query("SELECT COUNT(rtid) FROM {user_relationship_types}")) > 0);
  }
  $groups = array(
    'custom' => array(
      'items callback' => 'activity_log_eg_custom',
      'title' => t('Custom'),
      'expose fields' => array('id', 'type'),
      'weight' => -100,
    ),
    'acting user' => array(
      'items callback' => 'activity_log_eg_acting_user',
      'title' => t('Acting user'),
      'expose fields' => array('acting_uid'),
      'weight' => -95,
    ),
    'target entity' => array(
      'items callback' => 'activity_log_eg_target_entity',
      'title' => t('The entity on which the action was performed'),
      'additional arguments' => array($stream_owner),
      'weight' => -90,
    ),
  );
  if ($og) {
    $groups['active group'] = array(
      'items callback' => 'activity_log_eg_active_group',
      'title' => t('The active group'),
      'weight' => -85,
    );
    $groups['active group members'] = array(
      'items callback' => 'activity_log_eg_active_group_members',
      'title' => t('Members of the active group'),
      'weight' => -80,
    );
    $groups['active group admin'] = array(
      'items callback' => 'activity_log_eg_active_group_admin',
      'title' => t('Administrators of the active group'),
      'weight' => -78,
    );
  }
  if ($ur) {
    $groups['acting user relationships'] = array(
      'items callback' => 'activity_log_eg_acting_user_rels',
      'title' => t("The acting user's relationships"),
      'expose fields' => array('acting_uid'),
      'weight' => -75,
    );
    $groups['custom user relationships'] = array(
      'items callback' => 'activity_log_eg_custom_user_rels',
      'title' => t("A custom user's relationships"),
      'expose fields' => array('id'),
      'weight' => -70,
    );
    $ur_types = user_relationships_types_load();
    foreach ($ur_types as $type) {
      $groups['acting user relationships '. $type->rtid] = array(
        'items callback' => 'activity_log_eg_acting_user_rels_type',
        'title' => t("The acting user's %type relationships", array('%type' => $type->name)),
        'expose fields' => array('acting_uid'),
        'additional arguments' => array($type),
        'weight' => -65,
      );
      $groups['custom user relationships '. $type->rtid] = array(
        'items callback' => 'activity_log_eg_custom_user_rels_type',
        'title' => t("A custom user's %type relationships", array('%type' => $type->name)),
        'expose fields' => array('id'),
        'additional arguments' => array($type),
        'weight' => -60,
      );
    }
  }
  if ($og && $ur) {
    $groups['active group relationships acting user'] = array(
      'items callback' => 'activity_log_eg_active_group_rels_acting_user',
      'title' => t('Members of the active group who have a relationship with the acting user'),
      'expose fields' => array('acting_uid'),
      'weight' => -55,
    );
    $groups['active group relationships custom user'] = array(
      'items callback' => 'activity_log_eg_active_group_rels_custom_user',
      'title' => t('Members of the active group who have a relationship with a custom user'),
      'expose fields' => array('id'),
      'weight' => -50,
    );
    foreach ($ur_types as $type) {
      $groups['active group relationships '. $type->rtid .' acting user'] = array(
        'items callback' => 'activity_log_eg_active_group_rels_type_acting_user',
        'title' => t('Members of the active group who have a %type relationship with the acting user', array('%type' => $type->name)),
        'expose fields' => array('acting_uid'),
        'additional arguments' => array($type),
        'weight' => -45,
      );
      $groups['active group relationships '. $type->rtid .' custom user'] = array(
        'items callback' => 'activity_log_eg_active_group_rels_type_custom_user',
        'title' => t('Members of the active group who have a %type relationship with a custom user', array('%type' => $type->name)),
        'expose fields' => array('id'),
        'additional arguments' => array($type),
        'weight' => -40,
      );
    }
  }
  if ($co) {
    $groups['node commenters'] = array(
      'items callback' => 'activity_log_eg_node_commenters',
      'title' => t('Other people who have commented on this node (including the node author)'),
      'data types' => array('node'),
      'weight' => -35,
    );
  }
  if ($tx) {
    $groups['node terms'] = array(
      'items callback' => 'activity_log_eg_node_terms',
      'title' => t('The taxonomy terms used in the node to which the action occurred, if applicable'),
      'data types' => array('node'),
      'weight' => -30,
    );
  }
  if ($fc) {
    $groups['status commenters'] = array(
      'items callback' => 'activity_log_eg_status_commenters',
      'title' => t('Other people who have commented on this status (including the sender)'),
      'data types' => array('fbss_comment'),
      'weight' => -25,
    );
  }
  if ($ft) {
    $groups['mentioned users'] = array(
      'items callback' => 'activity_log_eg_mentioned_users',
      'title' => t('The users @mentioned in a status'),
      'data types' => array('facebook_status'),
      'weight' => -20,
    );
    $groups['hashtag terms'] = array(
      'items callback' => 'activity_log_eg_hashtag_terms',
      'title' => t('The taxonomy terms corresponding to the #hashtags in a status'),
      'data types' => array('facebook_status'),
      'weight' => -15,
    );
  }
  if ($fb) {
    $groups['status recipient'] = array(
      'items callback' => 'activity_log_eg_status_recipient',
      'title' => t('The recipient of the status message'),
      'data types' => array('facebook_status'),
      'additional arguments' => array($stream_owner),
      'weight' => -10,
    );
  }
  if (!$stream_owner) {
    unset($groups['active group'], $groups['hashtag terms'], $groups['node terms'], $groups['custom']['expose fields'][1]);
    $groups['target entity']['title'] = t('The user on which the action was performed, if applicable');
    $groups['everyone'] = array(
      'items callback' => 'activity_log_eg_everyone',
      'title' => t('Everyone'),
      'weight' => -105,
    );
    $groups['everyone_except_active'] = array(
      'items callback' => 'activity_log_eg_everyone_except_active',
      'title' => t('Everyone except the active user'),
      'expose fields' => array('acting_uid'),
      'weight' => -103,
    );
    $groups['everyone_except_custom'] = array(
      'items callback' => 'activity_log_eg_everyone_except_custom',
      'title' => t('Everyone except a custom user'),
      'expose fields' => array('id'),
      'weight' => -102,
    );
    $groups['stream_owner'] = array(
      'items callback' => 'activity_log_eg_stream_owner',
      'title' => t('The user in whose stream the activity will appear'),
      'weight' => -88,
    );
    $groups['not_stream_owner'] = array(
      'items callback' => 'activity_log_eg_not_stream_owner',
      'title' => t('Everyone except the user in whose stream the activity will appear'),
      'weight' => -87,
    );
  }
  return $groups;
}

/**
 * Returns the entity IDs for the Custom group.
 */
function activity_log_eg_custom($event, $settings, $id, $type = 'user') {
  if ($id) {
    if ($type == 'user' && module_exists('og') && $node = $event->og) {
      if ($node->og_private) {
        $members = _activity_log_get_active_group_members();
        if (!in_array($id, $members)) {
          return;
        }
      }
    }
    return array($type => array($id));
  }
}

/**
 * Returns the entity IDs for the Acting user group.
 */
function activity_log_eg_acting_user($event, $settings, $acting_uid) {
  if ($acting_uid) {
    return array('user' => array($acting_uid));
  }
}

/**
 * Returns the entity IDs for the Target entity group.
 */
function activity_log_eg_target_entity($event, $settings, $stream_owner) {
  if ((!$stream_owner || $event->target_type == 'user') && $event->target_id) {
    return array($event->target_type => array($event->target_id));
  }
}

/**
 * Returns the ID of the active group.
 */
function activity_log_eg_active_group($event, $settings) {
  if (module_exists('og') && $node = $event->og) {
    return array('node' => array($node->nid));
  }
}

/**
 * Returns the IDs of the active group's members.
 */
function activity_log_eg_active_group_members($event, $settings) {
  if (module_exists('og') && $members = _activity_log_get_active_group_members()) {
    return array('user' => $members);
  }
}

/**
 * Returns the IDs of the active group's administrators.
 * Does not include site administrators.
 */
function activity_log_eg_active_group_admin($event, $settings) {
  if (module_exists('og') && $members = _activity_log_get_active_group_members(TRUE)) {
    return array('user' => $members);
  }
}

/**
 * Returns the entity IDs for the Acting user's relationships group.
 */
function activity_log_eg_acting_user_rels($event, $settings, $acting_uid) {
  if (module_exists('user_relationships_api') && $acting_uid && $rels = _activity_log_get_user_relationships($acting_uid)) {
    if (module_exists('og') && $node = $event->og) {
      if ($node->og_private) {
        $members = _activity_log_get_active_group_members();
        $rels = array_intersect($rels, $members);
      }
    }
    if ($rels) {
      return array('user' => $rels);
    }
  }
}

/**
 * Returns the entity IDs for the Custom user's relationships group.
 */
function activity_log_eg_custom_user_rels($event, $settings, $id) {
  if (module_exists('user_relationships_api') && $id && $rels = _activity_log_get_user_relationships($id)) {
    if (module_exists('og') && $node = $event->og) {
      if ($node->og_private) {
        $members = _activity_log_get_active_group_members();
        $rels = array_intersect($rels, $members);
      }
    }
    if ($rels) {
      return array('user' => $rels);
    }
  }
}

/**
 * Returns the entity IDs for the Acting user's %type relationships group.
 */
function activity_log_eg_acting_user_rels_type($event, $settings, $acting_uid, $ur_type) {
  if (module_exists('user_relationships_api') && $acting_uid && $rels = _activity_log_get_user_relationships($acting_uid, $ur_type->rtid)) {
    if (module_exists('og') && $node = $event->og) {
      if ($node->og_private) {
        $members = _activity_log_get_active_group_members();
        $rels = array_intersect($rels, $members);
      }
    }
    if ($rels) {
      return array('user' => $rels);
    }
  }
}

/**
 * Returns the entity IDs for the Custom user's %type relationships group.
 */
function activity_log_eg_custom_user_rels_type($event, $settings, $id, $ur_type) {
  if (module_exists('user_relationships_api') && $id && $rels = _activity_log_get_user_relationships($id, $ur_type->rtid)) {
    if (module_exists('og') && $node = $event->og) {
      if ($node->og_private) {
        $members = _activity_log_get_active_group_members();
        $rels = array_intersect($rels, $members);
      }
    }
    if ($rels) {
      return array('user' => $rels);
    }
  }
}

/**
 * Returns the IDs of the members of the active group who have a relationship
 * with the acting user.
 */
function activity_log_eg_active_group_rels_acting_user($event, $settings, $acting_uid) {
  if (module_exists('user_relationships_api') && module_exists('og') && $acting_uid) {
    $members = _activity_log_get_active_group_members();
    $rels = _activity_log_get_user_relationships($acting_uid);
    if ($uids = array_intersect($members, $rels)) {
      return array('user' => $uids);
    }
  }
}

/**
 * Returns the IDs of the members of the active group who have a relationship
 * with a custom user.
 */
function activity_log_eg_active_group_rels_custom_user($event, $settings, $id) {
  if (module_exists('user_relationships_api') && module_exists('og') && $id) {
    $members = _activity_log_get_active_group_members();
    $rels = _activity_log_get_user_relationships($id);
    if ($uids = array_intersect($members, $rels)) {
      return array('user' => $uids);
    }
  }
}

/**
 * Returns the IDs of the members of the active group who have a %type
 * relationship with the acting user.
 */
function activity_log_eg_active_group_rels_type_acting_user($event, $settings, $acting_uid, $ur_type) {
  if (module_exists('user_relationships_api') && module_exists('og') && $acting_uid) {
    $members = _activity_log_get_active_group_members();
    $rels = _activity_log_get_user_relationships($acting_uid, $ur_type->rtid);
    if ($uids = array_intersect($members, $rels)) {
      return array('user' => $uids);
    }
  }
}

/**
 * Returns the IDs of the members of the active group who have a %type
 * relationship with a custom user.
 */
function activity_log_eg_active_group_rels_type_custom_user($event, $settings, $id, $ur_type) {
  if (module_exists('user_relationships_api') && module_exists('og') && $id) {
    $members = _activity_log_get_active_group_members();
    $rels = _activity_log_get_user_relationships($id, $ur_type->rtid);
    if ($uids = array_intersect($members, $rels)) {
      return array('user' => $uids);
    }
  }
}

/**
 * Returns the entity IDs for the Node commenters group.
 */
function activity_log_eg_node_commenters($event, $settings) {
  if ($event->target_type == 'node' && $event->target_id && module_exists('comment')) {
    $author = db_result(db_query("SELECT uid FROM {node} WHERE uid <> 0 AND nid = %d", $event->target_id));
    $uids = $author ? array($author) : array();
    $result = db_query("SELECT uid FROM {comments} WHERE uid <> 0 AND nid = %d", $event->target_id);
    while ($account = db_fetch_object($result)) {
      $uids[] = $account->uid;
    }
    if ($uids) {
      return array('user' => $uids);
    }
  }
}

/**
 * Returns the entity IDs for the Status commenters group.
 */
function activity_log_eg_status_commenters($event, $settings) {
  if ($event->target_type == 'facebook_status' && $event->target_id && module_exists('facebook_status')) {
    $status = db_fetch_object(db_query("SELECT sender FROM {facebook_status} WHERE sid = %d", $event->target_id));
    $uids = array($status->sender);
    $result = db_query("SELECT uid FROM {fbss_comments} WHERE uid <> 0 AND sid = %d", $event->target_id);
    while ($account = db_fetch_object($result)) {
      $uids[] = $account->uid;
    }
    if ($uids) {
      return array('user' => $uids);
    }
  }
}

/**
 * Returns the entity IDs for the Mentioned users group.
 */
function activity_log_eg_mentioned_users($event, $settings) {
  if ($event->target_type == 'facebook_status' && $event->target_id && module_exists('facebook_status_tags')) {
    $uids = array();
    $result = db_query("SELECT rid FROM {facebook_status_tags} WHERE type = 'user' AND sid = %d", $event->target_id);
    while ($account = db_fetch_object($result)) {
      $uids[] = $account->rid;
    }
    if ($uids) {
      return array('user' => $uids);
    }
  }
}

/**
 * Returns the entity IDs for the #Hashtags group.
 */
function activity_log_eg_hashtag_terms($event, $settings) {
  if ($event->target_type == 'facebook_status' && $event->target_id && module_exists('facebook_status_tags')) {
    $tids = array();
    $result = db_query("SELECT rid FROM {facebook_status_tags} WHERE type = 'term' AND sid = %d", $event->target_id);
    while ($term = db_fetch_object($result)) {
      $tids[] = $term->rid;
    }
    if ($tids) {
      return array('taxonomy_term' => $tids);
    }
  }
}

/**
 * Returns the entity ID for the status recipient.
 */
function activity_log_eg_status_recipient($event, $settings, $stream_owner) {
  if ($event->target_type == 'facebook_status' && $event->target_id && module_exists('facebook_status')) {
    $status = facebook_status_load($event->target_id);
    $type = $status->type;
    if (($type == 'user' || $stream_owner) && $status->recipient) {
      $type = ($type == 'og' ? 'node' : ($type == 'term' ? 'taxonomy_term' : $type));
      return array($type => array($status->recipient));
    }
  }
}

/**
 * Returns the entity IDs for the Node terms group.
 */
function activity_log_eg_node_terms($event, $settings) {
  if ($event->target_type == 'node' && $event->target_id && module_exists('taxonomy')) {
    $node = db_fetch_object(db_query("SELECT nid, vid FROM {node} WHERE nid = %d", $event->target_id));
    if ($tids = array_keys(taxonomy_node_get_terms($node))) {
      return array('taxonomy_term' => $tids);
    }
  }
}

/**
 * Returns the entity IDs for the Everyone group.
 */
function activity_log_eg_everyone($event, $settings) {
  if (module_exists('og') && $node = $event->og) {
    if ($node->og_private) {
      return array('user' => _activity_log_get_active_group_members());
    }
  }
  return array('user' => array(0));
}

/**
 * Returns the ID for the "everyone except the active user" group.
 */
function activity_log_eg_everyone_except_active($event, $settings, $acting_uid) {
  if ($acting_uid) {
    if (module_exists('og') && $node = $event->og) {
      if ($node->og_private && $uids = array_diff(_activity_log_get_active_group_members(), array($acting_uid))) {
        return array('user' => $uids);
      }
    }
    return array('user' => array(-$acting_uid));
  }
}

/**
 * Returns the ID for the "everyone except a custom user" group.
 */
function activity_log_eg_everyone_except_custom($event, $settings, $id) {
  if ($id) {
    if (module_exists('og') && $node = $event->og) {
      if ($node->og_private && $uids = array_diff(_activity_log_get_active_group_members(), array($id))) {
        return array('user' => $uids);
      }
    }
    return array('user' => array(-$id));
  }
}

/**
 * The stream owner.
 */
function activity_log_eg_stream_owner($event, $settings) {
  return array('user' => array('stream owner'));
}

/**
 * Everyone except the stream owner.
 */
function activity_log_eg_not_stream_owner($event, $settings) {
  return array('user' => array('not stream owner'));
}

/**
 * Gets an array of UIDs of members of the currently active group.
 *
 * @param $admin
 *   If TRUE, returns group administrators. Otherwise, returns all members.
 */
function _activity_log_get_active_group_members($admin = FALSE) {
  $node = $event->og;
  if (empty($node)) {
    return array();
  }
  $query = "SELECT uid FROM {og_uid} WHERE is_active = 1 AND nid = %d";
  if ($admin) {
    $query .= " AND is_admin = 1";
  }
  $result = db_query($query, $node->nid);
  $uids = array();
  while ($account = db_fetch_object($result)) {
    $uids[] = $account->uid;
  }
  return $uids;
}

/**
 * Gets an array of UIDs of a given user's relationships.
 *
 * @param $uid
 *   The user ID of the user whose relationships should be retrieved.
 * @param $rtid
 *   If specified, the relationship type ID of the relationships that should be
 *   retrieved. Otherwise, all relationships of all types are retrieved.
 * @return
 *   An array of UIDs of the given user's relationships.
 */
function _activity_log_get_user_relationships($uid, $rtid = 0) {
  $query = "
    SELECT ur.requester_id, ur.requestee_id, urt.is_oneway
    FROM user_relationships ur
    INNER JOIN user_relationship_types urt
      ON ur.rtid = urt.rtid
    WHERE (ur.requester_id = %d OR ur.requestee_id = %d) AND (ur.approved = 1 OR urt.is_oneway = 0)
  ";
  $args = array($uid, $uid);
  if ($rtid) {
    $query .= " AND ur.rtid = %d";
    $args[] = $rtid;
  }
  $uids = array();
  while ($rel = db_fetch_object($result)) {
    if ($rel->is_oneway) {
      if ($rel->requester_id != $uid) {
        $uids[] = $rel->requester_id;
      }
    }
    else {
      $uids[] = ($rel->requester_id == $uid) ? $rel->requestee_id : $rel->requester_id;
    }
  }
  return $uids;
}
