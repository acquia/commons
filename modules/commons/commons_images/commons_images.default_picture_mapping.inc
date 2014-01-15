<?php
/**
 * @file
 * commons_images.default_picture_mapping.inc
 */

/**
 * Implements hook_default_picture_mapping().
 */
function commons_images_default_picture_mapping() {
  $export = array();

  $picture_mapping = new stdClass();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 1;
  $picture_mapping->machine_name = 'commons_default';
  $picture_mapping->breakpoint_group = 'commons_default';
  $picture_mapping->mapping = array(
    'breakpoints.theme.commons_origins.commons small portrait' => array(
      '1x' => 'commons-default-small',
      '1.5x' => 'commons-default-small-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons small landscape' => array(
      '1x' => 'commons-default-small',
      '1.5x' => 'commons-default-small-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons medium portrait' => array(
      '1x' => 'commons-default-medium',
      '1.5x' => 'commons-default-medium-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons medium landscape' => array(
      '1x' => 'commons-default-medium',
      '1.5x' => 'commons-default-medium-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons large' => array(
      '1x' => 'commons-default-large',
      '1.5x' => 'commons-default-large-1_5x',
    ),
  );
  $export['commons_default'] = $picture_mapping;

  $picture_mapping = new stdClass();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 1;
  $picture_mapping->machine_name = 'commons_full';
  $picture_mapping->breakpoint_group = 'commons_full';
  $picture_mapping->mapping = array(
    'breakpoints.theme.commons_origins.commons small portrait' => array(
      '1x' => 'commons-full-small',
      '1.5x' => 'commons-full-small-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons small landscape' => array(
      '1x' => 'commons-full-small',
      '1.5x' => 'commons-full-small-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons medium portrait' => array(
      '1x' => 'commons-full-medium',
      '1.5x' => 'commons-full-medium-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons medium landscape' => array(
      '1x' => 'commons-full-medium',
      '1.5x' => 'commons-full-medium-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons large' => array(
      '1x' => 'commons-full-large',
      '1.5x' => 'commons-full-large-1_5x',
    ),
  );
  $export['commons_full'] = $picture_mapping;

  $picture_mapping = new stdClass();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 1;
  $picture_mapping->machine_name = 'commons_teaser';
  $picture_mapping->breakpoint_group = 'commons_teaser';
  $picture_mapping->mapping = array(
    'breakpoints.theme.commons_origins.commons small portrait' => array(
      '1x' => 'commons-teaser-small',
      '1.5x' => 'commons-teaser-small-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons small landscape' => array(
      '1x' => 'commons-teaser-small',
      '1.5x' => 'commons-teaser-small-1_5x',
    ),
    'breakpoints.theme.commons_origins.commons medium portrait' => array(
      '1x' => 'commons-teaser-medium',
      '1.5x' => 'commons-teaser-medium-1_5',
    ),
    'breakpoints.theme.commons_origins.commons medium landscape' => array(
      '1x' => 'commons-teaser-medium',
      '1.5x' => 'commons-teaser-medium-1_5',
    ),
    'breakpoints.theme.commons_origins.commons large' => array(
      '1x' => 'commons-teaser-large',
      '1.5x' => 'commons-teaser-large-1_5x',
    ),
  );
  $export['commons_teaser'] = $picture_mapping;

  return $export;
}
