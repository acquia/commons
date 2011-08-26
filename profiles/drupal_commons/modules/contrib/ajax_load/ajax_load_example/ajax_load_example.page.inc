<?php
// $Id: ajax_load_example.page.inc,v 1.1 2008/12/17 20:01:54 nedjo Exp $

/**
 * @file
 * Menu callbacks and associated methods for Ajax load example.
 */

/**
 * Menu callback: present a page with a link.
 */
function ajax_load_example_page() {
  // If this is an AJAX request, return the AJAX result.
  if (isset($_REQUEST['ajax_load_example']) && $_REQUEST['ajax_load_example']) {
    ajax_load_example_callback();
  }
  else {
    drupal_add_js(drupal_get_path('module', 'ajax_load_example') . '/ajax_load_example.js');
    return '<div>' . l(t('Load test form via AJAX'), 'ajax-load-example/callback', array('attributes' => array('class' => 'ajax-load-example'))) . '</div>';
  }
}

/**
 * Render a form in JSON.
 *
 * This function shows how to generate and alter an AJAX response to allow
 * ajax_load to add its functionality.
 */
function ajax_load_example_callback() {
  $result = array(
    'content' => drupal_get_form('ajax_load_example_form'),
    // Put the Javascript callback you will use here.
    // You can if you wish leave out this line and instead
    // call your callback directly in your Javascript. See 
    // comments in ajax_load_example.js.
    '__callbacks' => array('Drupal.AjaxLoadExample.formCallback'),
  );
  // Call drupal_alter('ajax_data', ...). This is what allows ajax_load to
  // add its data and register its Javascript callback.
  // The second argument is the data to be altered.
  // The third argument is a unique identifier for this AJAX data operation.
  // The fourth and optional argument is the original data that was the subject
  // of the ajax operation--in this case, a form ID.
  drupal_alter('ajax_data', $result, 'ajax_load_example', 'ajax_load_example_form');
  drupal_json($result);
}

/**
 * Generate a sample form.
 */
function ajax_load_example_form() {
  $form = array(
    '#prefix' => t('This form tests whether additional Javascript and CSS files were loaded via AJAX. Expected results: form has a grey border (via a new CSS instruction); form element Javascript is functional; the message "Ajax load example inline script called" appears below (via an inline script).'),
    '#suffix' => t('Submit button intentionally left out--nothing to submit.'),
  );
  // Add a sample inline script. This alert should be called after all scripts have
  // been added.
  drupal_add_js("$('#ajax-load-example-form').prepend('<p>" . t('Ajax load example inline script called.') . "</p>');", 'inline');
  drupal_add_css(drupal_get_path('module', 'ajax_load_example') . '/ajax_load_example.css');
  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sample collapsible fieldset'),
    '#collapsible' => TRUE,
  );
  $form['fieldset']['textarea'] = array(
    '#type' => 'textarea',
    '#title' => t('Sample expandable fieldset'),
  );
  $form['fieldset']['autocomplete'] = array(
    '#type' => 'textfield',
    '#autocomplete_path' => 'user/autocomplete',
    '#size' => '6',
    '#maxlength' => '7',
    '#title' => t('Sample user autocomplete'),
  );
  // Submit element intentionally omitted.
  return $form;
}

