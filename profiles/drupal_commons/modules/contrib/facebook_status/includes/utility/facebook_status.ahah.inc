<?php

/**
 * @file
 *   Utility functions for handling the AHAH callback for the status update form.
 */

/**
 * Saves statuses via AHAH.
 */
function facebook_status_save_js() {
  //Make sure we have form stuff available.
  module_load_include('inc', 'facebook_status', 'includes/utility/facebook_status.form');
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;
  $args = $form['#parameters'];
  //This happens if someone goes directly to the JS processing page.
  if (!is_array($args) && !$args) {
    watchdog('facebook_status', 'Someone tried to access the JavaScript processing page for Facebook-style Statuses directly.', array(), WATCHDOG_DEBUG);
    drupal_goto('user');
    return;
  }
  $form_id = array_shift($args);
  drupal_process_form($form_id, $form, $form_state);
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);
  //Get HTML for the replacement form. Only these elements will be AHAH-refreshed.
  $new_form['slider']      = $form['slider'];
  $new_form['fbss-status'] = $form['fbss-status'];
  $new_form['chars']       = $form['chars'];
  $new_form['fbss-submit'] = $form['fbss-submit'];
  $new_form['sdefault']    = $form['sdefault'];
  //Clear the status form after it's already been submitted once to prevent confusion.
  unset($new_form['status']['#default_value']);
  //Calls hook_facebook_status_form_ahah_alter(&$new_form, $form).
  drupal_alter('facebook_status_form_ahah', $new_form, $form);
  //If the $form['fbss-submit']['#ahah']['wrapper'] div was found in a #prefix or #suffix of a form element that we re-rendered here,
  //then we would have to unset() it to prevent duplicate wrappers. However, we have a somewhat unique implementation in which the wrappers
  //are actually their own elements, so this is not an issue.
  $output = theme('status_messages') . drupal_render($new_form);

  //Return the results.
  //The standard way is drupal_json(array('status' => TRUE, 'data' => $output));
  //However, this doesn't work with file uploading and re-attaching AHAH behaviors to form elements.
  //This version does work for these things.
  //From the AHAH Helper module, see http://drupal.org/node/331941
  //And from the Filefield module.
  $javascript = drupal_add_js(NULL, NULL, 'header');
  $GLOBALS['devel_shutdown'] = FALSE; //Still not really sure what the point of this is.
  echo drupal_to_js(array(
    'status' => TRUE,
    'data' => $output,
    'settings' => call_user_func_array('array_merge_recursive', $javascript['setting']),
  ));
  exit;
}
