<?php

/**
 * @file
 *   Filters Activity Log Views by stream type.
 */

/**
 * Provide a select box containing valid stream owner types.
 */
class activity_log_views_handler_filter_owner_type extends views_handler_filter {
  function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Stream type'),
      '#description' => t('The type of entity on whose stream the activity is intended to appear.'),
      '#default_value' => $this->options['type'],
      '#options' => activity_log_get_rules_data_types(),
      '#required' => TRUE,
    );
  }
}
