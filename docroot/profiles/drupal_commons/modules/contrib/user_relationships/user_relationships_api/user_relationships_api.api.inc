<?php
// $Id: user_relationships_api.api.inc,v 1.1.2.18 2010/05/13 19:15:57 alexk Exp $

/**
 * @file
 * User Relationships API. Data abstraction layer
 * @author Jeff Smick (creator)
 * @author Alex Karshakevich (maintainer) http://drupal.org/user/183217
 */

/**
 * Public API for retrieving a specific relationship
 *
 * @param $param
 *    The rtid or an associative array of attributes to search for in selecting the
 *    relationship, such as rtid or name. Attributes must match column names
 *    in the user_relationship_types table.
 *
 * @param $reset
 *    a boolean that forces a reset of the internal static types list
 *
 * @return
 *    object of the requested relationship type
 *
 */
function user_relationships_type_load($param = array(), $reset = NULL) {
  $types = user_relationships_types_load($reset);

  if (is_numeric($param)) {
    return $types[$param];
  }

  foreach ($types as $type) {
    $found = TRUE;

    foreach ($param as $column => $value) {
      $column = strtolower($column);

      if ($column == 'name' || $column == 'plural_name') {
        $value = strtolower($value);
        $col_val = strtolower($type->$column);
      }
      else {
        $col_val = $type->$column;
      }

      // mismatch, move to the next type
      if ($col_val != $value) {
        $found = FALSE;
        break;
      }
    }

    if ($found) {
      return $type;
    }
  }
}


/**
 * Public API for loading the full list of relationship types
 *
 * @param $reset
 *    a boolean that forces a reset of the internal static types list
 *
 * @return
 *    array of relationship_type objects
 */
function user_relationships_types_load($reset = NULL) {
  static $relationship_types_list = array();

  if ($reset || empty($relationship_types_list)) {
    //clear the cached list, since some relationships may have disappeared
    $relationship_types_list = array();
    $results = db_query("SELECT * FROM {user_relationship_types}");
    while ($relationship = db_fetch_object($results)) {
      $relationship_types_list[$relationship->rtid] = $relationship;
    }
    //load role permissions for all types
    $results = db_query('SELECT rtid, rid FROM {user_relationship_type_roles} ORDER BY rtid, rid');
    while ($mapping = db_fetch_object($results)) {
      $rtype = $relationship_types_list[$mapping->rtid];
      // //roles is an associative array {role id} => {role id}
      $rtype->roles[$mapping->rid] = $mapping->rid;//] = $mapping->name;
    }
    
    //load role receive permissions for all types
    $results = db_query('SELECT rtid, rid FROM {user_relationship_type_roles_receive} ORDER BY rtid, rid');
    while ($mapping = db_fetch_object($results)) {
      $rtype = $relationship_types_list[$mapping->rtid];
      // //roles is an associative array {role id} => {role id}
      $rtype->roles_receive[$mapping->rid] = $mapping->rid;//] = $mapping->name;
    }
  }

  _user_relationships_invoke('load', $relationship_types_list, TRUE);

  return $relationship_types_list;
}


/**
 * Create or Update a User Relationship Type
 *
 * @param $rtype
 *   A User Relationship type object
 */
function user_relationships_type_save(&$rtype) {
  _user_relationships_invoke('presave', $rtype, TRUE);

  $op = (isset($rtype->rtid) && $rtype->rtid) ? 'update' : 'insert';

  // find a relationship type with the name we're trying to save
  // if it's an update action check to see that the rtypes match
  // otherwise it's just invalid
  if (
    ($found_rt = user_relationships_type_load(array('name' => $rtype->name))) &&
    ($op == 'update' ? $found_rt->rtid != $rtype->rtid : TRUE)
  ) {
    return FALSE;
  }

  // ensure "expires_val" is numeric and not negative
  if (!is_numeric($rtype->expires_val) || $rtype->expires_val < 0) {
    $rtype->expires_val = 0;
  }

  drupal_write_record('user_relationship_types', $rtype, ($op == 'update' ? 'rtid' : NULL));

  _user_relationships_invoke($op, $rtype, TRUE);
}


/**
 * Delete a User Relationship Type
 *
 * @param $rtid
 *   A User Relationship type ID
 */
