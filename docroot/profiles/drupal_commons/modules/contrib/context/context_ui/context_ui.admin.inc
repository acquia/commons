<?php
// $Id: context_ui.admin.inc,v 1.1.2.7.2.27 2010/05/10 13:34:45 darthsteven Exp $

/**
 * Page callback for context_ui admin landing page.
 */
function context_ui_list_contexts() {
  // rebuild blocks
  _block_rehash();

  // rebuild context cache
  context_invalidate_cache();
  $output = theme('context_ui_list_contexts');
  return $output;
}

/**
 * Preprocess the contexts list theme
 */
function context_ui_preprocess_context_ui_list_contexts(&$vars) {
  drupal_add_css(drupal_get_path("module", "context_ui") ."/context_ui-list.css");
  $contexts = context_contexts();
  $conditions = context_conditions();
  $reactions = context_reactions();
  ksort($contexts);
  $vars['contexts_tree'] = array();

  foreach ($contexts as $key => $context) {
    $identifier = (isset($context->cid) && $context->cid) ? $context->cid : $key;

    $item = new stdClass();
    $item->namespace = $context->namespace;
    $item->attribute = $context->attribute;
    $item->name = $context->value;
    $item->ops = array();
    // Build the array of links:
    $links = array();

    switch ($context->type) {
      case CONTEXT_STORAGE_DEFAULT:
        $item->type = 'Default';
        $links[0] = l(t('Override'), "admin/build/context/$identifier/clone");
        $links[2] = l(t('Export'), "admin/build/context/$identifier/export");
        $links[3] = l(t('Clone'), "admin/build/context/$identifier/clone");
        break;
      case CONTEXT_STORAGE_OVERRIDDEN:
        $item->type = 'Overridden';
        $links[0] = l(t('Edit'), "admin/build/context/$identifier");
        $links[2] = l(t('Export'), "admin/build/context/$identifier/export");
        $links[3] = l(t('Clone'), "admin/build/context/$identifier/clone");
        $links[4] = l(t('Revert'), "admin/build/context/$identifier/delete");
        break;
      case CONTEXT_STORAGE_NORMAL:
        $item->type = 'Normal';
        $links[0] = l(t('Edit'), "admin/build/context/$identifier");
        $links[2] = l(t('Export'), "admin/build/context/$identifier/export");
        $links[3] = l(t('Clone'), "admin/build/context/$identifier/clone");
        $links[4] = l(t('Delete'), "admin/build/context/$identifier/delete");
    }
    switch ($context->status) {
      case CONTEXT_STATUS_DISABLED:
        $item->classes = 'context-disabled';
        $links[1] = l(t('Enable'), "admin/build/context/$identifier/enable");
        break;
      case CONTEXT_STATUS_ENABLED:
        $item->classes = 'context-enabled';
        $links[1] = l(t('Disable'), "admin/build/context/$identifier/disable");
    }
    $item->ops = implode(' | ', $links);

    foreach ($conditions as $id => $condition) {
      if (!empty($context->$id)) {
        $item->conditions[] = $condition['#title'];
      }
    }
    $item->conditions = isset($item->conditions) ? implode(', ', $item->conditions) : t('none');

    foreach ($reactions as $id => $reaction) {
      if (!empty($context->$id)) {
        $item->reactions[] = $reaction['#title'];
      }
    }
    $item->reactions = isset($item->reactions) ? implode(', ', $item->reactions) : t('none');

    $item->description = !empty($context->description) ? filter_xss_admin($context->description) : '';
    $vars['contexts_tree'][$item->namespace][$item->attribute][$item->name] = $item;
  }

  $getting_started = theme('advanced_help_topic', 'context_ui', 'getting-started', 'title');
  if (!$getting_started) {
    $getting_started = t('Install the advanced help module to view the getting started');
    $vars['help'] = t('If you install the <a href="@advanced_help_link">Advanced Help</a> module you can get more and better help.', array('@advanced_help_link' => url('http://drupal.org/project/advanced_help')));
  }
  else {
    $vars['help'] = t('Not sure what to do? Try the "!getting-started" page.', array('!getting-started' => $getting_started));
  }


  $vars['help_type_icon'] = theme('advanced_help_topic', 'context_ui', 'type');
}

/**
 * Recursive function that intelligently populates default values in a
 * form from a provided array of data.
 *
 * @param $form
 *   A form API element to populate with default values.
 * @param $data
 *   A keyed array of data that matches the tree structure of the
 *   form API branch it should populate.
 *
 * @return
 *   A form API element populated with default values.
 */
