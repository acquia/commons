<?php
// $Id: views_plugin_row_heartbeat_rss.inc,v 1.1.2.5 2010/02/21 22:45:27 stalski Exp $

/**
 * @file
 *   Contains the heartbeat message RSS row style plugin.
 */

/**
 * Class views_plugin_row_heartbeat_rss
 *   Plugin which performs a node_view on the resulting object
 *   and formats it as an RSS item.
 */
class views_plugin_row_heartbeat_rss extends views_plugin_row {

  function render($row) {

    $item = new stdClass();
    if (isset($row->heartbeat_activity_message)) {
      $item->title = $row->heartbeat_activity_message;
      $item->description = $row->heartbeat_activity_message;
      $item->time = $row->heartbeat_activity_timestamp;
    }

    return theme($this->theme_functions(), $this->view, $this->options, $item);
  }
}