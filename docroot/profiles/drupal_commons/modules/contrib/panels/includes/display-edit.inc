<?php
// $Id: display-edit.inc,v 1.7.2.35 2010/05/20 09:05:37 sdboyer Exp $

/*
 * @file
 * Core Panels API include file containing various display-editing functions.
 * This includes all the basic editing forms (content, layout, layout settings)
 * as well as the ajax modal forms associated with them.
 */

/**
 * Method to allow modules to provide their own caching mechanism for the
 * display editor.
 */
function panels_edit_cache_get($cache_key) {
  if (strpos($cache_key, ':') !== FALSE) {
    list($module, $argument) = explode(':', $cache_key, 2);
    return module_invoke($module, 'panels_cache_get', $argument);
  }

  // Fall back to our normal method:
  return panels_cache_get('display', $cache_key);
}

/**
 * Method to allow modules to provide their own caching mechanism for the
 * display editor.
 */
function panels_edit_cache_set($cache) {
  $cache_key = $cache->display->cache_key;
  if (strpos($cache_key, ':') !== FALSE) {
    list($module, $argument) = explode(':', $cache_key, 2);
    return module_invoke($module, 'panels_cache_set', $argument, $cache);
  }

  // Fall back to our normal method:
  return panels_cache_set('display', $cache_key, $cache);
}

/**
 * Handle calling and processing of the form for editing display content.
 *
 * Helper function for panels_edit().
 *
 * @see panels_edit() for details on the various behaviors of this function.
 */
function _panels_edit($display, $destination, $content_types, $title = FALSE) {
  $did = $display->did;
  if (!$did) {
    $display->did = $did = 'new';
  }

  // Load the display being edited from cache, if possible.
  if (!empty($_POST) && is_object($cache = panels_edit_cache_get($did))) {
    $display = $cache->display;
  }
  else {
    if (empty($content_types)) {
      $content_types = ctools_content_get_available_types();
    }

    $display->cache_key = $did;
    panels_cache_clear('display', $did);
    $cache = new stdClass();
    $cache->display = $display;
    $cache->content_types = $content_types;
    $cache->display_title = $title;
    panels_edit_cache_set($cache);
  }

  ctools_include('form');
  $form_state = array(
    'display' => &$display,
    'content_types' => $cache->content_types,
    're_render' => FALSE,
    'no_redirect' => TRUE,
    'display_title' => !empty($cache->display_title),
    'cache key' => $did,
  );

  $output = ctools_build_form('panels_edit_display_form', $form_state);
  // no output == submit
  if (!$output) {
    if (!empty($form_state['clicked_button']['#save-display'])) {
      drupal_set_message(t('Panel content has been updated.'));
      panels_save_display($display);
    }
    else {
      drupal_set_message(t('Your changes have been discarded.'));
    }

    panels_cache_clear('display', $display->did);
    if ($destination) {
      return drupal_goto($destination);
    }
    return $form_state['display'];
  }

  return $output;
}

/**
 * Form definition for the panels display editor
 *
 * No validation function is necessary, as all 'validation' is handled
 * either in the lead-up to form rendering (through the selection of
 * specified content types) or by the validation functions specific to
 * the ajax modals & content types.
 *
 * @ingroup forms
 * @see panels_edit_display_submit()
 */
function panels_edit_display_form(&$form_state) {
  $display = &$form_state['display'];
  $cache_key = isset($display->cache_key) ? $display->cache_key : $display->did;
  $display->cache_key = $cache_key;

  // Annoyingly, theme doesn't have access to form_state so we have to do this.
  $form['#display'] = $display;

  $layout = panels_get_layout($display->layout);
  $layout_panels = panels_get_panels($layout, $display);

  $form['panel'] = array('#tree' => TRUE);
  $form['panel']['pane'] = array('#tree' => TRUE);

  foreach ($layout_panels as $panel_id => $title) {
    // Make sure we at least have an empty array for all possible locations.
    if (!isset($display->panels[$panel_id])) {
      $display->panels[$panel_id] = array();
    }

    $form['panel']['pane'][$panel_id] = array(
      // Use 'hidden' instead of 'value' so the js can access it.
      '#type' => 'hidden',
      '#default_value' => implode(',', (array) $display->panels[$panel_id]),
    );
  }

  if (empty($form_state['no buttons'])) {
    $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#id' => 'panels-dnd-save',
      '#submit' => array('panels_edit_display_form_submit'),
      '#save-display' => TRUE,
    );
    $form['buttons']['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
    );
  }

  $links = panels_edit_display_get_links($display);

  $form['hide']['display-settings'] = array(
    '#value' => $links,
  );

  ctools_include('ajax');
  ctools_include('modal');
  ctools_modal_add_js();

  drupal_add_js(panels_get_path('js/panels-base.js'));
  drupal_add_js(panels_get_path('js/display_editor.js'));
  drupal_add_css(panels_get_path('css/panels_dnd.css'));
  drupal_add_css(panels_get_path('css/panels_admin.css'));

  $css = array();
  $js = array(drupal_get_path('module', 'ctools') . '/js/dependent.js' => TRUE);
  foreach ($form_state['content_types'] as $type_name => $subtypes) {
    if (is_array($subtypes)) {
      foreach ($subtypes as $subtype) {
        if (isset($subtype['js'])) {
          foreach ($subtype['js'] as $file) {
            if (file_exists($file)) {
              $js[$file] = TRUE;
            }
            else if (file_exists($subtype['path'] . '/' . $file)) {
              $js[$subtype['path'] . '/' . $file] = TRUE;
            }
          }
        }
        if (isset($subtype['css'])) {
          foreach ($subtype['css'] as $file) {
            if (file_exists($file)) {
              $css[$file] = TRUE;
            }
            else if (file_exists($subtype['path'] . '/' . $file)) {
              $css[$subtype['path'] . '/' . $file] = TRUE;
            }
          }
        }
      }
    }
  }

  foreach (array_keys($js) as $file) {
    drupal_add_js($file);
  }
  foreach (array_keys($css) as $file) {
    drupal_add_css($file);
  }

  $form += panels_edit_display_settings_form($form_state);

  // Build up the preview portion of the form, if necessary.
  if (empty($form_state['no preview'])) {
    $form['preview'] = array('#tree' => TRUE);
    ctools_context_replace_form($form['preview'], $display->context);
    $form['preview']['button'] = array(
      '#type' => 'submit',
      '#value' => t('Preview'),
      '#attributes' => array('class' => 'ctools-use-ajax'),
      '#id' => 'panels-live-preview-button',
      '#submit' => array('panels_edit_display_form_submit', 'panels_edit_display_form_preview'),
    );
  }

  return $form;
}

/**
 * Get the links for a panel display.
 *
 * This is abstracted out for easy ajax replacement.
 */
function panels_edit_display_get_links(&$display) {
  $cache_key = $display->cache_key;
  $links = array();

  $panel_settings = $display->panel_settings;
  $style = panels_get_style((!empty($panel_settings['style'])) ? $panel_settings['style'] : 'default');

  $links[] = array(
    'title' => t('Display style: @style', array('@style' => $style['title'])),
    'href' => 'panels/ajax/style-type/display/' . $cache_key,
    'attributes' => array('class' => 'ctools-use-modal'),
  );
  if (panels_plugin_get_function('style', $style, 'settings form')) {
    $links[] = array(
      'title' => ' -- ' . t('Style settings'),
      'href' => 'panels/ajax/style-settings/display/' . $cache_key,
      'attributes' => array('class' => 'ctools-use-modal'),
    );
  }

  if (user_access('use panels caching features')) {
    $method = isset($display->cache['method']) ? $display->cache['method'] : 0;
    $info = panels_get_cache($method);
    $cache_method = isset($info['title']) ? $info['title'] : t('No caching');
    $links[] = array(
      'title' => t('Cache method: @method', array('@method' => $cache_method)),
      'href' => 'panels/ajax/cache-method/' . $cache_key . '/display',
      'attributes' => array('class' => 'ctools-use-modal'),
    );
    if (panels_plugin_get_function('cache', $info, 'settings form')) {
      $links[] = array(
        'title' => ' -- ' . t('Cache settings'),
        'href' => 'panels/ajax/cache-settings/' . $cache_key . '/display',
        'attributes' => array('class' => 'ctools-use-modal'),
      );
    }
  }

  return theme('ctools_dropdown', t('Display settings'), $links, FALSE, 'panels-display-links');
}

