<?php

/**
 * @file
 * Definition of views_handler_filter_boolean_operator_string.
 */

/**
 * Views filter that toggles between flagged and unflagged content.
 */
class commons_follow_user_follow_filter_message extends views_handler_filter_boolean_operator {

  function query() {
    // The argument that toggles 'following' or 'not following' display.
    if ($this->value == 0) {
      foreach ($this->view->argument as $argument_name => $argument) {
        if ($argument->options['default_argument_type'] == 'commons_follow_message') {
          $this->view->argument[$argument_name]->options['not'] = !$this->value;
        }
      }
    }
  }
}
