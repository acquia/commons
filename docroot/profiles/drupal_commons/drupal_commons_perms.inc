<?php
// $Id$

/**
 * Map of permissions and associated roles
 * 
 * @return
 *   An associative array containing permissions and the roles
 *   to which the permission is granted to
 */
function drupal_commons_import_permissions() {
  $permissions = array();

  // Exported permission: access comments
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: access content
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: access news feeds
  $permissions['access news feeds'] = array(
    'name' => 'access news feeds',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: access og_aggregator
  $permissions['access og_aggregator'] = array(
    'name' => 'access og_aggregator',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: access user profiles
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: administer comments
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: administer content types
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
  );

  // Exported permission: administer nodes
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
    ),
  );

  // Exported permission: can have relationships
  $permissions['can have relationships'] = array(
    'name' => 'can have relationships',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: cancel own vote
  $permissions['cancel own vote'] = array(
    'name' => 'cancel own vote',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create group content
  $permissions['create group content'] = array(
    'name' => 'create group content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create notice content
  $permissions['create notice content'] = array(
    'name' => 'create notice content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: create page content
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete any group content
  $permissions['delete any group content'] = array(
    'name' => 'delete any group content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete any notice content
  $permissions['delete any notice content'] = array(
    'name' => 'delete any notice content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete any page content
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete heartbeat activity logs
  $permissions['delete heartbeat activity logs'] = array(
    'name' => 'delete heartbeat activity logs',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete own group content
  $permissions['delete own group content'] = array(
    'name' => 'delete own group content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete own heartbeat activity logs
  $permissions['delete own heartbeat activity logs'] = array(
    'name' => 'delete own heartbeat activity logs',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete own notice content
  $permissions['delete own notice content'] = array(
    'name' => 'delete own notice content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete own page content
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete own shouts
  $permissions['delete own shouts'] = array(
    'name' => 'delete own shouts',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: delete revisions
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit any group content
  $permissions['edit any group content'] = array(
    'name' => 'edit any group content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit any notice content
  $permissions['edit any notice content'] = array(
    'name' => 'edit any notice content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit any page content
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit any wiki content
  $permissions['edit any wiki content'] = array(
    'name' => 'edit any wiki content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit field_content_images
  $permissions['edit field_content_images'] = array(
    'name' => 'edit field_content_images',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_featured_content
  $permissions['edit field_featured_content'] = array(
    'name' => 'edit field_featured_content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit field_featured_group
  $permissions['edit field_featured_group'] = array(
    'name' => 'edit field_featured_group',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: edit field_group_image
  $permissions['edit field_group_image'] = array(
    'name' => 'edit field_group_image',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_group_sticky
  $permissions['edit field_group_sticky'] = array(
    'name' => 'edit field_group_sticky',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_grouplink
  $permissions['edit field_grouplink'] = array(
    'name' => 'edit field_grouplink',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit own group content
  $permissions['edit own group content'] = array(
    'name' => 'edit own group content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit own notice content
  $permissions['edit own notice content'] = array(
    'name' => 'edit own notice content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit own page content
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit own shouts
  $permissions['edit own shouts'] = array(
    'name' => 'edit own shouts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: inspect all votes
  $permissions['inspect all votes'] = array(
    'name' => 'inspect all votes',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: maintain own activity
  $permissions['maintain own activity'] = array(
    'name' => 'maintain own activity',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: maintain own relationships
  $permissions['maintain own relationships'] = array(
    'name' => 'maintain own relationships',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: maintain own subscriptions
  $permissions['maintain own subscriptions'] = array(
    'name' => 'maintain own subscriptions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: manage all subscriptions
  $permissions['manage all subscriptions'] = array(
    'name' => 'manage all subscriptions',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: manage own subscriptions
  $permissions['manage own subscriptions'] = array(
    'name' => 'manage own subscriptions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: moderate shoutbox
  $permissions['moderate shoutbox'] = array(
    'name' => 'moderate shoutbox',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: post comments
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: post comments without approval
  $permissions['post comments without approval'] = array(
    'name' => 'post comments without approval',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: post shouts
  $permissions['post shouts'] = array(
    'name' => 'post shouts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: post shouts in all groups
  $permissions['post shouts in all groups'] = array(
    'name' => 'post shouts in all groups',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: post shouts without approval
  $permissions['post shouts without approval'] = array(
    'name' => 'post shouts without approval',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: revert revisions
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: search content
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: skip notifications
  $permissions['skip notifications'] = array(
    'name' => 'skip notifications',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: subscribe to author
  $permissions['subscribe to author'] = array(
    'name' => 'subscribe to author',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: subscribe to content
  $permissions['subscribe to content'] = array(
    'name' => 'subscribe to content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: subscribe to content type
  $permissions['subscribe to content type'] = array(
    'name' => 'subscribe to content type',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: use advanced search
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view all og_aggregator sources
  $permissions['view all og_aggregator sources'] = array(
    'name' => 'view all og_aggregator sources',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: view analytics page
  $permissions['view analytics page'] = array(
    'name' => 'view analytics page',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: view field_content_images
  $permissions['view field_content_images'] = array(
    'name' => 'view field_content_images',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_featured_content
  $permissions['view field_featured_content'] = array(
    'name' => 'view field_featured_content',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: view field_featured_group
  $permissions['view field_featured_group'] = array(
    'name' => 'view field_featured_group',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: view field_group_image
  $permissions['view field_group_image'] = array(
    'name' => 'view field_group_image',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_group_sticky
  $permissions['view field_group_sticky'] = array(
    'name' => 'view field_group_sticky',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view field_grouplink
  $permissions['view field_grouplink'] = array(
    'name' => 'view field_grouplink',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view heartbeat messages
  $permissions['view heartbeat messages'] = array(
    'name' => 'view heartbeat messages',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache Small
  $permissions['view imagecache Small'] = array(
    'name' => 'view imagecache Small',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache group_images
  $permissions['view imagecache group_images'] = array(
    'name' => 'view imagecache group_images',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache group_images_showcase
  $permissions['view imagecache group_images_showcase'] = array(
    'name' => 'view imagecache group_images_showcase',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache group_images_thumb
  $permissions['view imagecache group_images_thumb'] = array(
    'name' => 'view imagecache group_images_thumb',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache member_list_image
  $permissions['view imagecache member_list_image'] = array(
    'name' => 'view imagecache member_list_image',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache profile_pictures
  $permissions['view imagecache profile_pictures'] = array(
    'name' => 'view imagecache profile_pictures',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache user_picture_meta
  $permissions['view imagecache user_picture_meta'] = array(
    'name' => 'view imagecache user_picture_meta',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view own userpoints
  $permissions['view own userpoints'] = array(
    'name' => 'view own userpoints',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view revisions
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view shouts
  $permissions['view shouts'] = array(
    'name' => 'view shouts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view user relationships
  $permissions['view user relationships'] = array(
    'name' => 'view user relationships',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view userpoints
  $permissions['view userpoints'] = array(
    'name' => 'view userpoints',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
