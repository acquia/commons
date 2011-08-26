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
    'weight' => '40',
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
    'weight' => '-20',
    'parent_path' => 'user',
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
  // Exported menu link: primary-links:groups/mine
  $menu_links['primary-links:groups/mine'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'groups/mine',
    'router_path' => 'groups/mine',
    'link_title' => 'My groups',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-40',
    'parent_path' => 'user',
  );
  // Exported menu link: primary-links:mycontent
  $menu_links['primary-links:mycontent'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'mycontent',
    'router_path' => 'mycontent',
    'link_title' => 'My content',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-30',
    'parent_path' => 'user',
  );
  // Exported menu link: primary-links:myprofile
  $menu_links['primary-links:myprofile'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'myprofile',
    'router_path' => 'myprofile',
    'link_title' => 'My profile',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
    'parent_path' => 'user',
  );
  // Exported menu link: primary-links:notices
  $menu_links['primary-links:notices'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'notices',
    'router_path' => 'notices',
    'link_title' => 'Notices',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '20',
    'parent_path' => 'community',
  );
  // Exported menu link: primary-links:relationships
  $menu_links['primary-links:relationships'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'relationships',
    'router_path' => 'relationships',
    'link_title' => 'My relationships',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-10',
    'parent_path' => 'user',
  );
  // Exported menu link: primary-links:user
  $menu_links['primary-links:user'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'user',
    'router_path' => 'user',
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
  // Translatables
  // Included for use with string extractors like potx.
  t('Community');
  t('Groups');
  t('My bookmarks');
  t('My content');
  t('My groups');
  t('My profile');
  t('My relationships');
  t('My stuff');
  t('Notices');
  t('Site analytics');


  return $menu_links;
}
