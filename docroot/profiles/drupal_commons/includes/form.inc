<?php

/**
 * @file
 *   Contains form-related functions for the installation profile
 */

/**
 * Provide a form to choose which features to enable
 */
function drupal_commons_features_form(&$form_state, $url) {
  $form = array();
  drupal_set_title(st('Choose from available features'));
  
  // Homebox, which is included in the Commons dashboard feature
  // requires PHP 5.2, so we need to check that to avoid allowing
  // the user to install it
  module_load_include('module', 'homebox');
  $php5_2 = _homebox_check_php();
  
  // Help message
  $form['message'] = array(
    '#type' => 'item',
    '#value' => st('The selected features will be enabled after the installation has completed. At any time, you can turn the available features on or off.'),
  );
  
  // Required features
  $form['required'] = array(
    '#type' => 'fieldset',
    '#title' => st('Required'),
    '#description' => t('These features are required for Drupal Commons to operate.'),
  );
  $form['required']['feature-commons_core'] = array(
    '#type' => 'checkbox',
    '#title' => st('Core'),
    '#default_value' => 1,
    '#disabled' => 1,
    '#required' => TRUE,
    '#value' => 1,
    '#description' => st('Provides the essential components for Drupal Commons'),
  );
  $form['required']['feature-commons_home'] = array(
    '#type' => 'checkbox',
    '#title' => st('Home page'),
    '#default_value' => 1,
    '#disabled' => 1,
    '#required' => TRUE,
    '#value' => 1,
    '#description' => st('Provides a community-driven home page.'),
  );
  
  // Content-related features
  $form['content'] = array(
    '#type' => 'fieldset',
    '#title' => st('Content'),
    '#description' => t('Select which content types you wish Drupal Commons to make available to members of Drupal Commons groups. Note: If you de-select any of these, you can always enable them again after installation.'),
  );
  $form['content']['feature-commons_blog'] = array(
    '#type' => 'checkbox',
    '#title' => st('Blogs'),
    '#default_value' => 1,
    '#description' => t('Used by individuals to create personal blog posts within a group.'),
  );
  $form['content']['feature-commons_discussion'] = array(
    '#type' => 'checkbox',
    '#title' => st('Discussions'),
    '#default_value' => 1,
    '#description' => st('Used to create threaded topical discussions within a group.'),
  );
  $form['content']['feature-commons_document'] = array(
    '#type' => 'checkbox',
    '#title' => st('Documents'),
    '#default_value' => 1,
    '#description' => st('Used as a container for attaching documents, images, and other digital files useful to a group.'),
  );
  $form['content']['feature-commons_wiki'] = array(
    '#type' => 'checkbox',
    '#title' => st('Wikis'),
    '#default_value' => 1,
    '#description' => st('A type of page that is editable by all members in a group (vs. editable only its original author).'),
  );
  $form['content']['feature-commons_poll'] = array(
    '#type' => 'checkbox',
    '#title' => st('Polls'),
    '#default_value' => 1,
    '#description' => st('Used to create polls within a group.'),
  );
  $form['content']['feature-commons_event'] = array(
    '#type' => 'checkbox',
    '#title' => st('Events & calendars'),
    '#default_value' => 1,
    '#description' => st('Used to create an event calendar for a group.'),
  );
  
  // Misc features
  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => st('Other functions'),
    '#description' => st('Select which functions you wish to provide in Drupal Commons. Again, if you de-select any of these, you can enable them again after installation.'),
  );
  $form['misc']['feature-commons_profile'] = array(
    '#type' => 'checkbox',
    '#title' => st('Social profiles'),
    '#default_value' => 1,
    '#description' => st('A feature that extends Drupal\'s simple profiles to include a variety of additional profile fields useful for community sites, plus various important user listings. (Strongly recommended.)'),
  );
  $form['misc']['feature-commons_dashboard'] = array(
    '#type' => 'checkbox',
    '#title' => st('Dashboard'),
    '#default_value' => $php5_2 ? 1 : 0,
    '#disabled' => !$php5_2,
    '#description' => st('A feature that provides a unique-per-user, user-customizable dashboard of recent relevant site activity.'),
  );
  if (!$php5_2) {
    $form['misc']['feature-commons_dashboard']['#value'] = 0;
    $form['misc']['feature-commons_dashboard']['#description'] .= '<span style="color:red;"> ' . st('Your server must have PHP 5.2 or higher in order to active this feature.') . '</span>';
  }
  $form['misc']['feature-commons_notifications'] = array(
    '#type' => 'checkbox',
    '#title' => st('Notifications'),
    '#default_value' => 1,
    '#description' => st('A feature that allows users to subscribe to email & site-based notifications of site activity & new content.'),
  );
  $form['misc']['feature-commons_reputation'] = array(
    '#type' => 'checkbox',
    '#title' => st('User awards'),
    '#default_value' => 1,
    '#description' => st('Award users points and badges for performing community-related actions.'),
  );
  $form['misc']['feature-commons_invite'] = array(
    '#type' => 'checkbox',
    '#title' => st('Community invitations'),
    '#default_value' => 1,
    '#description' => st('Enable users to send invitations to join the site to external people.'),
  );
  $form['misc']['feature-commons_shoutbox'] = array(
    '#type' => 'checkbox',
    '#title' => st('Shoutbox'),
    '#default_value' => 1,
    '#description' => st('A feature that lets users post short messages to each other, with (almost) live updates to other users. If enabled, this is provided on group home pages for group users.'),
  );
  $form['misc']['feature-commons_group_aggregator'] = array(
    '#type' => 'checkbox',
    '#title' => st('Content aggregator'),
    '#default_value' => 1,
    '#description' => st('Provides a way for group administrators to pull RSS content into a group from other sources.'),
  );
  $form['misc']['feature-commons_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Admin assist'),
    '#default_value' => 1,
    '#description' => st('Bundles a variety of administrative interface tools in one place. (Bundled as a single feature so administrators who wish to use alternate admin interface tools can turn off the defaults easily.).'),
  );
  $form['misc']['feature-commons_seo'] = array(
    '#type' => 'checkbox',
    '#title' => st('SEO'),
    '#default_value' => 1,
    '#description' => st('Bundles all SEO-oriented capabilities in a module separate from Drupal Commons Core (for ease of administration).'),
  );
  
  // Acquia features
  $form['acquia'] = array(
    '#type' => 'fieldset',
    '#title' => st('Acquia'),
    '#description' => st('The !an can supplement the functionality of Drupal Commons by providing enhanced site search (faceted search, content recommendations, content biasing, multi-site search, and others using the Apache Solr service), spam protection (using the Mollom service), and more.  A free 30-day trial is available.', array('!an' => l(t('Acquia Network'), 'http://acquia.com/products-services/acquia-network', array('attributes' => array('target' => '_blank'))))),
  );
  $form['acquia']['feature-acquia_network_subscription'] = array(
    '#type' => 'checkbox',
    '#title' => st('Acquia Network'),
    '#default_value' => 0,
    '#description' => st('Select this either if you wish to try a free trial of the Acquia Network or want to enter the keys for your existing Acquia Network subscription.'),
  );
  
  // Redirect URL to remain inside the installation after submission
  $form['url'] = array(
    '#type' => 'value',
    '#value' => $url,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Continue'),
  );
  
  return $form;
}

