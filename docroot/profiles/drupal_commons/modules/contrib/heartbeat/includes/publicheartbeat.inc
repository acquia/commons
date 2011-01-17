<?php
// $Id: publicheartbeat.inc,v 1.1.2.2.2.12 2010/12/13 18:38:09 stalski Exp $

/**
 * @file
 *   Public heartbeat activity access object
 */

heartbeat_include('HeartbeatAccess');

/**
 * Class PublicHeartbeat
 * Concrete class to prepare messages for all
 * users in the site of whom the heartbeat is
 * set to public
 *
 */
class PublicHeartbeat extends HeartbeatAccess {

  /**
   * Skip active user.
   * We never want to skip the active user. not for
   * logged-in user and not for displayed user (profile).
   * This is ofcourse because private stream is intended to
   * show own activity.
   */
  public function skipActiveUser() {
    return FALSE;
  }

  /**
   * Implementation of dressUpMessages().
   *
   * @param object HeartbeatParser $heartbeat
   *   The heartbeat parser object
   * @return object HeartbeatParser $heartbeat
   */
  public function dressUpMessages(HeartbeatParser $heartbeat) {

    $sql = " AND ua.access > 0 ";
    $heartbeat->raw_messages = $this->resultSql($sql);

    return $heartbeat;
  }

  /**
   * Function to add a part of a sql to a query built by views.
   * @param object $view
   *   The view handler object by reference to add our part to the query
   */
  public function addViewQuery(&$view) {

    // Make the sql limited to the access
    $view->query->add_where('andgroup', "$view->table_alias.access > 0");
  }
}