<?php
/**
 * @file
 * Enables modules and site configuration for a Commons site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function commons_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

/**
 * Implements hook_install_tasks().
 *
 * Allows the user to set a welcome message for anonymous users
 */
function commons_install_tasks() {

  return array(
    'commons_anonymous_message_homepage' => array(
      'display_name' => st('Enter Homepage welcome text'),
      'display' => TRUE,
      'type' => 'form',
      'function' => 'commons_anonymous_welcome_text_form'
    ),
    'commons_revert_features' => array(
      'display' => FALSE,
    ),
  );
}

/*
 * Revert Features after the installation.
 */
function commons_revert_features() {
  // These features must be twice in a row in order to
  // fully revert.
  $i = 0;
  while ($i < 2 ) {
   // Revert Features components to ensure that they are in their default states.
    $revert = array(
      'commons_groups' => array('field_instance'),
      'commons_wikis' => array('og_features_permission'),
    );
    features_revert($revert);
    $i++;
  }

}
/**
 * Configuration form to set welcome text for the anonymous site homepage.
 */
function commons_anonymous_welcome_text_form() {
  $form['commons_anonymous_welcome_explanation'] = array(
    '#markup' => '<h2>' . st('Homepage welcome text') . '</h2>' . st("Below, enter text that will be shown on your community's homeage to help new visitors understand what your community is about and why they should join. The image below shows an example of how this text will appear. You can always change this text later."),
    '#weight' => -1,
  );
  $form['commons_anonymous_welcome_example'] = array(
    '#markup' => theme('image', array('path' => 'profiles/commons/images/commons_homepage_text_example.png', 'alt' => 'Home page example', 'alt' => 'Home page example')),
    '#weight' => 0,
  );

  $form['commons_anonymous_welcome_title'] = array(
    '#type' => 'textfield',
    '#title' => st('Welcome headline'),
    '#description' => st('A short description of the community that visitors can understand at a glance.'),
    '#required' => TRUE,
  );

  $form['commons_anonymous_welcome_body'] = array(
    '#type' => 'textarea',
    '#title' => st('Welcome body text'),
    '#description' => st('Enter a couple of sentences elborating about your community.'),
    '#required' => TRUE,
  );

  $form['commons_anonymous_welcome_submit'] = array(
    '#type'  => 'submit',
    '#value' => st('Save and continue')
  );


  return $form;
}

/**
 * Save the configuration form for set welcome text for anonymous users
 * @see commons_anonymous_welcome_text_form()
 */
function commons_anonymous_welcome_text_form_submit($form_id, &$form_state) {
  variable_set('commons_anonymous_welcome_title', $form_state['values']['commons_anonymous_welcome_title']);
  variable_set('commons_anonymous_welcome_body', $form_state['values']['commons_anonymous_welcome_body']);
}
