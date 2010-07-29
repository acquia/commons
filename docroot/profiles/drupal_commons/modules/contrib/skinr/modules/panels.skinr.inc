<?php
// $Id: panels.skinr.inc,v 1.8.2.5 2010/02/23 17:50:00 moonray Exp $
/**
 * @file
 * Provide skinr handling for panels.module.
 */

/**
 * @defgroup skinr_panels_module panels.module handlers.
 *
 * @{
 */

/**
 * Implementation of hook_skinr_data().
 */
function panels_skinr_data() {
  $data['panels']['form']['panels_edit_style_settings_form'] = array(
    'index_handler' => 'panels_skinr_form_index_handler',
    'data_handler' => 'panels_skinr_data_handler',
    'submit_handler' => 'panels_skinr_submit_handler_settings',
    'preprocess_hook_callback' => 'panels_skinr_preprocess_hook_callback',
    'title' => t('panel pane settings'),
    'skinr_weight' => 0,
    'collapsed' => FALSE,
  );
  // Panel pages.
  $data['panels']['form']['page_manager_save_page_form'] = array(
    'access_handler' => 'panels_skinr_access_handler_display',
    'submit_handler' => 'panels_skinr_submit_handler_display',
  );
  // Content form for panel pages.
  $data['panels']['form']['panels_panel_context_edit_content'] = array(
    'access_handler' => 'panels_skinr_access_handler_display',
    'submit_handler' => 'panels_skinr_submit_handler_display',
  );
  // Mini panels.
  $data['panels']['form']['panels_edit_display_form'] = array(
    'access_handler' => 'panels_skinr_access_handler_display',
    'submit_handler' => 'panels_skinr_submit_handler_display',
  );
  $data['panels']['preprocess']['panels_pane'] = array(
    'index_handler' => 'panels_skinr_preprocess_index_handler',
  );

  return $data;
}

/**
 * Skinr form index handler.
 *
 * @param $op
 *   What kind of action is being performed. Possible values:
 *   - "form": the form elements for Skinr are being inserted in a form
 *   - "submit": the form has been submitted.
 * @param &$form
 *   - For "form", passes in the $form parameter from hook_form_alter().
 *   - For "submit", passes in the $form parameter from hook_form_submit().
 * @param $form_state
 *   - For "form", passes in the $form_state parameter from hook_form_alter().
 *   - For "submit", passes in the $form_state parameter from hook_form_submit().
 * @return
 *   The index where we can find our values in Skinrs data structure.
 */
function panels_skinr_form_index_handler($op, &$form, $form_state) {
  switch ($op) {
    case 'form':
    case 'submit':
      switch ($form['#parameters'][1]['type']) {
        case 'display':
          return 'display-'. $form['#parameters'][1]['display']->did;
        case 'panel':
          return 'display-'. $form['#parameters'][1]['display']->did .'-panel-'. $form['#parameters'][1]['pid'];
        case 'pane':
          return 'display-'. $form['#parameters'][1]['display']->did .'-pane-'. $form['#parameters'][1]['pid'];
      }
  }
}

/**
 * Skinr access handler.
 *
 * @param $op
 *   What kind of action is being performed. Possible values:
 *   - "access skinr": access to edit skinr's selector
 *   - "access skinr classes": access to edit skinr's additional classes
 * @param &$form
 *   Passes in the $form parameter from hook_form_alter().
 * @param $form_state
 *   Passes in the $form_state parameter from hook_form_alter().
 * @return
 *   TRUE if we get access, FALSE if we don't.
 */
