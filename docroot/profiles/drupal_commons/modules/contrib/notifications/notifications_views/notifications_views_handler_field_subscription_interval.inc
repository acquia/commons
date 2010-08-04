<?php
// $Id: notifications_views_handler_field_subscription_interval.inc,v 1.1.2.1 2009/02/20 18:43:18 jareyero Exp $

/**
 * Field handler to translate a node type into its readable form.
 */
class notifications_views_handler_field_subscription_interval extends views_handler_field {
  function render($values) {
    $types = _notifications_send_intervals();
    $value = $types[$values->{$this->field_alias}];
    return check_plain($value);
  }
}

