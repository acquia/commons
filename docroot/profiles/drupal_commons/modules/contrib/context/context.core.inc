<?php
// $Id: context.core.inc,v 1.1.2.3.2.27 2010/04/29 16:54:34 darthsteven Exp $

/**
 * Implementation of hook_theme().
 */
function context_theme() {
  $items = array();
  $items['context_links'] = array(
    'arguments' => array(),
  );
  return $items;
}

/**
 * Implementation of hook_theme_registry_alter().
 */
function context_theme_registry_alter(&$theme_registry) {
  // Push theme_page() through a context_preprocess to provide
  // context-sensitive menus and variables.
  if (!in_array('context_preprocess_page', $theme_registry['page']['preprocess functions'])) {
    $theme_registry['page']['preprocess functions'][] = 'context_preprocess_page';
  }
  // Add a page preprocess function to the very top of the theme_page()
  // stack so that we can actually set contexts *before* the page theming
  // is executed.
  if (!in_array('context_page_alter', $theme_registry['page']['preprocess functions'])) {
    array_unshift($theme_registry['page']['preprocess functions'], 'context_page_alter');
  }
  // Reroute theme_blocks() through context_blocks to determine block
  // visibility by context. Only override theme_blocks() if a theme
  // has not overridden it. It is the responsibility of any themes
  // implementing theme_blocks() to take advantage of context block
  // visibility on their own.
  if (!isset($theme_registry['blocks']['type']) || !in_array($theme_registry['blocks']['type'], array('base_theme_engine', 'theme_engine')) && !isset($theme_registry['blocks']['file'])) {
    unset($theme_registry['blocks']['preprocess functions']);
    $theme_registry['blocks']['function'] = 'context_blocks';
  }
}

/**
 * Implementation of hook_context_conditions().
 *
 * Allows modules to integrate with context and provide their native
 * objects as options for setting a context definition. The
 * hook should return an array of items keyed on the object "type"
 * (e.g. "node", "user", etc.) with key-value pairs corresponding to
 * a FormAPI element array with some restrictions and additional info.
 *
 * '#title': Required. The title of the object / form option.
 * '#type': Required. The FormAPI element type to use. Currently only
 *   'select', 'checkboxes', 'radios', and 'textfield' are allowed.
 * '#description': Optional. Help text to be displayed on the form.
 * '#options': Required. A key-value array of options. They key will be
 *   stored and passed to context_set_by_condition(), so the integrating module
 *   should use a unique (within its namespace) / usable identifier.
 */