/**
 * Theme the edit display form.
 *
 * This has to do a fair bit of work since it's actually rendering the layout
 * as well as ensuring that all of the gadgets go in the right place.
 */
function theme_panels_edit_display_form($form) {
  $output = '';
  $content = array();

  $display = $form['#display'];
  $cache_key = $display->cache_key;

  $layout = panels_get_layout($display->layout);
  $layout_panels = panels_get_panels($layout, $display);
  $save_buttons = drupal_render($form['buttons']);

  foreach ($layout_panels as $panel_id => $title) {
    if (empty($content[$panel_id])) {
      $content[$panel_id] = '';
    }

    foreach ((array) $display->panels[$panel_id] as $pid) {
      $pane = $display->content[$pid];
      $left_buttons = NULL;
      $content[$pane->panel] .= panels_show_pane($display, $pane);
    }

    $panel_buttons = panels_edit_panel_get_links($display, $panel_id, $cache_key);

    $content[$panel_id] = panels_render_region_dnd($content[$panel_id], $panel_id, $title, $panel_buttons);
  }

  $preview = '';
  if (isset($form['preview'])) {
    $preview .= '<h2>' . t('Live preview') . '</h2>';
    $preview .= '<div id="panels-live-preview">';
    $preview .= drupal_render($form['preview']);
    $preview .= '</div>';
  }

  $output .= drupal_render($form);

  ctools_include('display-render', 'panels');
  $output .= panels_render_dnd(panels_render_layout_admin($layout, $content, $display));
  $output .= $save_buttons;
  $output .= $preview;

  return $output;
}

/**
 * Get the links for a panel region.
 *
 * This is abstracted out for easy ajax replacement.
 */
function panels_edit_panel_get_links($display, $panel_id) {
  $cache_key = $display->cache_key;
  $links = array();
  $links[] = array(
    'title' => t('Add content'),
    'href' => "panels/ajax/add-pane/$cache_key/$panel_id",
    'attributes' => array(
      'class' => 'ctools-use-modal',
    ),
  );

  $panel_settings = $display->panel_settings;
  $style = panels_get_style((!empty($panel_settings[$panel_id]['style'])) ? $panel_settings[$panel_id]['style'] : '-1');
  $style_title = isset($style['title']) ? $style['title'] : t('Default');

  $links[] = array(
    'title' => t('Region style: @style', array('@style' => $style_title)),
    'href' => 'panels/ajax/style-type/panel/' . $cache_key . '/' . $panel_id,
    'attributes' => array('class' => 'ctools-use-modal'),
  );
  if (panels_plugin_get_function('style', $style, 'settings form')) {
    $links[] = array(
      'title' => ' -- ' . t('Style settings'),
      'href' => 'panels/ajax/style-settings/panel/' . $cache_key . '/' . $panel_id,
      'attributes' => array('class' => 'ctools-use-modal'),
    );
  }

  return theme('ctools_dropdown', theme('image', panels_get_path("images/icon-addcontent.png")), $links, TRUE, 'pane-add-link panels-region-links-' . $panel_id);
}

/**
 * Handle form submission of the display content editor.
 *
 * This reads the location of the various panes from the form, which will
 * have been modified from the ajax, rearranges them and then saves
 * the display.
 */
function panels_edit_display_form_submit($form, &$form_state) {
  $display = &$form_state['display'];

  $old_content = $display->content;
  $display->content = array();

  if (!empty($form_state['values']['panel']['pane'])) {
    foreach ($form_state['values']['panel']['pane'] as $panel_id => $panes) {
      $display->panels[$panel_id] = array();
      if ($panes) {
        $pids = explode(',', $panes);
        // need to filter the array, b/c passing it in a hidden field can generate trash
        foreach (array_filter($pids) as $pid) {
          if ($old_content[$pid]) {
            $display->panels[$panel_id][] = $pid;
            $old_content[$pid]->panel = $panel_id;
            $display->content[$pid] = $old_content[$pid];
          }
        }
      }
    }
  }

  panels_edit_display_settings_form_submit($form, $form_state);
}

/**
 * Submission of the preview button. Render the preview and put it into
 * the preview widget area.
 */
function panels_edit_display_form_preview(&$form, &$form_state) {
  $display = &$form_state['display'];
  ctools_include('ajax');

  $display->context = ctools_context_replace_placeholders($display->context, $form_state['values']['preview']);
  $output = panels_render_display($display);

  $commands = array();
  $commands[] = array(
    'command' => 'panel_preview',
    'output' => $output,
  );
  ctools_ajax_render($commands);
}

/**
 * Render a single pane in the edit environment.
 *
 * @param $pane
 *   The pane to render.
 * @param $left_buttons
 *   Buttons that go on the left side of the pane.
 * @param $buttons
 *   Buttons that go on the right side of the pane.
 * @param $skin
 *   If true, provide the outside div. Used to provide an easy way to get
 *   just the innards for ajax replacement
 */
