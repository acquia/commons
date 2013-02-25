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
  $palette = variable_get('commons_origins_palette', 'default');
  if ($palette != 'default') {
    $vars['classes_array'][] = 'palette-active';
    $vars['classes_array'][] = drupal_html_class($palette);
  }

  // Two examples of adding custom classes to the body.

  // Add a body class for the active theme name.
  // $vars['classes_array'][] = drupal_html_class($theme_key);

  // Browser/platform sniff - adds body classes such as ipad, webkit, chrome etc.
  $vars['classes_array'][] = css_browser_selector();

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
  if ($vars['promote']) {
    $vars['submitted'] .= ' <span class="featured-node-tooltip">' . t('Featured') . ' ' . $vars['type'] . '</span>';
  }

  if (empty($vars['user_picture'])) {
    $vars['classes_array'][] = 'no-user-picture';
  }

  // Add classes to render the comment-comments link as a button with a number attached.
  if (!empty($vars['content']['links']['comment']['#links']['comment-comments'])) {
    $comments_link = &$vars['content']['links']['comment']['#links']['comment-comments'];
    $comments_link['attributes']['class'][] = 'link-with-counter';
    $comments_link['title'] = str_replace($vars['comment_count'], '<span class="counter">' . $vars['comment_count'] . '</span>', $comments_link['title']);
  }

  // Hide some of the node links.
  if (!empty($vars['content']['links'])) {
    $hidden_links = array(
      'node' => array(
        'node-readmore',
      ),
      'comment' => array(
        'comment-add',
        'comment-new-comments'
      ),
    );
    foreach ($hidden_links as $element => $links) {
      foreach ($links as $link) {
        if (!empty($vars['content']['links'][$element]['#links'][$link])) {
          $vars['content']['links'][$element]['#links'][$link]['#access'] = FALSE;
        }
      }
    }
  }

  // Replace the submitted text on nodes with something a bit more pertinent to
  // the content type.
  if (variable_get('node_submitted_' . $vars['node']->type, TRUE)) {
    $placeholders = array(
      '!type' => '<span class="node-content-type">' . ucfirst($vars['node']->type) . '</span>',
      '!user' => $vars['name'],
      '!date' => $vars['date'],
    );

    $vars['submitted'] = t('!type created by !user on !date', $placeholders);
  }
}

/**
* Implements hook_form_alter().
*/
function commons_origins_form_alter(&$form, &$form_state, $form_id) {
  if (isset($form['#node']) && substr($form_id, -10) == '_node_form' && isset($form['additional_settings']) && $form['#node']->type != 'post') {
    $form['additional_settings']['#type'] = 'fieldset';
  }
  // Description text on these fields is redundant.
  if ($form_id == 'user_login') {
    $form['name']['#description'] = '';
    $form['pass']['#description'] = '';
  }

  if ($form_id == 'user_register_form') {
    $form['account']['mail']['#description'] = t('Password reset and notification emails will be sent to this address.');
  }
}

/**
* Implements hook_css_alter().
*/
function commons_origins_css_alter(&$css) {
  if (isset($css['profiles/commons/modules/contrib/rich_snippets/rich_snippets.css'])) {
    unset($css['profiles/commons/modules/contrib/rich_snippets/rich_snippets.css']);
  }
}


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

/**
 * Overrides theme_links() for nodes.
 *
 * This allows for the theme to set a link's #access argument to FALSE so it
 * will not render.
 */
function commons_origins_links($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      if (!isset($link['#access']) || $link['#access'] !== FALSE) {
        $class = array($key);

        // Add first, last and active classes to the list of links to help out themers.
        if ($i == 1) {
          $class[] = 'first';
        }
        if ($i == $num_links) {
          $class[] = 'last';
        }
        if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page())) && (empty($link['language']) || $link['language']->language == $language_url->language)) {
          $class[] = 'active';
        }
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

        if (isset($link['href'])) {
          // Pass in $link as $options, they share the same keys.
          $output .= l($link['title'], $link['href'], $link);
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
          $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
        }

        $i++;
        $output .= "</li>\n";
      }
    }

    $output .= '</ul>';
  }

  return $output;
}
