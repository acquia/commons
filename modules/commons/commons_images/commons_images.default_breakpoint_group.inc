<?php
/**
 * @file
 * commons_images.default_breakpoint_group.inc
 */

/**
 * Implements hook_default_breakpoint_group().
 */
function commons_images_default_breakpoint_group() {
  $export = array();

  // Breakpoints.
  $breakpoints = array();
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons small portrait';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons small landscape';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons medium portrait';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons medium landscape';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons large';

  // Breakpoint group.
  $breakpoint_group = new stdClass();
  $breakpoint_group->disabled = FALSE; /* Edit this to true to make a default breakpoint_group disabled initially */
  $breakpoint_group->api_version = 1;
  $breakpoint_group->machine_name = 'commons_default';
  $breakpoint_group->name = 'Commons default';
  $breakpoint_group->breakpoints = $breakpoints;
  $breakpoint_group->type = 'module';
  $breakpoint_group->overridden = 0;
  $export['commons_default'] = $breakpoint_group;

  // Breakpoints.
  $breakpoints = array();
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons small portrait';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons small landscape';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons medium portrait';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons medium landscape';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons large';

  // Breakpoint group.
  $breakpoint_group = new stdClass();
  $breakpoint_group->disabled = FALSE; /* Edit this to true to make a default breakpoint_group disabled initially */
  $breakpoint_group->api_version = 1;
  $breakpoint_group->machine_name = 'commons_full';
  $breakpoint_group->name = 'Commons full';
  $breakpoint_group->breakpoints = $breakpoints;
  $breakpoint_group->type = 'module';
  $breakpoint_group->overridden = 0;
  $export['commons_full'] = $breakpoint_group;

  // Breakpoints.
  $breakpoints = array();
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons small portrait';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons small landscape';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons medium portrait';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons medium landscape';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons large';

  // Breakpoint group.
  $breakpoint_group = new stdClass();
  $breakpoint_group->disabled = FALSE; /* Edit this to true to make a default breakpoint_group disabled initially */
  $breakpoint_group->api_version = 1;
  $breakpoint_group->machine_name = 'commons_origins';
  $breakpoint_group->name = 'Commons Origins';
  $breakpoint_group->breakpoints = $breakpoints;
  $breakpoint_group->type = 'theme';
  $breakpoint_group->overridden = 0;
  $export['commons_origins'] = $breakpoint_group;

  // Breakpoints.
  $breakpoints = array();
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons small portrait';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons small landscape';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons medium portrait';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons medium landscape';
  $breakpoints[] = 'breakpoints.theme.commons_origins.commons large';

  // Breakpoint group.
  $breakpoint_group = new stdClass();
  $breakpoint_group->disabled = FALSE; /* Edit this to true to make a default breakpoint_group disabled initially */
  $breakpoint_group->api_version = 1;
  $breakpoint_group->machine_name = 'commons_teaser';
  $breakpoint_group->name = 'Commons teaser';
  $breakpoint_group->breakpoints = $breakpoints;
  $breakpoint_group->type = 'module';
  $breakpoint_group->overridden = 0;
  $export['commons_teaser'] = $breakpoint_group;

  return $export;
}