function user_relationships_type_delete($rtid) {
  $rtype = user_relationships_type_load($rtid);

  db_query('DELETE FROM {user_relationship_types} WHERE rtid = %d', $rtid);
  db_query('DELETE FROM {user_relationships} WHERE rtid = %d', $rtid);

  _user_relationships_invoke('delete', $rtype, TRUE);
}


/**
 * Request a new user relationship
 *
 * @param $requester
 *   object or UID of the requester
 * @param $requestee
 *   object  or UID of the requestee
 * @param $type
 *   object or RTID of the relationship type
 * @param $approved
 *    boolean status of the relationship
 *
 * @return
 *    object of the newly created relationship
 */
function user_relationships_request_relationship($requester, $requestee = NULL, $type = NULL, $approved = FALSE) {
  //#578372 check if this is a "new" type of invocation, where first argument is a relationship object
  if (is_object($requester) && isset($requester->requester) && isset($requester->requestee) && isset($requester->type)) {
    $relationship = $requester;
    $requester = $relationship->requester;
    $requestee = $relationship->requestee;
    $type = $relationship->type;
    if (isset($relationship->approved)) {
      $approved = $relationship->approved;
    }
  }
  else {
    $relationship = new stdClass;
  }
  // translate an ID into an object
  foreach (array('requester' => $requester, 'requestee' => $requestee, 'type' => $type) as $key => $value) {
    if (!is_object($value)) {
      $$key = $key == 'type' ? user_relationships_type_load($value) : user_load($value);
    }
  }

  //check requester is allowed to create this rtype
  if (!user_relationships_api_can_request($requester, $type)) {
    watchdog('user_relationships_api', 'User %user has no suitable roles to request a %rtype relationship', array('%user' => $requester->name, '%rtype' => $type->name), WATCHDOG_WARNING);
    //it would be good to return a reason why save is denied, but it's the API portion, it does not expose anything user-visible
    return FALSE;
  }
  
  //check requestee is allowed to receive this rtype
  if (!user_relationships_api_can_receive($requestee, $type)) {
    watchdog('user_relationships_api', 'User %user has no suitable roles to receive a %rtype relationship', array('%user' => $requestee->name, '%rtype' => $type->name), WATCHDOG_WARNING);
    //it would be good to return a reason why save is denied, but it's the API portion, it does not expose anything user-visible
    return FALSE;
  }

  // check whether this relationship aleady exists
  if (!$type->is_oneway || !$type->is_reciprocal) {
    $existing = user_relationships_load(array('between' => array($requester->uid, $requestee->uid), 'rtid' => $type->rtid), array('count' => TRUE));
  }
  else {
    $existing = user_relationships_load(array('requester_id' => $requester->uid, 'requestee_id' => $requestee->uid, 'rtid' => $type->rtid), array('count' => TRUE));
  }
  
  if (!$existing) {
    $relationship->requester_id = $requester->uid;
    $relationship->requestee_id = $requestee->uid;
    $relationship->approved = $approved || !$type->requires_approval || (isset($requestee->user_relationships_ui_auto_approve) && $requestee->user_relationships_ui_auto_approve[$type->rtid]);
    $relationship->rtid = $type->rtid;

    return user_relationships_save_relationship($relationship);
  }
}


/**
 * Create or update a user relationship.
 *
 * @param $relationship
 *   object of the current relationship
 * @param $op
 *   the reason for the update
 *
 * @return
 *    object of the updated relationship
 *    or
 *    false if the relationship wasn't able to save
 */
