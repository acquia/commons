<?php
// $Id: views_handler_filter_user_relationships_status.inc,v 1.1.2.1 2008/10/08 14:38:41 alexk Exp $

/**
 * @file
 * User Relationships Views integration.
 * Filter on value of approved column
 */
class views_handler_filter_user_relationships_status extends views_handler_filter_equality {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Status');
      $this->value_options = array('0' => t('pending'), '1' => t('approved'));
    }
  }

  function value_form(&$form, &$form_state) { 
    parent::value_form($form, $form_state); 
    // 0 won't work as a key for checkboxes.
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Status'),
      '#options' => array(t('Pending'), t('Approved')),
      '#default_value' => $this->value,
      '#multiple' => FALSE
    );
  }
}
