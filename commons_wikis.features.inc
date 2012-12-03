<?php
/**
 * @file
 * commons_wikis.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_wikis_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_wikis_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function commons_wikis_default_message_type() {
  $items = array();
  $items['commons_wikis_wiki_updated'] = entity_import('message_type', '{
    "name" : "commons_wikis_wiki_updated",
    "description" : "commons_wikis_wiki_updated",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "[current-user:name] has updated the wiki [message:field-target-nodes:1].\\u003Ca\\u003E\\u003C\\/a\\u003E\\u003Ca\\u003E\\u003C\\/a\\u003E",
          "format" : "filtered_html",
          "safe_value" : "[current-user:name] has updated the wiki [message:field-target-nodes:1].\\u003Ca\\u003E\\u003C\\/a\\u003E\\u003Ca\\u003E\\u003C\\/a\\u003E"
        }
      ]
    }
  }');
  return $items;
}

/**
 * Implements hook_node_info().
 */
function commons_wikis_node_info() {
  $items = array(
    'wiki' => array(
      'name' => t('Wiki'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
