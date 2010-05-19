<?php

/**
 * Implementation of hook_content_default_fields().
 */
function commons_core_content_default_fields() {
  module_load_include('inc', 'commons_core', 'commons_core.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_core_content_default_fields', $args);
}

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_core_context_default_contexts() {
  module_load_include('inc', 'commons_core', 'commons_core.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_core_context_default_contexts', $args);
}

/**
 * Implementation of hook_ctools_plugin_api().
 */
function commons_core_ctools_plugin_api() {
  module_load_include('inc', 'commons_core', 'commons_core.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_core_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_heartbeat_message_info().
 */
function commons_core_heartbeat_message_info() {
  module_load_include('inc', 'commons_core', 'commons_core.features.features_hb');
  $args = func_get_args();
  return call_user_func_array('_commons_core_heartbeat_message_info', $args);
}

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function commons_core_fieldgroup_default_groups() {
  module_load_include('inc', 'commons_core', 'commons_core.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_core_fieldgroup_default_groups', $args);
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function commons_core_imagecache_default_presets() {
  module_load_include('inc', 'commons_core', 'commons_core.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_core_imagecache_default_presets', $args);
}

/**
 * Implementation of hook_node_info().
 */
function commons_core_node_info() {
  module_load_include('inc', 'commons_core', 'commons_core.features.node');
  $args = func_get_args();
  return call_user_func_array('_commons_core_node_info', $args);
}

/**
 * Implementation of hook_default_page_manager_handlers().
 */
function commons_core_default_page_manager_handlers() {
  module_load_include('inc', 'commons_core', 'commons_core.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_core_default_page_manager_handlers', $args);
}

/**
 * Implementation of hook_default_page_manager_pages().
 */
function commons_core_default_page_manager_pages() {
  module_load_include('inc', 'commons_core', 'commons_core.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_core_default_page_manager_pages', $args);
}

/**
 * Implementation of hook_rules_defaults().
 */
function commons_core_rules_defaults() {
  module_load_include('inc', 'commons_core', 'commons_core.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_core_rules_defaults', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function commons_core_strongarm() {
  module_load_include('inc', 'commons_core', 'commons_core.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_core_strongarm', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function commons_core_views_default_views() {
  module_load_include('inc', 'commons_core', 'commons_core.features.views');
  $args = func_get_args();
  return call_user_func_array('_commons_core_views_default_views', $args);
}
