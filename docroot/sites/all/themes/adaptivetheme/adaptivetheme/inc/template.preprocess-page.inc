<?php // $Id: template.preprocess-page.inc,v 1.1.2.33 2010/02/16 02:20:11 jmburnz Exp $
// adaptivethemes.com

/**
 * @file template.preprocess-page.inc
 */

/**
 * Override or insert variables into page templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called.
 */

global $theme, $theme_info, $user, $language;

// Don't display empty help from node_help().
if ($vars['help'] == "<div class=\"help\"> \n</div>") {
  $vars['help'] = '';
}

// Remove sidebars if disabled e.g., for Panels.
if (!$vars['show_blocks']) {
  $vars['left'] = '';
  $vars['right'] = '';
}

// Skip navigation class.
if (theme_get_setting('skip_navigation_display') == 'hide') {
  $vars['skip_nav_class'] = 'element-invisible';
}

if (theme_get_setting('skip_navigation_display') == 'show') {
  $vars['skip_nav_class'] = 'show';
}

if (theme_get_setting('skip_navigation_display') == 'focus') {
  $vars['skip_nav_class'] = 'show-on-focus';
}

// Set variables for the logo and site name for easy printing in templates.
$vars['logo_alt_text']    = check_plain(variable_get('site_name', '')) .' '. t('logo');
$vars['logo_img']         = $vars['logo'] ? '<img src="'. check_url($vars['logo']) .'" alt="'. $vars['logo_alt_text'] .'" title="'. t('Home page') .'"/>' : '';
$vars['linked_site_logo'] = $vars['logo_img'] ? l($vars['logo_img'], '<front>', array('attributes' => array('rel' => 'home'), 'title' => t('Home page'), 'html' => TRUE)) : '';
$vars['linked_site_name'] = $vars['site_name'] ? l($vars['site_name'], '<front>', array('attributes' => array('rel' => 'home'), 'title' => t('Home page'))) : '';

// Set variables for the primary and secondary links.
$primary_menu_links = $vars['primary_links'];
$secondary_menu_links = $vars['secondary_links'];

// Standard primary and secondary links.
if (!empty($primary_menu_links)) {
  $vars['primary_menu'] = theme('links', $primary_menu_links, array('class' => 'primary-links clearfix'));
}
if (!empty($secondary_menu_links)) {
  $vars['secondary_menu'] = theme('links', $secondary_menu_links, array('class' => 'secondary-links clearfix'));
}

// Output the primary and secondary menus as regular menu trees.
if (!empty($primary_menu_links) && theme_get_setting('primary_links_tree')) {
  $primary_tree_menu = menu_tree_all_data('primary-links'); 
  $vars['primary_menu'] = menu_tree_output($primary_tree_menu);
}
if (!empty($secondary_menu_links) && theme_get_setting('secondary_links_tree')) {
  $secondary_tree_menu = menu_tree_all_data('secondary-links'); 
  $vars['secondary_menu'] = menu_tree_output($secondary_tree_menu);
}

// Attribution.
$vars['attribution'] = "<div id=\"attribution\"><a href=\"http://adaptivethemes.com\">Premium Drupal Themes</a></div>"  ;

// Body classes - manipulate for our own ends, in Drupal 7 we can drop most of these shenanagins.
$classes = explode(' ', $vars['body_classes']);

// Section class - use the path alias otherwise all nodes will be in "section-node".
if (theme_get_setting('cleanup_classes_section')) {
  $path_alias = drupal_get_path_alias($_GET['q']);
  if (!$vars['is_front']) {
    list($section, ) = explode('/', $path_alias, 2);
    $classes[] = safe_string('section-'. $section);
  }
}

// Unset Drupals page-arg(0) class.
if ($index = array_search(preg_replace('![^abcdefghijklmnopqrstuvwxyz0-9-_]+!s', '', 'page-'. drupal_strtolower(arg(0))), $classes)) {
  unset($classes[$index]);
}

// Replace "node-type" with the more semantic "article-type".
$classes = str_replace('node-type-', 'article-type-', $classes);

