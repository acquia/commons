<?php

/**
 * @file
 *   Functions to generate and use the group hierarchy trees
 */

/**
 * Get a hierarchy tree of all groups on the site
 * 
 * param $reset
 *   TRUE if the tree should be regenerated. Default to FALSE.
 */
function og_subgroups_get_tree($reset = FALSE) {
  static $tree = FALSE;
  $cache_key = 'og_subgroups:tree';
  
  // Check if our static cache hasn't yet been populated
  // or if a reset has been requested
  if ($reset || $tree === FALSE) {
    // If no reset is requested, attempt to fetch a cached tree
    // from the database
    if (!$reset) {
      $cache = cache_get($cache_key);
      // See if the cache has data
      if (isset($cache->data)) {
        // Use the cached tree
        $tree = $cache->data;
      }
    }
    
    // If we don't yet have a tree, we must generate one
    if ($reset || !$tree) {
      $tree = _og_subgroups_get_tree();
      
      // Cache this tree in the database
      cache_set($cache_key, $tree);
    }
  }
  
  return $tree;
}

/**
 * Callback to generate a hierarchy tree of all groups from the database
 * 
 * This is called by og_subgroups_get_tree() if a cached version of the
 * tree is not currently available
 */
function _og_subgroups_get_tree() {
  // Fetch all subgroup relationships
  $sql = "SELECT ogs.gid, ogs.parent, og.og_private, og.og_selective, n.title, n.status, n.type";
  $sql .= " FROM {og_subgroups} ogs";
  $sql .= " INNER JOIN {node} n ON ogs.gid = n.nid";
  $sql .= " INNER JOIN {og} og ON ogs.gid = og.nid";
  $results = db_query($sql);
  
  // Move the children into an array
  $children = array();
  while ($child = db_fetch_object($results)) {
    // Change gid to nid
    $child->nid = $child->gid;
    unset($child->gid);
    // Initialize the children array
    $child->children = array();
    // Add to our array of children
    $children[$child->nid] = $child;
  }
  
  // Fetch all groups which are only parents
  $sql = "SELECT og.nid, og.og_private, og.og_selective, n.title, n.status, n.type";
  $sql .= " FROM {og} og";
  $sql .= " INNER JOIN {node} n ON og.nid = n.nid";
  $sql .= " LEFT JOIN {og_subgroups} ogs ON og.nid = ogs.gid";
  $sql .= " WHERE ogs.gid IS NULL";
  $results = db_query($sql);
  
  // Move the parents into an array
  $parents = array();
  while ($parent = db_fetch_object($results)) {
    // Add a parent field to keep the array uniform, but set to zero
    $parent->parent = 0;
    // Initialize the children array
    $parent->children = array();
    // Add to our array of parents
    $parents[$parent->nid] = $parent;
  }
  
  // Iterate each parent in order to detect the children
  foreach ($parents as $parent) {
    $parents[$parent->nid]->children = _og_subgroups_get_tree_recursive($parent, $children);
  }
  
  // Remove parents with no children
  foreach ($parents as $parent) {
    if (empty($parent->children)) {
      unset($parents[$parent->nid]);
    }
  }
  
  return $parents;
}

/**
 * Recursive callback to generate a group tree
 * 
 * @see
 *   _og_subgroups_get_tree()
 * @param $parent
 *   The parent group
 * @param $children
 *   An array of all child groups
 * @return
 *   A keyed array of the parents children
 */
function _og_subgroups_get_tree_recursive($parent, $children) {
  $ret = array();
  // Iterate all available children
  foreach ($children as $child) {
    // If this is a child of our parent
    if ($child->parent == $parent->nid) {
      // First gather all of the child's children
      $child->children = _og_subgroups_get_tree_recursive($child, $children);
      
      // Store the child to be returned
      $ret[$child->nid] = $child;
    }
  }
  return $ret;
}

/**
 * Get a hierarchy tree just for a given group
 * 
 * This will return the entire hierarchy that the group is a part of
 * 
 * @param $group
 *   The group object
 * @return
 *   A nested array representing the group hierarchy, or FALSE if there
 *   is none
 */