function context_context_conditions() {
  $items = array();

  // Content Types
  $nodetypes = array();
  foreach (node_get_types() as $type) {
    $nodetypes[$type->type] = t(drupal_ucfirst($type->name));
  }
  $items['node'] = array(
    '#title' => t('Node pages'),
    '#description' => t('Set this context when viewing a node page or using the add/edit form of one of these content types.'),
    '#options' => $nodetypes,
    '#type' => 'checkboxes',
    '#help_topic' => 'node-condition',
    '#help_module' => 'context_ui',
  );

  // User
  $items['user'] = array(
    '#title' => t('User pages'),
    '#description' => t('Set this context when a user with selected role(s) is viewed'),
    '#options' => user_roles(true),
    '#type' => 'checkboxes',
  );

  // Book
  if (module_exists('book')) {
    $options = array();
    foreach (book_get_books() as $book) {
      $options[$book['menu_name']] = $book['title'];
    }
    $items['book'] = array(
      '#title' => t('Book'),
      '#description' => t('Set this context when a node in the selected book is viewed.'),
      '#options' => $options,
      '#type' => 'checkboxes',
    );
  }

  // Sitewide context:
  $items['sitewide'] = array(
    '#title' => t('Sitewide context'),
    '#type' => 'radios',
    '#options' => array(0 => t('False'), 1 => t('True')),
    '#description' => theme('advanced_help_topic', 'context_ui', 'default-contexts') . t('Should this context always be set? If <strong>true</strong>, this context will be active across your entire site.'),
    '#help_topic' => 'default-contexts',
    '#help_module' => 'context_ui',
  );

  // Default context:
  $items['default'] = array(
    '#title' => t('Default context'),
    '#type' => 'radios',
    '#options' => array(0 => t('False'), 1 => t('True')),
    '#description' => theme('advanced_help_topic', 'context_ui', 'default-context') . t('If no other context is activated in this namespace and attribute, should this one be activated?'),
    '#help_topic' => 'default-context',
    '#help_module' => 'context_ui',
  );

  // Path:
  $items['path'] = array(
    '#title' => t('Path'),
    '#description' => t('Set this context when any of the paths above match the page path. Put each path on a separate line. You can use the "*" character as a wildcard and &lt;front&gt; for the front page.'),
    '#type' => 'textarea',
    '#element_validate' => array('context_condition_text_validate'),
  );

  // Menu trail
  // @TODO: Implement a real handler system : (
  // This condition most clearly shows the architecture problem of
  // storing both conditions and reactions as first-level children
  // on the context object.
  if (module_exists('menu')) {
    $menus = menu_parent_options(array_reverse(menu_get_menus()), NULL);
    $root_menus = array();
    foreach ($menus as $key => $name) {
      $id = explode(':', $key);
      if ($id[1] == '0') {
        $root_menus[$id[0]] = check_plain($name);
      }
      else {
        $link = menu_link_load($id[1]);
        $root_menu = $root_menus[$id[0]];
        $menus[$root_menu][$link['link_path']] = $name;
      }
      unset($menus[$key]);
    }
    array_unshift($menus, "-- ". t('None') ." --");
    $items['menu_trail'] = array(
      '#title' => t('Menu trail'),
      '#description' => t('Set this context when any of the selected menu items belong to the current active menu trail.'),
      '#options' => $menus,
      '#type' => 'select',
      '#multiple' => TRUE,
    );
  }
  else {
    $items['menu_trail'] = array('#type' => 'value');
  }

  if (module_exists('taxonomy')) {
    $taxonomy = array();
    $context_taxonomies = variable_get('context_taxonomy_vocabularies', array());
    foreach (taxonomy_get_vocabularies() as $vid => $vocab) {
      // Is using this vocab active for context:
      if (in_array($vid, $context_taxonomies)) {
        $taxonomy[$vid .':0'] = '<'. $vocab->name .'>';
        foreach (taxonomy_get_tree($vid) as $term) {
          $taxonomy[$vid .':'. $term->tid] = str_repeat('-', $term->depth + 1) .' '. $vocab->name .':  '. $term->name;
        }
      }
    }
    // Terms Selection
    $items['taxonomy'] = array(
      '#title' => t('Taxonomy Terms'),
      '#description' => t('Set this context when a node with a selected term is viewed. Select the vocabulary to set the context when a node contains any term in the vocabulary. Vocabularies and their terms will only appear in this list if you have explicity included them on their settings page.'),
      '#type' => 'select',
      '#options' => $taxonomy,
      '#multiple' => TRUE,
      '#help_topic' => 'taxonomy-condition',
    '#help_module' => 'context_ui',
    );
  }

  return $items;
}

/**
 * Element validate handler for setter textareas and texfields.
 * Will process and convert a string to an array of matchable
 * elements by splitting on an appropriate delimiter ("\n" for
 * textareas and "," for textfields).
 */
function context_condition_text_validate($element, &$form_state) {
  if (!empty($element['#value']) && in_array($element['#type'], array('textfield', 'textarea'))) {
    switch ($element['#type']) {
      case 'textfield':
        $delimiter = ',';
        break;
      case 'textarea':
        $delimiter = "\n";
        break;
    }

    $items = $element['#value'];
    $items = explode($delimiter, $items);

    if (!empty($items)) {
      $values = array();
      foreach ($items as $k => $v) {
        $v = trim($v);
        if (!empty($v)) {
          $values[$v] = $v;
        }
      }
      $id = end($element['#parents']);
      $form_state['values']['items'][$id] = $values;
    }
  }
}

/**
 * Implementation of hook_context_reactions().
 *
 * Allows modules to integrate with context and provide options for
 * responding when a context has been set. The hook should return an
 * array of items keyed on the "type" of getter (e.g. "menu", "theme",
 * etc.) with key-value pairs corresponding to a FormAPI element array
 * with some restrictions and additional info.
 *
 * The getter element array provided differs from the setter array in
 * that it may store a tree of values (i.e. where #tree => true). The
 * values will be stored in a serialized array in the database.
 *
 * '#title': Required. The title of the object / form option.
 * '#type': Required. The FormAPI element type to use. Currently only
 *   'select', 'checkboxes', 'radio', and 'textfield' are allowed.
 * '#description': Optional. Help text to be displayed on the form.
 * '#options': Required. A key-value array of options. They key will be
 *   stored and passed to context_set_by_condition(), so the integrating module
 *   should use a unique (within its namespace) / usable identifier.
 */
