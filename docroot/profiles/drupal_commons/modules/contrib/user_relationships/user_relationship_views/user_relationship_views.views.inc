<?php
// $Id: user_relationship_views.views.inc,v 1.1.2.5 2009/11/07 21:47:04 alexk Exp $

/**
 * @file
 * User Relationships Views support. Declares all the main tables to Views
 * @author Alex Karshakevich http://drupal.org/user/183217
 **/

/**
 * hook_views_data()
 */
function user_relationship_views_views_data() {
  $tables['user_relationships'] = array(
    'table' => array(
      'group' => t('User relationships'),
      'join' => array(
        'users' => array(
          'table' => 'user_relationships',
          'left_field' => 'uid',
          'field' => 'requestee_id'
         ),
         'node' => array(
           'table' => 'user_relationships',
           'left_field' => 'uid',
           'field' => 'requester_id'
         ),
         'user_relationship_types' => array(
           'left_table' => 'user_relationship_types',
           'table' => 'user_relationships',
           'left_field' => 'rtid',
           'field' => 'rtid'
         )
       ),
      'base' => array(
        'field' => 'rid',
        'title' => t('User relationship'),
        'help' => t('Relationships that link users to one another. Use this to show user data, profile fields, or content_profile nodes of related users.'),
        'weight' => 0,
      ),
    ),
    'rtid' => array(
      'title' => t('RTID'),
      'help' => t('Type ID of the relationship'),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric'
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'relationship' => array(
        'base' => 'user_relationship_types',
        'field' => 'rtid',
        'help' => t('Bring in name, type, and other properties of relationships'),
      ),
    ),
    'rtype' => array( // virtual field for simple views that just need the relationship name, and don't want to use a views relationship
      'title' => t('Relationship type'),
      'help' => t('Singular or plural name of the relationship'),
      'real field' => 'rtid',
      'argument' => array(
        'handler' => 'views_handler_argument_numeric'
      ),
      'field' => array(
        'handler' => 'views_handler_field_user_relationships_name',
        'click sortable' => TRUE
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_user_relationships_type',
      ),
    ),
    'requester_id' => array(
      'title' => t('Requester user'),
      'help' => t('User who started the relationship'),
      'field' => array(
        'handler' => 'views_handler_field_user_relationships_requester',
        'click sortable' => TRUE
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_user_uid',
        'name field' => 'name', // the field to display in the summary.
        'numeric' => TRUE,
        'validate type' => 'uid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_user_name'
      ),
      'relationship' => array( // this relationship brings in all fields the users table offers
        'base' => 'users',
        'field' => 'uid',
        'label' => 'requester',
        'help' => t('Bring in data about the user who started the relationship, or link to relationships that they have established'),
      ),
    ),
    'requestee_id' => array(
      'title' => t('Requestee user'),
      'help' => t('User who accepted the relationship'),
      'field' => array(
        'handler' => 'views_handler_field_user_relationships_requestee',
        'click sortable' => TRUE
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_user_uid',
        'name field' => 'name', // the field to display in the summary.
        'numeric' => TRUE,
        'validate type' => 'uid',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_user_name'
      ),
      'relationship' => array( // this relationship brings in all fields the users table offers
        'base' => 'users',
        'field' => 'uid',
        'label' => 'requestee',
        'help' => t('Bring in data about the user who accepted the relationship, or link to relationships that other users have established to this one'),
      ),
    ),
    'approved' => array(
      'title' => t('Relationship status'),
      'help' => t('Pending/approved relationship status'),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric'
      ),
      'field' => array(
        'handler' => 'views_handler_field_user_relationships_status',
        'click sortable' => TRUE
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_user_relationships_status',
      ),
    ),
    'created_at' => array(
      'title' => t('Created date'),
      'help' => t('Date the relationship was requested or created'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE
      ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    ),
    'updated_at' => array(
      'title' => t('Updated date'),
      'help' => t('Date the relationship was approved or edited'),
      'field' => array(
        'handler' => 'views_handler_field_date',
        'click sortable' => TRUE
      ),
      'sort' => array(
        'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_date',
      ),
    ),
    'status_link' => array(
      'title' => t('Status link'),
      'help' => t('Provides a link to change status of the relationship.'),
      'field' => array(
        'handler' => 'views_handler_field_user_relationships_status_link',
      ),
    ),
  );
  $tables['user_relationship_types'] = array(
    'table' => array(
      'group' => t('User relationship types'),
      'join' => array(
        'user_relationships_requesters' => array(
          'left_field' => 'rtid',
          'field' => 'rtid'
        ),
        'user_relationships_requestees' => array(
          'left_field' => 'rtid',
          'field' => 'rtid'
        ),
      ),
      'base' => array(
        'field' => 'rtid',
        'title' => t('User relationship type'),
        'help' => t('Kinds of relationships that can link users to one another. Use this if you want to show the kinds of relationships your site offers.'),
        'weight' => 0,
      ),
    ),
    'rtid' => array(
      'title' => t('RTID'),
      'help' => t('Type of the relationship'),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric'
      ),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'name' => array(
      'title' => t('Name'),
      'help' => t('Name of the relationship (singular)'),
      'argument' => array(
        'handler' => 'views_handler_argument_string'
      ),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'plural_name' => array(
      'title' => t('Plural name'),
      'help' => t('Name of the relationship (plural)'),
      'argument' => array(
        'handler' => 'views_handler_argument_string'
      ),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'is_oneway' => array(
      'title' => t('Type'),
      'help' => t('Whether the relationship is one way or mutual'),
      'field' => array(
        'handler' => 'views_handler_field_user_relationships_oneway',
        'click sortable' => TRUE
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'requires_approval' => array(
      'title' => t('Requires approval'),
      'help' => t('Whether relationship requests must be approved'),
      'field' => array(
        'handler' => 'views_handler_field_boolean',
        'click sortable' => TRUE
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'expires_val' => array(
      'title' => t('Expiration'),
      'help' => t('Expiration period of pending relationship requests'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );
  return $tables;
}
/**
 *  Implementation of hook_views_handlers().
 */
function user_relationship_views_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'user_relationship_views'),
    ),
    'handlers' => array(
      'views_handler_field_user_relationships_status' => array('parent' => 'views_handler_field'),
      'views_handler_filter_user_relationships_status' => array('parent' => 'views_handler_filter_equality'),
      'views_handler_field_user_relationships_name' => array('parent' => 'views_handler_field'),
      'views_handler_field_user_relationships_requestee' => array('parent' => 'views_handler_field_user_link'),
      'views_handler_field_user_relationships_requester' => array('parent' => 'views_handler_field_user_link'),
      'views_handler_filter_user_relationships_type' => array('parent' => 'views_handler_filter_in_operator'),
      'views_handler_field_user_relationships_oneway' => array('parent' => 'views_handler_field'),
      'views_handler_field_user_relationships_status_link' => array('parent' => 'views_handler_field'),
    ),
  );
}
