<?php
/**
 * @file
 * commons_follow.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_follow_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'message_subscribe_flag_prefix';
  $strongarm->value = 'commons_follow';
  $export['message_subscribe_flag_prefix'] = $strongarm;

  return $export;
}