// TODO check and see if $skin is ever FALSE; pane show/hide setting is dependent on it being TRUE. can't imagine it could be...
function panels_show_pane($display, $pane, $skin = TRUE) {
  $cache_key = $display->cache_key;
  ctools_include('content');
  $content_type = ctools_get_content_type($pane->type);

  // This is just used for the title bar of the pane, not the content itself.
  // If we know the content type, use the appropriate title for that type,
  // otherwise, set the title using the content itself.
  $title = ctools_content_admin_title($content_type, $pane->subtype, $pane->configuration, $display->context);
  if (!$title) {
    $title = t('Deleted/missing content type @type', array('@type' => $pane->type));
  }
  $links = array();

  if (!empty($pane->shown)) {
    $links[] = array(
      'title' => t('Disable this pane'),
      'href' => "panels/ajax/hide/$cache_key/$pane->pid",
      'attributes' => array('class' => 'ctools-use-ajax'),
    );
  }
  else {
    $links[] = array(
      'title' => t('Enable this pane'),
      'href' => "panels/ajax/show/$cache_key/$pane->pid",
      'attributes' => array('class' => 'ctools-use-ajax'),
    );
  }

  if (isset($display->title_pane) && $display->title_pane == $pane->pid) {
    $links['panels-set-title'] = array(
      'title' => t('&#x2713;Panel title'),
      'html' => TRUE,
    );
  }
  else {
    $links['panels-set-title'] = array(
      'title' => t('Panel title'),
      'href' => "panels/ajax/panel-title/$cache_key/$pane->pid",
      'attributes' => array('class' => 'ctools-use-ajax'),
    );
  }

  if (isset($content_type['edit form'])) {
    $links[] = array(
      'title' => t('Settings'),
      'href' => "panels/ajax/configure/$cache_key/$pane->pid",
      'attributes' => array('class' => 'ctools-use-modal'),
    );
  }

  if (user_access('administer advanced pane settings')) {
    $links[] = array(
      'title' => t('CSS properties'),
      'href' => "panels/ajax/pane-css/$cache_key/$pane->pid",
      'attributes' => array('class' => 'ctools-use-modal'),
    );
  }

  $links[] = array(
    'title' => '<hr />',
    'html' => TRUE,
  );

  $style = panels_get_style((!empty($pane->style['style'])) ? $pane->style['style'] : 'default');

  $style_links[] = array(
    'title' => $style['title'],
    'attributes' => array('class' => 'panels-text'),
  );

  $style_links[] = array(
    'title' => t('Change'),
    'href' => 'panels/ajax/style-type/pane/' . $cache_key . '/' . $pane->pid,
    'attributes' => array('class' => 'ctools-use-modal'),
  );

  if (panels_plugin_get_function('style', $style, 'pane settings form')) {
    $style_links[] = array(
      'title' => t('Settings'),
      'href' => 'panels/ajax/style-settings/pane/' . $cache_key . '/' . $pane->pid,
      'attributes' => array('class' => 'ctools-use-modal'),
    );
  }

  $links[] = array(
    'title' => '<span class="dropdown-header">' . t('Style') . '</span>' . theme_links($style_links),
    'html' => TRUE,
    'attributes' => array('class' => 'panels-sub-menu'),
  );

  if (user_access('administer pane access')) {
    $links[] = array(
      'title' => '<hr />',
      'html' => TRUE,
    );

    $contexts = $display->context;
    // Make sure we have the logged in user context
    if (!isset($contexts['logged-in-user'])) {
      $contexts['logged-in-user'] = ctools_access_get_loggedin_context();
    }

    $visibility_links = array();

    if (!empty($pane->access['plugins'])) {
      foreach ($pane->access['plugins'] as $id => $test) {
        $plugin = ctools_get_access_plugin($test['name']);
        $access_title  = isset($plugin['title']) ? $plugin['title'] : t('Broken/missing access plugin %plugin', array('%plugin' => $test['name']));
        $access_description = ctools_access_summary($plugin, $contexts, $test);

        $visibility_links[] = array(
          'title' => $access_description,
          'href' => "panels/ajax/access-test/$cache_key/$pane->pid/$id",
          'attributes' => array('class' => 'ctools-use-modal panels-italic'),
        );
      }
    }
    if (empty($visibility_links)) {
      $visibility_links[] = array(
        'title' => t('No rules'),
        'attributes' => array('class' => 'panels-text'),
      );
    }

    $visibility_links[] = array(
      'title' => t('Add new rule'),
      'href' => "panels/ajax/access-add/$cache_key/$pane->pid",
      'attributes' => array('class' => 'ctools-use-modal'),
    );

    $visibility_links[] = array(
      'title' => t('Settings'),
      'href' => "panels/ajax/access-settings/$cache_key/$pane->pid",
      'attributes' => array('class' => 'ctools-use-modal'),
    );

    $links[] = array(
      'title' => '<span class="dropdown-header">' . t('Visibility rules') . '</span>' . theme_links($visibility_links),
      'html' => TRUE,
      'attributes' => array('class' => 'panels-sub-menu'),
    );
  }

  if (panels_get_caches() && user_access('use panels caching features')) {
    $links[] = array(
      'title' => '<hr />',
      'html' => TRUE,
    );

    $method = isset($pane->cache['method']) ? $pane->cache['method'] : 0;
    $info = panels_get_cache($method);
    $cache_method = isset($info['title']) ? $info['title'] : t('No caching');
    $cache_links[] = array(
      'title' => $cache_method,
      'attributes' => array('class' => 'panels-text'),
    );
    $cache_links[] = array(
      'title' => t('Change'),
      'href' => "panels/ajax/cache-method/$cache_key/$pane->pid",
      'attributes' => array('class' => 'ctools-use-modal'),
    );
    if (panels_plugin_get_function('cache', $info, 'settings form')) {
      $cache_links[] = array(
        'title' => t('Settings'),
        'href' => "panels/ajax/cache-settings/$cache_key/$pane->pid",
        'attributes' => array('class' => 'ctools-use-modal'),
      );
    }

    $links[] = array(
      'title' => '<span class="dropdown-header">' . t('Caching') . '</span>' . theme_links($cache_links),
      'html' => TRUE,
      'attributes' => array('class' => 'panels-sub-menu'),
    );
  }

  $links[] = array(
    'title' => '<hr />',
    'html' => TRUE,
  );

  $links[] = array(
    'title' => t('Remove'),
    'href' => '#',
    'attributes' => array(
      'class' => 'pane-delete',
      'id' => "pane-delete-panel-pane-$pane->pid",
    ),
  );

  $buttons = theme('ctools_dropdown', theme('image', panels_get_path("images/icon-configure.png")), $links, TRUE);
  // Render administrative buttons for the pane.

  $block = new stdClass();
  if (empty($content_type)) {
    $block->title = '<em>' . t('Missing content type') . '</em>';
    $block->content = t('This pane\'s content type is either missing or has been deleted. This pane will not render.');
  }
  else {
    $block = ctools_content_admin_info($content_type, $pane->subtype, $pane->configuration, $display->context);
  }

  $output = panels_render_pane_dnd($block, $pane->pid, $title, '', $buttons);
  if ($skin) {
    $class = 'panel-pane';

    if (empty($pane->shown)) {
      $class .= ' hidden-pane';
    }

    if (isset($display->title_pane) && $display->title_pane == $pane->pid) {
      $class .= ' panel-pane-is-title';
    }

    $output = '<div class="' . $class . '" id="panel-pane-' . $pane->pid . '">' . $output . '</div>';
  }
  return $output;
}

/**
 * @defgroup panels_ajax Functions for panels ajax features
 * @{
 */

/**
 * Entry point for AJAX: 'Display settings' modal form, from which the user
 * can control settings for the display.
 *
 * @param $cache
 *  The display id of the $display object currently being edited.
 */
function panels_ajax_display_settings($cache) {
  $form_state = array(
    'display' => &$cache->display,
    'display_title' => !empty($cache->display_title),
    'title' => t('Display settings'),
    'ajax' => TRUE,
  );

  $output = ctools_modal_form_wrapper('panels_edit_display_settings_form', $form_state);
  if (empty($output)) {
    panels_edit_cache_set($cache);

    $output = array();
    $output[] = ctools_modal_command_dismiss();
  }

  ctools_ajax_render($output);
}

/**
 * Form for display settings.
 */
function panels_edit_display_settings_form(&$form_state) {
  $form = array();
  $display = &$form_state['display'];

  $layout = panels_get_layout($display->layout);
  $form_state['layout'] = $layout;

  ctools_include('dependent');

  if ($form_state['display_title']) {
    $form['display_title'] = array (
      '#tree' => TRUE,
    );

    $form['display_title']['hide_title'] = array(
      '#type' => 'select',
      '#title' => t('Title type'),
      '#default_value' => (int) $display->hide_title,
      '#options' => array(
        PANELS_TITLE_NONE => t('No title'),
        PANELS_TITLE_FIXED => t('Manually set'),
        PANELS_TITLE_PANE => t('From pane'),
      ),
    );

    $form['display_title']['title'] = array(
      '#type' => 'textfield',
      '#default_value' => $display->title,
      '#title' => t('Title'),
      '#description' => t('The title of this panel. If left blank, a default title may be used. Set to No Title if you want the title to actually be blank.'),
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('edit-display-title-hide-title' => array(PANELS_TITLE_FIXED)),
    );

    if (!empty($display->context)) {
      $form['display_title']['title']['#description'] .= ' ' . t('You may use substitutions in this title.');

      // We have to create a manual fieldset because fieldsets do not support IDs.
      // Use 'hidden' instead of 'markup' so that the process will run.
      $form['display_title']['contexts_prefix'] = array(
        '#type' => 'hidden',
        '#id' => 'edit-display-substitutions',
        '#prefix' => '<div><fieldset id="edit-display-substitutions" class="collapsed collapsible"><legend>' . t('Substitutions') . '</legend>',
        '#process' => array('ctools_dependent_process'),
        '#dependency' => array('edit-display-title-hide-title' => array(PANELS_TITLE_FIXED)),
      );

      $rows = array();
      foreach ($display->context as $context) {
        foreach (ctools_context_get_converters('%' . check_plain($context->keyword) . ':', $context) as $keyword => $title) {
          $rows[] = array(
            check_plain($keyword),
            t('@identifier: @title', array('@title' => $title, '@identifier' => $context->identifier)),
          );
        }
      }

      $header = array(t('Keyword'), t('Value'));
      $form['display_title']['contexts']['context'] = array('#value' => theme('table', $header, $rows));
      $form['display_title']['contexts_suffix'] = array(
        '#value' => '</fieldset></div>',
      );
    }
  }

  // TODO doc the ability to do this as part of the API
  if (!empty($layout['settings form']) && function_exists($layout['settings form'])) {
    $form['layout_settings'] = $layout['settings form']($display, $layout, $display->layout_settings);
  }
  $form['layout_settings']['#tree'] = TRUE;

  return $form;
}

