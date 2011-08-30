<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function commons_document_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function commons_document_node_info() {
  $items = array(
    'document' => array(
      'name' => t('Document'),
      'module' => 'features',
      'description' => t('A document item which contains a title, description, an unlimited amount of attached files.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function commons_document_views_api() {
  return array(
    'api' => '2',
  );
}
