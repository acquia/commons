<?php
/**
 * Argument handler to accept the first part of a string and complete the rest. See views_handler_filter_string.
 */
class notifications_views_handler_argument_autocomplete extends views_handler_argument {
  function query() {
    $this->ensure_my_table();
    $this->query->add_where(0, "$this->table_alias.$this->real_field LIKE '%s%%'", $this->argument);
  }

  function default_actions($which = NULL) {
    $defaults = array(
      'ignore' => array(
        'title' => t('Display all values'),
        'method' => 'default_ignore',
        'breadcrumb' => TRUE, // generate a breadcrumb to here
      ),
      'not found' => array(
        'title' => t('Hide view / Page not found (404)'),
        'method' => 'default_not_found',
        'hard fail' => TRUE, // This is a hard fail condition
      ),
      'empty' => array(
        'title' => t('Display empty text'),
        'method' => 'default_empty',
        'breadcrumb' => TRUE, // generate a breadcrumb to here
      ),
      'default' => array(
        'title' => t('Provide default argument'),
        'method' => 'default_default',
        'form method' => 'default_argument_form',
        'has default argument' => TRUE,
        'default only' => TRUE, // this can only be used for missing argument, not validation failure
      ),
    );

    if ($which) {
      if (!empty($defaults[$which])) {
        return $defaults[$which];
      }
    }
    else {
      return $defaults;
    }
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $options['wildcard'] = array('default' => '*');
  }
}
