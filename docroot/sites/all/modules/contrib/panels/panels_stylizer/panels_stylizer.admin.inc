<?php
// $Id: panels_stylizer.admin.inc,v 1.1.2.3 2010/05/20 09:05:37 sdboyer Exp $

/**
 * @file
 * Contains admin pages for stylizer integration for Panels.
 */

/**
 * Entry point for the panels style builder administration.
 */
function panels_stylizer_list_styles_page($js = NULL) {
  $js = ($js == 'ajax');

  $items = array();
  $sorts = array();

  $styles = panels_stylizer_load_all();

  $input = $_POST;

  // Respond to a reset command by clearing session and doing a drupal goto
  // back to the base URL.
  if (isset($input['op']) && $input['op'] == t('Reset')) {
    unset($_SESSION['panels']['#style_admin']);
    if (!$js) {
      return drupal_goto($_GET['q']);
    }
    // clear everything but form id, form build id and form token:
    $keys = array_keys($input);
    foreach ($keys as $id) {
      if ($id != 'form_id' && $id != 'form_build_id' && $id != 'form_token') {
        unset($input[$id]);
      }
    }
    $replace_form = TRUE;
  }
  if (!isset($input['form_id'])) {
    if (isset($_SESSION['panels']['#style_admin']) && is_array($_SESSION['panels']['#style_admin'])) {
      $input  = $_SESSION['panels']['#style_admin'];
    }
  }
  else {
    $_SESSION['panels']['#style_admin'] = $input;
    unset($_SESSION['panels']['#style_admin']['q']);
  }

  // This is where the form will put the output.
  $rows = array();

  $form_state = array(
    'styles' => &$styles,
    'rows' => &$rows,
    'input' => $input,
    'rerender' => TRUE,
    'no_redirect' => TRUE,
  );

  ctools_include('form');
  $form = ctools_build_form('panels_stylizer_list_styles_form', $form_state);

  $header = array(
    array('data' => t('Type'), 'class' => 'panels-style-type'),
    array('data' => t('Name'), 'class' => 'panels-style-name'),
    array('data' => t('Title'), 'class' => 'panels-style-title'),
    array('data' => t('Base'), 'class' => 'panels-style-base'),
    array('data' => t('Storage'), 'class' => 'panels-style-storage'),
  );

  $header[] = array('data' => t('Operations'), 'class' => 'panels-style-operations');
  $table = theme('table', $header, $form_state['rows'], array('id' => 'panels-style-list-styles'));

  if (!$js) {
    drupal_add_css(drupal_get_path('module', 'panels_stylizer') . '/panels-style.css');
    return $form . $table;
  }

  ctools_include('ajax');
  $commands = array();
  $commands[] = ctools_ajax_command_replace('#panels-style-list-styles', $table);
  if (!empty($replace_form)) {
    $commands[] = ctools_ajax_command_replace('#panels-style-list-styles-form', $form);
  }
  ctools_ajax_render($commands);
}

/**
 * Provide a form for sorting and filtering the list of pages.
 */
