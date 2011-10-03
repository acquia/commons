<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_wiki_menu_default_menu_links() {
  $menu_links = array();

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
  // Translatables
  // Included for use with string extractors like potx.
  t('Wikis');


  return $menu_links;
}
