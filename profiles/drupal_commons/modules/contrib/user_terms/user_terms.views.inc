<?php
// $Id: user_terms.views.inc,v 1.1.2.4 2010/02/19 17:34:28 joachim Exp $
/**
 * @file user_terms.views.inc
 * Provides integration with views module.
 */

/**
 * Implementation of hook_views_data().
 */
function user_terms_views_data() {
  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['term_user']['table']['group']  = t('User');

  $data['term_user']['table']['join'] = array(
    'term_data' => array(
      'left_field' => 'tid',
      'field' => 'tid',
    ),
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // tid field
  $data['term_user']['tid'] = array(
    'title' => t('Term ID'),
    'help' => t('The taxonomy term ID for the user'),
    'field' => array(
      'title' => t('All terms'),
      'help' => t('Display all taxonomy terms associated with a user.'),
      'handler' => 'user_terms_handler_field_term_user_tid',
      'skip base' => 'term_user',
    ),
    'argument' => array(
      // Use the views term tid argument: this has nothing specific to nodes .
      'handler' => 'views_handler_argument_term_node_tid',
      'name table' => 'term_data',
      'name field' => 'name',
      'empty field name' => t('Uncategorized'),
      'numeric' => TRUE,
      'skip base' => 'term_user',
    ),
    'filter' => array(
      'title' => t('Term'),
      'handler' => 'views_handler_filter_term_node_tid',
      'hierarchy table' => 'term_hierarchy',
      'numeric' => TRUE,
      'skip base' => 'term_user',
      'allow empty' => TRUE,
    ),
    'relationship' => array(
      'title' => t('Terms'),
      'label' => t('Terms for the user'),
      'help' => t('The terms assigned to the user. May produce multiple rows.'),
      'base' => 'term_data',
      'base field' => 'tid',
      'handler' => 'views_handler_relationship',
      // This allows us to not show this relationship if the base is already
      // term_data so users won't create circular relationships.
      'skip base' => array('term_data'),
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function user_terms_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'user_terms'),
    ),
    'handlers' => array(
      'user_terms_handler_field_term_user_tid' => array(
        'parent' => 'views_handler_field_term_node_tid',
      ),
    ),
  );
}
