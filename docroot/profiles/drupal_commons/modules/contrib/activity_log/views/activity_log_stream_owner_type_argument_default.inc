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
    $argument = $this->view->display[$this->view->current_display]->display_options['arguments']['stream_owner_type'];
    $form[$this->option_name] = array(
      '#type' => 'select',
      '#title' => t('Stream type'),
      '#description' => t('The type of entity on whose stream the activity is intended to appear.'),
      '#default_value' => isset($argument[$option_name]) ? $argument[$option_name] : 'user',
      '#options' => activity_log_get_rules_data_types(),
      '#required' => TRUE,
      '#process' => array('views_process_dependency'),
      '#dependency' => array(
        'radio:options[default_action]' => array('default'),
        'radio:options[default_argument_type]' => array($this->id)
      ),
      '#dependency_count' => 2,
    );
  }
  function get_argument() {
    if (!empty($this->argument->options[$this->option_name])) {
      return $this->argument->options[$this->option_name];
    }
  }
}