function context_context_reactions() {
  $items = array();

  // Menu
  if (module_exists('menu')) {
    $menus = menu_parent_options(array_reverse(menu_get_menus()), NULL);
    $root_menus = array();
    foreach ($menus as $key => $name) {
      $id = explode(':', $key);
      if ($id[1] == '0') {
        $root_menus[$id[0]] = check_plain($name);
      }
      else {
        $link = menu_link_load($id[1]);
        $root_menu = $root_menus[$id[0]];
        $menus[$root_menu][$link['link_path']] = $name;
      }
      unset($menus[$key]);
    }
    array_unshift($menus, "-- ". t('None') ." --");
    $items['menu'] = array(
      '#title' => t('Active menu'),
      '#description' => t('Display the selected menu item as active in the <strong>$primary_links</strong> or <strong>$secondary_links</strong> of page.tpl.php when this context is set.'),
      '#options' => $menus,
      '#type' => 'select',
      '#size' => 20,
      '#help_topic' => 'active-menus',
      '#help_module' => 'context_ui',
    );
  }
  else {
    $items['menu'] = array('#type' => 'value');
  }

  // Implements context-based theme improvements
  $items['theme_section'] = array(
    '#tree' => TRUE,
    '#title' => t('Theme variables'),
    'title' => array(
      '#title' => t('Section title'),
      '#description' => t('Provides this text as a <strong>$section_title</strong> variable for display in page.tpl.php when this context is active.'),
      '#type' => 'textfield',
      '#maxlength' => 255,
    ),
    'subtitle' => array(
      '#title' => t('Section subtitle'),
      '#description' => t('Provides this text as a <strong>$section_subtitle</strong> variable for display in page.tpl.php when this context is active.'),
      '#type' => 'textfield',
      '#maxlength' => 255,
    ),
    'class' => array(
      '#title' => t('Section class'),
      '#description' => t('Provides this text as an additional body class (in <strong>$body_classes</strong> in page.tpl.php) when this section is active.'),
      '#type' => 'textfield',
      '#maxlength' => 64,
    ),
  );

  // Implements context-based region disabling
  $theme_key = variable_get('theme_default', 'garland');
  $regions = system_region_list($theme_key);
  $items['theme_regiontoggle'] = array(
    '#title' => t('Disabled regions'),
    '#type' => 'checkboxes',
    '#options' => $regions,
  );

  return $items;
}

/**
 * Implementation of hook_nodeapi().
 */
function context_nodeapi(&$node, $op, $teaser, $page) {
  if ($op == 'view' && $page && ($menu_ob = menu_get_object()) && $menu_ob->nid == $node->nid) {
    context_node_condition($node, $op);
  }
}

/**
 * Implementation of hook_ctools_render_alter().
 *
 * Used to detect the presence of a page manager node view or node form.
 */
function context_ctools_render_alter($info, $page, $args, $contexts, $task, $subtask) {
  if ($page && in_array($task['name'], array('node_view', 'node_edit'), TRUE)) {
    foreach ($contexts as $ctools_context) {
      if ($ctools_context->type === 'node' && !empty($ctools_context->data)) {
        context_node_condition($ctools_context->data, $task['name'] === 'node_view' ? 'view' : 'form');
        break;
      }
    }
  }
}

/**
 * Centralized node condition call function for the ever increasing number of
 * ways to get at a node view / node form.
 */
function context_node_condition(&$node, $op) {

  // Implementation of context_set_by_condition for node.
  context_set_by_condition('node', $node->type);

  // Implementation of context_set_by_condition for book.
  if (module_exists('book') && isset($node->book)) {
    if ($node->book['menu_name']) {
      context_set_by_condition('book', $node->book['menu_name']);
    }
  }

  // Implementation of context for taxonomy.
  if (module_exists('taxonomy') && $node->taxonomy) {
    // Set context for terms
    foreach ($node->taxonomy as $term) {
      context_set_by_condition('taxonomy', $term->vid .':'. $term->tid);
      context_set_by_condition('taxonomy', $term->vid .':0');
    }
  }
}

/**
 * Implementation of hook_form_alter().
 */