function panels_stylizer_list_styles_form(&$form_state) {
  ctools_include('stylizer');

  // This forces the form to *always* treat as submitted which is
  // necessary to make it work.
  if (empty($_POST)) {
    $form["#programmed"] = TRUE;
  }

  $form['#action'] = url('admin/build/panels/style/list/nojs/', array('absolute' => TRUE));
  if (!variable_get('clean_url', FALSE)) {
    $form['q'] = array(
      '#type' => 'hidden',
      '#value' => $_GET['q'],
    );
  }

  $all = array('all' => t('- All -'));

  $plugins = ctools_get_style_bases();
  $form_state['plugins'] = $plugins;

  $options = $all;
  foreach ($plugins as $name => $plugin) {
    if ($plugin['module'] == 'panels') {
      $options[$name] = $plugin['title'];
    }
  }

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('type'),
    '#options' => $all + array(
      'pane' => t('Pane'),
      'region' => t('Region')
    ),
    '#default_value' => 'all',
  );

  $form['base'] = array(
    '#type' => 'select',
    '#title' => t('Base'),
    '#options' => $all + $options,
    '#default_value' => 'all',
  );

  $form['storage'] = array(
    '#type' => 'select',
    '#title' => t('Storage'),
    '#options' => $all + array(
      t('Normal') => t('Normal'),
      t('Default') => t('Default'),
      t('Overridden') => t('Overridden'),
    ),
    '#default_value' => 'all',
  );

  $form['disabled'] = array(
    '#type' => 'select',
    '#title' => t('Enabled'),
    '#options' => $all + array(
      '0' => t('Enabled'),
      '1' => t('Disabled')
    ),
    '#default_value' => 'all',
  );

  $form['search'] = array(
    '#type' => 'textfield',
    '#title' => t('Search'),
  );

  $form['order'] = array(
    '#type' => 'select',
    '#title' => t('Sort by'),
    '#options' => array(
      'disabled' => t('Enabled, title'),
      'title' => t('Title'),
      'name' => t('Name'),
      'path' => t('Base'),
      'type' => t('Type'),
      'storage' => t('Storage'),
    ),
    '#default_value' => 'disabled',
  );

  $form['sort'] = array(
    '#type' => 'select',
    '#title' => t('Order'),
    '#options' => array(
      'asc' => t('Up'),
      'desc' => t('Down'),
    ),
    '#default_value' => 'asc',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#id' => 'edit-style-apply',
    '#value' => t('Apply'),
    '#attributes' => array('class' => 'ctools-use-ajax'),
  );

  $form['reset'] = array(
    '#type' => 'submit',
    '#id' => 'edit-style-reset',
    '#value' => t('Reset'),
    '#attributes' => array('class' => 'ctools-use-ajax'),
  );

  ctools_add_js('ajax-responder');
  drupal_add_js('misc/jquery.form.js');
  drupal_add_js(drupal_get_path('module', 'panels_stylizer') . '/panels-style.js');

  $form['#prefix'] = '<div class="clear-block">';
  $form['#suffix'] = '</div>';

  return $form;
}

/**
 * Accept submission from the sort/filter form and apply it to the list
 */
function panels_stylizer_list_styles_form_submit(&$form, &$form_state) {
  // Filter and re-sort the pages.

  $sorts = array();
  foreach ($form_state['styles'] as $name => $style) {
    // Filter
    if (empty($form_state['plugins'][$style->settings['style_base']])) {
      $plugin = array(
        'name' => 'broken',
        'title' => t('Missing plugin'),
        'type' => t('Unknown'),
      );
    }
    else {
      $plugin = $form_state['plugins'][$style->settings['style_base']];
    }

    if ($form_state['values']['type'] != 'all' && $form_state['values']['type'] != $plugin['type']) {
      continue;
    }

    if ($form_state['values']['base'] != 'all' && $form_state['values']['base'] != $plugin['name']) {
      continue;
    }

    if ($form_state['values']['storage'] != 'all' && $form_state['values']['storage'] != $style->type) {
      continue;
    }

    if ($form_state['values']['disabled'] != 'all' && $form_state['values']['disabled'] != !empty($style->disabled)) {
      continue;
    }

    $search = strtolower($form_state['values']['search']);
    if ($form_state['values']['search'] &&
        strpos(strtolower($style->admin_title), $search) === FALSE &&
        strpos(strtolower($style->admin_description), $search) === FALSE &&
        strpos(strtolower($plugin['title']), $search) === FALSE) {
          continue;
    }

    // Set up sorting
    switch ($form_state['values']['order']) {
      case 'disabled':
        $sorts[$name] = empty($style->disabled) . $style->admin_title;
        break;
      case 'title':
        $sorts[$name] = $style->admin_title;
        break;
      case 'name':
        $sorts[$name] = $style->name;
        break;
      case 'type':
        $sorts[$name] = $plugin['type'] . $style->admin_title;
        break;
      case 'storage':
        $sorts[$name] = $style->type . $style->admin_title;
        break;
    }

    $operations = array(
      array(
        'title' => t('Edit'),
        'href' => 'admin/build/panels/style/edit/' . $name,
      ),
    );

    if (!empty($style->disabled)) {
      $operations[] = array(
        'title' => t('Enable'),
        'href' => 'admin/build/panels/style/enable/' . $name,
        'attributes' => array('class' => 'ctools-use-ajax'),
      );
    }
    else {
      $operations[] = array(
        'title' => t('Disable'),
        'href' => 'admin/build/panels/style/disable/' . $name,
        'attributes' => array('class' => 'ctools-use-ajax'),
      );
    }

    switch ($style->type) {
      case t('Normal'):
        $operations[] = array(
          'title' => t('Delete'),
          'href' => 'admin/build/panels/style/delete/' . $name,
        );
        break;
      case t('Overridden'):
        $operations[] = array(
          'title' => t('Revert'),
          'href' => 'admin/build/panels/style/delete/' . $name,
        );
        break;
    }

    $operations[] = array(
      'title' => t('Export'),
      'href' => 'admin/build/panels/style/export/' . $name,
    );

    $operations[] = array(
      'title' => t('Clone'),
      'href' => 'admin/build/panels/style/clone/' . $name,
    );

    $class = !empty($style->disabled) ? 'panels-style-disabled' : 'panels-style-enabled';
    switch ($plugin['type']) {
      case 'pane':
        $type = t('Pane');
        break;
      case 'region':
        $type = t('Region');
        break;
      default:
        $type = t('Unknown');
    }

    $rows[$name] = array(
      'data' => array(
        array('data' => $type, 'class' => 'panels-style-type'),
        array('data' => check_plain($style->name), 'class' => 'panels-style-name'),
        array('data' => check_plain($style->admin_title), 'class' => 'panels-style-title'),
        array('data' => check_plain($plugin['title']), 'class' => 'panels-style-base'),
        array('data' => check_plain($style->type), 'class' => 'panels-style-storage'),
        array('data' => theme('links', $operations), 'class' => 'panels-style-operations'),
      ),
      'title' => check_plain($style->admin_description),
      'class' => $class,
    );
  }

  // Now actually sort
  if ($form_state['values']['sort'] == 'desc') {
    arsort($sorts);
  }
  else {
    asort($sorts);
  }

  // Nuke the original.
  $form_state['rows'] = array();
  // And restore.
  foreach ($sorts as $name => $title) {
    $form_state['rows'][$name] = $rows[$name];
  }
}

