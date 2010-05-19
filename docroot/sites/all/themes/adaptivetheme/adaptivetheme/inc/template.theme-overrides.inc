<?php // $Id: template.theme-overrides.inc,v 1.1.2.19 2010/03/16 11:08:37 jmburnz Exp $
// adaptivethemes.com

/**
 * @file template.theme-overrides.inc
 */

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function adaptivetheme_breadcrumb($breadcrumb) {
  // Determine if we are to display the breadcrumb.
  $show_breadcrumb = theme_get_setting('breadcrumb_display');
  if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {

    // Optionally get rid of the homepage link.
    $show_breadcrumb_home = theme_get_setting('breadcrumb_home');
    if (!$show_breadcrumb_home) {
      array_shift($breadcrumb);
    }

    // Return the breadcrumb with separators.
    if (!empty($breadcrumb)) {
      $breadcrumb_separator = filter_xss(theme_get_setting('breadcrumb_separator'));
      $trailing_separator = $title = '';
      if (theme_get_setting('breadcrumb_title')) {
        $trailing_separator = $breadcrumb_separator;
        $title = menu_get_active_title();
        if ((module_exists('taxonomy')) && arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
          $title = drupal_get_title();
        }
      }
      elseif (theme_get_setting('breadcrumb_trailing')) {
        $trailing_separator = $breadcrumb_separator;
      }
      return implode($breadcrumb_separator, $breadcrumb) . $trailing_separator . $title;
    }
  }
  // Otherwise, return an empty string.
  return '';
}

/**
 * Override username theming to display/hide 'not verified' text
 */
function adaptivetheme_username($object) {
  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables.
    if (drupal_strlen($object->name) > 20) {
      $name = drupal_substr($object->name, 0, 15) .'...';
    }
    else {
      $name = $object->name;
    }
    if (user_access('access user profiles')) {
      $output = l($name, 'user/'. $object->uid, array('attributes' => array('title' => t('View user profile.'))));
    }
    else {
      $output = check_plain($name);
    }
  }
  else if ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if (!empty($object->homepage)) {
      $output = l($object->name, $object->homepage, array('attributes' => array('rel' => 'nofollow')));
    }
    else {
      $output = check_plain($object->name);
    }
    // Display or hide 'not verified' text
    if (theme_get_setting('user_notverified_display') == 1) {
      $output .= ' ('. t('not verified') .')';
    }
  }
  else {
    $output = variable_get('anonymous', t('Anonymous'));
  }
  return $output;
}

/**
 * Theme a form button.
 */
function adaptivetheme_button($element) {
  if (isset($element['#attributes']['class'])) {
    $element['#attributes']['class'] = 'form-'. $element['#button_type'] .' '. $element['#attributes']['class'];
  }
  else {
    $element['#attributes']['class'] = 'form-'. $element['#button_type'];
  }

  // Wrap visible inputs with span tags for button graphics
  if (stristr($element['#attributes']['style'], 'display: none;') || stristr($element['#attributes']['class'], 'fivestar-submit')) {
    return '<input type="submit" '. (empty($element['#name']) ? '' : 'name="'. $element['#name'] .'" ')  .'id="'. $element['#id'] .'" value="'. check_plain($element['#value']) .'" '. drupal_attributes($element['#attributes']) ." />\n";
  }
  else {
    return '<span class="button-wrapper '. $element['#id'] .'"><span class="button"><input type="submit" '. (empty($element['#name']) ? '' : 'name="'. $element['#name'] .'" ')  .'id="'. $element['#id'] .'" value="'. check_plain($element['#value']) .'" '. drupal_attributes($element['#attributes']) ." /></span></span>\n";
  }
}

/**
 * Format a group of form items.
 *
 * @param $element
 *   An associative array containing the properties of the element.
 *
 * @return
 *   A themed HTML string representing the form item group.
 */
function adaptivetheme_fieldset($element) {
  if ($element['#collapsible']) {
    drupal_add_js('misc/collapse.js');

    if (!isset($element['#attributes']['class'])) {
      $element['#attributes']['class'] = '';
    }

    $element['#attributes']['class'] .= ' collapsible';
    if ($element['#collapsed']) {
     $element['#attributes']['class'] .= ' collapsed';
    }
  }
  // Custom fieldset CSS class from element #title.
  $css_class = 'fieldset-'. safe_string($element['#title']);

  $element['#attributes']['class'] .= (!empty($element['#attributes']['class']) ? " " : "") . $css_class;

  return '<fieldset'. drupal_attributes($element['#attributes']) .'>'. ($element['#title'] ? '<legend>'. $element['#title'] .'</legend>' : '') . ($element['#description'] ? '<div class="description">'. $element['#description'] .'</div>' : '') . $element['#children'] . $element['#value'] ."</fieldset>\n";
}

/**
 * Modify the theme settings form for our theme.
 * In short this collapses the fieldsets on the theme configuration page.
 */
function adaptivetheme_system_settings_form($form) {
  // Reset titles.
  $form['theme_settings']['#title'] = t('Drupal core theme settings');
  $form['theme_specific']['#title'] = t('Advanced theme settings');
  // Collapse all fieldsets and give them a wrapper to help out themers.
  $form_elements = element_children($form);
  foreach ($form_elements as $element) {
    if ($form[$element]['#type'] == 'fieldset') {
      $form[$element]['#collapsible'] = TRUE;
      $form[$element]['#collapsed']   = TRUE;
      $form[$element]['#prefix'] = '<div class="'. safe_string($element) .'-settings-wrapper">';
      $form[$element]['#suffix'] = '</div>';
    }
  }
  return drupal_render($form);
}

