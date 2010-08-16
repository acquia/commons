<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function acquia_network_subscription_ctools_plugin_api() {
  module_load_include('inc', 'acquia_network_subscription', 'acquia_network_subscription.defaults');
  $args = func_get_args();
  return call_user_func_array('_acquia_network_subscription_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function acquia_network_subscription_strongarm() {
  module_load_include('inc', 'acquia_network_subscription', 'acquia_network_subscription.defaults');
  $args = func_get_args();
  return call_user_func_array('_acquia_network_subscription_strongarm', $args);
}