/**
 * Page entry point to add a new style.
 */
function panels_stylizer_add_style_page($type, $step = NULL) {
  ctools_include('stylizer');
  $js = FALSE;
  if ($type == 'region') {
    $path = 'admin/build/panels/style/add-region/%step';
  }
  else {
    $path = 'admin/build/panels/style/add/%step';
  }
  $info = array(
    'module' => 'panels',
    'type' => $type,
    'path' => $path,
    'owner form' => 'panels_stylizer_edit_style_form',
    'owner form validate' => 'panels_stylizer_edit_style_form_validate',
    'owner form submit' => 'panels_stylizer_edit_style_form_submit',
    'owner settings' => array('name' => '', 'admin_title' => '', 'admin_description' => ''),
  );

  $output = ctools_stylizer_edit_style($info, $js, $step);
  if (!empty($info['complete'])) {
    $style = panels_stylizer_new();
    $style->name = $info['settings']['name'];
    $style->admin_title = $info['owner settings']['admin_title'];
    $style->admin_description = $info['owner settings']['admin_description'];
    $style->settings = $info['settings'];
    panels_stylizer_save($style);
    drupal_set_message('The style has been created.');
    drupal_goto('admin/build/panels/style');
  }

  return $output;
}

/**
 * Entry point for the panels style builder administration.
 */
function panels_stylizer_edit_style_page($style, $step = NULL) {
  // Tabs and breadcrumb disappearing, this helps alleviate through cheating.
  ctools_include('menu');
  $trail = ctools_get_menu_trail('admin/build/panels/style/list');
  menu_set_active_trail($trail);

  ctools_include('stylizer');

  $js = FALSE;
  $info = array(
    'module' => 'panels',
    'path' => 'admin/build/panels/style/edit/%name/%step',
    'owner form' => 'panels_stylizer_edit_style_form',
    'owner form validate' => 'panels_stylizer_edit_style_form_validate',
    'owner form submit' => 'panels_stylizer_edit_style_form_submit',
    'owner settings' => array('name' => $style->name, 'admin_title' => $style->admin_title, 'admin_description' => $style->admin_description),
    'settings' => $style->settings,
  );

  $output = ctools_stylizer_edit_style($info, $js, $step);
  if (!empty($info['complete'])) {
    $style->admin_title = $info['owner settings']['admin_title'];
    $style->admin_description = $info['owner settings']['admin_description'];
    $style->settings = $info['settings'];
    // Don't let name accidentally change:
    $style->settings['name'] = $style->name;
    panels_stylizer_save($style);
    drupal_set_message('The style has been updated.');
    drupal_goto('admin/build/panels/style');
  }

  return $output;
}

