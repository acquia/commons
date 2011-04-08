<?php

/**
 * Theme the group features form
 */
function theme_og_features_feature_form($form) {
  $output = '';
  $headers = array();
  $rows = array();
  
  // Label the table headers
  $headers = array(
    t('Feature'),
    t('Enable'),
  );
  
  // Create a table row for each feature
  foreach ($form as $key => $field) {
    if (substr($key, 0, 8) == 'feature-') {
      $feature = substr($key, 8);
      $rows[] = array(
        '<div class="og-feature-name"><strong>' . drupal_render($form[$key]["name-$feature"]) . '</strong></div><div class="og-feature-description">' . drupal_render($form[$key]["description-$feature"]) . '</div>',
        drupal_render($form[$key]["toggle-$feature"])
      ); 
    }
  }
  
  $output .= theme('table', $headers, $rows, array('id' => 'og-features'));
  $output .= drupal_render($form);
  return $output;
}