// If DHTML module is installed dont override theme_menu_tree and theme_menu_item.
if (!function_exists('dhtml_menu_init')) {
  /**
   * Generate the HTML output for a menu tree
   *
   * @ingroup themeable
   */
  function adaptivetheme_menu_tree($tree) {
    if (theme_get_setting('cleanup_menu_menu_class')) {
      return "<ul class=\"menu\">\n $tree </ul>\n";
    }
    else{
      return "<ul>\n $tree \n</ul>\n";
    }
  }
  /**
   * Generate the HTML output for a menu item and submenu.
   */
  function adaptivetheme_menu_item($link, $has_children, $menu = '', $in_active_trail = FALSE, $extra_class = NULL) {
    static $counter = 0;
    if (theme_get_setting('cleanup_menu_leaf_class')) {
      $class = ($menu ? 'expanded' : ($has_children ? 'collapsed' : 'leaf'));
    }
    if ($class == 'leaf') {
      $counter ++;
      if ($extra_class == 'last') {
        if ($counter == 1) {
          $extra_class = 'single-item';
        }
        else $counter = 0;
      }
    }
    if (!empty($extra_class) && theme_get_setting('cleanup_menu_first_last_classes')) {
      if ($class) {
        $class .= ' '. $extra_class;
      }
      else {
        $class .= $extra_class;
      }
    }
    if (theme_get_setting('cleanup_menu_title_class')) {
      $class .= ' ' . safe_string(strip_tags($link));
    }
    if ($in_active_trail && theme_get_setting('cleanup_menu_active_classes')) {
      $class .= ' active-trail';
    }
    if ($class) {
      return '<li class="'. $class .'">'. $link . $menu ."</li>\n";
    }
    else{
      return '<li>'. $link . $menu ."</li>\n";
    }
  }
}

/**
 * Return a themed set of links.
 *
 * @param $links
 *   A keyed array of links to be themed.
 * @param $attributes
 *   A keyed array of attributes
 * @return
 *   A string containing an unordered list of links.
 */
function adaptivetheme_links($links, $attributes = array('class' => 'links')) {
  $output = '';
  if (count($links) > 0) {
    if (theme_get_setting('cleanup_links_type_class')) {
      $output = '<ul'. drupal_attributes($attributes) .'>';
    }
    else{
      $output = '<ul>';
    }
    $num_links = count($links);
    $i = 1;
    foreach ($links as $key => $link) {
      $class = $key;
      if (theme_get_setting('cleanup_links_first_last_classes')) {
        // Add first, last and active classes to the list of links to help out themers.
        if ($i == 1) {
          $class .= ' first';
        }
        if ($i == $num_links) {
          $class .= ' last';
        }
      }
      // Add Access keys if set for AT Mobile theme.
      if (theme_get_setting('add_access_keys')) {
        $link['attributes']['accesskey'] = $i;
      }
      if (theme_get_setting('cleanup_links_active_classes')) {
        if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))) {
          $class .= ' active';
        }
      }
      if (isset($link['href'])) {
        // add active class for containing <li> and <a> if active-trail is set on the link itself.
        if (theme_get_setting('cleanup_links_active_classes')) {
          if (strpos($link['attributes']['class'], 'active-trail') !== FALSE && strpos($class, 'active') === FALSE) {
            $class .= ' active';
            $link['attributes']['class'] .= ' active';
          }
        }
      
        // wrap <span>'s around the anchor text
        if (theme_get_setting('links_add_span_elements')) {
          $link['title'] = '<span>' . check_plain($link['title']) . '</span>';
          $link['html'] = TRUE;
        }

        // Pass in $link as $options, they share the same keys.
        $link = l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $link = '<span'. $span_attributes .'>'. $link['title'] .'</span>';
      }
      $i++;
      $output .= '<li'. drupal_attributes(array('class' => $class)) .'>';
      $output .= $link;
      $output .= "</li>\n";
    }
    $output .= "</ul>\n";
  }
  return $output;
}

/**
 * Return a themed list of items.
 *
 * @param $items
 *   An array of items to be displayed in the list. If an item is a string,
 *   then it is used as is. If an item is an array, then the "data" element of
 *   the array is used as the contents of the list item. If an item is an array
 *   with a "children" element, those children are displayed in a nested list.
 *   All other elements are treated as attributes of the list item element.
 * @param $title
 *   The title of the list.
 * @param $type
 *   The type of list to return (e.g. "ul", "ol")
 * @param $attributes
 *   The attributes applied to the list element.
 * @return
 *   A string containing the list output.
 */
function adaptivetheme_item_list($items = array(), $title = NULL, $type = 'ul', $attributes = NULL) {
  $output = '<div class="item-list">';
  if (isset($title)) {
    $output .= '<h3>'. $title .'</h3>';
  }
  if (!empty($items)) {
    $output .= "<$type". drupal_attributes($attributes) .'>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $attributes = array();
      $children = array();
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        $data .= theme_item_list($children, NULL, $type, $attributes); // Render nested list
      }
      if (theme_get_setting('cleanup_item_list_zebra')) {
        if ($i & 1) {
          $attributes['class'] = empty($attributes['class']) ? 'odd' : ($attributes['class'] .' odd');
        }
        else {
          $attributes['class'] = empty($attributes['class']) ? 'even' : ($attributes['class'] .' even');
        }
      }
      if (theme_get_setting('cleanup_item_list_first_last')) {
        if ($i == 0) {
          $attributes['class'] = empty($attributes['class']) ? 'first' : ($attributes['class'] .' first');
        }
        if ($i == $num_items - 1) {
          $attributes['class'] = empty($attributes['class']) ? 'last' : ($attributes['class'] .' last');
        }
      }
      $output .= '<li'. drupal_attributes($attributes) .'>'. $data ."</li>\n";
    }
    $output .= "</$type>";
  }
  $output .= '</div>';
  return $output;
}