function context_ui_default_values($form, $data) {
  if (!empty($form['#tree'])) {
    foreach (element_children($form) as $id) {
      if (isset($data[$id])) {
        $form[$id] = context_ui_default_values($form[$id], $data[$id]);
      }
    }
  }
  else {
    if (is_array($data) && $form['#type'] == 'checkboxes') {
      $form['#default_value'] = array();
      foreach ($data as $value) {
        $form['#default_value'][$value] = $value;
      }
    }
    else if (is_array($data) && $form['#type'] == 'select' && $form['#multiple'] == TRUE) {
      $form['#default_value'] = array();
      foreach ($data as $value) {
        $form['#default_value'][] = $value;
      }
    }
    else if (is_array($data) && $form['#type'] == 'textarea') {
      $form['#default_value'] = implode("\n", $data);
    }
    else if (is_array($data) && $form['#type'] == 'textfield') {
      $form['#default_value'] = implode(",", $data);
    }
    else {
      $form['#default_value'] = is_array($data) ? current($data) : $data;
    }
  }
  return $form;
}

/**
 * Generates the omnibus context definition editing form.
 * Note: submission and validation handlers are in context_ui.admin.inc
 *
 * @param $op
 *   The type of form to build. Either "add", "view" or "edit"
 * @param $cid
 *   The db context identifier - required when $op == "edit"
 *
 * @return
 *   A Drupal form array.
 */