function og_subgroups_get_group_tree($group) {
  static $group_tree;
  
  if (!isset($group_tree[$group->nid])) {
    // Get the hierarchy of all groups
    $tree = og_subgroups_get_tree();
  
    // Iterate the tree
    foreach ($tree as $parent) {
      // Check if this parent is the group we want or if the group
      // is inside this branch
      if ($parent->nid == $group->nid || _og_subgroups_group_in_branch($group, $parent)) {
        $group_tree[$group->nid] = array($parent->nid => $parent);
      }
    }
  }
  
  return isset($group_tree[$group->nid]) ? $group_tree[$group->nid] : NULL;
}

/**
 * Recursive callback to determine if a group is inside a given branch
 * 
 * @see
 *   _og_subgroups_get_group_tree()
 * @param $group
 *   The group we're checking to see is inside the branch
 * @param $branch
 *   The branch to iterate
 * @return
 *   TRUE if the group is inside the branch, otherwise FALSE
 */
function _og_subgroups_group_in_branch($group, $branch) {
  foreach ($branch->children as $child) {
    if ($child->nid == $group->nid) {
      return TRUE;
    }
    else if (!empty($child->children)) {
      if (_og_subgroups_group_in_branch($group, $child)) {
        return TRUE;
      }
    }
  }
  
  return FALSE;
}

/**
 * Determine the children of a given group
 * 
 * @param $group
 *   The group object
 * @param $nested
 *   TRUE if the returned array should be nested in the structure of
 *   the hierarchy. Defaults to TRUE.
 * @return
 *   An array of the children of the given group
 */
function og_subgroups_get_group_children($group, $nested = TRUE) {
  static $children = array();
  $output_type = ($nested) ? 'nested' : 'flat';
  if (!isset($children[$output_type][$group->nid])) {
    $children[$output_type][$group->nid] = array();
    if ($tree = og_subgroups_get_group_tree($group)) {
      _og_subgroups_get_group_children_recursive($group, $tree, $children[$output_type][$group->nid], $nested);
    }
  }

  return isset($children[$output_type][$group->nid]) ? $children[$output_type][$group->nid] : array();
}

/**
 * Recursive callback to help determine the children of a group
 */
function _og_subgroups_get_group_children_recursive($group, $branch, &$children, $nested, $add = FALSE) {
  // Iterate the branch
  foreach ($branch as $gid => $child) {
    // If we want to nest the children and the parent is already set
    // skip this
    if ($nested && isset($children[$child->parent])) {
      continue;
    }
    
    // If set to add, meaning this was called once we've reach the group
    // add the child
    if ($add) {
      $object = drupal_clone($child);
      // Children of the children are only kept if we're nesting
      if (!$nested) {
        unset($object->children);
      }
      $children[$gid] = $object;
    }
    
    // If we've reached the group, begin adding
    if ($group->nid == $gid) {
      _og_subgroups_get_group_children_recursive($group, $child->children, $children, $nested, TRUE);
    }
    else if (!empty($child->children)) {
      _og_subgroups_get_group_children_recursive($group, $child->children, $children, $nested, $add);
    }
  }
}

/**
 * Determine if a group is the child of a given parent group
 * 
 * This function will iterate though the entire parents lower ancestry,
 * returning TRUE even if the child is multiple levels below (child of
 * a child)
 * 
 * @param $parent
 *   The parent group node
 * @param $child
 *   The child group node
 * @return
 *   TRUE if $child is a child of $parent, or a child of a child of the
 *   $parent, and so on, otherwise FALSE.
 */
function og_subgroups_group_is_child($parent, $child) {
  return in_array($child->nid, array_keys(og_subgroups_get_group_children($parent, FALSE)));
}

/**
 * Retrieve all the parents of a given group
 * 
 * @param $group
 *   A group object
 * @return
 *   A keyed array of a groups parents in order from parent to grand
 *   parents
 */
function og_subgroups_get_group_parents($group) {
  static $parents;
  
  if (!isset($parents[$group->nid])) {
    if ($tree = og_subgroups_get_group_tree($group)) {
      $parents[$group->nid] = array();
      foreach ($tree as $gid => $branch) {
        if ($branch->nid != $group->nid && !empty($branch->children)) {
          $object = drupal_clone($branch);
          unset($object->children);
          
          if (!isset($branch->children[$group->nid])) {
            _og_subgroups_get_group_parents_recursive($group, $branch->children, $parents[$group->nid]);
          }
          
          $parents[$group->nid][$branch->nid] = $object;
        }
      }
    }
  }

  return isset($parents[$group->nid]) ? $parents[$group->nid] : array();
}

/**
 * Recursive callback to help determine all parents of a given group
 */
