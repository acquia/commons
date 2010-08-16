<?php
/**
 * Field handler to translate a node type into its readable form.
 */
class notifications_views_handler_field_subscription_type extends views_handler_field {
  function render($values) {
    $types = notifications_subscription_types();
    $value = $types[$values->{$this->field_alias}]['title'];
    return check_plain($value);
  }
}

