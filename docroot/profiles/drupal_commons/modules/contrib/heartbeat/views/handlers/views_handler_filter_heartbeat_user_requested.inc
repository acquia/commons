<?php

/**
 * @file
 *   Implementation of boolean filter to match the requested user
 *   with the actor of the activity.
 */

/**
 * Class views_handler_filter_heartbeat_user_requested
 *   Filter by requested user id
 */
class views_handler_filter_heartbeat_user_requested extends views_handler_filter_boolean_operator {

  function construct() {
    parent::construct();
    $this->value_value = t('message ... not implemented yet');
  }

  function query() {
    $this->ensure_my_table();
  }

}