/**
 * Validate the layout settings form.
 */
function panels_edit_display_settings_form_validate($form, &$form_state) {
  if ($function = panels_plugin_get_function('layout', $form_state['layout'], 'settings validate')) {
    $function($form_state['values']['layout_settings'], $form['layout_settings'], $form_state['display'], $form_state['layout'], $form_state['display']->layout_settings);
  }
}

/**
 * Store changes from the layout settings form.
 */
function panels_edit_display_settings_form_submit($form, &$form_state) {
  $display = &$form_state['display'];
  if ($function = panels_plugin_get_function('layout', $form_state['layout'], 'settings submit')) {
    $function($form_state['values']['layout_settings'], $display, $form_state['layout'], $display->layout_settings);
  }

  // Since not all layouts have layout settings, check here in case of notices.
  if (isset($form_state['values']['layout_settings'])) {
    $display->layout_settings = $form_state['values']['layout_settings'];
  }

  if (isset($form_state['values']['display_title']['title'])) {
    $display->title = $form_state['values']['display_title']['title'];
    $display->hide_title = $form_state['values']['display_title']['hide_title'];
  }
}

/**
 * Entry point for AJAX: 'Add Content' modal form, from which the user selects the
 * type of pane to add.
 *
 * @param int $cache
 *  The display id of the $display object currently being edited.
 * @param string $panel_id
 *  A string with the name of the panel region to which the selected
 *  pane type will be added.
 */
function panels_ajax_add_pane_choose($cache, $panel_id = NULL, $category = NULL) {
  $display = $cache->display;
  $layout = panels_get_layout($display->layout);
  $layout_panels = panels_get_panels($layout, $display);

  if ($layout && array_key_exists($panel_id, $layout_panels)) {
    ctools_modal_render(
      t('Add content to !s', array('!s' => $layout_panels[$panel_id])),
      panels_add_content($cache, $panel_id, $category)
    );
  }

  ctools_modal_render(t('Error'), t('Invalid input'));
}

/**
 * Display a list of content available.
 */
function panels_add_content($cache, $panel_id, $key) {
  ctools_include('content');
  $cache_key = $cache->display->cache_key;

  $category_names = array();
  $categories = array();
  $titles     = array();

  foreach ($cache->content_types as $type_name => $subtypes) {
    if (is_array($subtypes)) {
      $content_type = ctools_get_content_type($type_name);
      foreach ($subtypes as $subtype_name => $subtype_info) {
        $title = filter_xss_admin($subtype_info['title']);
        $description = isset($subtype_info['description']) ? $subtype_info['description'] : $title;

        $icon = ctools_content_admin_icon($subtype_info);

        if (isset($subtype_info['top level'])) {
          $category = 'root';
        }
        else if (isset($subtype_info['category'])) {
          if (is_array($subtype_info['category'])) {
            list($category, $weight) = $subtype_info['category'];
          }
          else {
            $category = $subtype_info['category'];
          }
        }
        else {
          $category = t('Uncategorized');
        }

        $category_key = preg_replace('/[^a-z0-9]/', '-', strtolower($category));

        $output = '<div class="content-type-button clear-block">';
        $url = "panels/ajax/add-pane-config/$cache_key/$panel_id/$type_name/$subtype_name";
        $output .= ctools_ajax_image_button($icon, $url, $description, 'panels-modal-add-config');
        $output .= '<div>' . ctools_ajax_text_button($title, $url, $description, 'panels-modal-add-config') . '</div>';
        $output .= '</div>';
        if (!isset($categories[$category_key])) {
          $category_names[$category_key] = $category;
          $categories[$category_key] = array();
          $titles[$category_key] = array();
        }

        $categories[$category_key][] = $output;
        $titles[$category_key][] = $title;
      }
    }
  }
  if (!$categories) {
    $output = t('There are no content types you may add to this display.');
  }
  else {
    if (!empty($category_names['root'])) {
      unset($category_names['root']);
    }

    $output = '<div class="panels-add-content-modal">';
    natcasesort($category_names);
    $selector = '<div class="panels-categories-box">';

    // Render our list of categories in column 0.
    foreach ($category_names as $category => $name) {
      $class = 'panels-modal-add-category';
      if ($category == $key) {
        $class .= ' active';
      }

      $url = "panels/ajax/add-pane/$cache_key/$panel_id/$category";
      $selector .= ctools_ajax_text_button($name, $url, '', $class);
    }

    $selector .= '</div>';
    if (!empty($categories['root'])) {
      foreach ($titles['root'] as $id => $title) {
        $selector .= $categories['root'][$id];
      }
    }

    if (empty($key) || empty($category_names[$key]) || $key == 'root') {
//      $key = current(array_keys($category_names));
      $center = '<div class="panels-categories-description">';
      $center .= t('Content options are divided by category. Please select a category from the left to proceed.');
      $center .= '</div>';
    }
    else {
      natcasesort($titles[$key]);

      // Fill out the info for our current category.
      $columns = 2;
      $col[1] = '';
      $col[2] = '';

      $col_size = count($titles[$key]) / $columns;
      $count = 0;
      foreach ($titles[$key] as $id => $title) {
        $which = floor($count++ / $col_size) + 1; // we leave 0 for the categories.
        $col[$which] .= $categories[$key][$id];
      }

      $center = '';
      foreach ($col as $id => $column) {
        $center .= '<div class="panels-section-column panels-section-column-' . $id . '">'
        . '<div class="inside">' . $column . '</div></div>';
      }
      $center .= '</div>'; // columns
    }
    $output .= '<div class="panels-section-column panels-section-column-categories">'
      . '<div class="inside">' . $selector . '</div></div>';
    $output .= '<div class="panels-section-columns">';
    $output .= $center;
    $output .= '</div>'; // categories box
  }
  return $output;
}

/**
 * AJAX entry point for configuring a pane that has just been added.
 */
function panels_ajax_add_pane_config($cache, $panel_id = NULL, $type_name = NULL, $subtype_name = NULL, $step = NULL) {
  ctools_include('content');
  $cache_key = $cache->display->cache_key;
  $content_type = ctools_get_content_type($type_name);
  $subtype = ctools_content_get_subtype($content_type, $subtype_name);

  if (!isset($step) || !isset($cache->new_pane)) {
    $pane = panels_new_pane($type_name, $subtype_name);
    $pane->configuration = ctools_content_get_defaults($content_type, $subtype);
    $pane->panel = $panel_id;
    $cache->new_pane = &$pane;
  }
  else {
    $pane = $cache->new_pane;
  }

  $form_state = array(
    'display' => &$cache->display,
    'contexts' => $cache->display->context,
    'pane' => &$pane,
    'cache_key' => $cache_key,
    'cache' => &$cache,
    'ajax' => TRUE,
    'modal' => TRUE,
    'commands' => array(),
  );

  $form_info = array(
    'path' => "panels/ajax/add-pane-config/$cache_key/$panel_id/$type_name/$subtype_name/%step",
    'next callback' => 'panels_ajax_edit_pane_config_next',
    'finish callback' => 'panels_ajax_add_pane_config_finish',
  );

  $rc = ctools_content_form('add', $form_info, $form_state, $content_type, $pane->subtype, $subtype, $pane->configuration, $step);
  if ($rc === FALSE) {
    panels_ajax_add_pane_config_finish($form_state);
    $form_state['commands'][] = ctools_modal_command_dismiss();
    ctools_ajax_render($form_state['commands']);
  }
}

/**
 * AJAX entry point for configuring a pane that already existed.
 */
