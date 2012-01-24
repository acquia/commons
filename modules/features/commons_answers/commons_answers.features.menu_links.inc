<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_answers_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:questions/all
  $menu_links['primary-links:questions/all'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'questions/all',
    'router_path' => 'questions/all',
    'link_title' => 'Q & A',
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
    'parent_path' => 'community',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Q & A');


  return $menu_links;
}
