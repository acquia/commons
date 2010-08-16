<?php
/**
 * Filter by node type
 */
class notifications_views_handler_filter_subscription_type extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Subscription type');
      $subtypes = notifications_subscription_types();
      $options = array();
      foreach ($subtypes as $type => $info) {
        $options[$type] = $info['title'];
      }
      $this->value_options = $options;
    }
  }
}
