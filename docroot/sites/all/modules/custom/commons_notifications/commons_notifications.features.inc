<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function commons_notifications_ctools_plugin_api() {
  module_load_include('inc', 'commons_notifications', 'commons_notifications.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_notifications_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function commons_notifications_strongarm() {
  module_load_include('inc', 'commons_notifications', 'commons_notifications.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_notifications_strongarm', $args);
}
