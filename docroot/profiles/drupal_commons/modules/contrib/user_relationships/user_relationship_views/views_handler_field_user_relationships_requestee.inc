<?php
// $Id: views_handler_field_user_relationships_requestee.inc,v 1.1.2.1 2008/10/08 14:38:41 alexk Exp $

/**
 * @file
 * User Relationships Views integration.
 * Link to user profile of relationship requestee
 */
class views_handler_field_user_relationships_requestee extends views_handler_field_user_link {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'requestee_id';
  }
  
  function render($values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
    $uid = $values->{$this->aliases['requestee_id']};
    return l($text, "user/$uid");
  }
  
}