function context_ui_form(&$form_state, $op, $context = NULL) {
  switch ($op) {
    case 'add':
      drupal_set_title(t('Add a new context'));
      break;
    case 'edit':
      if (!$context->system) {
        drupal_set_title(t('Edit context: %title', array('%title' => $context->value)));
      }
      else {
        drupal_set_title(t('View %title', array('%title' => $context->value)));
      }
      break;
    case 'clone':
      drupal_set_title(t('Clone context: %title', array('%title' => $context->value)));
      $context->system = 0;
      $context->cid = NULL;
      $cid = NULL;
      break;
  }

  // Initialize context object if it doesn't already exist
  $context = !$context ? new stdClass() : $context;

  // Core context definition
  $form = array(
    '#base' => 'context_ui_form',
    '#theme' => 'context_ui_form',
  );

  $form['cid'] = array(
    '#type' => 'value',
    '#value' => isset($context->cid) ? $context->cid : NULL,
  );

  $form['system'] = array(
    '#type' => 'value',
    '#value' => isset($context->system) ? $context->system : 0,
  );

  foreach (array('value', 'attribute', 'namespace', 'description') as $field) {
    $form[$field] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#maxlength' => 64,
      '#size' => 20,
      '#disabled' => !empty($context->system) ? TRUE : FALSE,
      '#default_value' => isset($context->{$field}) ? $context->{$field} : '',
      '#title' => t(ucfirst($field)),
    );
  }

  $form['value']['#description'] = t('A system name for this context. May only contain lowercase letters, underscores, and numbers. Example: <strong>science_blog</strong>');

  $form['attribute']['#default_value'] = empty($form['attribute']['#default_value']) ? 'section' : $form['attribute']['#default_value'];
  $form['attribute']['#description'] = t('The type of context information provided in this namespace. Example: <strong>section</strong>');

  $form['namespace']['#default_value'] = empty($form['namespace']['#default_value']) ? 'context_ui' : $form['namespace']['#default_value'];
  $form['namespace']['#description'] = t('The namespace for this context definition. Example: <strong>context_ui</strong>');

  $form['description']['#required'] = FALSE;
  $form['description']['#size'] = 40;
  $form['description']['#maxlength'] = 255;
  $form['description']['#description'] = t('The description of this context definition.');

  $form['items'] = array('#tree' => TRUE);

  // We need to initialize theme in order to deal with blocks
  // and also let themes integrate against context_ui
  init_theme();
  $theme_key = variable_get('theme_default', 'garland');

  // Generate settings for context item associations
  foreach ((context_conditions(TRUE) + context_reactions(TRUE)) as $id => $info) {
    $form['items'][$id] = $info;

    // Disable element
    if (isset($context->system) && $context->system) {
      $form['items'][$id]['#disabled'] = TRUE;
    }

    // Default values
    if (isset($context->{$id})) {
      $form['items'][$id] = context_ui_default_values($form['items'][$id], $context->{$id});
    }
  }

  $modules = array();
  $query = db_query("SELECT name, info FROM {system} WHERE type = '%s'", 'module');
  while ($result = db_fetch_object($query)) {
    $info = unserialize($result->info);
    $modules[$result->name] = $info['name'];
  }

  // Control block visibility
  $block_options =
  $block_defaults = array();
  $blocks = _context_ui_get_blocks();
  $regions = system_region_list($theme_key);
  // $blocks in [0] have not been assigned a region

  // Weights range from -delta to +delta, so delta should be at least half
  // of the amount of blocks present. This makes sure all blocks in the same
  // region get an unique weight.
  $block_count = 0;
  foreach ($blocks as $region => $block_list) {
    $block_count += count($block_list);
  }
  // Add 2 to make sure there's space at either end of the block list
  $weight_delta = round(($block_count + 2) / 2);

  foreach ($blocks[0] as $block) {
    $block_options[$block->module][$block->bid] = check_plain($block->label);
  }
  ksort($block_options);

  $form['block'] = array(
    '#tree' => TRUE,
  );

  //Save the value to use in the process function
  $form['block']['max_block_weight'] = array(
    '#value' => $weight_delta,
    '#type' => 'value',
  );

  $form['block']['help'] = array(
    '#type' => 'markup',
    '#value' => t('Control block visibility using context. Selected blocks will be shown when this context is set provided that custom block visibility settings and/or throttling do not hide them. Grayed out blocks are those provided by Drupal\'s standard block settings. These settings apply to the current theme and any enabled themes with regions in common.'),
  );

  $form['block']['selector'] = array(
    '#type' => 'item',
    '#tree' => TRUE,
    '#prefix' => '<div class="context-ui-block-selector">',
    '#suffix' => '</div>',
  );
  foreach ($block_options as $module => $module_blocks) {
    if (!empty($module_blocks)) {
      $form['block']['selector'][$module] = array(
        '#type' => 'checkboxes',
        '#title' => $modules[$module],
        '#options' => $module_blocks,
        '#disabled' => isset($context->system) && $context->system ? TRUE : FALSE,
      );
    }
  }

  $form['block']['blocks'] = array(
    '#tree' => TRUE,
    '#theme' => 'context_ui_block_ui',
  );
  foreach ($regions as $region => $label) {
    $defaults = array();
    $midpoint = FALSE;
    $form['block']['blocks'][$region] = array(
      '#type' => 'item',
      '#title' => $label,
      '#tree' => TRUE,
    );

    $system = _context_ui_get_blocks($region);
    if ($system) {
      $system_blocks = array();
      foreach ($system as $block) {
        $system_blocks[] = check_plain($block->label);
      }
      $system_blocks = "<span class='system-blocks'>". implode(", ", $system_blocks) ."</span";
      $form['block']['blocks'][$region]['system'] = array(
        '#type' => 'markup',
        '#tree' => TRUE,
        '#value' => $system_blocks,
        '#weight' => 0,
        'weight' => array(
          '#type' => 'weight',
          '#delta' => $weight_delta,
          '#default_value' => 0,
        ),
      );
    }

    $i = 0;
    foreach (_context_ui_get_blocks($region, $context) as $block) {
      if ($block->type == 'context_ui') {
        $form['block']['blocks'][$region][$block->bid] = array(
          '#type' => 'markup',
          '#tree' => TRUE,
          '#value' => check_plain($block->label),
          '#weight' => $block->weight,
          'weight' => array(
            '#type' => 'weight',
            '#delta' => $weight_delta,
            '#default_value' => $block->weight,
          ),
        );
      }
      $i++;
    }

    uasort($form['block']['blocks'][$region], 'element_sort');

    $defaults = implode(',', element_children($form['block']['blocks'][$region]));
    $form['block']['regions'][$region] = array(
      '#type' => 'hidden',
      '#default_value' => $defaults,
    );
  }

  if (!empty($context->system)) {
    $form['back'] = array(
      '#type' => 'item',
      '#value' => l(t('Back'), 'admin/build/context'),
    );
  }
  else {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
  }

  if (empty($context->system) && $op == 'edit') {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      // Skip validation for this button, as we're just doing a redirect:
      '#validate' => array(),
      '#submit' => array('context_ui_form_delete_submit'),
    );
  }

  return $form;
}

/**
 * Generates an abbreviated list of items for display in the
 * setter/getter UI.
 */
