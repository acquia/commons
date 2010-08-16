<?php
// $Id: node.skinr.inc,v 1.3.2.1 2009/12/29 08:26:27 moonray Exp $
/**
 * @file
 * Provide skinr handling for node.module
 */

/**
 * @defgroup skinr_node_module node.module handlers
 *
 * @{
 */

/**
 * Implementation of hook_skinr_data().
 */
function node_skinr_data() {
  $data['node']['form']['node_type_form'] = array(
    'index_handler' => 'node_skinr_form_index_handler',
    'preprocess_hook' => 'node',
    'title' => t('node settings'),
  );
  $data['node']['preprocess']['node'] = array(
    'index_handler' => 'node_skinr_preprocess_index_handler',
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
function node_skinr_form_index_handler($op, &$form, $form_state) {
  switch ($op) {
    case 'form':
      return $form['#node_type']->type;

    case 'submit':
      // Clear old variable before we set a new one if the node type has changed
      if ($form_state['values']['old_type'] != $form_state['values']['type']) {
        foreach ($form_state['values']['skinr_settings']['node_group'] as $theme_name => $theme_data) {
          skinr_set($theme_name, 'comment', $form_state['values']['old_type'], '');
        }
      }
    return $form_state['values']['type'];
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
function node_skinr_preprocess_index_handler(&$vars) {
  return $vars['node']->type;
}

/**
 * @}
 */
