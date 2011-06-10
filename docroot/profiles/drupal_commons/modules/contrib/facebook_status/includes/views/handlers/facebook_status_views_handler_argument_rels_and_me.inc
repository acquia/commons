<?php

/**
 * @file
 *   Allow only statuses from a user and that user's friends.
 */

/**
 * Argument handler to select statuses relevant to a user and that user's friends.
 */
class facebook_status_views_handler_argument_rels_and_me extends views_handler_argument {
  function query() {
    $this->ensure_my_table();
    $this->query->ensure_table('users');
    $argument = $this->argument;
    // Argument user is in an approved relationship
    $this->query->add_where($this->options['group'], db_prefix_tables("
      (($this->table_alias.requestee_id = %d OR $this->table_alias.requester_id = %d) AND $this->table_alias.approved = 1) OR {users}.uid = %d
    "), $argument, $argument, $argument);
  }
}
