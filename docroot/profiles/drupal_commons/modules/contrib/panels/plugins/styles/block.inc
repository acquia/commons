<?php
// $Id: block.inc,v 1.1.2.6 2010/01/13 06:25:15 merlinofchaos Exp $

/**
 * @file
 * Definition of the 'block' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('System block'),
  'description' => t('Display the pane as a system block; this is more restrictive than the default.'),
  'render pane' => 'panels_block_style_render_pane',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_block_style_render_pane($content, $pane, $display) {
  if (empty($content->content)) {
    return;
  }

  if (!empty($content->title)) {
    $content->subject = $content->title;
  }

  $content->region = $pane->panel;
  if (!isset($content->module)) {
    $content->module = $content->type;
  }
  if (!isset($content->delta)) {
    $content->delta = $content->subtype;
  }

  return theme('block', $content);
}

