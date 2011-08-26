<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_discussion_menu_default_menu_links() {
  $menu_links = array();

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
  // Translatables
  // Included for use with string extractors like potx.
  t('Discussions');


  return $menu_links;
}
