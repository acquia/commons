<?php
/**
 * @file
 * commons_trusted_contacts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_trusted_contacts_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_trusted_contacts_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function commons_trusted_contacts_default_message_type() {
  $items = array();
  $items['trusted_contact_request_approved'] = entity_import('message_type', '{
    "name" : "trusted_contact_request_approved",
    "description" : "Trusted-Contact request approved",
    "argument_keys" : [],
    "argument" : [],
    "category" : "commons_notify",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "[message:field-approving-user:field-name] approved your Trusted-Contact request.",
          "format" : "full_html",
          "safe_value" : "[message:field-approving-user:field-name] approved your Trusted-Contact request."
        },
        {
          "value" : "\\u003Cp\\u003E[message:field-approving-user:field-name] approved your Trusted-Contact request.\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003EView their profile.. etc.\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-approving-user:field-name] approved your Trusted-Contact request.\\u003C\\/p\\u003E\\n\\n\\u003Cp\\u003EView their profile.. etc.\\u003C\\/p\\u003E"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['trusted_contact_request_pending'] = entity_import('message_type', '{
    "name" : "trusted_contact_request_pending",
    "description" : "Trusted-Contact request pending",
    "argument_keys" : [],
    "argument" : [],
    "category" : "commons_notify",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003EYou have a Trusted-Contact request pending from [message:field-requesting-user:name]\\u003C\\/p\\u003E\\r\\n",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EYou have a Trusted-Contact request pending from [message:field-requesting-user:name]\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EHello,\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003EYou have a Trusted-Contact request pending from [message:field-requesting-user:name]\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003EYou may approve or ignore.\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003E\\u003Ca href=\\u0022@{approve-url}\\u0022\\u003EApprove\\u003C\\/a\\u003E | \\u003Ca href=\\u0022@{ignore-url}\\u0022\\u003EIgnore\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EHello,\\u003C\\/p\\u003E\\n\\n\\u003Cp\\u003EYou have a Trusted-Contact request pending from [message:field-requesting-user:name]\\u003C\\/p\\u003E\\n\\n\\u003Cp\\u003EYou may approve or ignore.\\u003C\\/p\\u003E\\n\\n\\u003Cp\\u003E\\u003Ca href=\\u0022@{approve-url}\\u0022\\u003EApprove\\u003C\\/a\\u003E | \\u003Ca href=\\u0022@{ignore-url}\\u0022\\u003EIgnore\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
