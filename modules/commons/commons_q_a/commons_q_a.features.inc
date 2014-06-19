<?php
/**
 * @file
 * commons_q_a.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_q_a_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function commons_q_a_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function commons_q_a_default_message_type() {
  $items = array();
  $items['commons_q_a_question_answered'] = entity_import('message_type', '{
    "name" : "commons_q_a_question_answered",
    "description" : "Commons Q\\u0026A: Question Answered",
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
          "value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E answered the question \\u003Cem\\u003E[message:field-target-nodes:0:field-related-question:title]\\u003C\\/em\\u003E with \\u0022\\u003Ca href=\\u0022[message:field-target-nodes:0:field-related-question:url]#node-[message:field-target-nodes:0:nid]\\u0022\\u003E[message:field-target-nodes:0:title_field]\\u003C\\/a\\u003E\\u0022",
          "format" : "full_html",
          "safe_value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E answered the question \\u003Cem\\u003E[message:field-target-nodes:0:field-related-question:title]\\u003C\\/em\\u003E with \\u0022\\u003Ca href=\\u0022[message:field-target-nodes:0:field-related-question:url]#node-[message:field-target-nodes:0:nid]\\u0022\\u003E[message:field-target-nodes:0:title_field]\\u003C\\/a\\u003E\\u0022"
        },
        {
          "value" : "[commons-groups:in-groups-text]",
          "format" : "full_html",
          "safe_value" : "[commons-groups:in-groups-text]"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['commons_q_a_question_asked'] = entity_import('message_type', '{
    "name" : "commons_q_a_question_asked",
    "description" : "Commons Q\\u0026A: Question Asked",
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
          "value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E asked the question \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title_field]\\u003C\\/a\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E asked the question \\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title_field]\\u003C\\/a\\u003E"
        },
        {
          "value" : "[commons-groups:in-groups-text]",
          "format" : "full_html",
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
function commons_q_a_node_info() {
  $items = array(
    'answer' => array(
      'name' => t('Answer'),
      'base' => 'node_content',
      'description' => t('Use answers for responses to Question content, which can be rated by user votes.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'question' => array(
      'name' => t('Question'),
      'base' => 'node_content',
      'description' => t('Ask a question to receive answers from other community members'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