function panels_skinr_access_handler_display($op, &$form, $form_state) {
  // We don't want the skinr settings form to appear on this form. We only want
  // to intercept it so we can save our cached data.

  // Since we're not using the form, we won't get our form submitter, so let's
  // add it manually.

  $form_id = $form['form_id']['#value'];

  switch ($form_id) {
    case 'panels_panel_context_edit_content':
      // Update and save button

      // Only add submit handler once.
      if (!in_array('skinr_form_submit', $form['#submit'])) {
        $form['#submit'][] = 'skinr_form_submit';
      }
      break;

    case 'page_manager_save_page_form':
      // Submitting a panel page.

      // Only add submit handler once.
      if (!in_array('skinr_form_submit', $form['#submit'])) {
        $form['#submit'][] = 'skinr_form_submit';
      }
      if (isset($form['save']['#submit']) && !in_array('skinr_form_submit', $form['save']['#submit'])) {
        $form['save']['#submit'][] = 'skinr_form_submit';
      }
      if (isset($form['cancel']['#submit']) && !in_array('skinr_form_submit', $form['cancel']['#submit'])) {
        $form['cancel']['#submit'][] = 'skinr_form_submit';
      }
      break;

    case 'panels_edit_display_form':
      // Only add submit handler once.
      if (!in_array('skinr_form_submit', $form['#submit'])) {
        $form['#submit'][] = 'skinr_form_submit';
      }
      if (isset($form['buttons']['submit']['#submit']) && !in_array('skinr_form_submit', $form['buttons']['submit']['#submit'])) {
        $form['buttons']['submit']['#submit'][] = 'skinr_form_submit';
      }
      break;

    default:
      // We only want to save or cancel on these other forms if we're dealing with a panel_page.
      if ($form_state['task']['name'] == 'panel_page') {
        // Only add submit handler once
        if (!in_array('skinr_form_submit', $form['#submit'])) {
          $form['#submit'][] = 'skinr_form_submit';
        }
        if (isset($form['buttons']['cancel']['#submit']) && !in_array('skinr_form_submit', $form['buttons']['cancel']['#submit'])) {
          $form['buttons']['cancel']['#submit'][] = 'skinr_form_submit';
        }
      }
      break;
  }

  return FALSE;
}

/**
 * Skinr data handler.
 * This is the data that populates the skinr form.
 *
 * @param &$form
 *   Passes in the $form parameter from hook_form_submit().
 * @param $form_state
 *   Passes in the $form_state parameter from hook_form_submit().
 * @param $module
 *   The module that is currently being processed.
 * @param $form_settings
 *   The settings from hook_skinr_data() for the form that's currently being
 *   processed.
 * @return
 *   TRUE if we get access, FALSE if we don't.
 */
function panels_skinr_data_handler(&$form, $form_state, $theme, $module, $form_settings) {
  // Ensure we have the required index_handler.
  if (empty($form_settings['index_handler'])) {
    trigger_error(sprintf("No index_handler was found for form_id '%s' in module '%s'.", $form_id, $module), E_USER_ERROR);
  }
  $index = skinr_handler('form_index_handler', 'form', $form_settings['index_handler'], $form, $form_state);

  // Fetch skinr data for this view from cache.
  ctools_include('object-cache');

  if ($skinr_data = ctools_object_cache_get('skinr', $form_state['display']->did, TRUE)) {
    if (isset($skinr_data[$theme][$index])) {
      return $skinr_data[$theme][$index];
    }
    else {
      return array();
    }
  }

  // No data exists in cache, so let's grab it from the regular source.
  return skinr_get($theme, $module, $index);
}

/**
 * Skinr submit handler.
 *
 * @param $op
 *   What kind of action is being performed. Possible values:
 *   - "access skinr": access to edit skinr's selector
 *   - "access skinr classes": access to edit skinr's additional classes
 * @param &$form
 *   Passes in the $form parameter from hook_form_alter().
 * @param $form_state
 *   Passes in the $form_state parameter from hook_form_alter().
 * @return
 *   TRUE if we get access, FALSE if we don't.
 */