function context_form_alter(&$form, $form_state, $form_id) {
  if ($form['#id'] === 'node-form' && arg(0) != 'admin') { // Prevent this from firing on admin pages... damn form driven apis...
    context_node_condition($form['#node'], 'form');
  }
  if ($form_id == 'system_modules') {
    context_invalidate_cache();
  }
  if ($form_id == 'taxonomy_form_vocabulary') {
    // Add the option to include this vocabulary in context conditions:
    $vid = isset($form['vid']['#value']) ? $form['vid']['#value'] : 0;
    $form['settings']['context'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include as context condition'),
      '#description' => t('Select to make this vocabulary available for use as a context condition.'),
      '#default_value' => in_array($vid, variable_get('context_taxonomy_vocabularies', array())),
    );
    // Add our submit handler:
    $form['#submit'][] = 'content_taxonomy_form_vocabulary_submit';
  }
}

/**
 * Form submission handler for the vocabulary add/edit form.
 *
 * We store our context specific settings for the given vocabulary, this is so
 * that people can choose to include specific taxonomies in the taxonomy
 * condition form.
 */
function content_taxonomy_form_vocabulary_submit($form, &$form_state) {
  $context_vocabularies = variable_get('context_taxonomy_vocabularies', array());
  $vid = $form_state['values']['vid'];

  if ($form_state['values']['context']) {
    $context_vocabularies[$vid] = $vid;
  }
  else {
    unset($context_vocabularies[$vid]);
  }

  // Update the settings:
  variable_set('context_taxonomy_vocabularies', $context_vocabularies);
}

/**
 * Implementation of hook_form_alter() for comment_form.
 */
function context_form_comment_form_alter(&$form, $form_state) {
  if ($nid = $form['nid']['#value']) {
    $node = node_load($nid);
    context_set_by_condition('node', $node->type);
  }
}

/**
 * Implementation of hook_user().
 */
function context_user($op, &$edit, &$account, $category = NULL) {
  if ($op == 'view' && !empty($account->roles)) {
    foreach (array_keys($account->roles) as $rid) {
      context_set_by_condition('user', $rid);
    }
  }
}

/**
 * BLOCK HANDLING =====================================================
 */

/**
 * This override of theme_blocks() is called because of an alter of the
 * theme registry. See context_theme_registry_alter().
 */
function context_blocks($region) {
  // Bail if this region is disabled.
  $disabled_regions = context_active_values('theme_regiontoggle');
  if (!empty($disabled_regions) && in_array($region, $disabled_regions)) {
    return '';
  }

  $output = "";
  if ($list = context_block_list($region)) {
    foreach ($list as $key => $block) {
      $output .= theme("block", $block);
    }
  }
  return $output . drupal_get_content($region);
}

/**
 * An alternative version of block_list() that provides any context enabled blocks.
 */
