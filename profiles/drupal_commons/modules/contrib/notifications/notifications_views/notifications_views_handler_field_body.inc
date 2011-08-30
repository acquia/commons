<?php
// $Id: notifications_views_handler_field_body.inc,v 1.1.2.1 2009/02/20 18:43:18 jareyero Exp $

/**
 * Field handler
 */
class notifications_views_handler_field_body extends views_handler_field {
  function render($values) {
    $method_info = messaging_method_info('simple');
    $value = $values->{$this->field_alias};
    
    // The filter is applied now only once
    if ($method_info['filter']) {
      return check_markup($value, $filter, FALSE);
    }

    return check_plain($value);
  }
}

