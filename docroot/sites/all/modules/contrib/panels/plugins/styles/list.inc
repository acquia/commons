<?php
// $Id: list.inc,v 1.1.2.2 2010/01/13 06:25:15 merlinofchaos Exp $


/**
 * @file
 * Definition of the 'list' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('List'),
  'description' => t('Presents the panes in the form of an HTML list.'),
  'render panel' => 'panels_list_style_render_panel',
  'settings form' => 'panels_list_style_settings_form',
  'settings validate' => 'panels_list_style_settings_validate',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_list_style_render_panel($display, $panel_id, $panes, $settings) {
  $items = array();

  foreach ($panes as $pane_id => $content) {
    $item = panels_render_pane($content, $display->content[$pane_id], $display);
    if (isset($item)) {
      $items[] = $item;
    }
  }

  if (empty($settings['list_type'])) {
    $settings['list_type'] = 'ul';
  }

  return theme('item_list', $items, NULL, $settings['list_type']);
}

/**
 * Settings form callback.
 */
function panels_list_style_settings_form($style_settings) {
  $form['list_type'] = array(
    '#type' => 'select',
    '#title' => t('List type'),
    '#options' => array(
      'ul' => t('Unordered'),
      'ol' => t('Ordered'),
    ),
    '#default_value' => (isset($style_settings['list_type'])) ? $style_settings['list_type'] : 'ul',
  );

  return $form;
}

