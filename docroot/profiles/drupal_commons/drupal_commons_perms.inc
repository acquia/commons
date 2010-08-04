<?php

/*
 * Map of permissions and associated roles
 * 
 * @return
 *   An associative array containing permissions and the roles
 *   to which the permission is granted to
 */
function drupal_commons_import_permissions() {
  $permissions = array();

  // Permission: access comments
  $permissions[] = array(
    'name' => 'access comments',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: access content
  $permissions[] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: access freelinking list
  $permissions[] = array(
    'name' => 'access freelinking list',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: access news feeds
  $permissions[] = array(
    'name' => 'access news feeds',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: access og_aggregator
  $permissions[] = array(
    'name' => 'access og_aggregator',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: access user profiles
  $permissions[] = array(
    'name' => 'access user profiles',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: administer comments
  $permissions[] = array(
    'name' => 'administer comments',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: administer og_aggregator
  $permissions[] = array(
    'name' => 'administer og_aggregator',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: can have relationships
  $permissions[] = array(
    'name' => 'can have relationships',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: cancel own vote
  $permissions[] = array(
    'name' => 'cancel own vote',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: create blog entries
  $permissions[] = array(
    'name' => 'create blog entries',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: create discussion content
  $permissions[] = array(
    'name' => 'create discussion content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: create document content
  $permissions[] = array(
    'name' => 'create document content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: create event content
  $permissions[] = array(
    'name' => 'create event content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: create group content
  $permissions[] = array(
    'name' => 'create group content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: create notice content
  $permissions[] = array(
    'name' => 'create notice content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: create page content
  $permissions[] = array(
    'name' => 'create page content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: create poll content
  $permissions[] = array(
    'name' => 'create poll content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: create wiki content
  $permissions[] = array(
    'name' => 'create wiki content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: delete any blog entry
  $permissions[] = array(
    'name' => 'delete any blog entry',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete any discussion content
  $permissions[] = array(
    'name' => 'delete any discussion content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete any document content
  $permissions[] = array(
    'name' => 'delete any document content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete any event content
  $permissions[] = array(
    'name' => 'delete any event content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete any group content
  $permissions[] = array(
    'name' => 'delete any group content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete any notice content
  $permissions[] = array(
    'name' => 'delete any notice content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete any page content
  $permissions[] = array(
    'name' => 'delete any page content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete any poll content
  $permissions[] = array(
    'name' => 'delete any poll content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete any wiki content
  $permissions[] = array(
    'name' => 'delete any wiki content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete heartbeat activity logs
  $permissions[] = array(
    'name' => 'delete heartbeat activity logs',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete own blog entries
  $permissions[] = array(
    'name' => 'delete own blog entries',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: delete own discussion content
  $permissions[] = array(
    'name' => 'delete own discussion content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: delete own document content
  $permissions[] = array(
    'name' => 'delete own document content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: delete own event content
  $permissions[] = array(
    'name' => 'delete own event content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: delete own group content
  $permissions[] = array(
    'name' => 'delete own group content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: delete own heartbeat activity logs
  $permissions[] = array(
    'name' => 'delete own heartbeat activity logs',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete own notice content
  $permissions[] = array(
    'name' => 'delete own notice content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete own page content
  $permissions[] = array(
    'name' => 'delete own page content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: delete own poll content
  $permissions[] = array(
    'name' => 'delete own poll content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: delete own shouts
  $permissions[] = array(
    'name' => 'delete own shouts',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: delete own wiki content
  $permissions[] = array(
    'name' => 'delete own wiki content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: delete revisions
  $permissions[] = array(
    'name' => 'delete revisions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit any blog entry
  $permissions[] = array(
    'name' => 'edit any blog entry',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit any discussion content
  $permissions[] = array(
    'name' => 'edit any discussion content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit any document content
  $permissions[] = array(
    'name' => 'edit any document content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit any event content
  $permissions[] = array(
    'name' => 'edit any event content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit any group content
  $permissions[] = array(
    'name' => 'edit any group content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit any notice content
  $permissions[] = array(
    'name' => 'edit any notice content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit any page content
  $permissions[] = array(
    'name' => 'edit any page content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit any poll content
  $permissions[] = array(
    'name' => 'edit any poll content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit any wiki content
  $permissions[] = array(
    'name' => 'edit any wiki content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );
  
  // Permission: edit field_content_images
  $permissions[] = array(
    'name' => 'edit field_content_images',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit field_date
  $permissions[] = array(
    'name' => 'edit field_date',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit field_featured_content
  $permissions[] = array(
    'name' => 'edit field_featured_content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit field_featured_group
  $permissions[] = array(
    'name' => 'edit field_featured_group',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: edit field_file
  $permissions[] = array(
    'name' => 'edit field_file',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit field_group_image
  $permissions[] = array(
    'name' => 'edit field_group_image',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit field_group_sticky
  $permissions[] = array(
    'name' => 'edit field_group_sticky',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit field_grouplink
  $permissions[] = array(
    'name' => 'edit field_grouplink',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit field_location
  $permissions[] = array(
    'name' => 'edit field_location',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own blog entries
  $permissions[] = array(
    'name' => 'edit own blog entries',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own discussion content
  $permissions[] = array(
    'name' => 'edit own discussion content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own document content
  $permissions[] = array(
    'name' => 'edit own document content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own event content
  $permissions[] = array(
    'name' => 'edit own event content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own group content
  $permissions[] = array(
    'name' => 'edit own group content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own notice content
  $permissions[] = array(
    'name' => 'edit own notice content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own page content
  $permissions[] = array(
    'name' => 'edit own page content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own poll content
  $permissions[] = array(
    'name' => 'edit own poll content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own shouts
  $permissions[] = array(
    'name' => 'edit own shouts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: edit own wiki content
  $permissions[] = array(
    'name' => 'edit own wiki content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: inspect all votes
  $permissions[] = array(
    'name' => 'inspect all votes',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: maintain own activity
  $permissions[] = array(
    'name' => 'maintain own activity',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: maintain own relationships
  $permissions[] = array(
    'name' => 'maintain own relationships',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );
  
  // Permission: maintain own subscriptions
  $permissions[] = array(
    'name' => 'maintain own subscriptions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );
  
  // Permission: manage own subscriptions
  $permissions[] = array(
    'name' => 'manage all subscriptions',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: manage own subscriptions
  $permissions[] = array(
    'name' => 'manage own subscriptions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: moderate shoutbox
  $permissions[] = array(
    'name' => 'moderate shoutbox',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: post comments
  $permissions[] = array(
    'name' => 'post comments',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: post comments without approval
  $permissions[] = array(
    'name' => 'post comments without approval',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: post shouts
  $permissions[] = array(
    'name' => 'post shouts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: post shouts in all groups
  $permissions[] = array(
    'name' => 'post shouts in all groups',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: post shouts without approval
  $permissions[] = array(
    'name' => 'post shouts without approval',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: revert revisions
  $permissions[] = array(
    'name' => 'revert revisions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: search content
  $permissions[] = array(
    'name' => 'search content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );
  
  // Permission: skip notifications
  $permissions[] = array(
    'name' => 'skip notifications',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: subscribe to author
  $permissions[] = array(
    'name' => 'subscribe to author',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: subscribe to content
  $permissions[] = array(
    'name' => 'subscribe to content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: subscribe to content type
  $permissions[] = array(
    'name' => 'subscribe to content type',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: use advanced search
  $permissions[] = array(
    'name' => 'use advanced search',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );
  
  // Permission: view analytics page
  $permissions[] = array(
    'name' => 'view analytics page',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );
  
  // Permission: view field_content_images
  $permissions[] = array(
    'name' => 'view field_content_images',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view field_date
  $permissions[] = array(
    'name' => 'view field_date',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view field_featured_content
  $permissions[] = array(
    'name' => 'view field_featured_content',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: view field_featured_group
  $permissions[] = array(
    'name' => 'view field_featured_group',
    'roles' => array(
      '0' => DRUPAL_COMMONS_MANAGER_ROLE,
    ),
  );

  // Permission: view field_file
  $permissions[] = array(
    'name' => 'view field_file',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view field_group_image
  $permissions[] = array(
    'name' => 'view field_group_image',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view field_group_sticky
  $permissions[] = array(
    'name' => 'view field_group_sticky',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: view field_grouplink
  $permissions[] = array(
    'name' => 'view field_grouplink',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view field_location
  $permissions[] = array(
    'name' => 'view field_location',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view heartbeat messages
  $permissions[] = array(
    'name' => 'view heartbeat messages',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );
  
  // Permission: view imagecache Featured
  $permissions[] = array(
    'name' => 'view imagecache Featured',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view imagecache group_images
  $permissions[] = array(
    'name' => 'view imagecache group_images',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view imagecache group_images_thumb
  $permissions[] = array(
    'name' => 'view imagecache group_images_thumb',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );
  
  // Permission: view imagecache member_list_image
  $permissions[] = array(
    'name' => 'view imagecache member_list_image',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view imagecache profile_pictures
  $permissions[] = array(
    'name' => 'view imagecache profile_pictures',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );
  
  // Permission: view imagecache Small
  $permissions[] = array(
    'name' => 'view imagecache Small',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view imagecache user_picture_meta
  $permissions[] = array(
    'name' => 'view imagecache user_picture_meta',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Permission: view own userpoints
  $permissions[] = array(
    'name' => 'view own userpoints',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: view revisions
  $permissions[] = array(
    'name' => 'view revisions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: view shouts
  $permissions[] = array(
    'name' => 'view shouts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: view user relationships
  $permissions[] = array(
    'name' => 'view user relationships',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: view userpoints
  $permissions[] = array(
    'name' => 'view userpoints',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Permission: vote on polls
  $permissions[] = array(
    'name' => 'vote on polls',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
