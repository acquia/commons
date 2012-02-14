<?php

/**
 * Implementation of hook_strongarm().
 */
function commons_answers_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_answer';
  $strongarm->value = 'group_post_standard';
  $export['og_content_type_usage_answer'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_question';
  $strongarm->value = 'group_post_standard';
  $export['og_content_type_usage_question'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_answer';
  $strongarm->value = '';
  $export['og_max_groups_answer'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_question';
  $strongarm->value = '';
  $export['og_max_groups_question'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_answer_pattern';
  $strongarm->value = 'answer/[title-raw]';
  $export['pathauto_node_answer_pattern'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_question_pattern';
  $strongarm->value = 'question/[title-raw]';
  $export['pathauto_node_question_pattern'] = $strongarm;

  return $export;
}
