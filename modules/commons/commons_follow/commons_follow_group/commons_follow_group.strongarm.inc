<?php
/**
 * @file
 * commons_follow_group.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_follow_group_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'message_subscribe_og';
  $strongarm->value = 'subscribe_node_email:default';
  $export['message_subscribe_og'] = $strongarm;

  return $export;
}