/**
 * Submit handler for the feature choice form
 */
function drupal_commons_features_form_submit(&$form, &$form_state) {
  // Build an array of chosen features
  $features = array();
  
  // Extract the selected features from the form
  foreach ($form_state['values'] as $key => $value) {
    if (substr($key, 0, 8) == 'feature-') {
      if ($value == 1) {
        $features[] = substr($key, 8);
      }
    }
  }
  
  // Store a temporary variable to access later
  variable_set('commons_selected_features', $features);
  
  // Initiate the next installation step
  variable_set('install_task', 'configure-theme');
  
  // Redirect back to the installation page
  if (isset($form_state['values']['url'])) {
    drupal_goto($form_state['values']['url']);
  }
}

/**
 * Provide a form to choose the default theme
 */
function drupal_commons_theme_form(&$form_state, $url) {
  $form = array();
  drupal_set_title(st('Choose your default theme'));
  
  // Help message
  $form['message'] = array(
    '#type' => 'item',
    '#value' => st('Choose the initial theme for your site. At any time after the installation, the theme can be changed.'),
  );
  
  // Theme selector
  $form['theme'] = array(
    '#type' => 'radios',
    '#options' => array(
      'commons_origins' => _drupal_commons_theme_option('commons_origins', st('Commons Origins')),
      'commons_connect' => _drupal_commons_theme_option('commons_connect', st('Commons Connect')),
      'commons_environs' => _drupal_commons_theme_option('commons_environs', st('Commons Environs')),
    ),
    '#default_value' => DRUPAL_COMMONS_DEFAULT_THEME,
  );
  
  // Submit button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Continue'),
  );
  
  // Store the installation url for redirection post-submit
  $form['url'] = array(
    '#type' => 'value',
    '#value' => $url,
  );
  
  return $form; 
}

/**
 * Submit handler for the theme form
 */
function drupal_commons_theme_form_submit(&$form, &$form_state) {
  $sql = "UPDATE {system} SET status = %d WHERE type = 'theme' and name = '%s'";
  
  // Disable garland
  db_query($sql, 0, 'garland');
  
  // Enable Fusion
  db_query($sql, 1, 'fusion_core');
  
  // Enable Commons Roots
  db_query($sql, 1, 'commons_roots');
  
  // Enable all of the available themes
  foreach ($form['theme']['#options'] as $theme => $label) {
    db_query($sql, 1, $theme);
  }
  
  // Set the selected theme as the default
  variable_set('theme_default', $form_state['values']['theme']);
  
  // Refresh the theme registry registry
  list_themes(TRUE);
  drupal_rebuild_theme_registry();

  // Initiate the next installation step
  variable_set('install_task', 'install-commons');
  
  // Redirect back to the installation page
  if (isset($form_state['values']['url'])) {
    drupal_goto($form_state['values']['url']);
  }
}

/**
 * Format a theme selection option
 * 
 * @param $theme
 *   The theme system name
 * @param $name
 *   The theme full name
 * @return
 *   An HTML string to be used as a theme form option
 */
function _drupal_commons_theme_option($theme, $name) {
  $option = '';
  $option .= "<strong>{$name}</strong>";
  $option .= "<br/>";
  $option .= "<img alt=\"{$name}\" title=\"{$name}\" src=\"./profiles/drupal_commons/themes/{$theme}/screenshot.png\"></img>";
  $option .= "<br/>";
  $option .= "<ul><li><i><a href=\"./profiles/drupal_commons/themes/{$theme}/screenshot_full.png\" target=\"_blank\">" . st('Click to view fullsize') . "</a></i></li></ul>";
  $option .= "<br/>";
  return $option;
}
