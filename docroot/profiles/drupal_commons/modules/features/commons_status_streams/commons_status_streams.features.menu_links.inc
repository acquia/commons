<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_status_streams_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:stream
  $menu_links['primary-links:stream'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'stream',
    'router_path' => 'stream',
    'link_title' => 'Stream',
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
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Stream');


  return $menu_links;
}
