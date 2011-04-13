<?php

/**
 * @file
 *   Contains form-related functions for the installation profile
 */

/**
 * Provide a form to choose which features to enable
 */
function drupal_commons_features_form($form_state, $url) {
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
    '#title' => st('User profiles'),
    '#default_value' => 1,
    '#description' => st('Allow users to have social profiles.'),
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
    '#title' => st('Invitations'),
    '#default_value' => 1,
    '#description' => st('Enable users to send invitations to join the site to external people.'),
  );
  $form['misc']['feature-commons_shoutbox'] = array(
    '#type' => 'checkbox',
    '#title' => st('Shoutbox'),
    '#default_value' => 1,
    '#description' => st('Provide a simple, micro-style chat for groups.'),
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
  variable_set('install_task', 'install-commons');
  
  // Redirect back to the installation page
  drupal_goto($form_state['values']['url']);
}
