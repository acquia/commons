<?php
// $Id: user_relationships_api.socnet.inc,v 1.1.2.3 2009/11/07 19:30:07 alexk Exp $

/**
 * @file
 * User Relationships implementation of http://drupal.org/project/drupal_universal_relation_api
 * @author Alex Karshakevich http://drupal.org/user/183217
 */

/**
 * return an array of module names that implement these hooks. e.g. array('friendlist', 'user_relationships_api')
 */
function user_relationships_api_socnet_get_implementations() {
  return 'user_relationships_api';
}

/**
 * Returns TRUE if uid1 has a confirmed relationship with uid2, optionally filter by relationship name and style
 * @param $relation_name optional name of relationship to restrict search to 
 * @param $relation_style optional, one of {'all', 'one-way', 'two-way'}
 * @return TRUE if the relationship exists, or nothing if it does not.
 */
function user_relationships_api_socnet_is_related($uid1 = NULL, $uid2 = NULL, $relation_name = NULL, $relation_style='all') {
  $args = array('requester_id' => $uid1, 'requestee_id' => $uid2, 'approved' => 1);
  //optinally filter on relationship name
  if ($relation_name) {
    $args['name'] = $relation_name;
  }
  //or, filter on relationship directionality
  if ($relation_style == 'one-way') {
    $args['is_oneway'] = TRUE;
  }
  elseif ($relation_style == 'two-way') {
    $args['is_oneway'] = FALSE;
  }
  $count = user_relationships_load($args, array('count' => TRUE));
  if ($count > 0) {
    return TRUE;
  }
  //else return nothing
}

/**
 * true if user1 has requested a relationship to uid2, optionally set which relation and style to query
 */
function user_relationships_api_socnet_is_pending($uid1 = NULL, $uid2 = NULL, $relation_name = NULL, $relation_style='all') {
  $args = array('requester_id' => $uid1, 'requestee_id' => $uid2, 'approved' => 0);
  //optinally filter on relationship name
  if ($relation_name) {
    $args['name'] = $relation_name;
  }
  //or, filter on relationship directionality
  if ($relation_style == 'one-way') {
    $args['is_oneway'] = TRUE;
  }
  elseif ($relation_style == 'two-way') {
    $args['is_oneway'] = FALSE;
  }
  $count = user_relationships_load($args, array('count' => TRUE));
  if ($count > 0) {
    return TRUE;
  }
  //else return nothing
}

/**
 * true if user1 does not want to see uid2
 */
function user_relationships_api_socnet_is_blocked($blocked_by_uid = NULL, $blocked_uid = NULL, $relation_name = NULL, $relation_style='all') {
  //UR does not implement it
}

/**
 * return a list of uids of established relationships of $uid, optionally filter by relationship name
 */
function user_relationships_api_socnet_get_related_users($uid = NULL, $relation_name = NULL, $relation_style='all') {
  $args = array('requester_id' => $uid, 'approved' => 1);
  //optinally filter on relationship name
  if ($relation_name) {
    $args['name'] = $relation_name;
  }
  //or, filter on relationship directionality
  if ($relation_style == 'one-way') {
    $args['is_oneway'] = TRUE;
  }
  elseif ($relation_style == 'two-way') {
    $args['is_oneway'] = FALSE;
  }
  $result = user_relationships_load($args, array('sort' => 'requestee_id'));
  if ($result > 0) {
    return array_keys($result);
  }
  //else return nothing
}

/**
 * return a list of uid of all, to whom uid has sent requests, optionally filter by relationship name
 */
function user_relationships_api_socnet_all_pending_from($uid = NULL, $relation_name = NULL, $relation_style='all') {
  $args = array('requester_id' => $uid, 'approved' => 0);
  //optinally filter on relationship name
  if ($relation_name) {
    $args['name'] = $relation_name;
  }
  //or, filter on relationship directionality
  if ($relation_style == 'one-way') {
    $args['is_oneway'] = TRUE;
  }
  elseif ($relation_style == 'two-way') {
    $args['is_oneway'] = FALSE;
  }
  $result = user_relationships_load($args, array('sort' => 'requestee_id'));
  if ($result > 0) {
    return array_keys($result);
  }
  //else return nothing
}

/**
 * return a list of uid of users who want to relate to $uid, optionally filter by relationship name
 */
function user_relationships_api_socnet_all_pending_to($uid = NULL, $relation_name = NULL, $relation_style='all') {
  $args = array('requestee_id' => $uid, 'approved' => 0);
  //optinally filter on relationship name
  if ($relation_name) {
    $args['name'] = $relation_name;
  }
  //or, filter on relationship directionality
  if ($relation_style == 'one-way') {
    $args['is_oneway'] = TRUE;
  }
  elseif ($relation_style == 'two-way') {
    $args['is_oneway'] = FALSE;
  }
  $result = user_relationships_load($args, array('sort' => 'requester_id'));
  if ($result > 0) {
    return array_keys($result);
  }
  //else return nothing
}

/**
 * return a list of all relationship names to use in other functions
 */
function user_relationships_api_socnet_get_relation_names($relation_style='all') {
  $rtypes = user_relationships_types_load();
  $result = array();
  foreach ($rtypes as $type) {
    if (($type->is_oneway && $relation_style == 'one-way') ||
        (!$type->is_oneway && $relation_style == 'two-way') ||
        $relation_style == 'all') {
      $result[] = $type->name;
    }
  }
  if (count($result)) {
    return $result;
  }
}

/**
 * return 'two-way' or 'one-way' depending on the relation type
 */
function user_relationships_api_socnet_relation_type($relation_name = NULL) {
  $type = user_relationships_type_load(array('name' => $relation_name));
  if (isset($type->is_oneway)) {
    return $type->is_oneway ? 'one-way' : 'two-way';
  }
}