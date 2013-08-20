<?php

/**
 * @file
 * Definition of views_handler_filter_boolean_operator_string.
 */

/**
 * Views filter that toggles between flagged and unflagged content.
 */
class commons_follow_user_follow_filter extends views_handler_filter_boolean_operator {

  function query() {
    foreach ($this->view->argument as $argument_name => $argument) {
      if ($argument->options['default_argument_type'] == 'commons_follow_node') {
        // The argument that toggles 'following' or 'not following' display.
        $this->view->argument[$argument_name]->options['not'] = !$this->value;
        break;
      }
    }
  }
}