<?php
// $Id: user_relationship_service.inc,v 1.1.2.1 2009/07/06 10:24:44 alexk Exp $
/**
 * @author Drupal 6 port by Darren Ferguson <http://drupal.org/user/70179>
 * @author Written by scottgifford http://drupal.org/user/245699
 * @file Link general user relationship functionalities to services module.
 */
// Loading the API functions if not already loaded
module_load_include('inc', 'user_relationships_api', 'user_relationships.api');


function user_relationship_service_types($version) {
  return user_relationships_types_load();
}

function user_relationship_service_mine($version) {
  try {
    global $user;
    $param = array('user' => $user->uid);
    $rels = user_relationships_load($param);
    if (!$rels || !is_array($rels)) {
      throw new Exception("User relationship load failed");
    }
    return array_values($rels);
  } catch (Exception $ex) {
    return services_error(t('Error getting user relationships: @msg', array('@msg' => $ex->getMessage())));
  }
}

function user_relationship_service_approve($version, $rid) {
  try {
    global $user;
    $rels = user_relationships_load(array('rid' => $rid , 'requestee_id' => $user->uid, 'approved' => 0));
    if (!$rels || !is_array($rels) || count($rels) != 1) {
      throw new Exception("User relationship load failed");
    }
    $rel = array_shift($rels);
    if ($rel->requestee_id != $user->uid) {
      throw new Exception("Access denied");
    }
    $updated = $rel;
    $updated->approved = TRUE;
    user_relationships_update_relationship($rel, $updated, 'approved');
    return $rel;
  } catch (Exception $ex) {
    return services_error(t('Error approving relationship: @msg', array('@msg' => $ex->getMessage())));
  }
}

function user_relationship_service_delete($version, $rid, $reason) {
  try {
    global $user;
    $rels = user_relationships_load(array('rid' => $rid , 'user' => $user->uid));
    if (!$rels || !is_array($rels) || count($rels) != 1) {
      throw new Exception("User relationship load failed");
    }
    $rel = array_shift($rels);
    if ($rel->requestee_id != $user->uid && $rel->requester_id != $user->uid) {
      throw new Exception("Access denied");
    }
    user_relationships_delete_relationship($rel, $user, $reason);
    return $rel;
  } catch (Exception $ex) {
    return services_error(t('Error removing relationship: @msg', array('@msg' => $ex->getMessage())));
  }
}

function user_relationship_service_request($version, $uid, $type_name) {
  try {
    $type = user_relationships_type_load(array('name' => $type_name));
    error_log("Relationship request with '$uid' type '$type_name'");
    if (!$type) {
      throw new Exception(t('No such relationship type'));
    }

    global $user;
    $ret = user_relationships_request_relationship($user, $uid, $type);
    if (!$ret) {
      throw new Exception(t('Unknown failure'));
    }
    else if (!is_object($ret)) {
      throw new Exception($ret);
    }
    return $ret;
  } catch (Exception $ex) {
    return services_error(t('Error requesting relationship: @msg', array('@msg' => $ex->getMessage())));
  }
}