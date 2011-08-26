<?php

/**
 * Callback for hook_token_values()
 */
function _og_subgroups_token_values($type, $object = NULL, $options = array()) {
  og_subgroups_include('tree');
  
  $gid = NULL;
  
  if ($type == 'node') {
    // If this is a group node, then the group id is the node id
    if (og_is_group_type($object->type)) {
      $gid = $object->nid;
    }
    // Otherwise, check group membership
    if (!empty($object->og_groups) && is_array($object->og_groups)) {
      $gids = array_filter($object->og_groups);
      if (!empty($gids)) {
        $gid = array_shift($gids);
      }
    }
    
    // Set some defaults so that tokens will be emptied for nodes with no group affiliations
    $tokens['subgroups-parent'] = '';
    $tokens['subgroups-parent-raw'] = '';
    $tokens['subgroups-parent-id'] = '';
    $tokens['subgroups-parent-alias'] = '';
    $tokens['subgroups-grandparent'] = '';
    $tokens['subgroups-grandparent-raw'] = '';
    $tokens['subgroups-grandparent-id'] = '';
    $tokens['subgroups-grandparent-alias'] = '';
  }
  
  if (isset($gid)) {
    $node = $object;
    $parent = og_subgroups_get_group_parent($node);
    $grandparent = $parent ? og_subgroups_get_group_parent($parent) : NULL;

    // Set the token
    $tokens['subgroups-parent'] = check_plain($parent->title);
    $tokens['subgroups-parent-raw'] = $parent->title;
    $tokens['subgroups-parent-id'] = $parent->nid;
    $tokens['subgroups-parent-alias'] = drupal_get_path_alias("node/{$parent->nid}");
    $tokens['subgroups-grandparent'] = check_plain($grandparent->title);
    $tokens['subgroups-grandparent-raw'] = $grandparent->title;
    $tokens['subgroups-grandparent-id'] = $grandparent->nid;
    $tokens['subgroups-grandparent-alias'] = drupal_get_path_alias("node/{$grandparent->nid}");
    
    return $tokens;
  }
}

/**
 * Callback for hook_token_list()
 */
function _og_subgroups_token_list($type = 'all') {
  if ($type == 'node' || $type == 'all') {
    $tokens['node']['subgroups-parent'] = t('Node title of the parent group');
    $tokens['node']['subgroups-parent-raw'] = t('Unfiltered node title of the parent group - raw user input');
    $tokens['node']['subgroups-parent-id'] = t('Node ID of the parent group');
    $tokens['node']['subgroups-parent-alias'] = t('URL alias for the parent group.');
    $tokens['node']['subgroups-grandparent'] = t('Node title of the parent of the parent group');
    $tokens['node']['subgroups-grandparent-raw'] = t('Unfiltered node title of the parent of the parent group - raw user input');
    $tokens['node']['subgroups-grandparent-id'] = t('Node ID of the parent of the parent group');
    $tokens['node']['subgroups-grandparent-alias'] = t('URL alias for the parent of the parent group.');
    return $tokens;
  }
}
