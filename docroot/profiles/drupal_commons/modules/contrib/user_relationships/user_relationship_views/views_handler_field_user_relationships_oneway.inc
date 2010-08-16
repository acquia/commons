<?php
// $Id: views_handler_field_user_relationships_oneway.inc,v 1.1.2.1 2008/10/08 14:38:41 alexk Exp $

/**
 * @file
 * User Relationships Views integration.
 * Map type column to a text label
 */
class views_handler_field_user_relationships_oneway extends views_handler_field {
  function construct() {
    parent::construct();
    $this->status_map = array('0' => t('mutual'), '1' => t('one way'));
  }
  
  function render($values) {
    return $this->status_map[$values->{$this->field_alias}];
  }
}