function context_ui_item_display($type, $element) {
  // We're dealing with an item with options --
  // try to grab the display-friendly value
  $items = array();
  $title = l($element['#title'], $_GET['q'], array('fragment' => $type, 'attributes' => array('class' => 'context_ui-item-section-link')));
  // Check for the extra help:
  if (isset($element['#help_topic']) && isset($element['#help_module']) && module_exists($element['#help_module'])) {
    $title = theme('advanced_help_topic', $element['#help_module'], $element['#help_topic']) . $title;
  }

  if (isset($element['#options'])) {
    if (isset($element['#default_value'])) {
      if (is_array($element['#default_value'])) {
        foreach ($element['#default_value'] as $k) {
          $items[] = isset($element['#options'][$k]) ? $element['#options'][$k] : $k;
        }
      }
      else if (is_string($element['#default_value']) && $k = $element['#default_value']) {
        if (!empty($element['#options'][$k])) {
          $items[] = $element['#options'][$k];
        }
        else {
          // Fallback to the actual value
          $items[] = $k;
        }
      }
    }
    if (empty($items)) {
      $items[] = array('data' => '', 'class' => 'empty');
    }
  }
  else if (isset($element['#type']) && in_array($element['#type'], array('textfield', 'textarea'))) {
    $items[] = !empty($element['#default_value']) ? $element['#default_value'] : array('data' => '', 'class' => 'empty');
  }
  foreach ($items as $k => $v) {
    $items[$k] = is_string($v) ? check_plain($v) : $v;
  }
  $output = '';
  $output .= theme('item_list', $items, $title, 'ul', array('id' => 'display-'. $type));
  return $output;
}

/**
 * Theme function for context_ui_form()
 */
function theme_context_ui_form($form) {
  drupal_add_css(drupal_get_path("module", "context_ui") ."/context_ui.css");
  drupal_add_js(drupal_get_path("module", "context_ui") ."/context_ui.js");

  $output = '';

  // Render space / key / value trio in a 3-column table
  $rows = array(
    'trio' => array('class' => 'trio'),
    'description' => array()
  );
  $rows['trio']['data'][] = array('data' => drupal_render($form['namespace']), 'class' => 'namespace');
  $rows['trio']['data'][] = array('data' => drupal_render($form['attribute']), 'class' => 'attribute');
  $rows['trio']['data'][] = array('data' => drupal_render($form['value']), 'class' => 'value');
  $rows['description'] = array(array('data' => drupal_render($form['description']), 'colspan' => 3));
  $output .= theme('table', array(), $rows, array('id' => 'context-ui-trio'));


  // Render setters / getters as a two column split
  $widgets = '';
  $display = "<div class='label'>";
  $display .= t('Conditions');
  $display .= "<span class='description'>". t('trigger the activation of this context') ."</span>";
  $display .= "</div>";
  foreach (array_keys(context_conditions()) as $id) {
    $widgets .= "<div id='widget-$id' class='widget'>". drupal_render($form['items'][$id]) ."</div>";
    $display .= context_ui_item_display($id, $form['items'][$id]);
  }

  $display .= "<div class='label'>";
  $display .= t('Reactions');
  $display .= "<span class='description'>". t('respond when this context is active') ."</span>";
  $display .= "</div>";
  foreach (array_keys(context_reactions()) as $id) {
    $widgets .= "<div id='widget-$id' class='widget'>". drupal_render($form['items'][$id]) ."</div>";
    $display .= context_ui_item_display($id, $form['items'][$id]);
  }
  $rows = array(
    array(
      array('data' => $display, 'class' => 'display'),
      array('data' => $widgets, 'class' => 'widget'),
    ),
  );
  $output .= theme('table', array(), $rows, array('id' => 'context-ui-items'));


  // Render block visibility
  $rows = array(
    array(
      array('data' => drupal_render($form['block']['blocks']), 'class' => 'display'),
      array('data' => drupal_render($form['block']['selector']) . drupal_render($form['block']['help']), 'class' => 'widget'),
    ),
  );
  $output .= theme('table', array(), $rows, array('id' => 'context-ui-blocks'));

  $output .= drupal_render($form);
  return $output;
}

/**
 * Provide a form to confirm one of the provided actions.
 */