function panels_ajax_configure_pane($cache, $pid = NULL, $step = NULL) {
  ctools_include('content');
  $cache_key = $cache->display->cache_key;
  if (empty($cache->display->content[$pid])) {
    ctools_modal_render(t('Error'), t('Invalid pane id.'));
  }

  $pane = &$cache->display->content[$pid];

  $content_type = ctools_get_content_type($pane->type);
  $subtype = ctools_content_get_subtype($content_type, $pane->subtype);

  $form_state = array(
    'display' => &$cache->display,
    'contexts' => $cache->display->context,
    'pane' => &$pane,
    'cache' => &$cache,
    'ajax' => TRUE,
    'modal' => TRUE,
    'commands' => array(),
  );

  $form_info = array(
    'path' => "panels/ajax/configure/$cache_key/$pid/%step",
    'next callback' => 'panels_ajax_edit_pane_config_next',
    'finish callback' => 'panels_ajax_edit_pane_config_finish',
  );

  ctools_content_form('edit', $form_info, $form_state, $content_type, $pane->subtype,  $subtype, $pane->configuration, $step);
}

function panels_ajax_edit_pane_config_next(&$form_state) {
  $form_state['cache']->new_pane = $form_state['pane'];
  panels_edit_cache_set($form_state['cache']);
}

function panels_ajax_add_pane_config_finish(&$form_state) {
  $cache = &$form_state['cache'];
  $pane = $cache->new_pane;
  unset($cache->new_pane);

  // Get a real pid for this pane.
  $pane->pid = "new-" . $cache->display->next_new_pid();
  // Put the pane into the display where it belongs

  $cache->display->content[$pane->pid] = $pane;
  $cache->display->panels[$pane->panel][] = $pane->pid;

  panels_edit_cache_set($cache);

  $form_state['commands'][] = ctools_ajax_command_append("#panel-pane-$pane->panel", panels_show_pane($cache->display, $pane, TRUE));
  $form_state['commands'][] = ctools_ajax_command_changed("#panel-pane-$pane->pid", "div.grabber span.text");
}

function panels_ajax_edit_pane_config_finish(&$form_state) {
  $cache = &$form_state['cache'];
  $pane = &$form_state['pane'];
  panels_edit_cache_set($cache);

  $form_state['commands'][] = ctools_ajax_command_replace("#panel-pane-$pane->pid", panels_show_pane($cache->display, $pane, TRUE));
  $form_state['commands'][] = ctools_ajax_command_changed("#panel-pane-$pane->pid", "div.grabber span.text");
}

/**
 * Entry point for AJAX: toggle pane show/hide status.
 *
 * @param int $cache
 *  The display id for the display object currently being edited. Errors out silently if absent.
 * @param int $pid
 *  The pane id for the pane object whose show/hide state we're toggling.
 * @param string $op
 *  The operation - showing or hiding - that this should perform. This could be calculated from
 *  cached values, but given that this is a toggle button and people may click it too fast,
 *  it's better to leave the decision on which $op to use up to the js than to calculate it here.
 */
function panels_ajax_toggle_shown($op, $cache, $pid = NULL) {
  if (empty($cache->display->content[$pid])) {
    ctools_ajax_render_error(t('Invalid pane id.'));
  }

  $pane = &$cache->display->content[$pid];

  $pane->shown = ($op == 'show');
  panels_edit_cache_set($cache);

  $output = array();
  $output[] = ctools_ajax_command_replace("#panel-pane-$pane->pid", panels_show_pane($cache->display, $pane, TRUE));
  $output[] = ctools_ajax_command_changed("#panel-pane-$pane->pid", "div.grabber span.text");

  ctools_ajax_render($output);
}

/**
 * Entry point for AJAX: switch which pane is being used to set the display title.
 *
 * @param int $cache
 *  The display id for the display object currently being edited. Errors out silently if absent.
 * @param int $pid
 *  The pane id for the pane object whose show/hide state we're toggling.
 */
function panels_ajax_set_display_title($cache, $pid = NULL) {
  if (empty($cache->display->content[$pid])) {
    ctools_ajax_render_error(t('Invalid pane id.'));
  }

  $pane = &$cache->display->content[$pid];

  $old_title = !empty($cache->display->title_pane) ? $cache->display->title_pane : NULL;
  $cache->display->title_pane = $pid;

  panels_edit_cache_set($cache);

  $output = array();
  $output[] = ctools_ajax_command_replace("#panel-pane-$pane->pid", panels_show_pane($cache->display, $pane, TRUE));

  if ($old_title && !empty($cache->display->content[$old_title])) {
    $old_pane = $cache->display->content[$old_title];
    $output[] = ctools_ajax_command_replace("#panel-pane-$old_pane->pid", panels_show_pane($cache->display, $old_pane, TRUE));
  }

  // Update the text stating which pane is currently selected as the title.
//  $output[] = ctools_ajax_command_changed("#panel-pane-$pane->pid", "div.grabber span.text");

  ctools_ajax_render($output);
}

/**
 * Entry point for AJAX modal: configure pane cache method
 */
function panels_ajax_cache_method($cache, $pid = NULL) {
  ctools_include('content');
  // This lets us choose whether we're doing the display's cache or
  // a pane's.
  if ($pid == 'display') {
    $conf = &$cache->display->cache;
    $title = t('Cache method for this display');
  }
  else if (!empty($cache->display->content[$pid])) {
    $pane = &$cache->display->content[$pid];
    $subtype = ctools_content_get_subtype($pane->type, $pane->subtype);
    $conf = &$pane->cache;
    $title = t('Cache method for !subtype_title', array('!subtype_title' => $subtype['title']));
  }
  else {
    ctools_modal_render(t('Error'), t('Invalid pane id.'));
  }

  $form_state = array(
    'display' => &$cache->display,
    'conf' => &$conf,
    'title' => $title,
    'ajax' => TRUE,
  );

  $output = ctools_modal_form_wrapper('panels_edit_cache_method_form', $form_state);
  if (empty($output)) {
    // Preserve this; this way we don't actually change the method until they
    // have saved the form.
    $info = panels_get_cache($form_state['method']);
    $function = panels_plugin_get_function('cache', $info, 'settings form');
    if (!$function) {
      $conf['method'] = $form_state['method'];
      $conf['settings'] = array();
      panels_edit_cache_set($cache);

      $output = array();
      $output[] = ctools_modal_command_dismiss();

      if ($pid != 'display') {
        $output[] = ctools_ajax_command_replace("#panel-pane-$pid", panels_show_pane($cache->display, $pane, TRUE));
        $output[] = ctools_ajax_command_changed("#panel-pane-$pid", "div.grabber span.text");
      }
      else {
        $links = panels_edit_display_get_links($cache->display);
        $output[] = ctools_ajax_command_replace('.panels-display-links', $links);
      }
    }
    else {
      $cache->method = $form_state['method'];
      panels_edit_cache_set($cache);
      // send them to next form.
      return panels_ajax_cache_settings($cache, $pid);
    }
  }

  ctools_ajax_render($output);
}

/**
 * Choose cache method form
 */
function panels_edit_cache_method_form(&$form_state) {
  $display = &$form_state['display'];
  $conf = &$form_state['conf'];

  // Set to 0 to ensure we get a selected radio.
  if (!isset($conf['method'])) {
    $conf['method'] = 0;
  }

  $caches = panels_get_caches();
  if (empty($caches)) {
    $form['markup'] = array('#value' => t('No caching options are available at this time. Please enable a panels caching module in order to use caching options.'));
    return $form;
  }

  $options[0] = t('No caching');
  foreach ($caches as $cache => $info) {
    $options[$cache] = check_plain($info['title']);
  }

  $form['method'] = array(
    '#prefix' => '<div class="no-float">',
    '#suffix' => '</div>',
    '#type' => 'radios',
    '#title' => t('Method'),
    '#options' => $options,
    '#default_value' => $conf['method'],
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );
  return $form;
}

/**
 * Submit callback for panels_edit_cache_method_form.
 *
 * All this needs to do is return the method.
 */
function panels_edit_cache_method_form_submit($form, &$form_state) {
  $form_state['method'] = $form_state['values']['method'];
}

