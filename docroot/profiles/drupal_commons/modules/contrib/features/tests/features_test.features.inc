<?php

/**
 * Implementation of hook_content_default_fields().
 */
function features_test_content_default_fields() {
  module_load_include('inc', 'features_test', 'features_test.defaults');
  $args = func_get_args();
  return call_user_func_array('_features_test_content_default_fields', $args);
}

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function features_test_fieldgroup_default_groups() {
  module_load_include('inc', 'features_test', 'features_test.defaults');
  $args = func_get_args();
  return call_user_func_array('_features_test_fieldgroup_default_groups', $args);
}

/**
 * Implementation of hook_filter_default_formats().
 */
function features_test_filter_default_formats() {
  module_load_include('inc', 'features_test', 'features_test.defaults');
  $args = func_get_args();
  return call_user_func_array('_features_test_filter_default_formats', $args);
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function features_test_imagecache_default_presets() {
  module_load_include('inc', 'features_test', 'features_test.defaults');
  $args = func_get_args();
  return call_user_func_array('_features_test_imagecache_default_presets', $args);
}

/**
 * Implementation of hook_node_info().
 */
function features_test_node_info() {
  module_load_include('inc', 'features_test', 'features_test.features.node');
  $args = func_get_args();
  return call_user_func_array('_features_test_node_info', $args);
}

/**
 * Implementation of hook_user_default_permissions().
 */
function features_test_user_default_permissions() {
  module_load_include('inc', 'features_test', 'features_test.defaults');
  $args = func_get_args();
  return call_user_func_array('_features_test_user_default_permissions', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function features_test_views_default_views() {
  module_load_include('inc', 'features_test', 'features_test.features.views');
  $args = func_get_args();
  return call_user_func_array('_features_test_views_default_views', $args);
}