function context_block_list($region) {
  static $blocks;
  static $context_blocks;

  if (!isset($context_blocks)) {
    $blocks = array();
    $context_blocks = array();

    // Store all active context blocks when first called
    $context_blocks = array();
    foreach (context_active_values('block') as $block) {
      $block = (object) $block;
      $context_blocks["{$block->module}-{$block->delta}"] = $block;
    }

    global $user, $theme_key;
    $rids = array_keys($user->roles);

    // This query is identical to the one in block_list(), but status = 1 is excluded to
    // retain blocks that may be enabled via context.
    $result = db_query(db_rewrite_sql("SELECT DISTINCT b.* FROM {blocks} b LEFT JOIN {blocks_roles} r ON b.module = r.module AND b.delta = r.delta WHERE b.theme = '%s' AND (r.rid IN (". db_placeholders($rids) .") OR r.rid IS NULL) ORDER BY b.region, b.weight, b.module", 'b', 'bid'), array_merge(array($theme_key), $rids));

    while ($block = db_fetch_object($result)) {
      $bid = "{$block->module}-{$block->delta}";

      // If block is not enabled & not enabled via context, skip it
      if (!empty($context_blocks[$bid])) {
        $block->region = $context_blocks[$bid]->region;
        $block->weight = $context_blocks[$bid]->weight;
        unset($context_blocks[$bid]);
        $enabled = TRUE;
      }
      else if (!$block->status) {
        continue;
      }

      // Initialize region key
      if (!isset($blocks[$block->region])) {
        $blocks[$block->region] = array();
      }

      // Use the user's block visibility setting, if necessary
      if ($block->custom != 0) {
        if ($user->uid && isset($user->block[$block->module][$block->delta])) {
          $enabled = $user->block[$block->module][$block->delta];
        }
        else {
          $enabled = ($block->custom == 1);
        }
      }
      else {
        $enabled = TRUE;
      }

      // Match path if necessary
      if ($block->pages) {
        if ($block->visibility < 2) {
          $path = drupal_get_path_alias($_GET['q']);
          // Compare with the internal and path alias (if any).
          $page_match = drupal_match_path($path, $block->pages);
          if ($path != $_GET['q']) {
            $page_match = $page_match || drupal_match_path($_GET['q'], $block->pages);
          }
          // When $block->visibility has a value of 0, the block is displayed on
          // all pages except those listed in $block->pages. When set to 1, it
          // is displayed only on those pages listed in $block->pages.
          $page_match = !($block->visibility xor $page_match);
        }
        else {
          $page_match = drupal_eval($block->pages);
        }
      }
      else {
        $page_match = TRUE;
      }

      $block->enabled = $enabled;
      $block->page_match = $page_match;
      $blocks[$block->region]["{$block->module}_{$block->delta}"] = $block;
    }
    // It's possible that there are still some leftover blocks in the enabled contexts.
    // Add these in as well.
    if (!empty($context_blocks)) {
      foreach ($context_blocks as $block) {
        $block = (object) $block;
        $block->status = 1;
        $block->enabled = TRUE;
        $block->page_match = TRUE;
        $block->throttle = FALSE;
        $block->title = '';
        $blocks[$block->region]["{$block->module}_{$block->delta}"] = $block;
      }
    }

    // Sort blocks -- we must do this here since blocks provided via
    // context may have overridden or altered weights.
    foreach ($blocks as $r => $dummy) {
      uasort($blocks[$r], '_context_block_sort');
    }
  }

  // ==================================================================
  // The block rendering code below is identical to block_list().
  // ==================================================================

  // Create an empty array if there were no entries
  if (!isset($blocks[$region])) {
    $blocks[$region] = array();
  }

  foreach ($blocks[$region] as $key => $block) {
    // Render the block content if it has not been created already.
    if (!isset($block->content)) {
      // Erase the block from the static array - we'll put it back if it has content.
      unset($blocks[$region][$key]);
      if ($block->enabled && $block->page_match) {
        // Check the current throttle status and see if block should be displayed
        // based on server load.
        if (!($block->throttle && (module_invoke('throttle', 'status') > 0))) {
          // Try fetching the block from cache. Block caching is not compatible with
          // node_access modules. We also preserve the submission of forms in blocks,
          // by fetching from cache only if the request method is 'GET'.
          if (!count(module_implements('node_grants')) && $_SERVER['REQUEST_METHOD'] == 'GET' && ($cid = _block_get_cache_id($block)) && ($cache = cache_get($cid, 'cache_block'))) {
            $array = $cache->data;
          }
          else {
            $array = module_invoke($block->module, 'block', 'view', $block->delta);
            if (isset($cid)) {
              cache_set($cid, $array, 'cache_block', CACHE_TEMPORARY);
            }
          }

          if (isset($array) && is_array($array)) {
            foreach ($array as $k => $v) {
              $block->$k = $v;
            }
          }
        }
        if (isset($block->content) && $block->content) {
          // Override default block title if a custom display title is present.
          if ($block->title) {
            // Check plain here to allow module generated titles to keep any markup.
            $block->subject = $block->title == '<none>' ? '' : check_plain($block->title);
          }
          if (!isset($block->subject)) {
            $block->subject = '';
          }
          $blocks[$block->region]["{$block->module}_{$block->delta}"] = $block;
        }
      }
    }
  }

  return $blocks[$region];
}

/**
 * Helper function to sort blocks.
 */
function _context_block_sort($a, $b) {
  return ($a->weight - $b->weight);
}

/**
 * THEME FUNCTIONS & RELATED ==========================================
 */

/**
 * Generates a themed set of links for node types associated with
 * the current active contexts.
 */
function theme_context_links($links) {
  $output = '';
  foreach ($links as $link) {
    $options = $link;
    $options['attributes']['class'] = isset($link['attributes']['class']) ? $link['attributes']['class'] : 'button';
    if (!empty($link['custom'])) {
      $output .= l($link['title'], $link['href'], $options);
    }
    else {
      $output .= l('+ '. t('Add !type', array('!type' => $link['title'])), $link['href'], $options);
    }
  }
  return $output;
}

/**
 * Generates an array of links (suitable for use with theme_links)
 * to the node forms of types associated with current active contexts.
 */
function context_links($reset = FALSE) {
  static $links;
  if (!$links || $reset) {
    $links = array();
    $active_types = context_active_values('node');
    if (!empty($active_types)) {
      // Collect types
      $types = node_get_types();
      // Iterate over active contexts
      foreach ($active_types as $type) {
        $add_url = 'node/add/'. str_replace('_', '-', $type);
        $item = menu_get_item($add_url);
        if ($item && $item['access'] && strpos($_GET['q'], $add_url) !== 0) {
          $links[$type] = array('title' => $types[$type]->name, 'href' => $add_url);
        }
      }
    }
    drupal_alter('context_links', $links);
  }
  return $links;
}

