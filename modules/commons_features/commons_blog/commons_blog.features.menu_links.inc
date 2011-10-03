<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function commons_blog_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:content/blogs
  $menu_links['primary-links:content/blogs'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'content/blogs',
    'router_path' => 'content/blogs',
    'link_title' => 'Blog posts',
    'options' => array(),
    'module' => 'commons',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-40',
    'parent_path' => 'community',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Blog posts');


  return $menu_links;
}
