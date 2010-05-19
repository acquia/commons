<?php
// $Id: callbacks.inc,v 1.2.4.9 2009/07/21 18:28:13 merlinofchaos Exp $
/**
 * @file callbacks.inc
 * Minor menu callbacks for Panels helpers.
 */

/**
 * A central administrative page for Panels.
 */
function panels_admin_page() {
  return theme('panels_dashboard');
}

function template_preprocess_panels_dashboard(&$vars) {
  drupal_add_css(panels_get_path('css/panels-dashboard.css'));
  $vars['image_path'] = url(panels_get_path('images'));

  $vars['panel_page_description'] = t('Panel pages can be used as landing pages. They have a URL path, accept arguments and can have menu entries.');
  $vars['panel_override_description'] = t('Customize an already existing page within your site.');
  if (module_exists('page_manager')) {
    $vars['new_panel_page'] = l(t('Panel page'), 'admin/build/pages/add');
  }
  else {
    $vars['new_panel_page'] = '<b>' . t('Panel page') . '</b><br /><em>' . t('You must activate the page manager module for this functionality.') . '</em>';
    $vars['new_panel_override'] = '<em>' . t('You must activate the page manager module for this functionality.') . '</em>';
  }

  $vars['panel_node_description'] = t('Panel nodes are node content and appear in your searches, but are more limited than panel pages.');
  if (module_exists('panels_node')) {
    $vars['new_panel_node'] = l(t('Panel node'), 'node/add/panel');
  }
  else {
    $vars['new_panel_node'] = '<b>' . t('Panel node') . '</b><br /><em>' . t('You must activate the panel node module for this functionality.') . '</em>';
  }

  $vars['panel_mini_description'] = t('Mini panels are small content areas exposed as blocks, for when you need to have complex block layouts or layouts within layouts.');
  if (module_exists('panels_mini')) {
    $vars['new_panel_mini'] = l(t('Mini panel'), 'admin/build/panel-mini/add');
  }
  else {
    $vars['new_panel_mini'] = '<b>' . t('Mini panel') . '</b><br /><em>' . t('You must activate the Mini panels module for this functionality.') . '</em>';
  }

  if (module_exists('page_manager')) {
    module_load_include('inc', 'page_manager', 'page_manager.admin');
    $tasks = page_manager_get_tasks_by_type('page');
    $pages = array('operations' => array());

    page_manager_get_pages($tasks, $pages);
    $count = 0;
    $rows = array();
    foreach ($pages['rows'] as $id => $info) {
      $rows[] = array(
        'data' => array(
          $info['data']['title'],
          $info['data']['operations'],
        ),
        'class' => $info['class'],
      );

      // Only show 10.
      if (++$count >= 10) {
        break;
      }
    }

    $vars['pages'] = theme('table', array(), $rows, array('class' => 'panels-manage'));
    $vars['pagelink'] = l(t('Go to list'), 'admin/build/pages');
  }
  else {
    $vars['pages'] = '<p>' . t('You must install and activate the Page Manager module to manage pages. This module is located within the Chaos Tools Suite.') . '</p>';
  }

  if (module_exists('panels_mini')) {
    // Load all mini panels and their displays.
    $panel_minis = panels_mini_load_all();
    $count = 0;
    $rows = array();

    foreach ($panel_minis as $panel_mini) {
      $rows[] = array(
        check_plain($panel_mini->title),
        array(
          'data' => l(t('Edit'), "admin/build/panel-mini/$panel_mini->name/edit-general"),
          'class' => 'page-manager-page-operations',
        ),
      );

      // Only show 10.
      if (++$count >= 10) {
        break;
      }
    }

    if ($rows) {
      $vars['minis'] = theme('table', array(), $rows, array('class' => 'panels-manage'));
    }
    else {
      $vars['minis'] = '<p>' . t('There are no mini panels.') . '</p>';
    }
    $vars['minilink'] = l(t('Go to list'), 'admin/build/panel-mini');
  }
  else {
    $vars['minis'] = '<p>' . t('You must install and activate the Mini Panels module to manage them.') . '</p>';
    $vars['minilink'] = '';
  }
}

function panels_admin_settings_page() {
  $form = array();
  if (module_exists('page_manager')) {
    foreach (page_manager_get_tasks() as $task) {
      if ($function = ctools_plugin_get_function($task, 'admin settings')) {
        $function($form);
      }
    }
  }

  ctools_include('content');
  foreach (ctools_get_content_types() as $content) {
    if ($function = ctools_plugin_get_function($content, 'admin settings')) {
      $function($form);
    }
  }

  if (empty($form)) {
    return array('#value' => t('There are currently no settings to change, but additional plugins or modules may provide them in the future.'));
  }

  return system_settings_form($form);
}

/**
 * Settings for panel contexts created by the page manager.
 */
function panels_admin_panel_context_page() {
  panels_load_include('common');
  return drupal_get_form('panels_common_settings', 'panels_page');
}