/**
 * Handle the cache settings form
 */
function panels_ajax_cache_settings($cache, $pid = 0) {
  ctools_include('content');
  $cache_key = $cache->display->cache_key;
  // This lets us choose whether we're doing the display's cache or
  // a pane's.
  if ($pid == 'display') {
    $conf = &$cache->display->cache;
    $title = t('Cache settings for this display');
  }
  else if (!empty($cache->display->content[$pid])) {
    $pane = &$cache->display->content[$pid];
    $subtype = ctools_content_get_subtype($pane->type, $pane->subtype);

    $conf = &$pane->cache;
    $title = t('Cache settings for !subtype_title', array('!subtype_title' => $subtype['title']));
  }
  else {
    ctools_modal_render(t('Error'), t('Invalid pane id.'));
  }

  if (isset($cache->method) && (empty($conf['method']) || $conf['method'] != $cache->method)) {
    $conf['method'] = $cache->method;
    $info = panels_get_cache($conf['method']);
    $conf['settings'] = isset($info['defaults']) ? $info['defaults'] : array();
  }

  $form_state = array(
    'display' => &$cache->display,
    'pid' => $pid,
    'conf' => &$conf,
    'ajax' => TRUE,
    'title' => $title,
    'url' => url("panels/ajax/cache-settings/$cache_key/$pid", array('absolute' => TRUE)),
  );

  $output = ctools_modal_form_wrapper('panels_edit_cache_settings_form', $form_state);
  if (empty($output)) {
    panels_edit_cache_set($cache);

    $output = array();
    $output[] = ctools_modal_command_dismiss();

    if ($pid != 'display') {
      $output[] = ctools_ajax_command_replace("#panel-pane-$pid", panels_show_pane($cache->display, $pane, TRUE));
      $output[] = ctools_ajax_command_changed("#panel-pane-$pid", "div.grabber span.text");
    }
    else {
      $links = panels_edit_display_get_links($cache->display);
      $output[] = ctools_ajax_command_replace('.panels-display-links', $links);
    }
  }
  ctools_ajax_render($output);
}

/**
 * Cache settings form
 */
