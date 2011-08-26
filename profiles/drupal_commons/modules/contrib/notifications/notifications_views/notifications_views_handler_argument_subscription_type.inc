<?php
/**
 * Argument handler to accept a subscription type.
 */
class notifications_views_handler_argument_subscription_type extends views_handler_argument {
  function construct() {
    parent::construct('type');
  }

  /**
   * Override the behavior of summary_name(). Get the user friendly version
   * of the subscription type.
   */
  function summary_name($data) {
    return $this->subscription_type($data->{$this->name_alias});
  }

  /**
   * Override the behavior of title(). Get the user friendly version of the
   * node type.
   */
  function title() {
    return $this->subscription_type($this->argument);
  }

  function subscription_type($type) {
    $output = notifications_subscription_types($type);
    $output = $type['title'];
    if (empty($output)) {
      $output = t('Unknown');
    }
    return check_plain($output);
  }
}
