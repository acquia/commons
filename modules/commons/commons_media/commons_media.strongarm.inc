<?php
/**
 * @file
 * commons_media.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_media_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'media__dialog_theme';
  $strongarm->value = 'ember';
  $export['media__dialog_theme'] = $strongarm;

  return $export;
}
