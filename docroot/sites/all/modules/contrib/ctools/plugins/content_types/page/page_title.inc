<?php
// $Id: page_title.inc,v 1.1.2.3 2010/02/23 22:14:43 merlinofchaos Exp $

/**
 * @file
 * Plugin to handle the 'page' content type which allows the standard page
 * template variables to be embedded into a panel.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Page title'),
  'icon' => 'icon_page.png',
  'description' => t('Add the page title as content.'),
  'category' => t('Page elements'),
  'render last' => TRUE,
);

/**
 * Output function for the 'page_title' content type.
 *
 * Outputs the page title of the current page.
 */
function ctools_page_title_content_type_render($subtype, $conf, $panel_args) {

  $block = new stdClass();

  $title = drupal_get_title();
  if ($title) { 
    // TODO: This should have a setting or something for the markup.
    $block->content = '<h1>'. $title .'</h1>';
  }

  return $block;

}
