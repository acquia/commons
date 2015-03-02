<?php

/**
 * @file
 * Custom buttons for embedding entities.
 */

/**
 * Implements hook_default_entity_embed_configuration().
 */
function commons_media_default_entity_embed_configuration() {
  $configurations = array();

  $configuration = new stdClass();
  $configuration->disabled = FALSE; /* Edit this to true to make a default configuration disabled initially */
  $configuration->api_version = 1;
  $configuration->admin_title = 'File';
  $configuration->name = 'file';
  $configuration->button_label = 'File';
  $configuration->entity_type = 'file';
  $configuration->button_icon_fid = 0;
  $configurations['file'] = $configuration;

  return $configurations;
}
