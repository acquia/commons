<?php

/**
 * @file
 *   Filters Activity Log Views by display type.
 */

/**
 * Provide a select box containing valid display types.
 */
class activity_log_views_handler_filter_display_type extends views_handler_filter {
  function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Display type'),
      '#description' => t('The location where the activity messages will be displayed.'),
      '#default_value' => isset($this->value) ? $this->value : 'web',
      '#options' => module_invoke_all('activity_log_display_types'),
      '#required' => TRUE,
    );
  }
}
