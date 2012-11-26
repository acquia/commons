<?php
/**
 * @file
 * commons_notify.features.inc
 */

/**
 * Implements hook_default_message_type_category().
 */
function commons_notify_default_message_type_category() {
  $defaults['commons_notify'] = entity_create('message_type_category', array(
    'category' => 'commons_notify',
    'description' => "Commons Notify",
    'language' => LANGUAGE_NONE,
  ));
  return $defaults;
}

/**
 * Implements hook_default_message_type().
 */
function commons_notify_default_message_type() {
  $items = array();
  $items['commons_notify_node_created'] = entity_import('message_type', '{
    "name" : "commons_notify_node_created",
    "description" : "The notification sent when a user creates a node.",
    "argument_keys" : [],
    "argument" : [],
    "category" : "commons_notify",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "New [message:field-target-nodes:0:content-type] in [message:field-target-nodes:0:og_group_ref:0:title]",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003ENew [message:field-target-nodes:0:content-type] in [message:field-target-nodes:0:og_group_ref:0:title]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "[message:field-target-nodes:0:body:value]\\r\\n[message:field-target-nodes:0:body:summary]\\r\\n\\r\\nHi [firstname or username],\\r\\n\\r\\n[message:field-target-nodes:0:author] created the [message:field-target-nodes:0:content-type] \\u201c[message:field-target-nodes:0:title]\\u201d on [site:name] [commons-groups][in-groups-text] on [message:field-target-nodes:0:created]:\\r\\n\\r\\n\\r\\n[message:field-target-nodes:0:url]\\r\\n\\r\\n[message:field-target-nodes:0:body:value]\\r\\n[message:field-target-nodes:0:body]\\r\\n[message:field-target-nodes:0:body:?]\\r\\n[message:field-target-nodes:0:body:summary]\\r\\n\\r\\n\\r\\n[message:field-target-nodes:1:body:value]\\r\\n[message:field-target-nodes:1:body]\\r\\n[message:field-target-nodes:1:body:?]\\r\\n[message:field-target-nodes:1:body:summary]\\r\\n\\r\\n\\r\\nAdd a comment at [message:field-target-nodes:0:url]#comment-form\\r\\n\\r\\nChange email notifications at [site:url]\\/settings",
          "format" : "plain_text",
          "safe_value" : "\\u003Cp\\u003E[message:field-target-nodes:0:body:value]\\u003Cbr \\/\\u003E\\n[message:field-target-nodes:0:body:summary]\\u003C\\/p\\u003E\\n\\u003Cp\\u003EHi [firstname or username],\\u003C\\/p\\u003E\\n\\u003Cp\\u003E[message:field-target-nodes:0:author] created the [message:field-target-nodes:0:content-type] \\u201c[message:field-target-nodes:0:title]\\u201d on [site:name] [commons-groups][in-groups-text] on [message:field-target-nodes:0:created]:\\u003C\\/p\\u003E\\n\\u003Cp\\u003E[message:field-target-nodes:0:url]\\u003C\\/p\\u003E\\n\\u003Cp\\u003E[message:field-target-nodes:0:body:value]\\u003Cbr \\/\\u003E\\n[message:field-target-nodes:0:body]\\u003Cbr \\/\\u003E\\n[message:field-target-nodes:0:body:?]\\u003Cbr \\/\\u003E\\n[message:field-target-nodes:0:body:summary]\\u003C\\/p\\u003E\\n\\u003Cp\\u003E[message:field-target-nodes:1:body:value]\\u003Cbr \\/\\u003E\\n[message:field-target-nodes:1:body]\\u003Cbr \\/\\u003E\\n[message:field-target-nodes:1:body:?]\\u003Cbr \\/\\u003E\\n[message:field-target-nodes:1:body:summary]\\u003C\\/p\\u003E\\n\\u003Cp\\u003EAdd a comment at [message:field-target-nodes:0:url]#comment-form\\u003C\\/p\\u003E\\n\\u003Cp\\u003EChange email notifications at [site:url]\\/settings\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
