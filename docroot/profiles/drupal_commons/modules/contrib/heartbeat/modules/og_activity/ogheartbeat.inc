<?php
// $Id: ogheartbeat.inc,v 1.1.2.10 2010/12/13 23:03:32 stalski Exp $

/**
 * @file
 *   HeartbeatAccess stream object for organic group activity
 */


heartbeat_include('HeartbeatAccess');

/**
 * Class OgHeartbeat
 * Concrete class to prepare messages for the current user
 * and all of his/her relations.
 *
 */
class OgHeartbeat extends HeartbeatAccess {

  protected $_gid = 0;
  protected $_group_access = FALSE;
  protected $group = NULL;

  public function construct() {

    // Where the user id is a member of the group
    // and where the nid target is the group nid
    $this->setGroup();

  }

  /**
   * Skip active user.
   * We never want to skip the active user.
   */
  public function skipActiveUser() {
    return FALSE;
  }

  /**
   * hasAccess
   *
   * Checks access for this stream.
   */
  protected function hasAccess() {

    // if the user has access to this node (member or public group)
    //og_set_group_context($this->group);
    if (isset($this->group) && (og_is_group_member($this->group) || $this->group->og_private == 0)) {
      $this->_group_access = TRUE;
    }

    if (!isset($this->group)) {
      $this->setError('We are not in a group context.');
    }

    return $this->_group_access;
  }

  /**
   * setGroup
   *
   * Sets the group for a given node ID.
   * @param Integer $nid
   *   The group node ID.
   */
  private function setGroup($nid = 0) {

    if ($nid != 0) {
      $this->_gid = $nid;
      $this->group = node_load($nid);
      return;
    }
    if(module_exists('spaces_og')) {
      if($space = spaces_get_space()) {
        if($space->type == 'og') {
          $this->_gid = $space->id;
          $this->group = $space->group;
          return;
        }
      }
    }
    if (arg(0) == 'node' && is_numeric(arg(1))) {

      $node = node_load(arg(1));

      if (og_is_group_type($node->type)) {
        $this->_gid = arg(1);
        $this->group = $node;
      }
      elseif (og_is_group_post_type($node->type)) {
        $this->_gid = current($node->og_groups);
        $this->group = node_load($this->_gid);
      }
    }

  }

  /**
   * dressUpMessages
   *
   * @param HeartbeatParser $heartbeat
   *   The parser for the messages in this stream.
   */
  public function dressUpMessages(HeartbeatParser $heartbeat) {

    $sql = " AND ua.nid <> 0 AND (ua.nid = %d OR ua.nid_target = %d) ";
    $heartbeat->raw_messages = $this->resultSql($sql, array($this->_gid, $this->_gid));

    return $heartbeat;
  }

  /**
   * Function to add a part of a sql to a query built by views UI
   *
   * @param object $view The view handler object by reference to add our part to the query
   */
  public function addViewQuery(&$view) {

    // Make the sql limited to the access
    $field = "$view->table_alias.$view->real_field";

    $view->query->set_where_group('AND', 'extra');

    $sql = "$view->table_alias.nid <> 0 AND ( $view->table_alias.nid = %d OR $view->table_alias.nid_target = %d ) ";
    $view->query->add_where('extra', $sql, $this->_gid, $this->_gid);
  }
}