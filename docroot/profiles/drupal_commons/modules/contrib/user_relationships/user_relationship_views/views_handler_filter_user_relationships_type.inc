<?php
// $Id: views_handler_filter_user_relationships_type.inc,v 1.1.2.3 2009/07/10 07:27:49 alexk Exp $

/**
 * @file
 * User Relationships Views integration.
 * Filter handler for relationship types, with autocomplete for type names. Modeled after views_handler_filter_user_name.
 * @author Alex Karshakevich http://drupal.org/user/183217
 */
class views_handler_filter_user_relationships_type extends views_handler_filter_in_operator {
  var $no_single = TRUE;

  function value_form(&$form, &$form_state) {
    $values = array();
    if ($this->value) {
      $result = db_query("SELECT * FROM {user_relationship_types} rt WHERE rtid IN (". implode(', ', $this->value) .")");
      while ($rtype = db_fetch_object($result)) {
        $values[] = $rtype->name;
      }
    }

    sort($values);
    $default_value = implode(', ', $values);
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Relationship types'),
      '#description' => t('Enter a comma separated list of types.'),
      '#default_value' => $default_value,
      //ajax callback is implemented in this module
      '#autocomplete_path' => 'admin/views/ajax/autocomplete/user_relationships_type',
    );
  }

  function value_validate(&$form, &$form_state) {
    $values = drupal_explode_tags($form_state['values']['options']['value']);
    $rtids = $this->validate_type_strings($form['value'], $values);

    if ($rtids) {
      $form_state['values']['options']['value'] = $rtids;
    }
  }

  function accept_exposed_input($input) {
    $rc = parent::accept_exposed_input($input);

    if ($rc) {
      // If we have previously validated input, override.
      if (isset($this->validated_exposed_input)) {
        $this->value = $this->validated_exposed_input;
      }
    }

    return $rc;
  }

  function exposed_validate(&$form, &$form_state) {
    if (empty($this->options['exposed'])) {
      return;
    }

    if (empty($this->options['expose']['identifier'])) {
      return;
    }

    $identifier = $this->options['expose']['identifier'];
    $values = drupal_explode_tags($form_state['values'][$identifier]);

    $rtids = $this->validate_type_strings($form[$identifier], $values);

    if ($rtids) {
      $this->validated_exposed_input = $rtids;
    }
  }

  /**
   * Validate the relationship type string. Since this can come from either the form
   * or the exposed filter, this is abstracted out a bit so it can
   * handle the multiple input sources.
   */
  function validate_type_strings(&$form, $values) {
    $rtids = array();
    $placeholders = array();
    $args = array();
    $results = array();
    foreach ($values as $value) {
      $missing[strtolower($value)] = TRUE;
      $args[] = $value;
      $placeholders[] = "'%s'";
    }

    if (!$args) {
      return $rtids;
    }

    $result = db_query("SELECT * FROM {user_relationship_types} WHERE name IN (". implode(', ', $placeholders) .")", $args);
    while ($rtype = db_fetch_object($result)) {
      unset($missing[strtolower($rtype->name)]);
      $rtids[] = $rtype->rtid;
    }

    if ($missing) {
      form_error($form, format_plural(count($missing), 'Unable to find relationship type: @types', 'Unable to find relationship types: @types', array('@types' => implode(', ', array_keys($missing)))));
    }

    return $rtids;
  }
  
  //Override to check that it's not adding IN ('') when filter is empty
  function query() {
    if (is_array($this->value)) {
      $values = implode('', $this->value);
      if (empty($values)) {
        return;
      }
    }
    parent::query();
  }

  // Override so that text names typed by user do not get stored as the value
  function value_submit() { }

  // Override to do nothing.
  function get_value_options() { }

  function admin_summary() {
    // set up $this->value_options for the parent summary
    $this->value_options = array();

    if ($this->value) {
      $result = db_query("SELECT * FROM {user_relationship_types} rt WHERE rtid IN (". implode(', ', $this->value) .")");

      while ($rtype = db_fetch_object($result)) {
        $this->value_options[$rtype->rtid] = $rtype->name;
      }
    }

    return parent::admin_summary();
  }
}