/**
 * Add owner information to a style form.
 *
 * This allows Panels to add administrative info to a style for saving
 * it in the database.
 */
function panels_stylizer_edit_style_form(&$form, &$form_state) {
  $settings = $form_state['owner info']['owner settings'];

  $form['panels']['admin_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Administrative title'),
    '#description' => t('The name of this style. This will appear in the administrative interface to easily identify it.'),
    '#default_value' => $settings['admin_title'],
  );

  $form['panels']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name'),
    '#description' => t('The machine readable name of this page. It must be unique, and it must contain only alphanumeric characters and underscores. Once created, you will not be able to change this value!'),
    '#default_value' => $settings['name'],
  );

  if ($form_state['form_type'] != 'add') {
    $form['name']['#disabled'] = TRUE;
    $form['name']['#value'] = $settings['name'];
  }

  $form['panels']['admin_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Administrative description'),
    '#description' => t('A description of what this style is, does or is for, for administrative use.'),
    '#default_value' => $settings['admin_description'],
  );
}

function panels_stylizer_edit_style_form_validate(&$form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Next') || $form_state['clicked_button']['#value'] == t('Finish')) {
    if (empty($form_state['values']['admin_title'])) {
      form_error($form['panels']['admin_title'], t('You must choose an administrative title.'));
    }

    // If this is new, make sure the name is unique:
    if ($form_state['form_type'] == 'add') {
      if (empty($form_state['values']['name'])) {
        form_error($form['panels']['name'], t('You must choose a machine name.'));
      }

      $test = panels_stylizer_load($form_state['values']['name']);
      if ($test) {
        form_error($form['panels']['name'], t('That name is used by another page: @page', array('@page' => $test->admin_title)));
      }

      // Ensure name fits the rules:
      if (preg_match('/[^a-zA-Z0-9_]/', $form_state['values']['name'])) {
        form_error($form['panels']['name'], t('Name must be alphanumeric or underscores only.'));
      }
    }
  }
}

function panels_stylizer_edit_style_form_submit(&$form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Next') || $form_state['clicked_button']['#value'] == t('Finish')) {
    $form_state['owner info']['owner settings']['admin_title'] = $form_state['values']['admin_title'];
    $form_state['owner info']['owner settings']['admin_description'] = $form_state['values']['admin_description'];

    // Clean up preview files before we set the name
    ctools_stylizer_cleanup_style($form_state['plugin'], $form_state['settings']);

    $form_state['settings']['name'] = $form_state['values']['name'];
    $form_state['name'] = $form_state['values']['name'];
  }
}

/**
 * Entry point to export a style.
 */
function panels_stylizer_export_style_page(&$form_state, $style) {
  // Tabs and breadcrumb disappearing, this helps alleviate through cheating.
  ctools_include('menu');
  $trail = ctools_get_menu_trail('admin/build/panels/style/list');
  menu_set_active_trail($trail);

  $export = panels_stylizer_export($style);

  $lines = substr_count($export, "\n");
  $form['code'] = array(
    '#type' => 'textarea',
    '#default_value' => $export,
    '#rows' => $lines,
  );

  return $form;
}

/**
 * Entry point to export a style.
 */