// Replace left and right with first and last - better support for RTL.
$classes = str_replace('sidebar-left', 'sidebar-first', $classes);
$classes = str_replace('sidebar-right', 'sidebar-last', $classes);

// .front and .not-front classes.
if (in_array('front', $classes)) {
  theme_get_setting('cleanup_classes_front') ? '' : $classes = str_replace('front', '', $classes);
}
if (in_array('not-front', $classes)) {
  theme_get_setting('cleanup_classes_front') ? '' : $classes = str_replace('not-front', '', $classes);
}

// User status classes.
if (in_array('logged-in', $classes)) {
  theme_get_setting('cleanup_classes_user_status') ? '' : $classes = str_replace('logged-in', '', $classes);
}
if (in_array('not-logged-in', $classes)) {
  theme_get_setting('cleanup_classes_user_status') ? '' : $classes = str_replace('not-logged-in', '', $classes);
}

// Article type classes.
if (in_array('article-type-'. $vars['node']->type, $classes)) {
  theme_get_setting('cleanup_classes_node_type') ? '' : $classes = str_replace('article-type-'. $vars['node']->type, '', $classes);
}

if (!$vars['is_front']) {
  // Replacement for Drupals page-arg(0) class, instead we print page-$normal_page.
  if (theme_get_setting('cleanup_classes_normal_path')) {
    $normal_path = drupal_get_normal_path($_GET['q']);
    $classes[] = safe_string('page-'. $normal_path);
  }
  // AT can use this class to restyle the blocks page.
  if (arg(2) == 'block') {
    $classes[] = 'page-block';
  }
  // Add extra classes for node add, edit and delete pages.
  if (theme_get_setting('cleanup_classes_add_edit_delete')) {
    if (arg(0) == 'node') {
      if (arg(1) == 'add') {
        $classes[] = 'article-add'; // Add .node-add class.
      }
      elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
        $classes[] = 'article-'. arg(2);
      }
    }
  }
}

// Language specific body class.
if (theme_get_setting('cleanup_classes_language')) {
  if (function_exists('locale')) {
    $classes[] = 'lang-'. $language->language;
  }
}

// $classes is the varaible that holds the page classes, printed in page tpl files.
$vars['classes'] = trim(implode(' ', $classes));

