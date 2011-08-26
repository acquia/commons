<?php
/**
 * Filter by node type
 */
class notifications_views_handler_filter_subscription_send_method extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Send method');
      $options = messaging_method_list();
      $this->value_options = $options;
    }
  }
}
