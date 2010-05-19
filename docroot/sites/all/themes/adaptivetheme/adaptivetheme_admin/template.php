<?php // $Id: template.php,v 1.1.2.8 2009/12/24 01:47:01 jmburnz Exp $
// adaptivethemes.com admin

/**
 * @file template.php
 */

// Don't include custom functions if the database is inactive.
if (db_is_active()) {
  // Include base theme custom functions.
  include_once(drupal_get_path('theme', 'adaptivetheme') .'/inc/template.custom-functions.inc');
}

/**
 * Add the color scheme stylesheet if color_enable_schemes is set to 'on'.
 * Note: you must have at minimum a color-default.css stylesheet in /css/theme/
 */
if (theme_get_setting('color_enable_schemes') == 'on') {
  drupal_add_css(drupal_get_path('theme', 'adaptivetheme_admin') .'/css/theme/'. get_at_colors(), 'theme');
}

// Load collapsed js on blocks pages
if (arg(2) == 'block') {
  drupal_add_js('misc/collapse.js', 'core', 'header', FALSE, TRUE, TRUE);
}

/**
 * Override or insert variables into page templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called.
 */
function adaptivetheme_admin_preprocess_page(&$vars, $hook) {
  global $user;
  // Admin welcome message with date for the admin theme.
  if ($vars['logged_in']) {
    $welcome = t('Welcome') .' '. check_plain($user->name);
    $conjunction = ', '. t('it\'s') .' ';
    $todays_date = date("l, jS F, Y" , time());
    $vars['admin_welcome'] = $welcome . $conjunction . $todays_date;
  }
}
