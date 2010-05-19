<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_search_context_default_contexts() {
  module_load_include('inc', 'commons_search', 'commons_search.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_search_context_default_contexts', $args);
}

/**
 * Implementation of hook_ctools_plugin_api().
 */
function commons_search_ctools_plugin_api() {
  module_load_include('inc', 'commons_search', 'commons_search.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_search_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function commons_search_strongarm() {
  module_load_include('inc', 'commons_search', 'commons_search.defaults');
  $args = func_get_args();
  return call_user_func_array('_commons_search_strongarm', $args);
}
