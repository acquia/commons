<?php
// $Id: realname_handler_field_user_name.inc,v 1.1.2.2 2009/04/22 00:44:47 nancyw Exp $

/**
 * @file
 * The RealName module allows the admin to choose fields from the user profile
 * that will be used to add a "realname" element (method) to a user object.
 */


/**
 * Field handler for realnames
 */
class realname_handler_field_user_name extends views_handler_field_user_name {
  function init(&$view, &$data) {
    parent::init($view, $data);
    $this->additional_fields['realname'] = 'realname';
  }
  
  function render_link($data, $values) {
    if (!empty($this->options['link_to_user']) || !empty($this->options['overwrite_anonymous'])) {
      $account = new stdClass();
      $account->uid = $values->{$this->aliases['uid']};
      if (!empty($this->options['overwrite_anonymous']) && !$account->uid) {
        // This is an anonymous user, and we're overriting the text.
        return check_plain($this->options['anonymous_text']);
      }
      elseif (!empty($this->options['link_to_user'])) {
        $account->name = $values->{$this->field_alias};
        return theme('username', $account);
      }
    }
    // Otherwise, there's no special handling, so return the data directly.
    return $values->{$this->aliases['realname']};
  }

}
