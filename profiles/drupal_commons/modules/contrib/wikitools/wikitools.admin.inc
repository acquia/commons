<?php

/**
 * @file
 * Wikitools administration UI.
 */

/**
 * Callback for wikitools settings form.
 */
function wikitools_admin_settings() {
  if (!module_exists('search')) {
    drupal_set_message(t('You will not be able to select the "Node Search" or "Link to search" options until you <a href="!url">enable</a> the search module.',
      array('!url' => url('admin/modules'))), 'warning');
  }

  $form = array();

  $form['wikitools_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Wiki path'),
    '#default_value' => wikitools_wiki_path(),
    '#description' => t('The drupal path for the wiki. Do not include a trailing slash. Leave empty to disable the wiki path.'),
    '#field_prefix' => url(NULL, array('absolute' => FALSE)) . (variable_get('clean_url', 0) ? '' : '?q=')
  );
  $form['wikitools_main_page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title of main page'),
    '#default_value' => wikitools_main_page_title(),
    '#description' => t('The main page is shown if you type in the wiki path. Leave empty to disable the main page.'),
  );
  $form['wikitools_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Wiki node types'),
    '#options' => array_map('filter_xss', node_get_types('names')),
    '#default_value' => wikitools_node_types(),
    '#multiple' => TRUE,
    '#description' => t('Select the node types which will be affected by the specified options. If you select multiple node types, all nodes of these types will be searched for when a wikipath is entered. If a wikipage doesn\'t exist, an option to create any of these types will be given.'),
  );
  $form['wikitools_options'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Options'),
    '#options' => array(
      'node creation' => t('Node Creation: Let users create new nodes when they type in a node name which does not exist.'),
      'node search' => t('Node Search: Let users search for nodes when they type in a node name which does not exist.'),
      'auto redirect' => t('Automatic Redirect: If a title of a moved page is entered, redirect automatically.'),
      'unique titles' => t('Unique Titles: Enforce that titles of new nodes are different from existing ones.'),
      'move protection' => t('Move Protection: Disallow change of node titles for users without <em>administer nodes</em> permission.'),
      'underscore as space' => t('Treat underscores as spaces when looking for node titles.'),
      'dash as space' => t('Treat dashes as spaces when looking for node titles.'),
    ),
    '#default_value' => wikitools_options(),
    '#description' => '<ul><li>'.
      t('To take full advantage of the options <em>Node Creation</em>, <em>Node Search</em> and <em>Automatic Redirect</em> you should use an input format which creates wikilinks which point to the wiki path set. For exapmle a wikilink [[Page Name]] should be linked to <em>wikipath/Page Name</em>.') .'</li><li>'. 
      t('The options <em>Node Creation</em>, <em>Node Search</em> and <em>Automatic Redirect</em> work only if a wiki path is set or if freelinking hijacking is enabled. They take the page name from the path after the wiki path, i.e. <em>wikipath/Page Name</em>, or the page name of a freelinking link, i.e. <em>freelinking/Page Name</em>.') .'</li><li>'.
      t('The option <em>Automatic Redirect</em> works only if node revisions are created.') .'</li></ul>',
  );
  $form['wikitools_404_type'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Wiki 404 type'),
    '#description' => t('Select the 404 (page not found) type for all pages under the wiki path.'),
    '#multiple' => TRUE,
    '#options' => array(
      'Link to search' => t('Link to search'),
      'Link to creation' => t('Link to creation'),
      'Creation form' => t('Creation form'),
    ),
    '#default_value' => wikitools_404(),
  );
  $form['wikitools_disallowed_characters'] = array(
    '#type' => 'textfield',
    '#title' => t('Disallowed characters in titles'),
    '#description' => t('Leave empty to disable this feature. Specify a list of characters which are not allowed in the title of a wiki page.'),
    '#default_value' => wikitools_disallowed_characters(),
  );
  if (module_exists('freelinking')) {
    $form['wikitools_hijack_freelinking'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hijack freelinking filter'),
      '#default_value' => wikitools_hijack_freelinking(),
      '#description' => t('If you activate this option, the links of the freelinking filter will be processed by the wikitools module rather than the freelinking module. When active, a link to <em>freelinking/Page Name</em> behaves exactly as a link to <em>wikipath/Page Name</em>.'),
    );
  }
  $form['subpages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Subpages'),
    '#description' => t('Subpages can be appended to a URL (either directly or via a query string) and will redirect the user to the named subpage.'),
  );
  $form['subpages']['wikitools_subpages_handling'] = array(
    '#type' => 'radios',
    '#title' => t('Activation'),
    '#options' => array(
      'disabled' => t('Disabled'),
      'url' => t('Enable url suffixes: With url suffixes, you can append the subpage to the URL. For example  <em>wikipath/Page/edit</em>.'),
      'query' => t('Enable query string: With query strings, you can append the subpage as a query. For example <em>wikipath/Page?wt_action=edit</em>.'),
    ),
    '#default_value' => wikitools_subpages_handling(),
  );
  $form['subpages']['wikitools_subpages'] = array(
    '#type' => 'textfield',
    '#title' => t('URL subpages'),
    '#description' => t('A list of available subpages. Only these subpages can be used as url suffixes or with the query string.'),
    '#default_value' => implode(", ", wikitools_subpages()),
  );

  $form = system_settings_form($form);
  // Rebuild the menu after updating the settings.
  $form['#submit'][] = 'menu_rebuild';
  return $form;
}

/**
 * Menu callback for duplicate pages list.
 */
function wikitools_page_duplicates() {
  $output = '';
  $found_nodes = FALSE;

  list($select_query, $count_query, $arguments) = _wikitools_duplicate_nodes_query();
  if ($select_query) {
    $nodes_per_page = variable_get('default_nodes_main', 10);

    // Grab all nodes that have the same title
    $result = pager_query($select_query, $nodes_per_page, 0, $count_query, $arguments);
    while ($node = db_fetch_object($result)) {
      $output .= node_view(node_load($node->nid), 1);
      $found_nodes = TRUE;
    }
  }

  if ($found_nodes) {
    $output .= theme('pager', NULL, $nodes_per_page);
  }

  // Return a nice listing of all the duplicate nodes
  return $output;
}

/**
 * Create queries to find nodes with duplicate titles.
 */
function _wikitools_duplicate_nodes_query() {
  $node_types = array_values(wikitools_node_types());
  if (count($node_types)) {
    // Make sure we deal with various title equalities
    $n1_title = 'n1.title';
    $n2_title = 'n2.title';
    if (wikitools_treat_underscore_as_space()) {
      $n1_title = "REPLACE($n1_title, '_', ' ')";
      $n2_title = "REPLACE($n2_title, '_', ' ')";
    }
    if (wikitools_treat_dash_as_space()) {
      $n1_title = "REPLACE($n1_title, '-', ' ')";
      $n2_title = "REPLACE($n2_title, '-', ' ')";
    }

    // Grab all nodes that have the same title
    $node_types_placeholders = db_placeholders($node_types, 'varchar');
    $from_part = 'FROM {node} n1, {node} n2 WHERE LOWER('. $n1_title .') = LOWER('. $n2_title .') AND n1.nid != n2.nid AND n1.type IN('. $node_types_placeholders .') AND n2.type IN('. $node_types_placeholders .')';
    $select_query = 'SELECT DISTINCT(n1.nid), n1.title ' . $from_part . ' ORDER BY n1.title ASC';
    $count_query = 'SELECT COUNT(DISTINCT(n1.nid)) ' . $from_part;
    return array($select_query, $count_query, array_merge($node_types, $node_types));
  }
  return array(NULL, NULL, NULL);
}
