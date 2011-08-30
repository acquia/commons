<?php

/**
 * @file
 *   Administrative page callbacks
 */

/**
 * Menu callback; displays the subgroups configuration page
 */
function og_subgroups_settings() {
  $form = array();
  
  // Node type settings
  $form['node_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enable subgroups for group types'),
    '#description' => t('Select which available group node types can have subgroups. If a certain node type already has subgroups and you deselect it, it will not remove the hierarchy of those nodes. They must be manually edited.'),
  );
  // Provide a checkbox for all valid group node types
  foreach (node_get_types() as $type => $node_type) {
    if (og_is_group_type($type)) {
      $form['node_types']["og_subgroups_node_type_enabled_{$type}"] = array(
        '#type' => 'checkbox',
        '#title' => $node_type->name,
        '#default_value' => variable_get("og_subgroups_node_type_enabled_{$type}", 0),
      );
    }
  }
  
  // Inheritance options
  $form['inheritance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Inheritance settings'),
  );
  $form['inheritance']['og_subgroups_inherit_privacy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force privacy on children'),
    '#default_value' => variable_get('og_subgroups_inherit_privacy', 0),
    '#description' => t('If checked, all children of a private group will be forced private. This will not affect existing groups. If a public parent is later set to private, it will automatically update all the children to be private as well. If it is then changed to public, it will not update the children to be public.'),
  );
  
  // Theme options
  $form['theme'] = array(
    '#type' => 'fieldset',
    '#title' => t('Theme settings'),
  );
  $form['theme']['og_subgroups_block_use_treeview'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use jQuery treeview for hierarchy block'),
    '#default_value' => variable_get('og_subgroups_block_use_treeview', 1),
    '#description' => t('If checked, the hierarchy block will be rendered with the jQuery treeview plugin'),
  );
  $form['theme']['og_subgroups_block_use_treeview_controls'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable collapse/expand controls'),
    '#default_value' => variable_get('og_subgroups_block_use_treeview_controls', 1),
    '#description' => t('If checked, and if jQuery treeview is enabled, the hierarchy block will include controls to collapse and expand the tree.'),
  );
  $form['theme']['og_subgroups_block_use_treeview_ajax'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use AJAX to load the tree data'),
    '#default_value' => variable_get('og_subgroups_block_use_treeview_ajax', 0),
    '#description' => t('If checked, and if jQuery treeview is enabled, the hierarchy block will be loaded via AJAX instead on the initial page load. This is useful if you expect to have very large hierarchies and do not want to slow down the page load time.'),
  );
  
  return system_settings_form($form);
}
