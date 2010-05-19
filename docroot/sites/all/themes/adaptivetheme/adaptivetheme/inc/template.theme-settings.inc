<?php
// $Id: template.theme-settings.inc,v 1.1.2.4 2009/12/24 01:47:01 jmburnz Exp $
// adaptivethemes.com

/**
 * @file template.theme-settings.inc
 */

/**
 * Return the default values from the info file
 * and save them into the database. The theme settings functions
 * code mostly comes from the Zen theme, whose inplimentation
 * for subthemes is superb.
 *
 * @param $theme
 *   The name of theme.
 */
function adaptivetheme_theme_get_default_settings($theme) {
  $themes = list_themes();

  // Get the default values from the .info file.
  $defaults = !empty($themes[$theme]->info['settings']) ? $themes[$theme]->info['settings'] : array();

  if (!empty($defaults)) {
    // Get the theme settings saved in the database.
    $settings = theme_get_settings($theme);
    // Don't save the toggle_node_info_ variables.
    if (module_exists('node')) {
      foreach (node_get_types() as $type => $name) {
        unset($settings['toggle_node_info_'. $type]);
      }
    }
    // Save default theme settings.
    variable_set(
      str_replace('/', '_', 'theme_'. $theme .'_settings'),
      array_merge($defaults, $settings)
    );
    // If the active theme has been loaded, force refresh of Drupal internals.
    if (!empty($GLOBALS['theme_key'])) {
      theme_get_setting('', TRUE);
    }
  }

  // Return the default settings.
  return $defaults;
}