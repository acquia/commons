<?php
// $Id: skinr.inc,v 1.1.4.4 2010/10/21 22:12:44 jgirlygirl Exp $

/**
 * @file
 * Definition of the 'skinr' panel style.
 */

// Plugin definition

/**
 * Implementation of hook_panels_style_info().
 */
function skinr_skinr_panels_styles() {
  return array(
    'skinr' => array(
      'title'              => t('Skinr'),
      'description'        => t('Allows you to apply Skinr skins.'),
      'render region'      => 'panels_skinr_style_render_region',
      'render pane'        => 'panels_skinr_style_render_pane',
      'settings form'      => 'panels_skinr_style_settings_form',
      'pane settings form' => 'panels_skinr_style_settings_form',
    ),
  );
}

/**
 * Render panel callback.
 *
 * @todo: Need to wait for a panels update to panels_render_panel()
 *        The panel_id is not sent through properly, yet. Once it works as
 *        promised, we can remove the workaround.
 *
 * @ingroup themeable
 */
function theme_panels_skinr_style_render_region($display, $region_id, $panes, $settings) {
  // Workaround for missing/invalid $region_id.
  if (empty($region_id)) {
    // Grab the first pane that we know exists in this panel and extract the
    // region_id from it.
    $panes_keys = array_keys($panes);
    $region_id = $display->content[$panes_keys[0]]->panel;
  }

  $output = '';
  $print_separator = FALSE;
  foreach ($panes as $pane_id => $content) {
    // Add the separator if we've already displayed a pane.
    if ($print_separator) {
      $output .= '<div class="panel-region-separator"></div>';
    }
    $output .= $text = $content;
    // If we displayed a pane, this will become true; if not, it will become
    // false.
    $print_separator = (bool) $text;
  }

  // Add skinr styles
  $hook = 'panels';
  if (isset($display->panel_settings[$region_id]['style']) && isset($display->panel_settings[$region_id]['style']) == 'skinr') {
    // Specific style set for this panel.
    $sid = 'display-'. $display->did .'-region-'. $region_id;
  }
  else {
    // No specific style set, so use the display's style.
    $sid = 'display-'. $display->did;
  }
  $style = array();
  // Get the Skinr classes for the current panel or display.
  if ($skinr = skinr_get(NULL, $hook, $sid)) {
    // Convert the array to a string fit for printing in the class attribute.
    $style = skinr_style_array_to_string($skinr);
  }

  // Wrap the output in a DIV containing the Skinr class.
  if (!empty($style)) {
    $output = '<div class="'. $style .'">'. $output .'</div>';
  }

  return $output;
}

/**
 * Render pane callback.
 *
 * @ingroup themeable
 */
function theme_panels_skinr_style_render_pane($content, $pane, $display, $plugin = NULL) {
  if (isset($pane->style['style']) && isset($pane->style['style']) == 'skinr') {
    $hook = 'panels';
    $sid = 'display-'. $display->did .'-pane-'. $pane->pid;

    $style = array();
    // Get the Skinr classes for the current panel or display.
    if ($skinr = skinr_get(NULL, $hook, $sid)) {
      // Convert the array to a string fit for printing in the class attribute.
      $style = skinr_style_array_to_string($skinr);
    }
    if (!empty($content->css_class)) {
      $content->css_class .= ' '. $style;
    }
    else {
      $content->css_class = $style;
    }
  }
  return theme('panels_pane', $content, $pane, $display);
}

/**
 * Settings form callback.
 */
function panels_skinr_style_settings_form($settings, $panels_display = NULL, $pid = NULL, $type = NULL, &$form_state = array()) {
  // Return an empty form, and let skinr handle the rest.
  $form = array();
  return $form;
}
