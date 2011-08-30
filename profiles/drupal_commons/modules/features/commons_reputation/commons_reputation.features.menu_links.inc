<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_reputation_menu_default_menu_links() {
  $menu_links = array();

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
    'weight' => '0',
    'parent_path' => 'user',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('My points');


  return $menu_links;
}
