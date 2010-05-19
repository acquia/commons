<?php
// $Id: page_tabs.inc,v 1.1.2.1 2010/01/29 20:18:25 merlinofchaos Exp $

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
  'title' => t('Tabs'),
  'single' => TRUE,
  'icon' => 'icon_page.png',
  'description' => t('Add the tabs (local tasks) as content.'),
  'category' => t('Page elements'),
);

/**
 * Output function for the 'page_tabs' content type.
 *
 * Outputs the tabs (local tasks) of the current page.
 */
function ctools_page_tabs_content_type_render($subtype, $conf, $panel_args) {
  $token = '<!-- ctools-page-tabs -->';
  ctools_set_page_token($token, 'variable', 'tabs');

  $block = new stdClass();
  $block->content = $token;

  return $block;
}

