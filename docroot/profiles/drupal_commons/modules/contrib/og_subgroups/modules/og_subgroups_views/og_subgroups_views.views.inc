<?php

/**
 * @file 
 *   Contains the Views api functions 
 */

/**
 * Implementation of hook_views_handlers().
 */
function og_subgroups_views_views_handlers() {
  return array(
    'info' => array(
        'path' => drupal_get_path('module', 'og_subgroups_views') .'/includes',
    ),
    'handlers' => array(
      // arguments
      'og_subgroups_views_handler_argument_gid' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'og_subgroups_views_handler_argument_parent' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'og_subgroups_views_handler_argument_content' => array(
        'parent' => 'og_subgroups_views_handler_argument_gid',
      ),
      // fields
      'og_subgroups_views_handler_field_children' => array(
        'parent' => 'views_handler_field_prerender_list',
      ),
      'og_subgroups_views_handler_field_child_count' => array(
        'parent' => 'views_handler_field',
      ),
      'og_subgroups_views_handler_field_siblings' => array(
        'parent' => 'views_handler_field_prerender_list',
      ),
      'og_subgroups_views_handler_field_parents' => array(
        'parent' => 'views_handler_field_prerender_list',
      ),
      'og_subgroups_views_handler_field_parent_title' => array(
        'parent' => 'views_handler_field',
      ),
      // filters
      'og_subgroups_views_handler_filter_og_group_nid_override' => array(
        'parent' => 'views_handler_filter_many_to_one',
      ),
      'og_subgroups_views_handler_filter_has_parent' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
      // sorts
      'og_subgroups_views_handler_sort_hierarchy' => array(
        'parent' => 'views_handler_sort',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data().
 */
function og_subgroups_views_views_data() {
  $data['og_subgroups']['table']['group']  = t('OG subgroups');
  $data['og_subgroups']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'gid',
    'type' => 'left',
  );

  $data['og_subgroups']['gid'] = array(
    'title' => t('Group ID'),
    'help' => t('Use the nid of a group as a starting point to retrieve other groups in the hierarchy.'),
    'argument' => array(
      'handler' => 'og_subgroups_views_handler_argument_gid',
    ),
    'field' => array(
      'title' => t('Child groups'),
      'help' => t('List of child groups nested under a parent.'),
      'handler' => 'og_subgroups_views_handler_field_children',
    ),
    'sort' => array(
      'title' => t('Hierarchy order'),
      'help' => t('Sort the groups by the order in which they appear in the subgroup tree.'),
      'handler' => 'og_subgroups_views_handler_sort_hierarchy',
    ),
  );
  
  $data['og_subgroups']['child_count'] = array(
    'title' => t('Child count'),
    'field' => array(
      'title' => t('Child count'),
      'help' => t('Provide a count of the number of child groups.'),
      'handler' => 'og_subgroups_views_handler_field_child_count',
    ),
  );

  $data['og_subgroups']['parent'] = array(
    'title' => t('Parent group ID'),
    'help' => t('The Node ID of the parent group.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'argument' => array(
      'help' => t('The group ID of a parent node. Filters for groups that has the specified parent(s)'),
      'handler' => 'og_subgroups_views_handler_argument_parent',
    ),
  );
  
  $data['og_subgroups']['siblings'] = array(
    'title' => t('Sibling groups'),
    'help' => t('The siblings of the group.'),
    'real field' => 'gid',
    'field' => array(
      'handler' => 'og_subgroups_views_handler_field_siblings',
    ),
  );
  
  $data['og_subgroups']['parents'] = array(
    'title' => t('Parent groups'),
    'help' => t('The parents of the group.'),
    'real field' => 'gid',
    'field' => array(
      'handler' => 'og_subgroups_views_handler_field_parents',
    ),
  );

  $data['og_subgroups']['parent_title'] = array(
    'title' => t('Parent group title'),
    'help' => t('The Node title of the parent group.'),
    'real field' => 'gid',
    'field' => array(
      'handler' => 'og_subgroups_views_handler_field_parent_title',
    ),
  );
  
  $data['og_subgroups']['has_parent'] = array(
    'real field' => 'parent',
    'title' => t('Has parent'),
    'help' => t('Filter the view based on whether or not the group has a parent.'),
    'filter' => array(
      'handler' => 'og_subgroups_views_handler_filter_has_parent',
      'type' => 'yes-no',
    ),
  );

  // Use the og_ancestry as an aliased table.
  $data['og_subgroups_posts']['table']['group']  = t('OG subgroups');
  $data['og_subgroups_posts']['table']['join']['node'] = array(
    'table' => 'og_ancestry',
    'left_field' => 'nid',
    'field' => 'nid',
  );

  $data['og_subgroups_posts']['content'] = array(
    'title' => t('Group ID'),
    'help' => t('<strong>Posts</strong> are filtered for specified branches of the subgroup tree'),
    'argument' => array(
      'handler' => 'og_subgroups_views_handler_argument_content',
      'field' => 'group_nid',
      'numeric' => TRUE,
    ),
  );

  return $data;
}
