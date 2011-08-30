<?php

/**
 * @file
 */

/**
 * Implementation of hook_views_data().
 */
function invite_views_views_data() {
  /* 'invite' table */
  $data['invite']['table']['group'] = 'Invite';
  $data['invite']['table']['base'] = array(
    'field' => 'iid',
    'title' => t('Invite'),
    'help' => t('The base table for invites.'),
  );
  /* fields */
  /* 'iid' field */
  $data['invite']['iid'] = array(
    'title' => t('Iid'),
    'help' => t('The invite ID.'),
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'format' => FILTER_FORMAT_DEFAULT,
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  /* 'reg_code' field */
  $data['invite']['reg_code'] = array(
    'title' => t('Registration code'),
    'help' => t('Issued registration code and acts as primary identifier for a invite.'),
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'format' => FILTER_FORMAT_DEFAULT,
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  /* 'email' field */
  $data['invite']['email'] = array(
    'title' => t('Invite email adress'),
    'help' => t('E-mail the invite has been addressed to.'),
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'format' => FILTER_FORMAT_DEFAULT,
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  /* 'uid' field */
  $data['invite']['uid'] = array(
    'title' => t('Invite owner user ID'),
    'help' => t('User ID of the inviter.'),
    'relationship' => array(
      'label' => t('Invite owner UID'),
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
    ),
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'format' => FILTER_FORMAT_DEFAULT,
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  /* 'invitee' field */
  $data['invite']['invitee'] = array(
    'title' => t('Invite registration user ID'),
    'help' => t('User ID of the invite upon registration.'),
    'relationship' => array(
      'label' => t('Invite registration UID'),
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
    ),
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'format' => FILTER_FORMAT_DEFAULT,
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  /* 'created' field */
  $data['invite']['created'] = array(
    'title' => t('Invite creation time'),
    'help' => t('Stores the creation time of the invite.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  /* 'expiry' field */
  $data['invite']['expiry'] = array(
    'title' => t('Invite expiry time'),
    'help' => t('Expiry time of the invite.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  /* 'joined' field */
  $data['invite']['joined'] = array(
    'title' => t('Invite joined time'),
    'help' => t('Time the invite was accepted upon registration.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  /* 'canceled' field */
  $data['invite']['canceled'] = array(
    'title' => t('Invite canceled'),
    'help' => t('The invite has been withdrawn.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
  );
  /* 'resent' field */
  $data['invite']['resent'] = array(
    'title' => t('Invite resent number'),
    'help' => t('How many times the invite has been resent.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  /* accept link */
  $data['invite']['accept_link'] = array(
    'title' => t('Invite accept link'),
    'help' => t('Invite accept link.'),
    'field' => array(
      'handler' => 'views_handler_field_invite_accept_link',
    ),
  );
  /* withdraw link */
  $data['invite']['withdraw_link'] = array(
    'title' => t('Invite withdraw link'),
    'help' => t('Invite withdraw link.'),
    'field' => array(
      'handler' => 'views_handler_field_invite_withdraw_link',
    ),
  );
  /* resend link */
  $data['invite']['resend_link'] = array(
    'title' => t('Invite resend link'),
    'help' => t('Invite resend link.'),
    'field' => array(
      'handler' => 'views_handler_field_invite_resend_link',
    ),
  );
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function invite_views_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'invite_views') . '/includes/views2/handlers',
    ),
    'handlers' => array(
      'views_handler_field_invite_uid_name' => array(
        'parent' => 'views_handler_field_user_name',
      ),
      'views_handler_field_invite_invitee_name' => array(
        'parent' => 'views_handler_field_user_name',
      ),
      'views_handler_field_invite_accept_link' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_field_invite_withdraw_link' => array(
        'parent' => 'views_handler_field_invite_accept_link',
      ),
      'views_handler_field_invite_resend_link' => array(
        'parent' => 'views_handler_field_invite_accept_link',
      ),
    ),
  );
}