function panels_skinr_submit_handler_settings(&$form, $form_state, $module, $form_settings) {
  foreach ($form_state['values']['skinr_settings'][$module .'_group'] as $theme_name => $theme) {
    if ((isset($theme['widgets']) && count($theme['widgets'])) || isset($theme['advanced']['_additional'])) {
      $hook  = $module;
      $key   = skinr_handler('form_index_handler', 'submit', $form_settings['index_handler'], $form, $form_state);

      // Key doesn't exist properly for new displays. Perhaps we should inject a timestamp based key into the display object
      // and use that for reference on the final submit? If it works...

      $value = array();

      if (is_array($theme['widgets'])) {
        foreach ($theme['widgets'] as $skin_id => $skin_value) {
          $value[$skin_id] = is_array($skin_value) ? _skinr_array_strip_empty($skin_value) : $skin_value;
        }
      }

      if (isset($theme['advanced']['_additional'])) {
        $theme['advanced']['_additional'] = trim($theme['advanced']['_additional']);
        if (!empty($theme['advanced']['_additional'])) {
          $value['_additional'] = $theme['advanced']['_additional'];
        }
      }

      if (isset($theme['advanced']['_template'])) {
        $theme['advanced']['_template'] = trim($theme['advanced']['_template']);
        if (!empty($theme['advanced']['_template'])) {
          $value['_template'] = $theme['advanced']['_template'];
        }
      }

      if (empty($key)) {
        // We didn't receive a valid key, so raise an error.
        drupal_set_message(t("Skinr settings weren't saved due to an error."), 'error');
      }

      // Save skinr_settings for this panel display in cache.
      ctools_include('object-cache');
      if (!$skinr_data = ctools_object_cache_get('skinr', $form_state['display']->did, TRUE)) {
        $skinr_data = array();
        // Fetch skinr data.
        $skinr = skinr_get($theme_name);
        if (isset($skinr[$module])) {
          foreach ($skinr[$module] as $skinr_key => $skinr_value) {
            if (drupal_substr($skinr_key, 0, drupal_strlen('display-'. $form_state['display']->did)) == 'display-'. $form_state['display']->did) {
              $skinr_data[$theme_name][$skinr_key] = $skinr_value;
            }
          }
        }
      }
      $skinr_data[$theme_name][$key] = $value;
      ctools_object_cache_set('skinr', $form_state['display']->did, $skinr_data);
    }
  }
}

/**
 * @todo remove values from skinr if a display is deleted
 */
function panels_skinr_submit_handler_display(&$form, $form_state, $module, $form_settings) {
  $form_id = $form_state['values']['form_id'];

  // Include ctools' object cache files.
  ctools_include('object-cache');

  if ($form_state['values']['op'] == t('Save') || $form_state['values']['op'] == t('Update and save')) {
    switch ($form_id) {
      case 'panels_panel_context_edit_content':
      case 'page_manager_save_page_form':
        // Panel page.
        foreach ($form_state['page']->handler_info as $id => $info) {
          if ($info['changed']) {
            _panels_skinr_save_and_clear_cache($form_state['page']->handlers[$id]->conf['did']);
          }
        }
        break;

      case 'panels_edit_display_form':
        // Mini panels.
        _panels_skinr_save_and_clear_cache($form_state['display']->did);
        break;
    }
  }
  elseif ($form_state['values']['op'] == t('Cancel')) {
    switch ($form_id) {
      case 'page_manager_save_page_form':
        // Panel page.
        foreach ($form_state['page']->handler_info as $id => $info) {
          if ($info['changed']) {
            ctools_object_cache_clear('skinr', $form_state['page']->handlers[$id]->conf['did']);
          }
        }
        break;

      case 'panels_edit_display_form':
        // Mini panels.
        ctools_object_cache_clear('skinr', $form_state['display']->did);
        break;
    }
  }
}

function _panels_skinr_save_and_clear_cache($did) {
  if ($skinr_data = ctools_object_cache_get('skinr', $did, TRUE)) {
    foreach ($skinr_data as $theme_name => $theme) {
      foreach ($theme as $key => $value) {
        skinr_set($theme_name, 'panels', $key, $value);
      }
    }
    ctools_object_cache_clear('skinr', $did);
  }
}

/**
 * Skinr preprocess_hook_callback.
 *
 * @param &$form
 *   Passes in the $form parameter from hook_form_alter().
 * @param $form_state
 *   Passes in the $form_state parameter from hook_form_alter().
 * @return
 *   The preprocess_hook we wish to use.
 */