function _og_subgroups_get_group_parents_recursive($group, $branch, &$parents) {
  foreach ($branch as $gid => $child) {
    if (isset($child->children[$group->nid])) {
      $object = drupal_clone($child);
      unset($object->children);
      $parents[$child->nid] = $object;
      return TRUE;
    }
    else if (!empty($child->children)) {
      if (_og_subgroups_get_group_parents_recursive($group, $child->children, $parents)) {
        $object = drupal_clone($child);
        unset($object->children);
        $parents[$child->nid] = $object;
        return TRUE;
      }
    }
  }
  
  return FALSE;
}

/**
 * Retrieve the primary parent of a given group
 * 
 * @param $group
 *   A group object
 * @return
 *   The parent group object, or NULL if there is not one
 */
function og_subgroups_get_group_parent($group) {
  static $parent;
  
  if (!isset($parent[$group->nid])) {
    if ($tree = og_subgroups_get_group_tree($group)) {
      $parent[$group->nid] = _og_subgroups_get_group_parent_recursive($group, $tree);
    }
  }

  return isset($parent[$group->nid]) ? $parent[$group->nid] : NULL;
}

/**
 * Recursive callback to help determine the primary parent of a given group
 */
function _og_subgroups_get_group_parent_recursive($group, $branch) {
  foreach ($branch as $gid => $child) {
    if (isset($child->children[$group->nid])) {
      return $child;
    }
    else if (!$parent && !empty($child->children)) {
      $parent = _og_subgroups_get_group_parent_recursive($group, $child->children);
    }
  }
  
  return $parent ? $parent : NULL;
}

/**
 * Determine the siblings of a given group
 * 
 * @param $group
 *   The group object
 * @return
 *   An array of sibling groups
 */
function og_subgroups_get_group_siblings($group) {
  static $siblings;
  
  if (!isset($siblings[$group->nid])) {
    if ($tree = og_subgroups_get_group_tree($group)) {
      $siblings[$group->nid] = array();
      foreach ($tree as $gid => $branch) {
        // If the group is the primary parent, then there are no siblings
        if ($group->nid == $gid) {
          continue;  
        }

        $siblings[$group->nid] = _og_subgroups_get_group_siblings_recursive($group, $branch);
      }
    }
    
    // Remove the group from the list of siblings
    unset($siblings[$group->nid][$group->nid]);
  }
  
  return isset($siblings[$group->nid]) ? $siblings[$group->nid] : array();
}

/**
 * Recursive callback to help determine the siblings of a given group
 */
function _og_subgroups_get_group_siblings_recursive($group, $branch) {
  if (isset($branch->children[$group->nid])) {
    return $branch->children;
  }
  else if (is_array($branch->children)) {
    return _og_subgroups_get_group_siblings_recursive($group, $branch->children);
  }
}

/**
 * Retrieve the groups that are not inside a hierarchy
 * 
 * @return 
 *   An array of groups that are not part of a group hierarchy
 */
function og_subgroups_get_groups_without_family() {
  $groups = array();

  $sql = "SELECT og.nid, og.og_private, og.og_selective, n.title, n.status, n.type";
  $sql .= " FROM {og} og";
  $sql .= " INNER JOIN {node} n ON og.nid = n.nid";
  $sql .= " LEFT JOIN {og_subgroups} ogs ON og.nid = ogs.gid";
  $sql .= " WHERE ogs.gid IS NULL";
  $sql .= " AND ogs.parent IS NULL";
  $sql .= " ORDER BY n.title ASC";
  $results = db_query($sql);
  
  // Put the groups in array format
  while ($group = db_fetch_object($results)) {
    // Make sure this type is enabled
    if (og_subgroups_is_subgroup_type($group->type)) {
      $groups[$group->nid] = $group;
    }
  }

  return $groups;
}

/**
 * Flatten the subgroups tree or branch
 * 
 * @param $tree
 *  A tree of group objects
 * @return
 *  a flat array of all groups in the tree
 */
function og_subgroups_flatten_tree($tree) {
  $flat = array();
  foreach ($tree as $gid => $parent) {
    $children = og_subgroups_get_group_children($parent, FALSE);
    
    // Remove the children
    $object = drupal_clone($parent);
    unset($object->children);
    
    // Save the parent and children
    $flat[$gid] = $object;
    $flat += $children;
  }
  
  return $flat;
}
