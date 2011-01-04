<?php
// $Id: realname_handler_argument_user_uid.inc,v 1.1.2.2 2009/04/22 00:44:47 nancyw Exp $

/**
 * @file
 * The RealName module allows the admin to choose fields from the user profile
 * that will be used to add a "realname" element (method) to a user object.
 */

/**
 * Argument handler for realnames
 */
class realname_handler_argument_user_uid extends views_handler_argument_user_uid {
  /**
   * Override the behavior of title(). Get the realname of the user.
   */
  function title_query() {
    if (!$this->argument) {
      return array(variable_get('anonymous', t('Anonymous')));
    }
    
    $titles = array();
    $placeholders = implode(', ', array_fill(0, sizeof($this->value), '%d'));

    $result = db_query("SELECT r.realname FROM {users} u LEFT JOIN {realname} r ON u.uid=r.uid WHERE u.uid IN ($placeholders)", $this->value);
    while ($term = db_fetch_object($result)) {
      $titles[] = check_plain($term->realname);
    }
    return $titles;
  }
}
