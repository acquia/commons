<?php

/**
 * @file
 *   Filters statuses to a certain recipient type.
 */

/**
 * Filter handler to select statuses with a given recipient type.
 */
class facebook_status_views_handler_filter_type extends views_handler_filter_in_operator {
  function get_value_options() {
    $contexts = facebook_status_all_contexts();
    $options = array();
    foreach ($contexts as $type => $info) {
      $options[$type] = $info['title'];
    }
    $this->value_options = $options;
  }
}
