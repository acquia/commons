<?php
/**
 * @file
 * commons_posts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_posts_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_posts_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function commons_posts_default_message_type() {
  $items = array();
  $items['commons_posts_post_created'] = entity_import('message_type', '{
    "name" : "commons_posts_post_created",
    "description" : "Commons Posts - Post Created",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 1 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "[message:user:picture:35x35]",
          "format" : "filtered_html",
          "safe_value" : "[message:user:picture:35x35]"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E posted \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title_field]\\u003C\\/a\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E posted \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title_field]\\u003C\\/a\\u003E"
        },
        {
          "value" : "[commons-groups:in-groups-text]",
          "format" : "filtered_html",
          "safe_value" : "[commons-groups:in-groups-text]"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_node_info().
 */
function commons_posts_node_info() {
  $items = array(
    'post' => array(
      'name' => t('Post'),
      'base' => 'node_content',
      'description' => t('Start a conversation or share some information.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