function context_ui_confirm(&$form_state, $op = 'delete', $context) {
  $form = array();
  $form['context'] = array('#type' => 'value', '#value' => $context);
  $form['action'] = array('#type' => 'value', '#value' => $op);
  switch ($op) {
    case 'delete':
      $contexts = context_contexts();
      switch ($contexts["{$context->namespace}-{$context->attribute}-{$context->value}"]->type) {
        case CONTEXT_STORAGE_OVERRIDDEN:
          $action = t('revert');
          $message = t('This action will permanently remove any customizations made to this context.');
          break;
        default:
          $action = t('delete');
          $message = t('This action will remove this context permanently from your site.');
          break;
      }
      break;
    case 'disable':
      $action = t('disable');
      $message = '';
      break;
    case 'enable':
      $action = t('enable');
      $message = '';
      break;
  }
  $form = confirm_form($form,
    t('Are you sure you want to !action the context %title?', array('%title' => $context->value, '!action' => $action)),
    'admin/build/context',
    $message,
    drupal_ucfirst($action), t('Cancel')
  );
  return $form;
}

/**
 * Submit handler for the context_ui_confirm form.
 */
function context_ui_confirm_submit($form, &$form_state) {
  switch ($form_state['values']['action']) {
    case 'delete':
      context_delete_context($form_state['values']['context']);
      break;
    case 'disable':
    case 'enable':
      $context = $form_state['values']['context'];
      if ($context) {
        $status = variable_get('context_status', array());
        $status["{$context->namespace}-{$context->attribute}-{$context->value}"] = ($form_state['values']['action'] == 'disable' ? CONTEXT_STATUS_DISABLED : CONTEXT_STATUS_ENABLED);
        variable_set('context_status', $status);
        context_invalidate_cache();
      }
      break;
  }
  $form_state['redirect'] = 'admin/build/context';
}

/**
 * Page callback for import form. Switches form output to context form
 * if import submission has occurred.
 */
function context_ui_import_page() {
  if (!empty($_POST) && $_POST['form_id'] == 'context_ui_form') {
    return drupal_get_form('context_ui_form', 'add');
  }
  return drupal_get_form('context_ui_import');
}

/**
 * Import form. Provides simple helptext instructions and textarea for
 * pasting a context definition.
 */
