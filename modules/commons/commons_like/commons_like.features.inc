<?php
/**
 * @file
 * commons_like.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_like_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function commons_like_default_message_type() {
  $items = array();
  $items['commons_like_user_likes_node'] = entity_import('message_type', '{
    "name" : "commons_like_user_likes_node",
    "description" : "Commons like: User likes a node",
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
          "value" : "[message:user:picture]",
          "format" : "full_html",
          "safe_value" : "[message:user:picture]"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E liked the [message:field-target-nodes:0:type] \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title_field]\\u003C\\/a\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E liked the [message:field-target-nodes:0:type] \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title_field]\\u003C\\/a\\u003E"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
