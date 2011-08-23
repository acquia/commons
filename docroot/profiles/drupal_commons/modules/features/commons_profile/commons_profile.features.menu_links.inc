<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_profile_menu_default_menu_links() {
  $menu_links = array();

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
    'weight' => '30',
    'parent_path' => 'community',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Members');


  return $menu_links;
}
