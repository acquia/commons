<?php
// $Id: page_title.inc,v 1.1.2.1 2010/01/29 20:18:25 merlinofchaos Exp $

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
);

/**
 * Output function for the 'page_title' content type.
 *
 * Outputs the page title of the current page.
 */
function ctools_page_title_content_type_render($subtype, $conf, $panel_args) {
  $token = '<!-- ctools-page-title -->';
  ctools_set_page_token($token, 'variable', 'title');

  $block = new stdClass();
  $block->content = '<h1>'. $token .'</h1>';

  return $block;
}