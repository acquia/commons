<?php // $Id: template.theme-js.inc,v 1.1.2.8 2010/03/27 05:27:12 jmburnz Exp $
// adaptivethemes.com 62

/**
 * @file template.theme-js.inc
 * Load Javascript files as required.
 */

$path_to_js_core = drupal_get_path('theme', 'adaptivetheme') .'/js/';

// Load equal height blocks
$regions = array(
  'leaderboard',
  'header', 
  'secondary-content',
  'content-top',
  'content-bottom',
  'tertiary-content',
  'footer'
);
foreach ($regions as $region) {
  $setting = theme_get_setting('equalize_'. $region);
  if ($setting == 1) {
    $active_regions[] = $region;
  }
}
if (!empty($active_regions)) {
  $active_regions_list = $active_regions;
  drupal_add_js(array('active_regions' => $active_regions_list), 'setting');
  drupal_add_js($path_to_js_core .'equalize-blocks.js', 'theme', 'header', FALSE, TRUE, TRUE);
}

// Load equal height sidebars
if (theme_get_setting('equal_heights_sidebars')) {
  drupal_add_js($path_to_js_core .'equalize-columns.js', 'theme', 'header', FALSE, TRUE, TRUE); 
}

// Load equal height gpanels
if (theme_get_setting('equal_heights_gpanels')) {
  drupal_add_js($path_to_js_core .'equalize-gpanels.js', 'theme', 'header', FALSE, TRUE, TRUE); 
}

// Use horizontal login block overlabel js
if (theme_get_setting('horizontal_login_block_overlabel')) {
  drupal_add_js($path_to_js_core .'jquery.overlabel.js', 'theme', 'header', FALSE, TRUE, TRUE);
}