function panels_skinr_preprocess_hook_callback(&$form, $form_state) {
  switch ($form['#parameters'][1]['type']) {
    case 'display':
      return 'panels_display';
    case 'panel':
      return 'panels_panel';
    case 'pane':
      return 'panels_pane';
  }
}

/**
 * Skinr preprocess index handler.
 *
 * @param &$vars
 *   Passes in the $vars parameter from module_preprocess().
 * @return
 *   The index where we can find our values in Skinrs data structure. If an
 *   array is returned, it will loop through each index in Skinr's data
 *   structure and merge the returned classes.
 */
function panels_skinr_preprocess_index_handler(&$vars) {
  $index = '';
  if ($vars['pane']->style['style'] == 'skinr') {
    $index =  'display-'. $vars['pane']->did .'-pane-'. $vars['pane']->pid;
  }
  return $index;
}

//----------------------------------------------------------------------------
// Panels hooks.

/**
 * Implementation of hook_ctools_plugin_directory() to let the system know
 * we implement panels plugins.
 */
function skinr_ctools_plugin_directory($module, $plugin) {
  // Safety: go away if CTools is not at an appropriate version.
  if (!module_invoke('ctools', 'api_version', PANELS_REQUIRED_CTOOLS_API)) {
    return;
  }
  if ($module == 'panels') {
    return 'modules/'. $plugin;
  }
}

/**
 * Implementation of hook_panels_style_info().
 */
function skinr_panels_styles() {
  return array(
    'skinr' => array(
      'title'              => t('Skinr'),
      'description'        => t('Allows you to apply Skinr skins.'),
      'render panel'       => 'panels_skinr_style_render_panel',
      'render pane'        => 'panels_skinr_style_render_pane',
      'settings form'      => 'panels_skinr_style_settings_form',
      'pane settings form' => 'panels_skinr_style_settings_form',
    ),
  );
}

//----------------------------------------------------------------------------
// Panels style plugin callbacks.

/**
 * Render panel callback.
 *
 * @todo: Need to wait for a panels update to panels_render_panel()
 *        The panel_id is not sent through properly, yet. Once it works as
 *        promised, we can remove the workaround.
 */
function theme_panels_skinr_style_render_panel($display, $panel_id, $panes, $settings) {
  // Workaround for missing/invalid $panel_id.
  if (empty($panel_id)) {
    // We grab the first pane that we know exists in this panel and extract the panel_id from it.
    $panes_keys = array_keys($panes);
    $panel_id = $display->content[$panes_keys[0]]->panel;
  }

  $output = '';
  $print_separator = FALSE;
  foreach ($panes as $pane_id => $content) {
    // Add the separator if we've already displayed a pane.
    if ($print_separator) {
      $output .= '<div class="panel-separator"></div>';
    }
    $output .= $text = panels_render_pane($content, $display->content[$pane_id], $display);

    // If we displayed a pane, this will become true; if not, it will become
    // false.
    $print_separator = (bool) $text;
  }

  // Add skinr styles
  $hook = 'panels';
  if (isset($display->panel_settings[$panel_id]['style']) && isset($display->panel_settings[$panel_id]['style']) == 'skinr') {
    // Specific style set for this panel.
    $key = 'display-'. $display->did .'-panel-'. $panel_id;
  }
  else {
    // No specific style set, so use the display's style.
    $key = 'display-'. $display->did;
  }
  $style = skinr_style_array_to_string(skinr_get(NULL, $hook, $key));

  if (!empty($style)) {
    $output = '<div class="'. $style .'">'. $output .'</div>';
  }

  return $output;
}

/**
 * Render pane callback.
 */
function theme_panels_skinr_style_render_pane($content, $pane, $display) {
  return theme('panels_pane', $content, $pane, $display);
}

/**
 * Settings form callback.
 */
function panels_skinr_style_settings_form($settings, $panels_display = NULL, $region = NULL, $type = NULL) {
  // Return an empty form, and let skinr handle the rest.
  $form = array();
  return $form;
}

/**
 * @}
 */
