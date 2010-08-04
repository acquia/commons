<?php
// $Id: og_statistics.views.inc,v 1.2.2.3 2009/09/10 07:06:33 dereine Exp $

/**
 * @file
 *   Views Integration of og_statitics.
 */

/**
 * Implementation of hook_views_data().
 */
function og_statistics_views_data() {
  $data = array();
  $data += og_statistics_views_og_statistics();
  return $data;
}

function og_statistics_views_og_statistics() {
  $data['og_statistics']['table']['group'] = t('OG Statistics');

  $data['og_statistics']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  $data['og_statistics']['members_count'] = array(
    'title' => t('Group Statistic: Members Count'),
    'real field' => 'members_count',
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['og_statistics']['posts_count'] = array(
    'title' => t('Group Statistic: Posts Count'),
    'real field' => 'posts_count',
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['og_statistics']['comments_count'] = array(
    'title' => t('Group Statistic: Comments Count'),
    'real field' => 'comments_count',
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['og_statistics']['last_node_timestamp'] = array(
    'title' => t('Group Statistic: Last inserted/updated Node-time'),
    'real field' => 'last_node_timestamp',
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  $data['og_statistics']['last_comment_timestamp'] = array(
    'title' => t('Group Statistic: Last Comment-time'),
    'real field' => 'last_comment_timestamp',
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  $data['og_statistics']['last_member_timestamp'] = array(
    'title' => t('Group Statistic: last Member subscription'),
    'real field' => 'last_member_timestamp',
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  // Add relationship to node table for last node posted.
  $data['og_statistics']['last_node_nid'] = array(
    'title' => 'Group Statistic: Last Node posted',
    'help' => 'Create a relationship to for the last node posted',
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'field' => 'nid',
      'label' => t('node'),
    ),
  );
  // Add relationship to user table for last node posted.
  $data['og_statistics']['last_node_uid'] = array(
    'title' => 'Group Statistic: User that created the last node posted',
    'help' => 'Create a relationship to the user that last posted a node.',
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('user'),
    ),
  );

  // Add relationship to node table for last comment posted.
  $data['og_statistics']['last_comment_nid'] = array(
    'title' => 'Group Statistic: Node the last comment was posted to',
    'help' => 'Create a relationship to the last comment posted',
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'field' => 'nid',
      'label' => t('node'),
    ),
  );
  // Add relationship to user table for last comment posted.
  $data['og_statistics']['last_comment_uid'] = array(
    'title' => 'Group Statistic: User that posted the last comment',
    'help' => 'Create a relationship to the user that last posted a comment.',
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('user'),
    ),
  );
  // Add relationship to the comment table for the last comment posted.
  $data['og_statistics']['last_comment_cid'] = array(
    'title' => 'Group Statistic: Comment last posted',
    'help' => 'Create a relationship to the last comment posted',
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'comments',
      'field' => 'cid',
      'label' => t('comment'),
    ),
  );

  // Add relationship to the users table for the last member.
  $data['og_statistics']['last_member_uid'] = array(
    'title' => 'Group Statistic: Last member to join',
    'help' => 'Create a relationship to the last user to join',
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('user'),
    ),
  );

  return $data;
}

