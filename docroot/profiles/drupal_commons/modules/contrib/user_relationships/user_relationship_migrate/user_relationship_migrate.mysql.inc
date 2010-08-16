<?php
// $Id: user_relationship_migrate.mysql.inc,v 1.1.2.1 2009/06/22 12:36:05 alexk Exp $
/**
 * @file MySQL implementation of Buddylist2->UR migration
 */

/**
 * Migrate pending relationships.
 */
function user_relationship_migrate_pending($rtid) {
  db_query('LOCK TABLE {user_relationships} WRITE, {buddylist_pending_requests} READ');
  db_query(
    "INSERT INTO {user_relationships} (requester_id, requestee_id, rtid, approved, created_at)
     SELECT requester_uid, requestee_uid, %d, 0, %d FROM {buddylist_pending_requests}",
     $rtid, time()
  );
  db_query('UNLOCK TABLES');

  return TRUE;
}


/**
 * Helper function to run the actual transactions.
 */
function _user_relationship_migrate_run($rtid) {
  $rtype = user_relationships_type_load(array('rtid' => $rtid));
  if (!$rtype->rtid) {
    return FALSE;
  }
  $start_time = time();

  if ($rtype->is_oneway) {
    //migrate one-way relationships as is, rid will autoincrement
    db_query(
      "INSERT INTO {user_relationships} (rtid, requester_id, requestee_id, created_at, updated_at, approved) 
       SELECT %d, uid, buddy, timestamp, %d, 1 
       FROM {buddylist}",
      $rtid, time()
    );
  }
  else {
    //for two-way relationship, use IF and IGNORE so that only one direction is imported
    db_query(
      "INSERT IGNORE INTO {user_relationships} (rtid, requester_id, requestee_id, created_at, updated_at, approved) 
       SELECT %d, IF( uid > buddy, uid, buddy ) AS uid, IF( uid < buddy, uid, buddy ) AS buddy, timestamp, %d, 1 
       FROM {buddylist}",
      $rtid, time()
    );
    //then, fill in the other direction keeping the same rid. The SELECT below picks two-way relationships which do not
    //have a record going in the opposite direction.
    db_query(
      'INSERT INTO {user_relationships} (rid, rtid, requester_id, requestee_id, created_at, updated_at, approved) 
        SELECT ur1.rid, ur1.rtid, ur1.requestee_id, ur1.requester_id, ur1.created_at, ur1.updated_at, ur1.approved
        FROM {user_relationships} ur1 LEFT JOIN {user_relationships} ur2 ON ur1.rid = ur2.rid AND ur1.requester_id = ur2.requestee_id 
        WHERE ur1.rtid = %d AND ur2.rid is null and ur1.updated_at >= %d', $rtid, $start_time
    );
  }

  return TRUE;
}
