<?php

/**
 * @file
 *   JSON callback functions for og subgroups
 */

/**
 * Generate a group hierarchy tree in JSON format
 * 
 * This is used by jQuery Treeview to load the tree via AJAX
 * 
 * @param $node
 *   The group node
 */
function og_subgroups_group_tree_json($group) {
  $json = new stdClass;
  og_subgroups_include('tree');

  // Make sure this is a group node
  if (!og_is_group_type($group->type)) {
    return drupal_json();
  }

  // Fetch the group tree
  if (!($tree = og_subgroups_get_group_tree($group))) {
    // If no tree, then no menu
    return drupal_json();
  }
  
  // Generate a list of the groups parents
  $parents = og_subgroups_get_group_parents($group);
  
  // Iterate the tree to begin generating nested links
  foreach ($tree as $branch) {
    // If the branch has no children, end here
    if (empty($branch->children)) {
      return drupal_json(); 
    }
  
    $json->text = theme('og_subgroups_menu_tree_link', $group, $branch);
    $json->expanded = TRUE;
    
    // Recursively add the rest of the tree
    if (!empty($branch->children)) {
      $json->children = _og_subgroups_group_tree_branch_json($group, $branch->children, $parents);
    }
  }
  
  return drupal_json(array($json));
}

/**
 * Recursive callback to return a tree branch in the format needed for JSON
 */
function _og_subgroups_group_tree_branch_json($group, $branch, $parents) {
  $children = array();
  foreach ($branch as $stem) {
    $expanded = in_array($stem->nid, array_keys($parents)) ? TRUE : FALSE;
    $json = new stdClass;
    $json->text = theme('og_subgroups_menu_tree_link', $group, $stem);
    $json->classes = ($group->nid == $stem->nid) ? 'og-subgroups-tree-active' : $expanded ? 'open og-subgroups-tree-active-trail' : NULL;
    $json->expanded = $expanded;

    if (!empty($stem->children)) {
      $json->children = _og_subgroups_group_tree_branch_json($group, $stem->children, $parents);
    }
    
    $children[] = $json;
  }
  return $children;
}

