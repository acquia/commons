<?php
// $Id: block.skinr.inc,v 1.3.2.1 2009/12/29 08:26:27 moonray Exp $
/**
 * @file
 * Provide skinr handling for block.module
 */

/**
 * @defgroup skinr_block_module block.module handlers
 *
 * @{
 */

/**
 * Implementation of hook_skinr_data().
 */
function block_skinr_data() {
  $data['block']['form']['block_admin_configure'] = array(
    'index_handler' => 'block_skinr_form_index_handler',
    'preprocess_hook' => 'block',
    'title' => t('block settings'),
    'skinr_weight' => 0,
    'collapsed' => FALSE,
  );
  $data['block']['form']['block_add_block_form'] = array(
    'index_handler' => 'block_skinr_form_index_handler',
    'preprocess_hook' => 'block',
    'title' => t('block settings'),
    'skinr_weight' => 0,
    'collapsed' => FALSE,
  );
  $data['block']['preprocess']['block'] = array(
    'index_handler' => 'block_skinr_preprocess_index_handler',
  );

  return $data;
}

/**
 * Skinr form index handler.
 *
 * @param $op
 *   What kind of action is being performed. Possible values:
 *   - "form": the form elements for Skinr are being inserted in a form
 *   - "submit": the form has been submitted.
 * @param &$form
 *   - For "form", passes in the $form parameter from hook_form_alter().
 *   - For "submit", passes in the $form parameter from hook_form_submit().
 * @param $form_state
 *   - For "form", passes in the $form_state parameter from hook_form_alter().
 *   - For "submit", passes in the $form_state parameter from hook_form_submit().
 * @return
 *   The index where we can find our values in Skinrs data structure.
 */
function block_skinr_form_index_handler($op, &$form, $form_state) {
  switch ($op) {
    case 'form':
      return $form['module']['#value'] .'-'. $form['delta']['#value'];

    case 'submit':
      $form_id = $form['form_id']['#value'];
      if ($form_id == 'block_add_block_form') {
        // This is a new block, so we need to fetch the delta from DB
        if ($delta = db_result(db_query("SELECT delta FROM {blocks} WHERE bid = '%s'", db_last_insert_id('boxes', 'bid')))) {
          return $form_state['values']['module'] .'-'. $delta;
        }
      }
      else {
        return $form_state['values']['module'] .'-'. $form_state['values']['delta'];
      }
  }
}

/**
 * Skinr preprocess index handler.
 *
 * @param &$vars
 *   Passes in the $vars parameter from module_preprocess().
 * @return
 *   The index where we can find our values in Skinrs data structure. If an
 *   array is returned, it will loop through each index in Skinr's data
 *   structure and merge the returned classes.
 */
function block_skinr_preprocess_index_handler(&$vars) {
  return $vars['block']->module .'-'. $vars['block']->delta;
}

/**
 * @}
 */
