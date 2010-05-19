<?php // $Id: theme-settings.php,v 1.1.2.2 2009/10/24 10:54:31 jmburnz Exp $
// adaptivethemes.com admin

/**
 * @file theme-settings.php
 */

// Include the definition of adaptivetheme_settings() and adaptivetheme_theme_get_default_settings().
include_once(drupal_get_path('theme', 'adaptivetheme') .'/theme-settings.php');

/**
* Implementation of themehook_settings() function.
*
* @param $saved_settings
*   An array of saved settings for this theme.
* @return
*   A form array.
*/
function adaptivetheme_admin_settings($saved_settings) {
  
  // Get the default values from the .info file.
  $defaults = adaptivetheme_theme_get_default_settings('adaptivetheme_admin');
    
  // Merge the saved variables and their default values.
  $settings = array_merge($defaults, $saved_settings);

  /*
   * Create the form using Forms API: http://api.drupal.org/api/6
   */
  $form = array();
  // Color schemes
  if ($settings['color_enable_schemes'] == 'on') {
    $form['color'] = array(
      '#type' => 'fieldset',
      '#title' => t('Color settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 90,
      '#description'   => t('Use these settings to customize the colors of your site. If no stylesheet is selected the default colors will apply.'),
    );
    $form['color']['color_schemes'] = array(
      '#type' => 'select',
      '#title' => t('Color Schemes'),
      '#default_value' => $settings['color_schemes'],
      '#options' => array(
        'colors-default.css' => t('Onyx'),
        'ruby.css' => t('Ruby'),
        'saphire.css' => t('Saphire'),
        'amber.css' => t('Amber'),
        'emerald.css' => t('Emerald'),
      ),
    );
    $form['color']['color_enable_schemes'] = array(
      '#type'    => 'hidden',
      '#value'   => $settings['color_enable_schemes'],
    ); 
  } // endif color schemes

  // Add the base theme's settings.
  $form += adaptivetheme_settings($saved_settings, $defaults);

  // Return the form
  return $form;
}
  