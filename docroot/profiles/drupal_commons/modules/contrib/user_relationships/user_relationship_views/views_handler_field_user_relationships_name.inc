<?php
// $Id: views_handler_field_user_relationships_name.inc,v 1.1.2.1 2008/10/08 14:38:41 alexk Exp $

/**
 * @file
 * User Relationships Views integration.
 * Map RTID to relationship name
 */
class views_handler_field_user_relationships_name extends views_handler_field {
  function construct() {
    parent::construct();
    //just preload all relationships {rtid}->{relationship object}
    $this->rel_names = user_relationships_types_load();
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $options['name_field'] = array('default' => 'name');
    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['name_field'] = array(
      '#type' => 'radios',
      '#title' => t('Singular/Plural'),
      '#default_value' => $this->options['name_field'],
      '#options' => array('name' => t('Singular name'), 'plural_name' => t('Plural name')),
    );
  }
  
  function render($values) {
    $name = $this->rel_names[parent::render($values)]->{$this->options['name_field']};
    //sanity check, return rtid if no name
    $name = $name ? $name : parent::render($values);
    return $name;
  }
}
