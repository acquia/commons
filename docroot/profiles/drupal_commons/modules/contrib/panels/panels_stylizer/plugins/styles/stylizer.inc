<?php
// $Id: stylizer.inc,v 1.1.2.2 2010/02/17 01:49:23 merlinofchaos Exp $

/**
 * @file
 * Definition of the 'stylizer' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('Stylizer'),
  'description' => t('Allows choice of a stylizer style'),

  'render pane' => 'panels_stylizer_stylizer_style_render_pane',
  'pane settings form' => 'panels_stylizer_stylizer_style_pane_settings_form',

  'render panel' => 'panels_stylizer_stylizer_style_render_region',
  'settings form' => 'panels_stylizer_stylizer_style_region_settings_form',

//  'settings validate' => 'panels_stylizer_stylizer_style_settings_validate',
);

/**
 * Region render theme.
 */
function theme_panels_stylizer_stylizer_style_render_region($display, $panel_id, $panes, $style_settings) {
  $output = '';

  foreach ($panes as $pane_id => $content) {
    $output .= panels_render_pane($content, $display->content[$pane_id], $display);
  }

  if ($style_settings['style'] == '$') {
    $settings = $style_settings['settings'];
  }
  else {
    $style = panels_stylizer_load($style_settings['style']);
    if ($style) {
      $settings = $style->settings;
    }
  }

  if (!empty($settings)) {
    ctools_include('stylizer');
    $plugin = ctools_get_style_base($settings['style_base']);
    ctools_stylizer_add_css($plugin, $settings);

    return theme($plugin['theme'], $settings, ctools_stylizer_get_css_class($plugin, $settings), $output);
  }
  else {
    // if the style is gone, just display the output.
    return $output;
  }
}

/**
 * Pane render theme
 */
function theme_panels_stylizer_stylizer_style_render_pane($content, $pane, $display) {
  $style_settings = $pane->style['settings'];

  if ($style_settings['style'] == '$') {
    $settings = $style_settings['settings'];
  }
  else {
    $style = panels_stylizer_load($style_settings['style']);
    if ($style) {
      $settings = $style->settings;
    }
  }

  if ($settings) {
    ctools_include('stylizer');
    $plugin = ctools_get_style_base($settings['style_base']);

    if (empty($content->css_class)) {
      $content->css_class = '';
    }
    $content->css_class .= ctools_stylizer_get_css_class($plugin, $settings);
    ctools_stylizer_add_css($plugin, $settings);

    if (isset($plugin['theme'])) {
      return theme($plugin['theme'], $settings, $content, $pane, $display);
    }
  }

  // if the style is gone or has no theme of its own, just display the output.
  return theme('panels_pane', $content, $pane, $display);
}

function panels_stylizer_stylizer_style_region_settings_form($style_settings) {
  return panels_stylizer_stylizer_style_settings_form($style_settings, 'region');
}

function panels_stylizer_stylizer_style_pane_settings_form($style_settings) {
  return panels_stylizer_stylizer_style_settings_form($style_settings, 'pane');
}

/**
 * Settings form callback.
 */
function panels_stylizer_stylizer_style_settings_form($style_settings, $style_type = 'region') {
  $type = arg(3);
  $cache_key = arg(4);
  $pid = arg(5);
  if (!empty($style_settings['style']) && $style_settings['style'] == '$') {
    module_load_include('inc', 'panels_stylizer', 'panels_stylizer.admin');
    $cache = panels_edit_cache_load($cache_key);
    panels_stylizer_pane_add_style($type, $cache, $pid, 'settings');
  }

  ctools_include('stylizer');
  $plugins = ctools_get_style_bases();
  $styles = panels_stylizer_load_all();

  $options = array('' => t('- None selected -'));

  foreach ($styles as $name => $style) {
    if (empty($plugins[$style->settings['style_base']])) {
      continue;
    }

    $plugin = $plugins[$style->settings['style_base']];
    if ($plugin['type'] == $style_type) {
      $options[$name] = $style->admin_title;
    }
  }

  $form['style'] = array(
    '#type' => 'select',
    '#title' => t('Select a preconfigured style'),
    '#options' => $options,
    '#default_value' => (isset($style_settings['style'])) ? $style_settings['style'] : '',
  );

  // I really hate to do this, but the style system does not actually send all
  // of the data necessary to do this through. It's one of the older plugins and
  // its form treatment goes all the way back to 4.7 and hasn't changed much.

  $path = 'admin/build/panels/style/pane-style/' . arg(3) . '/' . arg(4) . '/' . arg(5);
  $form['new'] = array(
    '#value' => '<div>' . l(t('Or create a custom style...'), $path, array('attributes' => array('class' => 'ctools-use-ajax'))) . '</div>',
  );

  return $form;
}

