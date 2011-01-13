<?php
// $Id: user_badges.views.inc,v 1.1 2008/11/20 17:12:09 heine Exp $

/**
 * @file
 * This defines views hooks for the User_badges module. It will be loaded automatically as needed by the Views module.
 *
 * @author Heine Deelstra (Heine), http://drupal.org/user/17943
 * @author Richard Skinner (Likeless), http://drupal.org/user/310635
 *
 */

/**
 * Implements hook_views_handlers().
 */
function user_badges_views_handlers() {
  return array(
    'handlers' => array(
      'views_handler_field_user_badges_badges_badge' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_field_user_badges_user_uid' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_filter_user_badges_user_type' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function user_badges_views_data() {
  // Describe the user_badges_user table.

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['user_badges_user']['table']['group']  = t('User Badges');

  // How to join this table to the users table
  $data['user_badges_user']['table']['join']['users'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
  );

  // How to join this table to the node table
  $data['user_badges_user']['table']['join']['node'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
  );

  // How to join to node_revisions; through the node table for consistent authorship.
  $data['user_badges_user']['table']['join']['node_revisions'] = array(
    'left_table' => 'node',
    'left_field' => 'uid',
    'field' => 'uid',
  );

  // Describe the user_badges_badges table.
  $data['user_badges_badges']['table']['group']  = t('User Badges');

  //We always the user_badges_badges table on to the user_badges_user table
  $user_badges_badges_join_info = array(
    'left_table' => 'user_badges_user',
    'left_field' => 'bid',
    'field' => 'bid',
  );

  $data['user_badges_badges']['table']['join']['users'] = $user_badges_badges_join_info;
  $data['user_badges_badges']['table']['join']['node'] = $user_badges_badges_join_info;
  $data['user_badges_badges']['table']['join']['node_revisions'] = $user_badges_badges_join_info;


  // Information for processing badge IDs
  $data['user_badges_user']['bid'] = array(
    'title' => t('Bid'),
    'help' => t('The badge ID of the user badge itself.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    // Information for accepting a bid as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'Badge ID',
      'numeric' => TRUE,
    ),
    //Info for filtering by bid
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on a bid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Information for processing badge types
  $data['user_badges_user']['type'] = array(
    'title' => t('Type'),
    'help' => t('Whether the badge was set as part of the role, or individually assigned.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    //Info for filtering by badge type
    'filter' => array(
      'handler' => 'views_handler_filter_user_badges_user_type',
    ),
    // Information for sorting on a bid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Information for processing badges by name
  $data['user_badges_badges']['name'] = array(
    'title' => t('Badge Name'),
    'help' => t('The name of the user badge.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
      'name field' => 'Badge Name',
    ),
    //Info for filtering by badge name
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    // Information for sorting on a bid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Information for processing badges weights
  $data['user_badges_badges']['weight'] = array(
    'title' => t('Badge Weight'),
    'help' => t('The weight of the badge, as defined on the user badges settings page.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['user_badges_badges']['badge'] = array(
    'title' => t('Badge'),
    'real field' => 'bid',
    'help' => t('An individual user badge.'),
    'field' => array(
      'handler' => 'views_handler_field_user_badges_badges_badge',
    ),
  );

  // Add the grouped user badges to the user table
  $data['users']['user_badges_html'] = array(
    'real field' => 'uid',
    'title' => t('Grouped User Badges'),
    'help' => t("All the user's user badges."),
    'group' => t('User Badges'),
    'field' => array(
      'handler' => 'views_handler_field_user_badges_user_uid',
    ),
  );

  return $data;
}
