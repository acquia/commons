<?php

/**
 * Implementation of hook_strongarm().
 */
function commons_shoutbox_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shoutbox_escape_html';
  $strongarm->value = 0;

  $export['shoutbox_escape_html'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shoutbox_filter_format';
  $strongarm->value = 5;

  $export['shoutbox_filter_format'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shoutbox_showamount_block';
  $strongarm->value = 3;

  $export['shoutbox_showamount_block'] = $strongarm;
  return $export;
}
