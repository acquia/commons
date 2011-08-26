<?php // $Id$

/**
 * @todo placeholder settings page.
 */
function skinr_admin() {
  $output = '';
  return $output;
}

/**
 * Skinr settings export form.
 */
function skinr_export_form(&$form_state, $theme = NULL) {
  $form = array();
  $themes = list_themes();

  if ($theme) {
    // Export an individual theme.

    $theme = str_replace('-', '_', $theme);
    $code = '$skinr = '. var_export(skinr_get($theme), TRUE) .';';
    $lines = substr_count($code, "\n") + 1;

    $form['theme'] = array(
      '#type' => 'textfield',
      '#title' => t('Theme'),
      '#value' => $themes[$theme]->info['name'],
      '#disabled' => TRUE,
    );

    $form['skinr_settings'] = array(
      '#type' => 'textarea',
      '#title' => t('Skinr settings'),
      '#default_value' => $code,
      '#rows' => min($lines, 150),
    );
  }
  else {
    // Give the option for which theme to export.
    $options = array();
    ksort($themes);
    $current_theme = skinr_current_theme();

    // Put default theme at the top.
    $options[$current_theme] = $themes[$current_theme]->info['name'].' ['. t('default') .']';

    foreach ($themes as $theme) {
      if ($theme->name == $current_theme) {
        // Do nothing.
      }
      elseif ($theme->status) {
        $options[$theme->name] = $theme->info['name'] .' ['. t('enabled') .']';
      }
      else {
        $options[$theme->name] = $theme->info['name'];
      }
    }

    $form['theme'] = array(
      '#type' => 'select',
      '#title' => t('Theme'),
      '#description' => t('Theme to export the skinr settings for.'),
      '#options' => $options,
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Export'),
    );
  }

  return $form;
}

/**
 * Validation handler for skinr settings export form.
 */
function skinr_export_form_validate(&$form, &$form_state) {
  if (!empty($form_state['values']['theme']) && preg_match('/[^a-zA-Z0-9_]/', $form_state['values']['theme'])) {
    form_error($form['theme'], t('The theme name must be alphanumeric and can contain underscores only.'));
  }
}

/**
 * Submit handler for skinr settings export form.
 */
function skinr_export_form_submit(&$form, &$form_state) {
  drupal_goto('admin/settings/skinr/export/'. str_replace('_', '-', $form_state['values']['theme']));
}

/**
 * Skinr settings import form.
 */
function skinr_import_form(&$form_state) {
  $form = array();

  $options = array();
  $themes = list_themes();
  ksort($themes);
  $current_theme = skinr_current_theme();

  // Put default theme at the top.
  $options[$current_theme] = $themes[$current_theme]->info['name'].' ['. t('default') .']';

  foreach ($themes as $theme) {
    if ($theme->name == $current_theme) {
      // Do nothing.
    }
    elseif ($theme->status) {
      $options[$theme->name] = $theme->info['name'] .' ['. t('enabled') .']';
    }
    else {
      $options[$theme->name] = $theme->info['name'];
    }
  }

  $form['theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#options' => $options,
    '#required' => TRUE,
  );
  $form['skinr_settings'] = array(
    '#type' => 'textarea',
    '#title' => t('Skinr settings'),
    '#description' => t('Paste skinr settings here.'),
    '#rows' => 16,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

/**
 * Validation handler for Skinr settings import form.
 */
function skinr_import_form_validate(&$form, &$form_state) {
  $skinr = '';
  ob_start();
  eval($form_state['values']['skinr_settings']);
  ob_end_clean();

  foreach ($skinr as $module => $setting) {
    if (!is_array($setting)) {
      // Error.
      form_error($form['skinr_settings'], t('These are not valid Skinr settings.'));
    }
    foreach ($setting as $key => $value) {
      if (!is_array($value)) {
        // Error.
        form_error($form['skinr_settings'], t('These are not valid Skinr settings.'));
      }
    }
  }

  if (!empty($form_state['values']['theme']) && preg_match('/[^a-zA-Z0-9_]/', $form_state['values']['theme'])) {
    form_error($form['theme'], t('The theme name must be alphanumeric and can contain underscores only.'));
  }

  $form_state['skinr'] = &$skinr;
}

/**
 * Submit handler for skinr settings import form.
 */
function skinr_import_form_submit(&$form, &$form_state) {
  variable_set('skinr_'. $form_state['values']['theme'], $form_state['skinr']);

  drupal_set_message(t('Skinr settings for the theme %theme have been saved.', array('%theme' => $form_state['values']['theme'])));
  drupal_goto('admin/settings/skinr');
}