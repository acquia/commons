<?php
// $Id: page_messages.inc,v 1.1.2.1 2010/01/29 20:18:25 merlinofchaos Exp $

/**
 * @file
 * Plugin to handle the 'page_messages' content type which allows the
 * status messages of the current page to be embedded into a panel.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Status messages'),
  'single' => TRUE,
  'icon' => 'icon_page.png',
  'description' => t('Add the status messages of the current page as content.'),
  'category' => t('Page elements'),
);

/**
 * Output function for the 'page_messages' content type.
 *
 * Outputs the breadcrumb for the current page.
 */
function ctools_page_messages_content_type_render($subtype, $conf, $panel_args) {
  $token = '<!-- ctools-page-messages -->';
  ctools_set_page_token($token, 'variable', 'messages');

  $block = new stdClass();
  $block->content = $token;

  return $block;
}

