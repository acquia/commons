<?php
// $Id: default.inc,v 1.1.2.3 2010/01/13 06:25:15 merlinofchaos Exp $

/**
 * @file
 * Definition of the 'default' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('No style'),
  'description' => t('The default panel rendering style; displays each pane with a separator.'),
  'render panel' => 'panels_default_style_render_panel',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_default_style_render_panel($display, $panel_id, $panes, $settings) {
  $output = '';

  $print_separator = FALSE;
  foreach ($panes as $pane_id => $content) {
    // Add the separator if we've already displayed a pane.
    if ($print_separator) {
      $output .= '<div class="panel-separator"></div>';
    }
    $output .= $text = panels_render_pane($content, $display->content[$pane_id], $display);

    // If we displayed a pane, this will become true; if not, it will become
    // false.
    $print_separator = (bool) $text;
  }

  return $output;
}

