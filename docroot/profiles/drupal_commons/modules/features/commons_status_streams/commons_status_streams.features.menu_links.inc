<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function test_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:statuses/all
  $menu_links['primary-links:all-activity'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'statuses/all',
    'router_path' => 'statuses/all',
    'link_title' => 'All activity',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
    'parent_path' => 'community',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('All activity');


  return $menu_links;
}
