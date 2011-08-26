<?php

/**
 * Add form components to select group parents on the group node form
 */
function og_subgroups_add_group_select_form(&$form, $node) {
  // Check access
  if (!og_subgroups_can_edit_hierarchy($node)) {
    return;
  }
  
  // Determine the default parent ID to be used on the form
  if (!$node->nid) {
    // See if a default parent was included in the URL
    $pid = isset($_GET['og_parent']) && is_numeric($_GET['og_parent']) ? $_GET['og_parent'] : 0;
    if ($pid) {
      // Attempt to load the parent
      if ($parent = node_load($pid)) {
        // Check that it's a group
        if (og_is_group_type($parent->type)) {
           // Check that the user is a member of this grou
           if (og_is_group_member($parent->nid)) {
             // Set this parent as the current context
             og_set_group_context($parent);
             // Use this parent as the default parent in the form
             $parent_id = $parent->nid;
           }
        }
      }
    }
  }
  else {
    // Use the already chosen parent for this group
    $parent_id = isset($node->og_parent->nid) ? $node->og_parent->nid : 0;
  }
  
  // The subgroup selection title
  $title = t('Parent');
  
  // The subgroup selection description
  $description = t('The parent group for this group node.');
  
  $form['og_subgroups'] = array(
    '#type' => 'fieldset',
    '#title' => $title,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  if (module_exists('og_subgroups_hs')) {
    $form['og_subgroups']['og_parent'] = array(
      '#type' => 'hierarchical_select',
      '#title' => $title,
      '#size' => 1,
      '#config' => array(
        'module' => 'og_subgroups_hs',
        'params' => array(
          'nid' => (isset($node->nid)) ? $node->nid : NULL,
          'optional' => 0,
        ),
        'save_lineage'    => 0,
        'enforce_deepest' => 0,
        'entity_count'    => 0,
        'resizable'       => 0,
      ),
      '#default_value' => $parent_id,
      '#description' => $description,
    );
  }
  else {
    $form['og_subgroups']['og_parent'] = array(
      '#type' => 'select',
      '#title' => $title,
      '#default_value' => $parent_id,
      '#options' => og_subgroups_group_select_options(),
      '#description' => $description,
    );
  }
  
  // Add our validator to the form
  array_unshift($form['#validate'], 'og_subgroups_node_form_validate');
}

/**
 * Create form select options for the subgroup selector
 * 
 * @param $indent
 *   The indention to be used.
 * @return
 *   A keyed array used for a form select widget
 */
function og_subgroups_group_select_options($indent = '--') {
  og_subgroups_include('tree');
  $options = array();
  
  // Get the tree 
  if ($tree = og_subgroups_get_tree()) {
    // Iterate the tree
    foreach ($tree as $branch) {
      // Check access to use this group
      if (!og_subgroups_mask_group($branch, TRUE)) {
        // Add the initial group as an option
        $options[$branch->nid] = $branch->title;
      }
      
      // Add all the children
      _og_subgroups_group_select_options_recursive($options, $branch->children, $indent);
    }
  }
  
  // Add the groups that don't have children
  $options += _og_subgroups_group_select_options_without_family();
  
  // Add no parent as a selection option
  $options = array(t('<No parent group>')) + $options;

  return $options;
}

/**
 * Recursive callback to help create group select options
 * 
 * @see
 *   og_subgroups_group_select_options()
 */
function _og_subgroups_group_select_options_recursive(&$options, $branch, $indent) {
  foreach ($branch as $child) {
    // Check access to use this group
    if (!og_subgroups_mask_group($child, TRUE)) {
      $options[$child->nid] = $indent . ' ' . $child->title;
    }

    if (!empty($child->children)) {
      _og_subgroups_group_select_options_recursive($options, $child->children, $indent . $indent);
    }
  }
}

/**
 * Helper function to generate a list of select options of groups
 * that do not have a hierarchy, meaning they are not in a family
 */
function _og_subgroups_group_select_options_without_family() {
  og_subgroups_include('tree');
  $options = array();
  
  // Fetch the groups not in a family
  $groups = og_subgroups_get_groups_without_family();
  
  // Iterate the groups
  foreach ($groups as $group) {
    // Check for access
    if (!og_subgroups_mask_group($group, TRUE)) {
      $options[$group->nid] = $group->title;
    }
  }
  
  return $options;
}
