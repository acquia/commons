<?php

/**
 * @file
 * Page callbacks for wikitools pages.
 */

/**
 * Menu callback for wiki path.
 * This function is called if a page without an alias is called below the wiki path.
 */
function wikitools_handle_request() {
  $output = '';

  // Create list of path parts.
  $args = explode('/', $_GET['q']);

  // Calculate index of first path argument after wiki path.
  if (arg(0) != 'freelinking') {
    $i = count(explode('/', wikitools_wiki_path()));
  }
  else {
    $i = 1;
  }

  // Determine subpage.
  $subpage = NULL;
  if (wikitools_subpages_handling() == 'query') {
    // Check if a query string is in the URL with a valid subpage
    if (isset($_GET[wikitools_subpages_query_string()])) {
      $subpage = $_GET[wikitools_subpages_query_string()];
      if (!in_array($subpage, wikitools_subpages())) {
        $subpage = NULL;
      }
    }
  }
  elseif (wikitools_subpages_handling() == 'url') {
    // Check if there are more than one part, and if the last one is a valid subpage.
    if (count($args)-$i > 1 && in_array(end($args), wikitools_subpages())) {
      $subpage = end($args);
      array_pop($args);
    }
  }

  // Determine page name.
  if (isset($args[$i])) {
    $page_name = wikitools_decode_page_name(implode('/', array_slice($args, $i)));
  }
  else {
    // Use default page title if only wiki path is entered.
    $page_name = wikitools_main_page_title();
  }

  // Don't do anything if no node types are active or no page name is available
  $node_types = wikitools_node_types();
  if (count($node_types) && $page_name) {
    // Try to find the current page with this name.
    $result = db_query("SELECT nid, type FROM {node} WHERE LOWER(title) = LOWER('%s')", $page_name);
    $found_nodes = array();
    while ($node = db_fetch_object($result)) {
      if (wikitools_type_affected($node->type)) {
        $found_nodes[] = $node;
      }
    }
    if (count($found_nodes) == 1) {
      // Single match for title.
      $node = current($found_nodes);
      if ($subpage) {
        drupal_goto("node/$node->nid/$subpage");
      }
      else {
        drupal_goto("node/$node->nid");
      }
    }
    else if (count($found_nodes) > 1) {
      // Multiple match for title.
      drupal_set_title(t('Page found: %page', array('%page' => $page_name)));
      $output .= theme('wikitools_page_found', $page_name, $found_nodes);
    }
    else {
      // No match for title. Try to find an old page with this name
      $result = db_query("SELECT n.nid, n.type, n.title FROM {node} n LEFT JOIN {node_revisions} r ON n.nid = r.nid WHERE LOWER(r.title) = LOWER('%s') ORDER BY n.vid DESC", $page_name);
      $moved_nodes = array();
      while ($node = db_fetch_object($result)) {
        if (wikitools_type_affected($node->type)) {
          $moved_nodes[] = $node;
        }
      }
      if (count($moved_nodes) > 0 && wikitools_auto_redirect() && !isset($_REQUEST['noredirect'])) {
        $node = current($moved_nodes);
        drupal_set_message(t('Redirected from <a href="@url">%page</a>', array('%page' => $page_name, '@url' => wikitools_wikilink_url($page_name, 'noredirect'))));
        drupal_goto("node/$node->nid");
      }
      else if (count($moved_nodes) > 0) {
        drupal_set_title(t('Page moved: %page', array('%page' => $page_name)));
        $output = theme('wikitools_page_moved', $page_name, $moved_nodes);
      }
      else {
        drupal_set_title(t('Page does not exist: %page', array('%page' => $page_name)));
        $output = theme('wikitools_page_does_not_exist', $page_name);
      }
    }
  }

  if (empty($output)) {
    return MENU_NOT_FOUND;
  }

  return $output;
}

/**
 * Theme functions
 * @ingroup themeable
 */