function panels_edit_cache_settings_form(&$form_state) {
  $display = &$form_state['display'];
  $conf = &$form_state['conf'];
  $pid = $form_state['pid'];
  $info = panels_get_cache($conf['method']);

  $form['#action'] = $form_state['url'];

  $form['description'] = array(
    '#prefix' => '<div class="description">',
    '#suffix' => '</div>',
    '#value' => check_plain($info['description']),
  );

  $function = panels_plugin_get_function('cache', $conf['method'], 'settings form');

  $form['settings'] = $function($conf['settings'], $display, $pid);
  $form['settings']['#tree'] = TRUE;

  $form['display'] = array(
    '#type' => 'value',
    '#value' => $display,
  );

  $form['pid'] = array(
    '#type' => 'value',
    '#value' => $pid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Validate cache settings.
 */
function panels_edit_cache_settings_form_validate($form, &$form_state) {
  if ($function = panels_plugin_get_function('cache', $form_state['conf']['method'], 'settings form validate')) {
    $function($form, $form_state['values']['settings']);
  }
}

/**
 * Allows panel styles to validate their style settings.
 */
function panels_edit_cache_settings_form_submit($form, &$form_state) {
  if ($function = panels_plugin_get_function('cache', $form_state['conf']['method'], 'settings form submit')) {
    $function($form_state['values']['settings']);
  }

  $form_state['conf']['settings'] = $form_state['values']['settings'];
}

/**
 * Entry point for AJAX modal: configure pane style method
 */
function panels_ajax_style_type($type, $cache, $pid = NULL) {
  // This lets us choose whether we're doing the display's cache or
  // a pane's.
  switch ($type) {
    case 'display':
      $style = isset($cache->display->panel_settings['style']) ? $cache->display->panel_settings['style'] : 'default';
      $title = t('Default style for this display');
      break;

    case 'panel':
      $style = isset($cache->display->panel_settings[$pid]['style']) ? $cache->display->panel_settings[$pid]['style'] : '-1'; // -1 signifies to use the default setting.
      $layout = panels_get_layout($cache->display->layout);
      $layout_panels = panels_get_panels($layout, $cache->display);
      $title = t('Panel style for region "!region"', array('!region' => $layout_panels[$pid]));
      break;

    case 'pane':
      ctools_include('content');
      $pane = &$cache->display->content[$pid];
      $style = isset($pane->style['style']) ? $pane->style['style'] : 'default';
      $subtype = ctools_content_get_subtype($pane->type, $pane->subtype);
      $title = t('Pane style for "!pane"', array('!pane' => $subtype['title']));
      break;

    default:
      ctools_modal_render(t('Error'), t('Invalid pane id.'));
  }

  $form_state = array(
    'display' => &$cache->display,
    'style' => $style,
    'title' => $title,
    'ajax' => TRUE,
    'type' => $type,
  );

  $output = ctools_modal_form_wrapper('panels_edit_style_type_form', $form_state);
  if (empty($output)) {
    // Preserve this; this way we don't actually change the method until they
    // have saved the form.
    $style = panels_get_style($form_state['style']);
    $function = panels_plugin_get_function('style', $style, ($type == 'pane') ? 'pane settings form' : 'settings form');
    if (!$function) {
      // If there's no settings form, just change the style and exit.
      switch($type) {
        case 'display':
          $cache->display->panel_settings['style'] = $form_state['style'];
          if (isset($cache->display->panel_settings['style_settings']['default'])) {
            unset($cache->display->panel_settings['style_settings']['default']);
          }
          break;

        case 'panel':
          $cache->display->panel_settings[$pid]['style'] = $form_state['style'];
          if (isset($cache->display->panel_settings['style_settings'][$pid])) {
            unset($cache->display->panel_settings['style_settings'][$pid]);
          }
          break;

        case 'pane':
          $pane->style['style'] = $form_state['style'];
          if (isset($pane->style['settings'])) {
            unset($pane->style['settings']);
          }

          break;
      }
      panels_edit_cache_set($cache);

      $output = array();
      $output[] = ctools_modal_command_dismiss();

      if ($type == 'pane') {
        $output[] = ctools_ajax_command_replace("#panel-pane-$pane->pid", panels_show_pane($cache->display, $pane, TRUE));
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
    else {
      if ($form_state['style'] != $form_state['old_style']) {
        $cache->style = $form_state['style'];
        panels_edit_cache_set($cache);
      }

      // send them to next form.
      return panels_ajax_style_settings($type, $cache, $pid);
    }
  }

  ctools_ajax_render($output);
}

/**
 * Choose cache method form
 */
function panels_edit_style_type_form(&$form_state) {
  $display = &$form_state['display'];
  $style = $form_state['style'];
  $type = $form_state['type'];

  $styles = panels_get_styles();

  $function = ($type == 'pane' ? 'render pane' : 'render panel');
  $options = array();
  if ($type == 'panel') {
    $options[-1] = t('Use display default style');
  }

  foreach ($styles as $id => $info) {
    if (empty($info['hidden']) && (!empty($info[$function]) || $id == 'default')) {
      $options[$id] = check_plain($info['title']);
    }
  }

  asort($options);

  $form['style'] = array(
    '#prefix' => '<div class="no-float">',
    '#suffix' => '</div>',
    '#type' => 'radios',
    '#title' => t('Style'),
    '#options' => $options,
    '#default_value' => $style,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );
  return $form;
}

/**
 * Submit callback for panels_edit_cache_method_form.
 *
 * All this needs to do is return the method.
 */
function panels_edit_style_type_form_submit($form, &$form_state) {
  $form_state['old_style'] = $form_state['style'];
  $form_state['style'] = $form_state['values']['style'];
}

/**
 * Get the appropriate style from the panel in the cache.
 */
function panels_edit_style_get_style($type, &$cache, $pid = '') {
  if (isset($cache->style)) {
    $style = panels_get_style($cache->style);
    $defaults = isset($style['defaults']) ? $style['defaults'] : array();
    // Get the &$conf variable based upon whose style we're editing.
    switch ($type) {
      case 'display':
        $cache->display->panel_settings['style'] = $cache->style;
        $cache->display->panel_settings['style_settings']['default'] = $defaults;
        break;

      case 'panel':
        $cache->display->panel_settings[$pid]['style'] = $cache->style;
        $cache->display->panel_settings['style_settings'][$pid] = $defaults;
        break;

      case 'pane':
        $pane = &$cache->display->content[$pid];
        $pane->style['style'] = $cache->style;
        $pane->style['settings'] = $defaults;
        $conf = &$pane->style['settings'];
        break;
    }
  }
  else {
    switch ($type) {
      case 'display':
        $style = panels_get_style($cache->display->panel_settings['style']);
        break;

      case 'panel':
        $style = panels_get_style($cache->display->panel_settings[$pid]['style']);
        break;

      case 'pane':
        $pane = &$cache->display->content[$pid];
        $style = panels_get_style($pane->style['style']);
        break;
    }
  }

  // Set up our $conf reference.
  switch ($type) {
    case 'display':
      $conf = &$cache->display->panel_settings['style_settings']['default'];
      break;

    case 'panel':
      $conf = &$cache->display->panel_settings['style_settings'][$pid];
      break;

    case 'pane':
      ctools_include('content');
      $pane = &$cache->display->content[$pid];
      $conf = &$pane->style['settings'];
      break;
  }

  return array($style, &$conf);
}

/**
 * Handle the cache settings form
 */
function panels_ajax_style_settings($type, $cache, $pid = '') {
  $info = panels_edit_style_get_style($type, $cache, $pid);
  $style = $info[0];
  $conf = &$info[1];

  $cache_key = $cache->display->cache_key;

  switch ($type) {
    case 'display':
      $title = t('Style settings for @style (display)', array('@style' => $style['title']));
      break;

    case 'panel':
      $layout = panels_get_layout($cache->display->layout);
      $layout_panels = panels_get_panels($layout, $cache->display);
      $title = t('Style settings for style @style (Region "!region")', array('@style' => $style['title'], '!region' => $layout_panels[$pid]));
      break;

    case 'pane':
      ctools_include('content');
      $pane = &$cache->display->content[$pid];
      $subtype = ctools_content_get_subtype($pane->type, $pane->subtype);
      $title = t('Style settings for style @style (Pane "!pane")', array('@style' => $style['title'], '!pane' => $subtype['title']));
      break;
  }

  $form_state = array(
    'display' => &$cache->display,
    'type' => $type,
    'pid' => $pid,
    'conf' => &$conf,
    'style' => $style,
    'ajax' => TRUE,
    'title' => $title,
    'url' => url("panels/ajax/style-settings/$type/$cache_key/$pid", array('absolute' => TRUE)),
  );

  $output = ctools_modal_form_wrapper('panels_edit_style_settings_form', $form_state);
  if (empty($output)) {
    if (isset($cache->style)) {
      unset($cache->style);
    }

    // $conf was a reference so it should just modify.
    panels_edit_cache_set($cache);

    $output = array();
    $output[] = ctools_modal_command_dismiss();

    if ($type == 'pane') {
      $output[] = ctools_ajax_command_replace("#panel-pane-$pane->pid", panels_show_pane($cache->display, $pane, TRUE));
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
 * Cache settings form
 */
function panels_edit_style_settings_form(&$form_state) {
  $display = &$form_state['display'];
  $conf = &$form_state['conf'];
  $pid = $form_state['pid'];
  $style = $form_state['style'];
  $type = $form_state['type'];

  $form['#action'] = $form_state['url'];

  $form['description'] = array(
    '#prefix' => '<div class="description">',
    '#suffix' => '</div>',
    '#value' => check_plain($style['description']),
  );

  $function = panels_plugin_get_function('cache', $style, ($type == 'pane') ? 'pane settings form' : 'settings form');

  $form['settings'] = $function($conf, $display, $pid, $type);
  $form['settings']['#tree'] = TRUE;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Validate cache settings.
 */
function panels_edit_style_settings_form_validate($form, &$form_state) {
  $name = $form_state['type'] == 'pane' ? 'pane settings form validate' : 'settings form validate';
  if ($function = panels_plugin_get_function('style', $form_state['style'], $name)) {
    $function($form, $form_state['values']['settings'], $form_state);
  }
}

/**
 * Allows panel styles to validate their style settings.
 */
function panels_edit_style_settings_form_submit($form, &$form_state) {
  $name = $form_state['type'] == 'pane' ? 'pane settings form submit' : 'settings form submit';
  if ($function = panels_plugin_get_function('style', $form_state['style'], $name)) {
    $function($form, $form_state['values']['settings'], $form_state);
  }

  $form_state['conf'] = $form_state['values']['settings'];
}

/**
 * AJAX entry point to configure CSS for a pane.
 */
function panels_ajax_configure_pane_css($cache, $pid = NULL) {
  ctools_include('content');
  if (empty($cache->display->content[$pid])) {
    ctools_modal_render(t('Error'), t('Invalid pane id.'));
  }

  $pane = &$cache->display->content[$pid];
  $subtype = ctools_content_get_subtype($pane->type, $pane->subtype);

  $form_state = array(
    'display' => &$cache->display,
    'pane' => &$pane,
    'ajax' => TRUE,
    'title' => t('Configure CSS on !subtype_title', array('!subtype_title' => $subtype['title'])),
  );

  $output = ctools_modal_form_wrapper('panels_content_configure_pane_css_form', $form_state);
  if (empty($output)) {
    panels_edit_cache_set($cache);
    $output = array();
    $output[] = ctools_ajax_command_changed("#panel-pane-$pane->pid", "div.grabber span.text");
    $output[] = ctools_modal_command_dismiss();
  }

  ctools_ajax_render($output);
}


/**
 * Configure CSS on a pane form.
 */
function panels_content_configure_pane_css_form(&$form_state) {
  $display = &$form_state['display'];
  $pane = &$form_state['pane'];

  $form['css_id'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($pane->css['css_id']) ? $pane->css['css_id'] : '',
    '#title' => t('CSS ID'),
    '#description' => t('CSS ID to apply to this pane. This may be blank.'),
  );
  $form['css_class'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($pane->css['css_class']) ? $pane->css['css_class'] : '',
    '#title' => t('CSS class'),
    '#description' => t('CSS class to apply to this pane. This may be blank.'),
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * FAPI submission function for the CSS configure form.
 *
 * All this does is set up $pane properly. The caller is responsible for
 * actually storing this somewhere.
 */
function panels_content_configure_pane_css_form_submit($form, &$form_state) {
  $pane = &$form_state['pane'];
  $display = $form_state['display'];

  $pane->css['css_id'] = $form_state['values']['css_id'];
  $pane->css['css_class'] = $form_state['values']['css_class'];
}

/**
 * AJAX entry point to configure access settings for a pane.
 */
function panels_ajax_configure_access_settings($cache, $pid = NULL) {
  ctools_include('content');
  if (empty($cache->display->content[$pid])) {
    ctools_modal_render(t('Error'), t('Invalid pane id.'));
  }

  $pane = &$cache->display->content[$pid];
  $subtype = ctools_content_get_subtype($pane->type, $pane->subtype);

  $form_state = array(
    'display' => &$cache->display,
    'pane' => &$pane,
    'ajax' => TRUE,
    'title' => t('Access settings on !subtype_title', array('!subtype_title' => $subtype['title'])),
  );

  $output = ctools_modal_form_wrapper('panels_content_configure_access_settings_form', $form_state);
  if (empty($output)) {
    panels_edit_cache_set($cache);
    $output = array();
    $output[] = ctools_ajax_command_replace("#panel-pane-$pane->pid", panels_show_pane($cache->display, $pane, TRUE));
    $output[] = ctools_ajax_command_changed("#panel-pane-$pane->pid", "div.grabber span.text");
    $output[] = ctools_modal_command_dismiss();
  }

  ctools_ajax_render($output);
}


/**
 * Form to control basic visibility settings.
 */
function panels_content_configure_access_settings_form(&$form_state) {
  $display = &$form_state['display'];
  $pane = &$form_state['pane'];

  $form['logic'] = array(
    '#type' => 'radios',
    '#options' => array(
      'and' => t('All criteria must pass.'),
      'or' => t('Only one criteria must pass.'),
    ),
    '#default_value' => isset($pane->access['logic']) ? $pane->access['logic'] : 'and',
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * FAPI submission function for the edit access settings form.
 *
 * All this does is set up $pane properly. The caller is responsible for
 * actually storing this somewhere.
 */
function panels_content_configure_access_settings_form_submit($form, &$form_state) {
  $pane = &$form_state['pane'];
  $display = $form_state['display'];

  $pane->access['logic'] = $form_state['values']['logic'];
}

/**
 * AJAX entry point for to add a visibility rule.
 */
function panels_ajax_add_access_test($cache, $pid = NULL) {
  ctools_include('content');
  if (empty($cache->display->content[$pid])) {
    ctools_modal_render(t('Error'), t('Invalid pane id.'));
  }

  $pane = &$cache->display->content[$pid];
  $subtype = ctools_content_get_subtype($pane->type, $pane->subtype);

  $form_state = array(
    'display' => &$cache->display,
    'pane' => &$pane,
    'ajax' => TRUE,
    'title' => t('Add visibility rule for !subtype_title', array('!subtype_title' => $subtype['title'])),
  );

  $output = ctools_modal_form_wrapper('panels_content_add_access_test_form', $form_state);
  if (empty($output)) {
    // Set up the plugin in cache
    $plugin = ctools_get_access_plugin($form_state['values']['type']);
    $cache->new_plugin = ctools_access_new_test($plugin);
    panels_edit_cache_set($cache);

    // go to the next step.
    return panels_ajax_configure_access_test($cache, $pid, 'add');
  }

  ctools_ajax_render($output);
}

/**
 * Form to add a visibility rule.
 */
function panels_content_add_access_test_form(&$form_state) {
  $display = &$form_state['display'];
  $pane = &$form_state['pane'];

  $plugins = ctools_get_relevant_access_plugins($display->context);
  $options = array();
  foreach ($plugins as $id => $plugin) {
    $options[$id] = $plugin['title'];
  }

  asort($options);

  $form['type'] = array(
    // This ensures that the form item is added to the URL.
    '#type' => 'radios',
    '#options' => $options,
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );

  return $form;
}

/**
 * AJAX entry point for to configure vsibility rule
 */
function panels_ajax_configure_access_test($cache, $pid = NULL, $id = NULL) {
  ctools_include('content');
  $cache_key = $cache->display->cache_key;
  if (empty($cache->display->content[$pid])) {
    ctools_modal_render(t('Error'), t('Invalid pane id.'));
  }

  $pane = &$cache->display->content[$pid];
  $subtype = ctools_content_get_subtype($pane->type, $pane->subtype);

  // Set this up here because $id gets changed later.
  $url = "panels/ajax/access-test/$cache_key/$pid/$id";

  // If we're adding a new one, get the stored data from cache and
  // add it. It's stored as a cache so that if this is closed
  // we don't accidentally add an unconfigured plugin.
  if ($id == 'add') {
    $pane->access['plugins'][] = $cache->new_plugin;
    $id = max(array_keys($pane->access['plugins']));
  }
  else if (empty($pane->access['plugins'][$id])) {
    ctools_modal_render(t('Error'), t('Invalid test id.'));
  }

  $form_state = array(
    'display' => &$cache->display,
    'pane' => &$pane,
    'ajax' => TRUE,
    'title' => t('Configure visibility rule for !subtype_title', array('!subtype_title' => $subtype['title'])),
    'test' => &$pane->access['plugins'][$id],
    'plugin' => ctools_get_access_plugin($pane->access['plugins'][$id]['name']),
    'url' => url($url, array('absolute' => TRUE)),
  );

  $output = ctools_modal_form_wrapper('panels_content_configure_access_test_form', $form_state);
  if (empty($output)) {
    // Unset the new plugin
    if (isset($cache->new_plugin)) {
      unset($cache->new_plugin);
    }

    if (!empty($form_state['remove'])) {
      unset($pane->access['plugins'][$id]);
    }

    panels_edit_cache_set($cache);
    $output = array();
    $output[] = ctools_ajax_command_replace("#panel-pane-$pane->pid", panels_show_pane($cache->display, $pane, TRUE));
    $output[] = ctools_ajax_command_changed("#panel-pane-$pane->pid", "div.grabber span.text");
    $output[] = ctools_modal_command_dismiss();
  }

  ctools_ajax_render($output);
}

/**
 * Form to configure a visibility rule.
 */
function panels_content_configure_access_test_form(&$form_state) {
  $display = &$form_state['display'];
  $test = &$form_state['test'];
  $plugin = &$form_state['plugin'];

  $form['#action'] = $form_state['url'];

  $contexts = $display->context;
  if (!isset($contexts['logged-in-user'])) {
    $contexts['logged-in-user'] = ctools_access_get_loggedin_context();
  }

  if (isset($plugin['required context'])) {
    $form['context'] = ctools_context_selector($contexts, $plugin['required context'], $test['context']);
  }

  $form['settings'] = array('#tree' => TRUE);
  if ($function = ctools_plugin_get_function($plugin, 'settings form')) {
    $function($form, $form_state, $test['settings']);
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['remove'] = array(
    '#type' => 'submit',
    '#value' => t('Remove'),
    '#remove' => TRUE,
  );

  return $form;
}

/**
 * Validate handler for visibility rule settings
 */
function panels_content_configure_access_test_form_validate(&$form, &$form_state) {
  if (!empty($form_state['clicked_button']['#remove'])) {
    return;
  }

  if ($function = ctools_plugin_get_function($form_state['plugin'], 'settings form validate')) {
    $function($form, $form_state);
  }
}

/**
 * Submit handler for visibility rule settings
 */
function panels_content_configure_access_test_form_submit(&$form, &$form_state) {
  if (!empty($form_state['clicked_button']['#remove'])) {
    $form_state['remove'] = TRUE;
    return;
  }

  if ($function = ctools_plugin_get_function($form_state['plugin'], 'settings form submit')) {
    $function($form, $form_state);
  }

  $form_state['test']['settings'] = $form_state['values']['settings'];
  if (isset($form_state['values']['context'])) {
    $form_state['test']['context'] = $form_state['values']['context'];
  }
}

/**
 * }@ End of 'defgroup panels_ajax'
 */

// ---------------------------------------------------------------------------
// Panels theming functions

// @DND
function panels_render_dnd($content) {
  $output = '<div class="panels-dnd" id="panels-dnd-main">' . $content . '</div>';
  return $output;
}

// @DND
function panels_render_region_dnd($content, $area, $label, $footer) {
  return "<div class='panels-display' id='panel-pane-$area'>$footer<h2 class='label'>$label</h2>$content</div>";
}

// @DND
function panels_render_pane_dnd($block, $id, $label, $left_buttons = NULL, $buttons = NULL) {
  $output = '';
  if (!$block->title) {
    $block->title = t('No title');
  }
  static $count = 0;
  $output .= '<div class="grabber">';
  if ($buttons) {
    $output .= '<span class="buttons">' . $buttons . '</span>';
  }
  if ($left_buttons) {
    $output .= '<span class="left_buttons">' . $left_buttons . '</span>';
  }
  $output .= '<span class="text">' . $label . '</span></div>';
  $output .= '<div class="panel-pane-collapsible">';
  $output .= panels_render_pane_collapsible($block);
  $output .= '</div>';
  return $output;
}

// @DND
function panels_render_pane_collapsible($block) {
  $output = '';
  $output .= '<div class="pane-title">' . $block->title . '</div>';
  $output .= '<div class="pane-content">' . filter_xss_admin($block->content) . '</div>';
  return $output;
}
