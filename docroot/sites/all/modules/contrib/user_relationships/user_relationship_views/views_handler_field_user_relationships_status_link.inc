<?php
// $Id: views_handler_field_user_relationships_status_link.inc,v 1.1.2.2 2010/01/02 12:42:01 alexk Exp $

/**
 * @file
 * User Relationships Views integration.
 * Show colum with link to change approval status.
 */
class views_handler_field_user_relationships_status_link extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['requestee_id'] = 'requestee_id';
    $this->additional_fields['requester_id'] = 'requester_id';
    $this->additional_fields['rid']          = 'rid';
    $this->additional_fields['approved']     = 'approved';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    global $user;

    //Do not show to guests or users witout permission to have relationships.
    if (!$user->uid && user_access('can have relationships')) {
      return;
    }

    //Requests for me to add or remove.
    if ($values->{$this->aliases['requestee_id']} === $user->uid) {
      //Remove the request.
      if ($values->{$this->aliases['approved']}) {
        return theme('user_relationships_remove_link', $values->{$this->aliases['requestee_id']}, $values->{$this->aliases['rid']}) ;
      }
      //Accept or decline the request.
      else {
        return
        theme('user_relationships_pending_request_approve_link', $values->{$this->aliases['requestee_id']}, $values->{$this->aliases['rid']}) .
        ' | '.
        theme('user_relationships_pending_request_disapprove_link', $values->{$this->aliases['requestee_id']}, $values->{$this->aliases['rid']}) ;
      }
    }
    //Requests by me.
    if ($values->{$this->aliases['requester_id']} === $user->uid) {
      if ($values->{$this->aliases['approved']}) {
        return theme('user_relationships_remove_link', $values->{$this->aliases['requester_id']}, $values->{$this->aliases['rid']}) ;
      }
      else {
        return theme('user_relationships_pending_request_cancel_link', $values->{$this->aliases['requester_id']}, $values->{$this->aliases['rid']}) ;
      }
    }
  }
}
