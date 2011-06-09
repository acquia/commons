<?php

/**
 * @file
 *   Filters to statuses matching the current context.
 */

/**
 * Filter handler to select statuses from matching the current context.
 */
class facebook_status_views_handler_filter_autotype extends views_handler_filter {
  function query() {
    $context = facebook_status_determine_context();
    $type = $context['handler']->type();
    $recipient = $context['handler']->find_recipient();
    $recipient_id = $context['handler']->recipient_id($recipient);
    $query = db_prefix_tables("{$this->table}.recipient = %d AND {$this->table}.type = '%s'");
    $this->query->add_where($this->options['group'], $query, $recipient_id, $type);
  }
}
