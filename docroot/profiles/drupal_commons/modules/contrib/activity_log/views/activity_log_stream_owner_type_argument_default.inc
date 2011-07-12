<?php
  
/**
 * @file
 *   Adds an option to set the default argument from known stream owner types.
 */

/**
 * Provide a select box containing valid stream owner types.
 */
class activity_log_stream_owner_type_argument_default extends views_plugin_argument_default {
  var $option_name = 'default_argument_activity_log_stream_owner_type';
  function argument_form(&$form, &$form_state) {
    $form[$this->option_name] = array(
      '#type' => 'select',
      '#title' => t('Stream type'),
      '#description' => t('The type of entity on whose stream the activity is intended to appear.'),
      '#default_value' => $this->options['type'],
      '#options' => activity_log_get_rules_data_types(),
      '#required' => TRUE,
    );
  }
  function get_argument() {
    if (!empty($this->argument->options[$this->option_name])) {
      return $this->argument->options[$this->option_name];
    }
  }
}
