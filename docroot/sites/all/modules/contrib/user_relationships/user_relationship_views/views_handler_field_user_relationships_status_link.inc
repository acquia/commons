<?php
// $Id: views_handler_field_user_relationships_status_link.inc,v 1.1.2.1 2009/11/07 21:47:04 alexk Exp $

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
    if ($values->user_relationships_requestee_id === $user->uid) {
      //Remove the request.
      if ($values->user_relationships_approved) {
        return theme('user_relationships_remove_link', $values->user_relationships_requestee_id, $values->rid) ;
      }
      //Accept or decline the request.
      else {
        return
        theme('user_relationships_pending_request_approve_link', $values->user_relationships_requestee_id, $values->rid) .
        ' | '.
        theme('user_relationships_pending_request_disapprove_link', $values->user_relationships_requestee_id, $values->rid) ;
      }
    }
    //Requests by me.
    if ($values->user_relationships_requester_id === $user->uid) {
      if ($values->user_relationships_approved) {
        return theme('user_relationships_remove_link', $values->user_relationships_requester_id, $values->rid) ;
      }
      else {
        return theme('user_relationships_pending_request_cancel_link', $values->user_relationships_requester_id, $values->rid) ;
      }
    }
  }
}