function user_relationships_save_relationship(&$relationship, $op = 'request') {
  //set basic info if it doesn't already exist
  !isset($relationship->flags) ? $relationship->flags = UR_OK : NULL;
  !isset($relationship->created_at) ? $relationship->created_at = time() : NULL;
  $relationship->updated_at = time();
  
  if ($op == 'approve') {
    $relationship->approved = 1;
  }
  
  _user_relationships_invoke('presave', $relationship);

  if (isset($relationship->rid)) {
    // Delete possible requests coming the other direction
    $relationship_type = user_relationships_type_load($relationship->rtid);
    if (!$relationship_type->is_oneway) {
      db_query(
        'DELETE FROM {user_relationships} WHERE rtid = %d AND requester_id = %d AND requestee_id = %d',
        $relationship->rtid, $relationship->requestee_id, $relationship->requester_id
      );
    }
  }

  //#454680 make sure that an update is performed if this is an existing relationship
  if ($valid = drupal_write_record('user_relationships', $relationship, (isset($relationship->rid) ? array('rid') : array()))) {
    // if the relationship has been approved and is two-way we need
    // to do a double entry for DB efficiency
    $relationship_type = user_relationships_type_load($relationship->rtid);
    if ($relationship->approved && !$relationship_type->is_oneway) {
      //#365623 drupal_write_record will not work because rid is a serial field, and we need to use the same rid
      $valid = db_query('INSERT INTO {user_relationships} (rid, requester_id, requestee_id, rtid, approved, created_at, updated_at, flags) SELECT rid, requestee_id, requester_id, rtid, approved, created_at, updated_at, flags from {user_relationships} where rid = %d', $relationship->rid);
    }

    // second entry didn't go well. revert the first
    if (!$valid) {
      db_query('DELETE FROM {user_relationships} WHERE rid = %d', $relationship->rid);
      unset($relationship->rid);
    }
  }

  if ($valid) {
    _user_relationships_invoke($op, $relationship);
    return $relationship;
  }
}


/**
 * Public API for deleting a relationship.
 *
 * @param $relationship
 *    object of the relationship
 * @param $deleted_by
 *    object of the user that initiated the delete command
 * @param $op
 *    string reason for removal ('cancel','disapprove','remove')
 */
function user_relationships_delete_relationship(&$relationship, &$deleted_by, $op = 'remove') {
  $relationship->deleted_by = $deleted_by;
  db_query("DELETE FROM {user_relationships} WHERE rid = %d", $relationship->rid);

  _user_relationships_invoke($op, $relationship);
}


/**
  * Load relationship objects from the database.
  *
  * @param $param
  *   an array of parameters with the key being the column. columns from both the user_relationships and user_relationship_types tables will work
  *     columns from user_relationships: rid, requester_id, requestee_id, rtid, approved, created_at, updated_at, flags
  *     columns from user_relationship_types: name, plural_name, is_oneway, requires_approval, expires_val
  *   There are two special keys:
  *     1) array("between" => array($uid1, $uid2)) will return all relationships between the two user ids.
  *     2) array("user" => $uid) will return all relationships for the specified uid
  *
  *   arguments will process operators as well using the syntax: array(col => '> {value}').
  *     example: show all relationships created in 2007
  *       $start_time = mktime(0,0,0,0,0,2007);
  *       $end_time = mktime(0,0,0,0,0,2008);
  *       user_relationships_load(array('created_at' => ">= {$start_time}", 'created_at' => '< {$end_time'}));
  * 
  *   each parameter may be an array, if you wish to pass several values
  *     example: user_relationships_load(array('rtid' => array(2, 3), 'between' => array($uid1, $uid2)))
  *       will load all relationships of types 2 or 3 between uid1 and uid2 (query will have an IN clause)
  *
  * @param @options
  *   An array keyed by the option
  *   count
  *     a boolean stating whether or not the return value should be the number of relationships found
  *
  *   sort
  *     a string containing a valid column name which will become the key for the returned array of relationships
  *     default is 'rid'
  *
  *   order
  *     a string containing SQL stating the column and direction of the sort (ex. "requester_id ASC, rtid DESC")
  *
  *   limit
  *     a string containing SQL stating the limit (ex "10" or "10, 5")
  *
  *   include_user_info
  *     a boolean that will load basic user info without having to call user_load
  *     columns: uid, name, mail, data, picture
  *     
  *   include_twoway_reverse (not used unless there is a specific need)
  *     a boolean that, if present, and if sort is set to other than 'rid', will include records for both directions for
  *     two-way relationships. Normally for a two-way relationship only one entry is returned, although in the database there
  *     are two records. This flag has no effect if sort is 'rid'
  *
  * @param $reset
  *   a boolean that will reset the internal static $relationships variable to ensure programatic relationship insertion works
  *
  * @return
  *   an array of relationships
  *   if the key is "rid" the array will be a single dimention: array($rid => $relationship, $rid => $relationship)
  *   otherwise it'll be multidimentional: array($rtid => array($relationship, $relationship))
  *
  *   each relationship will have the user's name, mail, and data attached as requester_name, requester_mail, requester_data
  *   or requestee_name, requestee_mail, requestee_data
 */
