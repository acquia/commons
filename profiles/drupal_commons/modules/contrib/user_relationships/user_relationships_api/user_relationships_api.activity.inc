<?php
// $Id: user_relationships_api.activity.inc,v 1.1.2.2 2010/01/03 23:03:54 alexk Exp $

/**
 * @file:
 * provides the activity implementation for user_relationships_api module
 */

/**
 * Implementation of hook_activity_grants().
 */
function user_relationships_api_activity_grants($activity) {
  $relationships = array();
  foreach (user_relationships_types_load() as $type_obj) {
    $relationships["user_relationships_" . $type_obj->rtid] = array($activity->uid);
  }
  return $relationships;
}

/**
 * hook_activity_access_grants().
 */
function user_relationships_api_activity_access_grants($account, $object = NULL, $type = NULL) {
  // load up all the users relationships
  $params = array(
    'user' => $account->uid
  );
  $relationships = user_relationships_load($params);

  $relationship_ids = array();
  foreach ($relationships as $rid => $relationship) {
    // is this approved yet?
    $relationship_approved = (!$relationship->requires_approval || $relationship->approved);

    if ($relationship_approved) {
      // if the relationship is not one way, grant to the other uid
      if (!$relationship->is_oneway) {
        if ($relationship->requester_id == $account->uid) {
          $relationship_ids["user_relationships_" . $relationship->rtid][] = $relationship->requestee_id;
        }
        else {
          $relationship_ids["user_relationships_" . $relationship->rtid][] = $relationship->requester_id;
        }
      }
      // if the relationship is one way, grant only if $account->uid == requester_id
      elseif ($relationship->is_oneway) {
        if ($relationship->requester_id == $account->uid) {
          $relationship_ids["user_relationships_" . $relationship->rtid][] = $relationship->requestee_id;
        }
      }
    }
  }
  return $relationship_ids;
}

