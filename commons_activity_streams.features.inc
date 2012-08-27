<?php
/**
 * @file
 * commons_activity_streams.features.inc
 */

/**
 * Implements hook_default_message_type().
 */
function commons_activity_streams_default_message_type() {
  $items = array();
  $items['commons_activity_streams_comment_created'] = entity_import('message_type', '{
    "name" : "commons_activity_streams_comment_created",
    "description" : "commons_activity_streams_comment_created",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "[message:user:picture]",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E commented on \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E\\u0026lt;a href=\\u0026quot;[message:user:url]\\u0026quot;\\u0026gt;@{message:user:name}\\u0026lt;\\/a\\u0026gt; commented on \\u0026lt;a href=\\u0026quot;[message:field-target-nodes:0:url]\\u0026quot;\\u0026gt;[message:field-target-nodes:0:title]\\u0026lt;\\/a\\u0026gt;\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  $items['commons_activity_streams_node_created'] = entity_import('message_type', '{
    "name" : "commons_activity_streams_node_created",
    "description" : "commons_activity_streams_node_created",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "[message:user:picture]",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E[message:user:picture]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url]\\u0022\\u003E@{message:user:name}\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field_target_nodes]\\u003C\\/a\\u003E",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E\\u0026lt;a href=\\u0026quot;[message:user:url]\\u0026quot;\\u0026gt;@{message:user:name}\\u0026lt;\\/a\\u0026gt; created \\u0026lt;a href=\\u0026quot;[message:field-target-nodes:0:url]\\u0026quot;\\u0026gt;[message:field_target_nodes]\\u0026lt;\\/a\\u0026gt;\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
