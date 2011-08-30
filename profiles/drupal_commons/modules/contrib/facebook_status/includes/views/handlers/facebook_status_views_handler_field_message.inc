<?php

/**
 * @file
 *   Formats statuses in Views.
 */

/**
 * Field handler to provide the most recent status update.
 */
class facebook_status_views_handler_field_message extends views_handler_field {
  function render($values) {
    $message = _facebook_status_run_filter($values->{$this->field_alias});
    if (variable_get('facebook_status_nl2br', 0)) {
      $message = nl2br($message);
    }
    return '<span class="facebook-status-content">'. $message .'</span>';
  }
}