// Layout settings - set the page width and layout method.
if (theme_get_setting('layout_enable_settings') == 'on') {
  $vars['at_layout_width'] = '#container{width:'. theme_get_setting('layout_width') .';}';
  $method = theme_get_setting('layout_method');
  $sidebar_last_width = theme_get_setting('layout_sidebar_last_width');
  $sidebar_first_width = theme_get_setting('layout_sidebar_first_width');
  if ($vars['language']->dir == 'ltr') {
    $left = 'left';
    $right = 'right';
  }
  if ($vars['language']->dir == 'rtl') {
    $left = 'right';
    $right = 'left';
  }
  if ($method == '0') {
    $push_right = $sidebar_last_width;
    $push_left  = $sidebar_first_width;
    $pull_right = $sidebar_last_width;
    $styles = array();
    $styles[] = '.two-sidebars .content-inner{margin-'. $left .':'. $push_left .'px; margin-'. $right .':'. $push_right .'px;}';
    $styles[] = '.sidebar-first .content-inner{margin-'. $left .':'. $push_left .'px; margin-'. $right .':0;}';
    $styles[] = '.sidebar-last .content-inner{margin-'. $right .':'. $push_right .'px; margin-'. $left .':0;}';
    $styles[] = '#sidebar-first{width:'. $sidebar_first_width .'px;margin-'. $left .':-100%;}';
    $styles[] = '#sidebar-last{width:'. $sidebar_last_width .'px;margin-'. $left .':-'. $pull_right .'px;}';
  }
  if ($method == '1') {
    $content_margin = $sidebar_last_width + $sidebar_first_width;
    $push_right     = $sidebar_last_width;
    $push_left      = $sidebar_first_width;
    $left_margin    = $sidebar_last_width + $sidebar_first_width;
    $right_margin   = $sidebar_last_width;
    $styles = array();
    $styles[] = '.two-sidebars .content-inner{margin-'. $right .':'. $content_margin .'px;margin-'. $left .':0;}';
    $styles[] = '.sidebar-first .content-inner{margin-'. $right .':'. $push_left .'px;margin-'. $left .':0;}';
    $styles[] = '.sidebar-last .content-inner{margin-'. $right .':'. $push_right .'px;margin-'. $left .':0;}';
    $styles[] = '#sidebar-first{width:'. $sidebar_first_width .'px;margin-'. $left .':-'. $left_margin .'px;}';
    $styles[] = '#sidebar-last{width:'. $sidebar_last_width .'px;margin-'. $left .':-'. $right_margin .'px;}';
    $styles[] = '.sidebar-first #sidebar-first{width:'. $sidebar_first_width .'px;margin-'. $left .':-'. $sidebar_first_width .'px;}';
  }
  if ($method == '2') {
    $content_margin = $sidebar_last_width + $sidebar_first_width;
    $left_margin    = $sidebar_first_width;
    $right_margin   = $sidebar_last_width;
    $push_right     = $sidebar_first_width;
    $styles = array();
    $styles[] = '.two-sidebars .content-inner{margin-'. $left .':'. $content_margin .'px;margin-'. $right .':0;}';
    $styles[] = '.sidebar-first .content-inner{margin-'. $left .':'. $left_margin .'px;margin-'. $right .':0;}';
    $styles[] = '.sidebar-last .content-inner{margin-'. $left .':'. $right_margin .'px;margin-'. $right .':0;}';
    $styles[] = '#sidebar-first{width:'. $sidebar_first_width .'px; margin-'. $left .': -100%;}';
    $styles[] = '#sidebar-last{width:'. $sidebar_last_width .'px; margin-'. $left .': -100%;}';
    $styles[] = '.two-sidebars #sidebar-last {width:'. $sidebar_last_width .'px; position: relative;'. $left .':'. $push_right .'px;}';
  }
  $styles ? $vars['at_layout'] = implode('', $styles) : '';
  $vars['layout_settings'] = '<style type="text/css">'. $vars['at_layout_width'] . $vars['at_layout'] .'</style>';
}

// Display mission statement on all pages.
if (theme_get_setting('mission_statement_pages') == 'all') {
  $vars['mission'] = theme_get_setting('mission', FALSE);
}

// Show $theme_info output using krumo.
if (module_exists('devel') && theme_get_setting('show_theme_info') == 1) {
  dsm($theme_info); /* Use dsm, kpr messes up IE */
}

// Check whether help is disabled.
if (theme_get_setting('at_admin_hide_help')) {
  unset($vars['help']);
}

// Hide search theme form label
if ($vars['search_box'] && theme_get_setting('display_search_form_label') == 0) {
  $vars['toggle_label'] = ' class="hide-label"';
}

// Admin user links.
if ($vars['logged_in'] && theme_get_setting('at_user_menu') == 1) {
  if (!function_exists(admin_menu_perm)) {
    $admin_user_links[] = l(t('Create content'), 'node/add');
    $admin_user_links[] = user_access('administer nodes') ? l(t('Manage content'), 'admin/content/node') : '';
    $admin_user_links[] = user_access('administer blocks') ? l(t('Blocks'), 'admin/build/block') : '';
    $admin_user_links[] = user_access('administer menu') ? l(t('Menus'), 'admin/build/menu') : '';
    $admin_user_links[] = user_access('administer users') ? l(t('Users'), 'admin/user/user') : '';
    $admin_user_links[] = user_access('access administration pages') ? l(t('Admin'), 'admin') : '';
  }
  if ($vars['logged_in']) {
    $admin_user_links[] = l(t('My Account'), 'user/'. $user->uid);
  }
  if (!function_exists(admin_menu_perm)) {
    $admin_user_links[] = l(t('Logout'), 'logout');
  }
  $vars['admin_user_menu'] = $admin_user_links;
  $vars['admin_user_links'] = theme('item_list', $admin_user_links);
}