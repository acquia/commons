<?php
// $Id: naked.inc,v 1.1.2.2 2010/01/13 06:25:15 merlinofchaos Exp $

/**
 * @file
 * Definition of the 'naked' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('No markup at all'),
  'description' => t('Display the pane with no markup, not even a title.'),
  'render pane' => 'panels_naked_style_render_pane',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_naked_style_render_pane($content, $pane, $display) {
  return $content->content;
}

