<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function commons_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration pages
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: access all views
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: access comments
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
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

  // Exported permission: access site reports
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: access user profiles
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: administer actions
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer blocks
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer comments
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: administer content types
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer features
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer files
  $permissions['administer files'] = array(
    'name' => 'administer files',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer filters
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer flags
  $permissions['administer flags'] = array(
    'name' => 'administer flags',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer imageapi
  $permissions['administer imageapi'] = array(
    'name' => 'administer imageapi',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer imagecache
  $permissions['administer imagecache'] = array(
    'name' => 'administer imagecache',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer menu
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer nodes
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'content manager',
      '2' => 'site admin',
    ),
  );

  // Exported permission: administer og features
  $permissions['administer og features'] = array(
    'name' => 'administer og features',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer organic groups
  $permissions['administer organic groups'] = array(
    'name' => 'administer organic groups',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer permissions
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer quant
  $permissions['administer quant'] = array(
    'name' => 'administer quant',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer search
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer site configuration
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer site-wide contact form
  $permissions['administer site-wide contact form'] = array(
    'name' => 'administer site-wide contact form',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer taxonomy
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer url aliases
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer user relationships
  $permissions['administer user relationships'] = array(
    'name' => 'administer user relationships',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer users
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: administer views
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: can have relationships
  $permissions['can have relationships'] = array(
    'name' => 'can have relationships',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: change own username
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      '0' => 'site admin',
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

  // Exported permission: delete own group content
  $permissions['delete own group content'] = array(
    'name' => 'delete own group content',
    'roles' => array(
      '0' => 'authenticated user',
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

  // Exported permission: delete revisions
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit all group features
  $permissions['edit all group features'] = array(
    'name' => 'edit all group features',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
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

  // Exported permission: edit field_content_images
  $permissions['edit field_content_images'] = array(
    'name' => 'edit field_content_images',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'site admin',
    ),
  );

  // Exported permission: edit field_featured_content
  $permissions['edit field_featured_content'] = array(
    'name' => 'edit field_featured_content',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: edit field_featured_group
  $permissions['edit field_featured_group'] = array(
    'name' => 'edit field_featured_group',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: edit field_group_image
  $permissions['edit field_group_image'] = array(
    'name' => 'edit field_group_image',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'site admin',
    ),
  );

  // Exported permission: edit field_group_sticky
  $permissions['edit field_group_sticky'] = array(
    'name' => 'edit field_group_sticky',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: edit field_grouplink
  $permissions['edit field_grouplink'] = array(
    'name' => 'edit field_grouplink',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'site admin',
    ),
  );

  // Exported permission: edit own group content
  $permissions['edit own group content'] = array(
    'name' => 'edit own group content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit own group features
  $permissions['edit own group features'] = array(
    'name' => 'edit own group features',
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

  // Exported permission: flush imagecache
  $permissions['flush imagecache'] = array(
    'name' => 'flush imagecache',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: maintain own relationships
  $permissions['maintain own relationships'] = array(
    'name' => 'maintain own relationships',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: manage features
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      '0' => 'site admin',
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

  // Exported permission: select different theme
  $permissions['select different theme'] = array(
    'name' => 'select different theme',
    'roles' => array(
      '0' => 'site admin',
    ),
  );

  // Exported permission: use PHP for block visibility
  $permissions['use PHP for block visibility'] = array(
    'name' => 'use PHP for block visibility',
    'roles' => array(
      '0' => 'site admin',
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

  // Exported permission: view analytics page
  $permissions['view analytics page'] = array(
    'name' => 'view analytics page',
    'roles' => array(
      '0' => 'community manager',
    ),
  );

  // Exported permission: view content rss feeds
  $permissions['view content rss feeds'] = array(
    'name' => 'view content rss feeds',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_content_images
  $permissions['view field_content_images'] = array(
    'name' => 'view field_content_images',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'site admin',
    ),
  );

  // Exported permission: view field_featured_content
  $permissions['view field_featured_content'] = array(
    'name' => 'view field_featured_content',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: view field_featured_group
  $permissions['view field_featured_group'] = array(
    'name' => 'view field_featured_group',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: view field_group_image
  $permissions['view field_group_image'] = array(
    'name' => 'view field_group_image',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'site admin',
    ),
  );

  // Exported permission: view field_group_sticky
  $permissions['view field_group_sticky'] = array(
    'name' => 'view field_group_sticky',
    'roles' => array(
      '0' => 'community manager',
      '1' => 'site admin',
    ),
  );

  // Exported permission: view field_grouplink
  $permissions['view field_grouplink'] = array(
    'name' => 'view field_grouplink',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'site admin',
    ),
  );

  // Exported permission: view group content rss feeds
  $permissions['view group content rss feeds'] = array(
    'name' => 'view group content rss feeds',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache Featured
  $permissions['view imagecache Featured'] = array(
    'name' => 'view imagecache Featured',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
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

  // Exported permission: view revisions
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
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

  return $permissions;
}