function user_relationships_load($param = array(), $options = array(), $reset = FALSE) {
  static $relationships = array();

  $default_options = array(
    'sort' => 'rid',
  );
  $options = array_merge($default_options, $options);
  extract($options, EXTR_SKIP);

  $arguments = array();
  if (is_numeric($param)) {
    if (!$reset && isset($relationships[$param])) {
      return is_object($relationships[$param]) ? drupal_clone($relationships[$param]) : $relationships[$param];
    }
    $rid = $param;
    $param = array('rid' => $param);
  }

  $query = _user_relationships_generate_query($param, $options);

  $results = db_query($query[(isset($count) && $count ? 'count' : 'query')], $query['arguments']);

  if (isset($count) && $count) {
    return (int)db_result($results);
  }

  $relationships = array();
  while ($relationship = db_fetch_object($results)) {
    if (isset($include_user_info)) {
      user_relationships_api_translate_user_info($relationship);
    }

    if ($sort == 'rid') {
      $relationships[$relationship->$sort] = $relationship;
    }
    else {
      $relationships[$relationship->$sort][] = $relationship;
    }
  }

  $return = isset($rid) ? $relationships[$rid] : $relationships;
  _user_relationships_invoke('load', $return);

  return $return;
}


/**
 * Used when the "include_user_info" option is set on user_relationships_load
 * to translate the retrieved user fields into actual user objects. This allows us
 * to pull the basic user data without having to run user_load
 *
 * @param $relationship
 *    The relationship object with pulled user info
 */
function user_relationships_api_translate_user_info(&$relationship) {
  if ($relationship->requester_name) {
    foreach (array('requester', 'requestee') as $user_type) {
      $relationship->{$user_type} = new stdClass();
      foreach (array('name', 'mail', 'data', 'picture') as $field) {
        $db_field = "{$user_type}_{$field}";
        $relationship->{$user_type}->{$field} = $relationship->{$db_field};

        unset($relationship->{$db_field});
      }
      $user_type_id = "{$user_type}_id";
      $relationship->{$user_type}->uid = $relationship->{$user_type_id};
      $relationship->{$user_type}->data = unserialize($relationship->{$user_type}->data);
    }
  }
}

/**
 * Check whether a user is allowed to request a certain relationship type
 *
 * @param $requester requesting user object or uid
 * @param $relationship_type loaded relationship type object or rtid
 * @return TRUE iff requester is allowed to request this type of relationship
 */
function user_relationships_api_can_request($requester, $relationship_type) {
  //validate arguments
  if (is_numeric($requester)) {
    $requester = user_load($requester);
  }
  if (is_numeric($relationship_type)) {
    $relationship_type = user_relationships_type_load($relationship_type);
  }
  if (!is_object($requester) || !is_object($relationship_type)) {
    return FALSE;
  }
  if ($requester->uid == 1) {
    return TRUE;
  }
  //if no roles have been set, any user can request
  if (!isset($relationship_type->roles) || !count($relationship_type->roles)) {
    return TRUE;
  }
  //check user has at least one required role
  foreach ($relationship_type->roles as $role_id) {
    if ($requester->roles[$role_id]) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Check whether a user is allowed to receive a certain relationship type
 *
 * @param $requestee requesting user object or uid
 * @param $relationship_type loaded relationship type object or rtid
 * @return TRUE iff receiver is allowed to request this type of relationship
 */
function user_relationships_api_can_receive($requestee, $relationship_type) {
  //validate arguments
  if (is_numeric($relationship_type)) {
    $relationship_type = user_relationships_type_load($relationship_type);
  }
  if (is_numeric($requestee)) {
    $requestee = user_load($requestee);
  }
  if (!is_object($requestee) || !is_object($relationship_type)) {
    return FALSE;
  }
  //if no roles have been set to receive the relationship, any user can receive it
  if (!isset($relationship_type->roles_receive) || !count($relationship_type->roles_receive)) {
    return TRUE;
  }
  //check user has at least one required role
  foreach ($relationship_type->roles_receive as $role_id) {
    if ($requestee->roles[$role_id]) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Implements the hook_cck_field_privacy_access to allow users to display privacy fields
 * based on a relationship with other users
 */
function user_relationships_api_cck_field_privacy_access($requestee, $requester) {
  $relationship = user_relationships_load(array('between' => array($requestee->uid, $requester->uid), 'approved' => TRUE), array('count' => TRUE), FALSE);
  return $relationship;
}