function theme_wikitools_page_found($page_name, $found_nodes) {
  $output = '<p>'. t('Multiple pages have this name:') .'</p>';
  foreach ($found_nodes as $info) {
    $node = node_load($info->nid);
    $output .= node_view($node, TRUE, FALSE, FALSE);
  }
  $output .= theme('wikitools_search_notice', $page_name);
  if (!wikitools_enforce_unique_titles()) {
    $output .= theme('wikitools_create_notice', $page_name);
  }
  return $output;
}

function theme_wikitools_page_moved($page_name, $moved_nodes) {
  $output = '<p>'. t('The page %page_name has been moved.', array('%page_name' => $page_name)) .'</p>';
  $node = current($moved_nodes);
  $output .= '<p>'. t('The new page name is !new_name', array('!new_name' => l($node->title, "node/$node->nid"))) .'</p>';
  // Todo: show all moved pages
  $output .= theme('wikitools_search_notice', $page_name);
  $output .= theme('wikitools_create_notice', $page_name);
  return $output;
}

function theme_wikitools_page_does_not_exist($page_name) {
  $output = '<p>'. t('The page %page_name does not exist.', array('%page_name' => $page_name)) .'</p>';
  $settings = wikitools_404();
  if (!empty($settings['Link to search'])) {
    $output .= theme('wikitools_search_notice', $page_name);
  }
  if (!empty($settings['Link to creation'])) {
    $output .= theme('wikitools_create_notice', $page_name);
  }
  if (!empty($settings['Creation form'])) {
    $output .= theme('wikitools_create', $page_name);
  }
  return $output;
}

function theme_wikitools_search_notice($page_name) {
  $output = '';
  if (module_exists('search') && user_access('search content') && wikitools_node_search()) {
    $output .= '<p>'. t('You can <a href="@url">search for %page_name</a>', array('@url' => wikitools_search_url($page_name), '%page_name' => $page_name)) .'</p>';
  }
  return $output;
}

function theme_wikitools_create_notice($page_name) {
  $output = '';
  $node_types = wikitools_node_types();
  if (wikitools_node_creation() && count($node_types)) {
    $create = '';
    $count = 0;
    foreach ($node_types as $type) {
      $type = node_get_types('type', $type);
      if (node_access('create', $type->type)) {
        $create .= '<dt><a href="'. wikitools_create_url($type, $page_name) .'">'. $type->name .'</a></dt>';
        $create .= '<dd>'. filter_xss_admin($type->description) .'</dd>';
      }
    }
    if ($create) {
      $output .= '<p>'. t('You can create the page as:') .'</p>';
      $output .= '<dl>'. $create .'</dl>';
    }
  }
  return $output;
}

function theme_wikitools_create($page_name) {
  $node_types = wikitools_node_types();
  $form = array();
  $output = '';
  if (wikitools_node_creation() && count($node_types)) {
    $output .= '<p>'. t('You can create the page as:') .'</p>';
    // Collapse the forms initially if there are more than one.
    $collapsed = count($node_types) > 1 ? ' collapsed' : '';
    // The form_alter hooks excpects the preset title in the GET array, so we put it there.
    $_GET['edit']['title'] = $page_name;
    foreach ($node_types as $type) {
      drupal_add_js('misc/collapse.js');
      $type = node_get_types('type', $type);
      if (node_access('create', $type->type)) {
        $output .= '<fieldset class="collapsible' . $collapsed . '"><legend>'. $type->name .'</legend>';
        if ($router_item = menu_get_item('node/add/'. str_replace('_', '-', $type->type))) {
          if ($router_item['file']) {
            require_once($router_item['file']);
          }
          $output .= call_user_func_array($router_item['page_callback'], $router_item['page_arguments']);
        }
        $output .= '</fieldset>';
      }
    }
    // Some of the callbacks could have set the page title, so we reset it.
    drupal_set_title(t('Page does not exist: %page', array('%page' => $page_name)));
  }
  return $output;
}
