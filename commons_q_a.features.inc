<?php
/**
 * @file
 * commons_q_a.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commons_q_a_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "panelizer" && $api == "panelizer") {
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
function commons_q_a_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_message_type().
 */
function commons_q_a_default_message_type() {
  $items = array();
  $items['commons_q_a_question_asked'] = entity_import('message_type', '{
    "name" : "commons_q_a_question_asked",
    "description" : "Commons Q\\u0026A: Question Asked",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "[message:user:picture]",
          "format" : "filtered_html",
          "safe_value" : "[message:user:picture]"
        },
        {
          "value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022 class=\\u0022aloha-link-text\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E\\u0026nbsp;asked the question\\u0026nbsp;\\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Ca href=\\u0022[message:user:url:absolute]\\u0022 class=\\u0022aloha-link-text\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E\\u0026nbsp;asked the question\\u0026nbsp;\\u003Ca href=\\u0022[message:field-target-nodes:0:url]\\u0022\\u003E[message:field-target-nodes:0:title]\\u003C\\/a\\u003E"
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
      'description' => 'Use answers for responses to Question content, which can be rated by user votes.',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'question' => array(
      'name' => t('Question'),
      'base' => 'node_content',
      'description' => 'Ask a question to receive answers from other community members',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
