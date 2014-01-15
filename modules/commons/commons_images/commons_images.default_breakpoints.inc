<?php
/**
 * @file
 * commons_images.default_breakpoints.inc
 */

/**
 * Implements hook_default_breakpoints().
 */
function commons_images_default_breakpoints() {
  $export = array();

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.commons_origins.commons large';
  $breakpoint->name = 'Commons large';
  $breakpoint->breakpoint = 'only screen and (min-width:935px)';
  $breakpoint->source = 'commons_origins';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 4;
  $breakpoint->multipliers = array(
    '1x' => '1x',
  );
  $export['breakpoints.theme.commons_origins.commons large'] = $breakpoint;

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.commons_origins.commons medium landscape';
  $breakpoint->name = 'Commons medium landscape';
  $breakpoint->breakpoint = 'only screen and (min-width:769px) and (max-width:934px';
  $breakpoint->source = 'commons_origins';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 3;
  $breakpoint->multipliers = array(
    '1x' => '1x',
  );
  $export['breakpoints.theme.commons_origins.commons medium landscape'] = $breakpoint;

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.commons_origins.commons medium portrait';
  $breakpoint->name = 'Commons medium portrait';
  $breakpoint->breakpoint = 'only screen and (min-width:481px) and (max-width:768px)';
  $breakpoint->source = 'commons_origins';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 2;
  $breakpoint->multipliers = array(
    '1x' => '1x',
  );
  $export['breakpoints.theme.commons_origins.commons medium portrait'] = $breakpoint;

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.commons_origins.commons small landscape';
  $breakpoint->name = 'Commons small landscape';
  $breakpoint->breakpoint = 'only screen and (min-width:321px) and (max-width:480px)';
  $breakpoint->source = 'commons_origins';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 1;
  $breakpoint->multipliers = array(
    '1x' => '1x',
  );
  $export['breakpoints.theme.commons_origins.commons small landscape'] = $breakpoint;

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.commons_origins.commons small portrait';
  $breakpoint->name = 'Commons small portrait';
  $breakpoint->breakpoint = 'only screen and (max-width:320px)';
  $breakpoint->source = 'commons_origins';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 0;
  $breakpoint->multipliers = array(
    '1x' => '1x',
  );
  $export['breakpoints.theme.commons_origins.commons small portrait'] = $breakpoint;

  return $export;
}
