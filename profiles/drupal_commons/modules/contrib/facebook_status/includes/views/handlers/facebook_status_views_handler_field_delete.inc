<?php

/**
 * @file
 *   Provides an edit link to Views.
 */

/**
 * Field handler to add a field with an edit link.
 */
class facebook_status_views_handler_field_delete extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['sender'] = 'sender';
    $this->additional_fields['recipient'] = 'recipient';
    $this->additional_fields['type'] = 'type';
  }
  function render($values) {
    $status = new stdClass();
    $status->sender = $values->{$this->aliases['sender']};
    $status->recipient = $values->{$this->aliases['recipient']};
    $status->type = $values->{$this->aliases['type']};
    $status->sid = $values->{$this->field_alias};
    if (facebook_status_user_access('delete', $status)) {
      if (module_exists('modalframe')) {
        modalframe_parent_js();
      }
      drupal_add_css(drupal_get_path('module', 'facebook_status') .'/resources/facebook_status.css');
      $q = $_GET['q'];
      if ($q == 'facebook_status/js') {
        $q = 'user';
      }
      return '<span class="facebook-status-delete">'. l(t('Delete'), 'statuses/'. $status->sid .'/delete', array('query' => array('destination' => $q))) .'</span>';
    }
  }
}
