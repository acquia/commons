<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_core_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:analytics
  $menu_links['primary-links:analytics'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'analytics',
    'router_path' => 'analytics',
    'link_title' => 'Site analytics',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '30',
    'parent_path' => 'community',
  );
  // Exported menu link: primary-links:bookmarks
  $menu_links['primary-links:bookmarks'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'bookmarks',
    'router_path' => 'bookmarks',
    'link_title' => 'My bookmarks',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-30',
    'parent_path' => 'mystuff',
  );
  // Exported menu link: primary-links:community
  $menu_links['primary-links:community'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'community',
    'router_path' => 'community',
    'link_title' => 'Community',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '1',
    'expanded' => '1',
    'weight' => '10',
  );
  // Exported menu link: primary-links:content/blogs
  $menu_links['primary-links:content/blogs'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'content/blogs',
    'router_path' => 'content/blogs',
    'link_title' => 'Blog posts',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-40',
    'parent_path' => 'community',
  );
  // Exported menu link: primary-links:content/calendar
  $menu_links['primary-links:content/calendar'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'content/calendar',
    'router_path' => 'content/calendar',
    'link_title' => 'Calendar',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '10',
    'parent_path' => 'community',
  );
  // Exported menu link: primary-links:content/discussions
  $menu_links['primary-links:content/discussions'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'content/discussions',
    'router_path' => 'content/discussions',
    'link_title' => 'Discussions',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-20',
    'parent_path' => 'community',
  );
  // Exported menu link: primary-links:content/documents
  $menu_links['primary-links:content/documents'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'content/documents',
    'router_path' => 'content/documents',
    'link_title' => 'Documents',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-30',
    'parent_path' => 'community',
  );
  // Exported menu link: primary-links:content/polls
  $menu_links['primary-links:content/polls'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'content/polls',
    'router_path' => 'content/polls',
    'link_title' => 'Polls',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-10',
    'parent_path' => 'community',
  );
  // Exported menu link: primary-links:content/wikis
  $menu_links['primary-links:content/wikis'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'content/wikis',
    'router_path' => 'content/wikis',
    'link_title' => 'Wikis',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'parent_path' => 'community',
  );
  // Exported menu link: primary-links:group
  $menu_links['primary-links:group'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'group',
    'router_path' => 'group',
    'link_title' => 'My unread',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-40',
    'parent_path' => 'mystuff',
  );
  // Exported menu link: primary-links:groups
  $menu_links['primary-links:groups'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'groups',
    'router_path' => 'groups',
    'link_title' => 'Groups',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
    'parent_path' => 'community',
  );
  // Exported menu link: primary-links:mystuff
  $menu_links['primary-links:mystuff'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'mystuff',
    'router_path' => 'mystuff',
    'link_title' => 'My stuff',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '1',
    'expanded' => '1',
    'weight' => '20',
  );
  // Exported menu link: primary-links:myuserpoints
  $menu_links['primary-links:myuserpoints'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'myuserpoints',
    'router_path' => 'myuserpoints',
    'link_title' => 'My points',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-10',
    'parent_path' => 'mystuff',
  );
  // Exported menu link: primary-links:relationships
  $menu_links['primary-links:relationships'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'relationships',
    'router_path' => 'relationships',
    'link_title' => 'My friends',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-20',
    'parent_path' => 'mystuff',
  );
  // Exported menu link: primary-links:user
  $menu_links['primary-links:user'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My profile',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
    'parent_path' => 'mystuff',
  );
  // Exported menu link: primary-links:users
  $menu_links['primary-links:users'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'users',
    'router_path' => 'users',
    'link_title' => 'Members',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '20',
    'parent_path' => 'community',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Blog posts');
  t('Calendar');
  t('Community');
  t('Discussions');
  t('Documents');
  t('Groups');
  t('Members');
  t('My bookmarks');
  t('My friends');
  t('My points');
  t('My profile');
  t('My stuff');
  t('My unread');
  t('Polls');
  t('Site analytics');
  t('Wikis');


  return $menu_links;
}
