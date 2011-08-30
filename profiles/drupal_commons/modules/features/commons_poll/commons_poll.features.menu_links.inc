<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_poll_menu_default_menu_links() {
  $menu_links = array();

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
  // Translatables
  // Included for use with string extractors like potx.
  t('Polls');


  return $menu_links;
}
