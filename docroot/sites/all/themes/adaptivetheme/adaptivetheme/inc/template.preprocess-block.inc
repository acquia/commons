<?php // $Id: template.preprocess-block.inc,v 1.1.2.18 2010/03/17 00:57:51 jmburnz Exp $
// adaptivethemes.com

/**
 * @file template.preprocess-block.inc
 */

/**
 * Override or insert variables into block templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called.
 */

global $theme, $user;

$block = $vars['block'];

// Rewrite the left and right region names.
if ($block->region == 'left') {
  $block->region = 'sidebar-first';
}
if ($block->region == 'right') {
  $block->region = 'sidebar-last';
}

// Set the block id.
if (theme_get_setting('cleanup_block_block_module_delta')) {
  $vars['block_module_delta'] = 'block-'. $block->module .'-'. $block->delta;
}

// Special classes for blocks, emulate Drupal 7.
$classes = array();

$classes[] = 'block';

if (theme_get_setting('cleanup_block_classes_module')) {
  $classes[] = 'block-'. $block->module;
}

if (theme_get_setting('cleanup_block_classes_zebra')) {
  $classes[] = $vars['block_zebra']; // odd, even zebra class
}

if (theme_get_setting('cleanup_block_classes_region')) {
  $classes[] = 'block-region-'. safe_string($block->region); // block-[region] class
}

if (theme_get_setting('cleanup_block_classes_count')) {
  $classes[] = 'block-count-'. $vars['id']; // block-count-[count] class
}

// Add special classes to support the http://drupal.org/project/blocktheme module.
if (function_exists('blocktheme_preprocess_block') && isset($vars['blocktheme'])) {
  $classes[] = $vars['blocktheme'];
  $classes[] = safe_string($block->region) .'-'. $vars['blocktheme'];
}

// Add special classes to support the http://drupal.org/project/block_class module.
if (function_exists('block_class') && block_class($block)) {
  $classes[] = block_class($block);
  $classes[] = safe_string($block->region) .'-'. block_class($block);
}

// Add support for Skinr module classes http://drupal.org/project/skinr.
if (function_exists('skinr_preprocess') && !empty($vars['skinr'])) {
  $classes[] = $vars['skinr'];
}

// Add class for block edit links if enabled.
if (theme_get_setting('block_edit_links') && user_access('administer blocks')) {
  $classes[] = 'block-edit-links';
}

// Add classes for the horizontal login block if enabled.
if (theme_get_setting('horizontal_login_block') && $block->module == 'user' && $block->delta == '0') {
  $classes[] = 'at-horizontal-login clearfix';
}

// Hide search label on the search block
if ($block->module == 'search' && $block->delta == 0) {
  if (theme_get_setting('display_search_form_label') == 0) {
    $classes[] = 'hide-label';
  }
}

// $classes is the varaible that will hold the blocks classes, and is printed in block tpl files.
$vars['classes'] = implode(' ', $classes);

// Set title classes
$title_classes = array();
if (theme_get_setting('cleanup_headings_title_class')) {
  $title_classes[] = 'title';
}

if (theme_get_setting('cleanup_headings_namespaced_class')) {
  $title_classes[] = 'block-title';
}

$vars['title_classes'] = implode(' ', $title_classes);

// Block edit links.
$vars['edit_links_array'] = array();
$vars['edit_links'] = '';
if (theme_get_setting('block_edit_links') && user_access('administer blocks')) {
  include_once './'. drupal_get_path('theme', 'adaptivetheme') .'/inc/template.block-editing.inc';
  adaptivetheme_preprocess_block_editing($vars, $hook);
}