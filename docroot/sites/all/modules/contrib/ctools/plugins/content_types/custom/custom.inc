<?php
// $Id: custom.inc,v 1.9.2.3 2010/01/29 20:18:25 merlinofchaos Exp $

/**
 * @file
 * Custom content type.
 *
 * This content type is nothing more than a title and a body that is entered
 * by the user and run through standard filters. The information is stored
 * right in the config, so each custom content is unique.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'no title override' => TRUE,
  'title' => t('New custom content'),
  'icon' => 'icon_block_custom.png',
  'description' => t('Create a completely custom piece of HTML content.'),
  // Make this a top level category so it appears higher in UIs that support
  // that.
  'top level' => TRUE,
  'category' => t('Custom'),
  'defaults' => array('admin_title' => '', 'title' => '', 'body' => '', 'format' => FILTER_FORMAT_DEFAULT, 'substitute' => TRUE),
  // render callback is automatically deduced:
  // 'render callback' => 'ctools_custom_content_type_render',
  'js' => array('misc/autocomplete.js', 'misc/textarea.js', 'misc/collapse.js'),
  'all contexts' => TRUE,
);

/**
 * Output function for the 'custom' content type. Outputs a custom
 * based on the module and delta supplied in the configuration.
 */
function ctools_custom_content_type_render($subtype, $conf, $args, $contexts) {
  static $delta = 0;

  $block          = new stdClass();
  $block->subtype = ++$delta;
  $block->title   = filter_xss_admin($conf['title']);
  $block->content = check_markup($conf['body'], $conf['format'], FALSE);

  // Add keyword substitutions if we were configured to do so.
  if (!empty($contexts) && !empty($conf['substitute'])) {
    $block->content = ctools_context_keyword_substitute($block->content, array(), $contexts);
  }
  return $block;
}

/**
 * Callback to provide the administrative title of the custom content.
 */
function ctools_custom_content_type_admin_title($subtype, $conf) {
  $output = t('Custom');
  $title = !empty($conf['admin_title']) ? $conf['admin_title'] : $conf['title'];
  if ($title) {
    $output = t('Custom: @title', array('@title' => $title));
  }
  return $output;
}

/**
 * Callback to provide administrative info. In this case we'll render the
 * content as long as it's not PHP, which is too risky to render here.
 */
function ctools_custom_content_type_admin_info($subtype, $conf) {
  $block = new stdClass();
  $block->title = filter_xss_admin($conf['title']);
  // We don't want to render php output on preview here, because if something is
  // wrong the whole display will be borked. So we check to see if the php
  // evaluator filter is being used, and make a temporary change to the filter
  // so that we get the printed php, not the eval'ed php.
  $php_filter = FALSE;
  foreach (filter_list_format($conf['format']) as $filter) {
    if ($filter->module == 'php') {
      $php_filter = TRUE;
      break;
    }
  }
  // If a php filter is active, just print the source, but only if the current
  // user has access to the actual filter.
  if ($php_filter) {
    if (!filter_access($conf['format'])) {
      return NULL;
    }
    $block->content = '<pre>'. check_plain($conf['body']) .'</pre>';
  }
  else {
    $block->content = check_markup($conf['body'], $conf['format']);
  }
  return $block;
}

/**
 * Returns an edit form for the custom type.
 */
function ctools_custom_content_type_edit_form(&$form, &$form_state) {
  $conf = $form_state['conf'];
  $form['admin_title'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($conf['admin_title']) ? $conf['admin_title'] : '',
    '#title' => t('Administrative title'),
    '#description' => t('This title will be used administratively to identify this pane. If blank, the regular title will be used.'),
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#default_value' => $conf['title'],
    '#title' => t('Title'),
  );

  $form['body_field']['body'] = array(
    '#title' => t('Body'),
    '#type' => 'textarea',
    '#default_value' => $conf['body'],
  );
  $parents[] = 'format';
  $form['body_field']['format'] = filter_form($conf['format'], 1, $parents);

  if (!empty($form_state['contexts'])) {
    $form['substitute'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use context keywords'),
      '#description' => t('If checked, context keywords will be substituted in this content.'),
      '#default_value' => !empty($conf['substitute']),
    );
    $form['contexts'] = array(
      '#title' => t('Substitutions'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $rows = array();
    foreach ($form_state['contexts'] as $context) {
      foreach (ctools_context_get_converters('%' . check_plain($context->keyword) . ':', $context) as $keyword => $title) {
        $rows[] = array(
          check_plain($keyword),
          t('@identifier: @title', array('@title' => $title, '@identifier' => $context->identifier)),
        );
      }
    }
    $header = array(t('Keyword'), t('Value'));
    $form['contexts']['context'] = array('#value' => theme('table', $header, $rows));
  }

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function ctools_custom_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