function context_ui_import() {
  drupal_set_title(t('Import context'));
  $help = t('You can import a context definition by pasting the exported context object code into the field below.');
  $form = array();
  $form['help'] = array(
    '#type' => 'item',
    '#value' => $help,
  );
  $form['import'] = array(
    '#title' => t('Context Object'),
    '#type' => 'textarea',
    '#rows' => 10,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

/**
 * Import form submit handler. Evaluates import code and transfers to
 * context definition form.
 */
function context_ui_import_submit($form, &$form_state) {
  $items = array();
  if ($import = $form_state['values']['import']) {
    if (strpos($import, 'return') !== 0) {
      $import = "return {$import};";
    }
    ob_start();
    $context = eval($import);
    ob_end_clean();
  }
  if (is_array($context)) {
    $context = (object) $context;
    if ($exists = context_load_context($context)) {
      drupal_set_message(t('A user-defined context definition with this space/key/value identifier already exists. Please remove the existing context before importing this definition.'), 'error');
      $form_state['redirect'] = 'admin/build/context';
    }
    else {
      drupal_set_title(t('Add context'));
      $output = drupal_get_form('context_ui_form', 'add', (object) $context);
      print theme('page', $output);
      exit;
    }
  }
  else {
    drupal_set_message(t('An error occurred while importing. Please check your context definition.', 'error'));
    $form_state['redirect'] = 'admin/build/context';
  }
}

/**
 * Provides a form with an exported context definition for use in modules.
 *
 * @param $cid
 *   A context id.
 *
 * @return
 *   A FormAPI array.
 */
function context_ui_export(&$form_state, $context) {
  drupal_set_title(t('Export %title', array('%title' => $context->value)));

  // prune system specific information and cast for Drupal's AOP (array oriented programming)
  $prune = array('cid', 'status', 'system', 'type');
  foreach ($prune as $key) {
    if (isset($context->{$key})) {
      unset($context->{$key});
    }
  }
  $context = (array) $context;

  // clear out empty associations
  foreach ($context as $key => $item) {
    if (context_empty($item)) {
      unset($context[$key]);
    }
  }

  // clean up blocks
  if (!empty($context['block'])) {
    foreach ($context['block'] as $bid => $block) {
      unset($block->bid);
      $context['block'][$bid] = (array) $block;
    }
  }

  // build the form
  $form = array();
  $form['export'] = array(
    '#type' => 'textarea',
    '#rows' => 24,
    '#value' => $context,
    '#theme' => 'context_ui_export_form',
  );
  return $form;
}

/**
 * Themes a context value into an export friendly var_export().
 */
function theme_context_ui_export_form($form) {
  $form['#value'] = $form['#default_value'] = context_var_export($form['#value'], '', FALSE) . ';';
  return theme('textarea', $form);
}

/**
 * Export multiple contexts
 */
function context_ui_bulk_export(&$form_state) {
  $form = array();
  $contexts = context_contexts();
  if (isset($form_state['storage']['module_name'])) {
    $code = "function ". $form_state['storage']['module_name'] ."_context_default_contexts() {\n";
    if (isset($form_state['storage']['contexts']) && is_array($form_state['storage']['contexts'])) {
      foreach ($form_state['storage']['contexts'] as $id) {
        $context = (array) $contexts[$id];
        unset($context['cid']);
        $code .= '  $items[] = '. context_var_export($context, '  ') .";\n\n";
      }
    }
    $code .= "  return \$items;\n}";
    $form['code'] = array(
      '#type' => 'textarea',
      '#title' => t('Code'),
      '#description' => t('Put this in your module\'s .module file.'),
      '#cols' => 60,
      '#rows' => 30,
      '#value' => $code,
      '#default_value' => $code,
    );
  }
  else {
    $form['#contexts'] = $contexts;
    $form['checkboxes']['#tree'] = TRUE;

    foreach ($contexts as $context) {
      $form['checkboxes']["$context->namespace-$context->attribute-$context->value"] = array(
        '#title' => $context->value,
        '#type' => 'checkbox',
      );
    }

    $form['module_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Module Name'),
      '#description' => t('The name of the module for which to generate the hook.'),
      '#size' => 40,
      '#maxlength' => 255,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Export'),
    );

    $form['#theme'] = 'context_ui_bulk_export_table';
  }

  return $form;
}

function context_ui_bulk_export_submit($form, &$form_state) {
  $form_state['storage']['module_name'] = $form_state['values']['module_name'];
  foreach ($form_state['values']['checkboxes'] as $key => $value) {
    if ($value) {
      $form_state['storage']['contexts'][] = $key;
    }
  }
}

function theme_context_ui_bulk_export_table($form) {
  // Add css
  drupal_add_css(drupal_get_path("module", "context_ui") ."/context_ui.css");

  $rows = $headings = array();
  foreach (element_children($form['checkboxes']) as $key) {
    $context = $form['#contexts'][$key];
    $row = array();

    $namespace = $context->namespace;
    $attribute = $context->attribute;
    $value = $context->value;
    if (isset($context->cid) && $context->cid) {
      $identifier = $context->cid;
    }
    else {
      $identifier = $key;
    }

    // If no heading has been printed for this n/a pair, do so
    if (!isset($rows["$namespace-$attribute"])) {
      $row = array('', array('data' => "<span class='context-namespace'>$namespace &gt; $attribute</span>", 'colspan' => 2));
      $rows["$namespace-$attribute"] = $row;
    }
    unset($form['checkboxes'][$key]['#title']);

    $rows[$key] = array(
      'data' => array(
        array(
          'data' => drupal_render($form['checkboxes'][$key]),
          'class' => 'context-ui-checkbox',
        ),
        array(
          'data' => '<strong>'. $value .'</strong>',
          'class' => 'context-name',
        ),
      ),
      'class' => 'context-table-row ',
    );
  }
  $output = theme('table', array(theme('table_select_header_cell'), t('Context')), $rows, array('class' => 'context-ui-bulk-export context-ui-overview'));
  $output .= drupal_render($form);

  return $output;
}

/**
 * Generates the AJAX enabled block administration portion of the context_ui admin form.
 */
function theme_context_ui_block_ui($form) {
  // Add draggable weights
  drupal_add_js('misc/tableheader.js');

  $output = '';

  foreach (element_children($form) as $region) {
    $table_id = 'context-ui-region-'. str_replace('_', '-', $region);
    drupal_add_tabledrag($table_id, 'order', 'sibling', 'block-weight', NULL, NULL, FALSE);
    $rows = array();
    foreach (element_children($form[$region]) as $id) {
      $form[$region][$id]['weight']['#attributes'] = array('class' => 'block-weight');
      $label = $form[$region][$id]['#value'];
      if ($id == 'system') {
        $remove = '';
      }
      else {
        $remove = l(t('X'), $_GET['q'], array('fragment' => 'remove', 'attributes' => array('class' => 'remove')));
      }
      $rows[] = array(
        'data' => array($label . drupal_render($form[$region][$id]['weight']), $remove),
        'class' => 'draggable',
        'id' => $id,
      );
    }
    $output .= "<div class='label'>";
    $output .= l(t('+ Add'), $_GET['q'], array('fragment' => $region, 'attributes' => array('class' => 'add-block')));
    $output .= $form[$region]['#title'];
    $output .= "</div>";
    $output .= theme('table', array(), $rows, array('id' => $table_id));
  }
  return $output;
}

/**
 * hook_validate()
 */
function context_ui_form_validate($form, &$form_state) {
  // Check for string identifier sanity
  foreach (array('value', 'attribute', 'namespace') as $elem) {
    if (!preg_match('!^[a-z0-9_]+$!', $form_state['values'][$elem])) {
      form_set_error($elem, t('The context !elem can only consist of lowercase letters, underscores, and numbers.', array('!elem' => $elem)));
    }
  }
  if (!isset($form_state['values']['cid'])) {
    // Check that no other user-defined context definition has taken this identifier already
    $context = new stdClass();
    $context->namespace = $form_state['values']['namespace'];
    $context->attribute = $form_state['values']['attribute'];
    $context->value = $form_state['values']['value'];
    if ($exists = context_load_context($context)) {
      form_set_error($form_state['values']['value'], t('A user-defined context with this namespace/key/value identifier already exists. Please delete the existing definition before creating a new one.'));
    }
  }
  else {
    // Check that this context won't overwite another:
    $context = new stdClass();
    $context->namespace = $form_state['values']['namespace'];
    $context->attribute = $form_state['values']['attribute'];
    $context->value = $form_state['values']['value'];
    $exists = context_load_context($context);
    if (isset($exists->cid) && ($exists->cid != $form_state['values']['cid'])) {
      form_set_error($form_state['values']['value'], t('A user-defined context with this namespace/key/value identifier already exists. Please delete the existing context or change your namespace/key/value identifiers.'));
    }
  }
}

/**
 * Produces a context object from submitted form values.
 *
 * @param $form
 *   A form array with submitted values
 *
 * @return
 *   A context object
 */
function context_ui_form_process($form) {
  $context = new stdClass();

  // Context ns/attr/value definition
  foreach (array('cid', 'system', 'namespace', 'attribute', 'value', 'description') as $item) {
    $context->$item = isset($form[$item]) ? $form[$item] : NULL;
  }
  $context->status = 1; // all user defined contexts have status 1

  // Retrieve values for conditions and reactions
  foreach (context_conditions() + context_reactions() as $id => $element) {
    if (is_array($form['items'][$id])) {
      if (isset($element['#type']) && $element['#type'] == 'checkboxes') {
        $items = array_keys(array_filter($form['items'][$id]));
      }
      else {
        $items = array_filter($form['items'][$id]);
      }
    }
    else {
      $items = isset($form['items'][$id]) ? $form['items'][$id] : '';
    }

    if (!empty($items)) {
      $context->{$id} = $items;
    }
  }

  // Blocks must be done by region
  $theme_key = variable_get('theme_default', 'garland');
  // Get list of "valid" available blocks
  $valid = _context_ui_get_blocks();
  $valid = $valid[0];
  foreach (system_region_list($theme_key) as $region => $label) {
    if ($blocks = $form['block']['regions'][$region]) {
      $blocks = explode(',', $blocks);
      $midpoint = array_search('system', $blocks);
      foreach ($blocks as $position => $bid) {
        // Don't initialize the block array until we're actually sure
        // the context contains blocks.
        if (!isset($context->block)) {
          $context->block = array();
        }
        if ($bid != 'system') {
          $block = $valid[$bid];
          //use the max block weight to calculate modifier
          $modifier = $position < $midpoint ? $form['block']['max_block_weight'] * -1 : $form['block']['max_block_weight'];
          $block->weight = $position - $midpoint + $modifier;
          $block->region = $region;
          $block->type = 'context_ui';
          $context->block[$block->bid] = $block;
        }
      }
    }
  }

  return $context;
}

/**
 * Submit handler for main context_ui form.
 */
function context_ui_form_submit($form, &$form_state) {
  $context = context_ui_form_process($form_state['values']);
  $result = context_save_context($context);
  if ($result) {
    drupal_set_message(t('The context %title was saved successfully.', array('%title' =>  $context->value)));
  }
  else {
    drupal_set_message(t('An error occurred while attempting to save your context information.'), 'error');
  }
  $form_state['redirect'] = 'admin/build/context';
}

/**
 * Submit handler for the delete button on the main context_ui form.
 */
function context_ui_form_delete_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/context/'. $form_state['values']['cid'] .'/delete';
}

