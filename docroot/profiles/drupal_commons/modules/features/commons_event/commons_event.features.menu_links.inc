<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_event_menu_default_menu_links() {
  $menu_links = array();

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
  // Translatables
  // Included for use with string extractors like potx.
  t('Calendar');


  return $menu_links;
}
