<?php
/**
 * @file
 * commons_activity_streams.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_activity_streams_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'timeago_comment';
  $strongarm->value = 0;
  $export['timeago_comment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'timeago_node';
  $strongarm->value = 0;
  $export['timeago_node'] = $strongarm;

  return $export;
}