/**
 * A preprocess_page() function that is called *before* all other
 * preprocessors (including template_preprocess_page()). This allows
 * any final context conditions to be set and any initial reactions
 * to be triggered.
 */
function context_page_alter(&$vars) {
  module_invoke_all('context_page_condition');

  // One final, special, context reaction, for 'default' contexts:
  context_set_by_condition('default', 1);

  module_invoke_all('context_page_reaction');
}

/**
 * Implementation of hook_context_page_condition().
 */
function context_context_page_condition() {
  // Menu trail condition integration
  $trail = menu_get_active_trail();
  foreach ($trail as $item) {
    if (!empty($item['href'])) {
      context_set_by_condition('menu_trail', $item['href']);
    }
  }
}

/**
 * Implementation of preprocess_page().
 */
function context_preprocess_page(&$vars) {
  $info = context_active_values('theme_section');
  $vars['section_title'] = !empty($info['title']) ? $info['title'] : '';
  $vars['section_subtitle'] = !empty($info['subtitle']) ? $info['subtitle'] : '';

  // Merge body classes from *any* active contexts.
  $classes = array();
  foreach (context_active_contexts() as $context) {
    if (!empty($context->theme_section['class'])) {
      $classes[$context->theme_section['class']] = $context->theme_section['class'];
    }
  }
  $vars['body_classes'] .= !empty($classes) ? ' '. implode(' ', $classes) : '';

  // If primary + secondary links are pointed at the same menu, provide
  // contextual trailing by default.
  if (variable_get('menu_primary_links_source', 'primary-links') == variable_get('menu_secondary_links_source', 'secondary-links')) {
    $vars['primary_links'] = theme_get_setting('toggle_primary_links') ? context_menu_navigation_links(variable_get('menu_primary_links_source', 'primary-links')) : $vars['primary_links'];
    $vars['secondary_links'] = theme_get_setting('toggle_secondary_links') ? context_menu_navigation_links(variable_get('menu_secondary_links_source', 'secondary-links'), 1) : $vars['secondary_links'];
  }

  $vars['primary_links'] = theme_get_setting('toggle_primary_links') ? context_menu_set_active($vars['primary_links']) : $vars['primary_links'];
  $vars['secondary_links'] = theme_get_setting('toggle_secondary_links') ? context_menu_set_active($vars['secondary_links']) : $vars['secondary_links'];

  if ($context_links = context_links()) {
    $vars['context_links'] = theme('context_links', $context_links);
  }
}

/**
 * Iterates through a provided links array for use with theme_links()
 * (e.g. from menu_primary_links()) and provides an active class for
 * any items that have a path that matches an active context.
 *
 * @param $links
 *   An array of links.
 * @param $reset
 *   A boolean flag for resetting the static cache.
 *
 * @return
 *   A modified links array.
 */
function context_menu_set_active($links = array(), $reset = FALSE) {
  $active_paths = context_active_values('menu');

  // Iterate through the provided links and build a new set of links
  // that includes active classes
  $new_links = array();
  if (!empty($links)) {
    foreach ($links as $key => $link) {
      if (!empty($link['href']) && in_array($link['href'], $active_paths)) {
        if (isset($links['attributes']['class'])) {
          $link['attributes']['class'] .= ' active';
        }
        else {
          $link['attributes']['class'] = 'active';
        }
        if (strpos(' active', $key) === FALSE) {
          $new_links[$key .' active'] = $link;
        }
      }
      else {
        $new_links[$key] = $link;
      }
    }
  }

  return $new_links;
}

/**
 * Wrapper around menu_navigation_links() that gives themers the option of
 * building navigation links based on an active context trail.
 */
function context_menu_navigation_links($menu_name, $level = 0) {
  // Retrieve original path so we can repair it after our hack.
  $original_path = $_GET['q'];

  // Retrieve the first active menu path found.
  $active_paths = context_active_values('menu');
  if (!empty($active_paths)) {
    $path = current($active_paths);
    if (menu_get_item($path)) {
      menu_set_active_item($path);
    }
  }

  // Build the links requested
  $links = menu_navigation_links($menu_name, $level);

  // Repair and get out
  menu_set_active_item($original_path);
  return $links;
}
