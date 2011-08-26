<?php

/**
 * Theme a group hierachy tree
 * 
 * @param $group
 *   Optionally supply a group to focus
 * @return
 *   An HTML-rendered tree of group links
 */
function theme_og_subgroups_menu_tree($group) {
  og_subgroups_include('tree');
  
  // Fetch the group tree
  if (!($tree = og_subgroups_get_group_tree($group))) {
    // If no tree, then no menu
    return NULL;
  }
  
  // Fetch settings for the treeview and controls
  $treeview = variable_get('og_subgroups_block_use_treeview', 1);
  $controls = variable_get('og_subgroups_block_use_treeview_controls', 1);
  $ajax = variable_get('og_subgroups_block_use_treeview_ajax', 0);
  
  // Add treeview externals
  if ($treeview) {
    $path = drupal_get_path('module', 'og_subgroups');
    drupal_add_css($path . '/theme/og_subgroups.css');
    drupal_add_css($path . '/theme/jquery.treeview.css');
    drupal_add_js($path . '/scripts/jquery.treeview.min.js');
    
    // Determine which additional JS settings we need
    $js_settings = array();
    if ($controls) {
      $js_settings[] = "control: '#og-subgroups-tree-controls-{$group->nid}'";
    }
    if ($ajax) {
      $js_settings[] = "url: Drupal.settings.basePath + 'subgroups/tree/{$group->nid}'";
      drupal_add_js($path . '/scripts/jquery.treeview.async.js');
    }
    
    // Add the declaration for treeview
    drupal_add_js("
      $(document).ready(function() {
        $('ul.og-subgroups-menu-tree').treeview({ 
          collapsed: true,
          animated: 'fast',
          " . (!empty($js_settings) ? implode(",\n\t", $js_settings) : '') . "
        });
      });
    ", 'inline');
  }
  
  // Wrap the entire block in a div
  $content .= "<div id=\"og-subgroups-tree-{$group->nid}\" class=\"og-subgroups-tree\">";
 
  // If we're using the treeview, and controls are desired, add them
  if ($treeview && $controls) {
    $content .= "<div id=\"og-subgroups-tree-controls-{$group->nid}\" class=\"og-subgroups-tree-controls\">";
    $content .= '<a title="' . t('Collapse the entire tree below') . '" href="#">' . t('Collapse') . '</a> | '; 
	  $content .= '<a title="' . t('Expand the entire tree below') . '" href="#">' . t('Expand') . '</a>'; 
    $content .= '</div>'; 
  }
  
  // Generate a list of the groups parents
  $parents = og_subgroups_get_group_parents($group);
  
  // Wrap the list
  $content .= "<ul id=\"og-subgroups-menu-tree-{$group->nid}\" class=\"og-subgroups-menu-tree\">";
  
  // If we're using treeview with AJAX, we do not need to generate the tree here
  if (!($treeview && $ajax)) {
    // Iterate the tree to begin generating nested links
    foreach ($tree as $branch) {
      // If the branch has no children, end here
      if (empty($branch->children)) {
        return NULL; 
      }
  
      $content .= '<li class="open og-subgroups-tree-active-trail">';
      $content .= theme('og_subgroups_menu_tree_link', $group, $branch);
    
      // Recursively add the rest of the tree
      if (!empty($branch->children)) {
        $content .= '<ul>' . theme('og_subgroups_menu_tree_branch', $group, $branch->children, $parents) . '</ul>';
      }
    
      $content .= '</li>';
    }
  }
  
  $content .= '</ul>';
  $content .= '</div>';
  
  return $content;
}

/**
 * Theme a group hierachy tree branch
 * 
 * @param $group
 *   Optionally supply a group to focus
 * @param $branch
 *   An array of tree branch stems
 * @param $parents
 *   An array, keyed by group nid, of the $group's parents
 * @return
 *   An HTML-rendered tree of group links
 */
function theme_og_subgroups_menu_tree_branch($group, $branch, $parents) {
  $content = '';
  foreach ($branch as $stem) {
    $class = array();
    if ($group->nid == $stem->nid) {
      $class[] = 'og-subgroups-tree-active-trail';
    }
    
    if (in_array($stem->nid, array_keys($parents))) {
      $class[] = 'open';
      $class[] = 'og-subgroups-tree-active-trail';
    }
    
    $content .= '<li' . (!empty($class) ? ' class="' . implode(" ", $class) . '"' : '') . '>' . theme('og_subgroups_menu_tree_link', $group, $stem);
    
    if (!empty($stem->children)) {
      $content .= '<ul>' . theme('og_subgroups_menu_tree_branch', $group, $stem->children, $parents) . '</ul>';
    }
    
    $content .= '</li>';
  }
  return $content;
}

/**
 * Theme callback to output a link for a group tree
 * 
 * @param $current
 *   The current group being view
 * @param $group
 *   The group we're generating a link for
 * @param $access
 *   Whether or not to check each link for adequate access, neaning if
 *   the group is private, and the user is not a member, mask the name
 *   and provide plain-text instead of a link. The same goes for unpublished
 *   group nodes. @see og_subgroups_mask_group_title()
 */
function theme_og_subgroups_menu_tree_link($current, $group, $access = TRUE) {
  // Check access, if desired
  if ($access) {
    // Mask the group title, if needed
    if (og_subgroups_mask_group($group)) {
      // If it was masked, return just the title instead of a link
      return $group->title;
    }
  }
  
  // Generate the link
  $link = array(
    'title' => $group->title,
    'href' => "node/{$group->nid}",
    'options' => array()
  );
  
  // See if this link is for the current group
  if ($current->nid == $group->nid) {
    // Add an active class
    $link['options']['attributes']['class'] = 'og-subgroups-tree-active';
  }
  
  return l($link['title'], $link['href'], $link['options']);
}