/**
 * Helper function to generate a list of blocks from a specified region. If provided a context object,
 * will generate a full list of blocks for that region distinguishing between system blocks and
 * context-provided blocks.
 *
 * @param $region
 *   The string identifier for a theme region. e.g. "left"
 * @param $context
 *   A context object.
 *
 * @return
 *   A keyed (by "module_delta" convention) array of blocks.
 */
function _context_ui_get_blocks($region = NULL, $context = NULL) {
  static $block_info, $valid, $system_blocks;

  // we don't static cache context blocks
  $context_blocks = $blocks = array();

  if (!isset($system_blocks)) {
    $system_blocks = array();

    // Compute the active themes:
    $active_themes = array();
    foreach (list_themes() as $theme => $theme_ob) {
      if ($theme_ob->status) {
        $active_themes[] = $theme;
      }
    }

    // There's a small chance that Drupal doesn't actually have any themes active:
    if (empty($active_themes)) {
      $active_themes[] = variable_get('theme_default', 'garland');
    }

    // Rebuild block 'cache':
    _context_ui_block_rehash($active_themes);

    // Load blocks from database
    $result = db_query("SELECT module, delta, weight, region, status FROM {blocks} WHERE theme IN (" . db_placeholders($active_themes, 'varchar') . ") ORDER BY module, delta, weight, region, status", $active_themes);
    while ($block = db_fetch_object($result)) {
      // load block info
      $block_info[$block->module] = isset($block_info[$block->module]) ? $block_info[$block->module] : module_invoke($block->module, 'block', 'list');

      // ensure DB entry wasn't stale before making block usable
      if (!empty($block_info[$block->module][$block->delta]['info'])) {
        $block->label = $block_info[$block->module][$block->delta]['info'];
        $block->type = 'system';
        $block->bid = $block->module .'_'. $block->delta;
        // add block to region
        if ($block->region && $block->status) {
          $system_blocks[$block->region][$block->bid] = $block;
        }
        else {
          $system_blocks[0][$block->bid] = $block;
        }
        // mark block as available in DB
        $valid[$block->module ."_". $block->delta] = TRUE;
      }
    }
  }

  // load system blocks into main block array
  $blocks = $system_blocks;

  // load context blocks if provided
  if (is_object($context) && !empty($context->block)) {
    // iterate over context-associated blocks
    foreach ($context->block as $block) {
      $block = (object) $block;
      // check that this is a valid block
      if ($valid[$block->module ."_". $block->delta]) {
        // if region has been specified, ensure that block belongs to it
        if (!$region || (isset($region) && $block->region == $region)) {
          // load block info
          $block_info[$block->module] = $block_info[$block->module] ? $block_info[$block->module] : module_invoke($block->module, 'block', 'list');
          $block->label = $block_info[$block->module][$block->delta]['info'];
          $block->type = 'context_ui';
          $block->bid = $block->module .'_'. $block->delta;
          // add block to region
          if ($block->region) {
            $blocks[$block->region][$block->bid] = $block;
          }
          else {
            $blocks[0][$block->bid] = $block;
          }
        }
      }
    }
  }

  foreach ($blocks as $r => $sort_region) {
    if ($r !== 0) {
      uasort($sort_region, create_function('$a, $b', 'return ($a->weight - $b->weight);'));
      $blocks[$r] = $sort_region;
    }
  }

  if (!empty($region)) {
    return isset($blocks[$region]) ? $blocks[$region] : array();
  }
  return $blocks;
}

/**
 * A helper function to rebuild the 'block cache' for a number of given themes.
 *
 * This is needed because _block_rehash() uses the global $theme_key to know
 * which theme's block cache to 'rehash'.
 * This function has the potential to go horribly wrong, and leave the user
 * looking at some very random theme.
 *
 * Drupal maintains a 'block cache' of all the blocks from different modules in
 * the 'blocks' table, but it doesn't get rebuilt very often, and it doesn't get
 * rebuilt for any themes except the active one (in that page request).
 *
 * @param $themes
 *   An array of theme names to rebuild the 'block cache' for.
 */
function _context_ui_block_rehash($themes) {
  global $theme_key;

  // Store the current theme key for later:
  $previous_theme_key = $theme_key;

  foreach ($themes as $theme) {
    // Temporarily set the given theme as the active theme:
    $theme_key = $theme;
    // Rebuild the 'block cache' for the given theme.
    _block_rehash();
  }

  // Restore the previously set theme:
  $theme_key = $previous_theme_key;
}