function panels_stylizer_import_style_page() {
  $form['object'] = array(
    '#type' => 'textarea',
    '#title' => t('Paste style code here'),
    '#rows' => 15,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

/**
 * Make sure that an import actually provides a style.
 */
function panels_stylizer_import_style_page_validate($form, &$form_state) {
  ob_start();
  eval($form_state['values']['object']);
  ob_end_clean();

  if (empty($style)) {
    $errors = ob_get_contents();
    if (empty($errors)) {
      $errors = t('No variant found.');
    }

    form_error($form['object'], t('Unable to get a style from the import. Errors reported: @errors', array('@errors' => $errors)));
  }

  $form_state['style'] = $style;
}

/**
 * Make sure that an import actually provides a style.
 */
function panels_stylizer_import_style_page_submit($form, &$form_state) {
  ctools_include('stylizer');
  $style = $form_state['style'];
  $cache = array(
    'owner settings' => array('name' => $style->name, 'admin_title' => $style->admin_title, 'admin_description' => $style->admin_description),
    'settings' => $style->settings,
  );

  ctools_stylizer_set_settings_cache('::new', $cache);
  if (empty($plugin['forms'])) {
    $step = 'settings';
  }
  else {
    $forms = array_keys($form_info['forms']);
    $step = array_shift($forms);
  }

  $form_state['redirect'] = 'admin/build/panels/style/add/' . $step;
}

/**
 * Entry point to export a style.
 */
function panels_stylizer_clone_style_page($style) {
  ctools_include('stylizer');

  $cache = array(
    'owner settings' => array('name' => $style->name, 'admin_title' => $style->admin_title, 'admin_description' => $style->admin_description),
    'settings' => $style->settings,
  );

  ctools_stylizer_set_settings_cache('::new', $cache);
  if (empty($plugin['forms'])) {
    $step = 'settings';
  }
  else {
    $forms = array_keys($form_info['forms']);
    $step = array_shift($forms);
  }

  drupal_goto('admin/build/panels/style/add/' . $step);
}

/**
 * Page callback to enable a disabled style.
 */
function panels_stylizer_enable_style_page($style) {
  ctools_include('export');
  ctools_export_set_object_status($style, FALSE);

  if (empty($_REQUEST['js'])) {
    drupal_goto('admin/build/panels/style');
  }
  else {
    return panels_stylizer_list_styles_page('ajax');
  }
}

/**
 * Page callback to disable a disabled style.
 */
function panels_stylizer_disable_style_page($style) {
  ctools_include('export');
  ctools_export_set_object_status($style, TRUE);

  if (empty($_REQUEST['js'])) {
    drupal_goto('admin/build/panels/style');
  }
  else {
    return panels_stylizer_list_styles_page('ajax');
  }
}

/**
 * Rearrange the order of variants.
 */
function panels_stylizer_delete_style_page(&$form_state, $style) {
  $form_state['style'] = &$style;
  $form = array();

  $cancel = 'admin/build/panels/style';
  if (!empty($_REQUEST['cancel'])) {
    $cancel = $_REQUEST['cancel'];
  }

  if ($style->type == t('Overridden')) {
    $title = t('Are you sure you want to revert the style %name?', array('%name' => $style->name));
    $desc = t('Reverting the style will delete the style that is in the database, reverting it to the original default style. Any changes you have made will be lost and cannot be recovered.');
    $button = t('Revert');
  }
  else {
    $title = t('Are you sure you want to delete the style %name?', array('%name' => $style->name));
    $desc = t('Deleting a style cannot be undone.');
    $button = t('Delete');
  }

  return confirm_form($form,
                  $title,
                  $cancel,
                  $desc,
                  $button,
                  t('Cancel'));
}

/**
 * Submit handler to delete a style.
 */
function panels_stylizer_delete_style_page_submit(&$form, &$form_state) {
  ctools_include('stylizer');
  $style = $form_state['style'];
  $plugin = ctools_get_style_base($style->settings['style_base']);

  if ($plugin) {
    ctools_stylizer_cleanup_style($plugin, $style->settings);
  }

  panels_stylizer_delete($style);
  if ($style->type == t('Overridden')) {
    drupal_set_message(t('The style has been reverted.'));
  }
  else {
    drupal_set_message(t('The style has been deleted.'));
  }

  $form_state['redirect'] = 'admin/build/panels/style';
}

/**
 * Allow on-the-fly creation of styles in panes.
 */
function panels_stylizer_pane_add_style($type, $cache, $pid = '', $step = NULL) {
  // This must be reached through the Panels style edit dialog, so reject
  // it if the cache is not populated:
  $info = panels_edit_style_get_style($type, $cache, $pid);
  $style = $info[0];
  $conf = &$info[1];

  ctools_include('stylizer');
  $js = FALSE;

  $cache_key = $cache->display->cache_key;
  $path = "admin/build/panels/style/pane-style/$type/$cache_key/$pid/%step";

  $info = array(
    'module' => 'panels',
    'type' => $type == 'panel' ? 'region' : 'pane',
    'path' => $path,
    'modal' => t('Create custom style'),
    'owner form' => 'panels_stylizer_edit_pane_style_form',
    'owner form validate' => 'panels_stylizer_edit_pane_style_form_validate',
    'owner form submit' => 'panels_stylizer_edit_pane_style_form_submit',
    'owner settings' => array('preconfigured' => FALSE, 'name' => '', 'admin_title' => '', 'admin_description' => ''),
    'cache' => &$cache,
    'conf' => &$conf,
    'pid' => $pid,
  );

  if (!empty($conf['settings'])) {
    $info['settings'] = $conf['settings'];
  }

  $output = ctools_stylizer_edit_style($info, TRUE, $step);
  if (!empty($info['complete'])) {
    if (isset($cache->style)) {
      unset($cache->style);
    }

    if (!empty($info['owner settings']['preconfigured'])) {
      $style = panels_stylizer_new();
      $style->name = $info['settings']['name'];
      $style->admin_title = $info['owner settings']['admin_title'];
      $style->admin_description = $info['owner settings']['admin_description'];
      $style->settings = $info['settings'];
      panels_stylizer_save($style);
      $conf['style'] = $info['settings']['name'];
      if (isset($conf['settings'])) {
        unset($conf['settings']);
      }
    }
    else {
      $conf['style'] = '$';
      $conf['settings'] = $info['settings'];
    }

    // $conf was a reference so it should just modify.
    panels_edit_cache_set($cache);

    $output = array();
    $output[] = ctools_modal_command_dismiss();

    if ($type == 'pane') {
      $pane = &$cache->display->content[$pid];
      $output[] = ctools_ajax_command_replace("#panel-pane-$pid", panels_show_pane($cache->display, $pane, TRUE));
      $output[] = ctools_ajax_command_changed("#panel-pane-$pid", "div.grabber span.text");
    }
    else if ($type == 'panel') {
      $links = panels_edit_panel_get_links($cache->display, $pid);
      $output[] = ctools_ajax_command_replace('.panels-region-links-' . $pid, $links);
    }
    else {
      $links = panels_edit_display_get_links($cache->display);
      $output[] = ctools_ajax_command_replace('.panels-display-links', $links);
    }
  }

  ctools_ajax_render($output);
}

/**
 * The form for determining if a pane should create a local style or a
 * preconfigured style.
 */
function panels_stylizer_edit_pane_style_form(&$form, &$form_state) {
  if (!user_access('administer panels styles')) {
    return;
  }

  panels_stylizer_edit_style_form($form, $form_state);
  $settings = $form_state['owner info']['owner settings'];

  // Add the checkbox, set the weight early
  $form['panels']['preconfigured'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make this style available to other regions or panes'),
    '#default_value' => $settings['name'],
    '#weight' => -1,
  );

  // Make the other form items dependent upon it.
  ctools_include('dependent');
  $depends = array(
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-preconfigured' => array(1)),
  );

  $form['panels']['name'] += $depends;
  $form['panels']['admin_title'] += $depends;
  $form['panels']['admin_description'] += $depends;

  // Add a revert button to get rid of an existing style.
  if ($form_state['form_type'] != 'add') {
    $form['buttons']['revert'] = array(
      '#type' => 'submit',
      '#value' => t('Choose a preconfigured style'),
    );
  }
}

/**
 * Validate to see if we need to check the preconfigured values.
 */
function panels_stylizer_edit_pane_style_form_validate(&$form, &$form_state) {
  if (!user_access('administer panels styles')) {
    return;
  }

  // Only validate if preconfigured is checked.
  if ($form_state['values']['preconfigured']) {
    panels_stylizer_edit_style_form_validate($form, $form_state);
  }
}

/**
 * Store the preconfigured values.
 */
function panels_stylizer_edit_pane_style_form_submit(&$form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Choose a preconfigured style')) {
    // If they chose to revert, get rid of these settings and go back to the
    // normal style settings page.
    $cache = &$form_state['owner info']['cache'];
    $conf = &$form_state['owner info']['conf'];

    $conf['style'] = '';
    if (isset($conf['settings'])) {
      unset($conf['settings']);
    }

    // $conf was a reference so it should just modify.
    panels_edit_cache_set($cache);

    $type = $form_state['owner info']['type'] == 'region' ? 'panel' : 'pane';
    $pid = $form_state['owner info']['pid'];

    ctools_include('display-edit', 'panels');
    panels_ajax_style_settings($type, $cache, $pid);
  }

  if (!user_access('administer panels styles')) {
    return;
  }

  // Only validate if preconfigured is checked.
  if ($form_state['values']['preconfigured']) {
    panels_stylizer_edit_style_form_submit($form, $form_state);
    $form_state['owner info']['owner settings']['preconfigured'] = $form_state['values']['preconfigured'];
  }
}
