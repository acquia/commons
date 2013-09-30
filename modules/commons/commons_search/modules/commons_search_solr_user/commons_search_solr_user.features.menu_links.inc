<?php
/**
 * @file
 * commons_search_solr_user.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function commons_search_solr_user_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:people
  $menu_links['main-menu:people'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'people',
    'router_path' => 'people',
    'link_title' => 'People',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 5,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('People');


  return $menu_links;
}
