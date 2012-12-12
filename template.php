<?php

/**
 * @file
 * Process theme data.
 *
 * Use this file to run your theme specific implimentations of theme functions,
 * such preprocess, process, alters, and theme function overrides.
 *
 * Preprocess and process functions are used to modify or create variables for
 * templates and theme functions. They are a common theming tool in Drupal, often
 * used as an alternative to directly editing or adding code to templates. Its
 * worth spending some time to learn more about these functions - they are a
 * powerful way to easily modify the output of any template variable.
 *
 * Preprocess and Process Functions SEE: http://drupal.org/node/254940#variables-processor
 * 1. Rename each function and instance of "commons_origins" to match
 *    your subthemes name, e.g. if your theme name is "footheme" then the function
 *    name will be "footheme_preprocess_hook". Tip - you can search/replace
 *    on "commons_origins".
 * 2. Uncomment the required function to use.
 */




/**
 * Preprocess variables for the html template.
 */
function commons_origins_preprocess_html(&$vars) {
  global $theme_key;

  $site_name = variable_get('site_name', 'Commons');

  if (strlen($site_name) > 23) {
    $vars['classes_array'][] = 'site-name-long-2-lines';
  } else if (strlen($site_name) > 15) {
    $vars['classes_array'][] = 'site-name-long';
  }

  // Two examples of adding custom classes to the body.

  // Add a body class for the active theme name.
  // $vars['classes_array'][] = drupal_html_class($theme_key);

  // Browser/platform sniff - adds body classes such as ipad, webkit, chrome etc.
  // $vars['classes_array'][] = css_browser_selector();

}
//


/**
 * Process variables for the html template.
 */
/* -- Delete this line if you want to use this function
function commons_origins_process_html(&$vars) {
}
// */

/**
 * Implements theme_menu_link().
 */
function commons_origins_menu_link($vars) {
  $output = '';
  $path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

  include_once($path_to_at_core . '/inc/get.inc');

  global $theme_key;
  $theme_name = $theme_key;

  $element = $vars['element'];
  commons_origins_menu_link_class($element);
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  if (at_get_setting('extra_menu_classes', $theme_name) == 1 && !empty($element['#original_link'])) {
    if (!empty($element['#original_link']['depth'])) {
      $element['#attributes']['class'][] = 'menu-depth-' . $element['#original_link']['depth'];
    }
    if (!empty($element['#original_link']['mlid'])) {
      $element['#attributes']['class'][] = 'menu-item-' . $element['#original_link']['mlid'];
    }
  }

  if (at_get_setting('menu_item_span_elements', $theme_name) == 1 && !empty($element['#title'])) {
    $element['#title'] = '<span>' . $element['#title'] . '</span>';
    $element['#localized_options']['html'] = TRUE;
  }

  if (at_get_setting('unset_menu_titles', $theme_name) == 1 && !empty($element['#localized_options']['attributes']['title'])) {
    unset($element['#localized_options']['attributes']['title']);
  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>";
}

/**
 * Helper function to examine menu links and return the appropriate class.
 */
function commons_origins_menu_link_class(&$element)  {
  if ($element['#original_link']['menu_name'] == 'main-menu') {
    $element['#attributes']['class'][] = drupal_html_class($element['#original_link']['menu_name'] . '-' . $element['#original_link']['router_path']);
  }
}

/**
 * Override or insert variables for the page templates.
 */
function commons_origins_preprocess_page(&$vars) {
  if (module_exists('page_manager')) {
    $p = page_manager_get_current_page();
    if (isset($p['name']) && $p['name'] == 'node_view') {
      $node = $p['contexts']['argument_entity_id:node_1']->data;
      if (module_exists('og') && !og_is_group('node', $node)) {
        $vars['hide_panelized_title'] = 1;
      }
    }
  }
}
function commons_origins_process_page(&$vars) {
}
// */


/**
 * Override or insert variables into the node templates.
 */
function commons_origins_preprocess_node(&$vars) {
  // dpm($vars);

  if ($vars['promote']) {
    $vars['submitted'] .= ' <span class="featured-node-tooltip">' . t('Featured') . ' ' . $vars['type'] . '</span>';
  }
}
function commons_origins_process_node(&$vars) {
}
// */


/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function commons_origins_preprocess_comment(&$vars) {
}
function commons_origins_process_comment(&$vars) {
}
// */


/**
 * Override or insert variables into the block templates.
 */
/* -- Delete this line if you want to use these functions
function commons_origins_preprocess_block(&$vars) {
}
function commons_origins_process_block(&$vars) {
}
// */
