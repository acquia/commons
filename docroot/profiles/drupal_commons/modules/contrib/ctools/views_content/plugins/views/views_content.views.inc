<?php
// $Id: views_content.views.inc,v 1.2 2009/04/30 22:37:52 merlinofchaos Exp $

/**
 * @file
 * Contains Views plugin definitions for the panel pane display.
 */

/**
 * Implementation of hook_views_plugins
 */
function views_content_views_plugins() {
  return array(
    'display' => array(
      'panel_pane' => array(
        'title' => t('Content pane'),
        'help' => t('Is available as content for a panel or dashboard display.'),
        'handler' => 'views_content_plugin_display_panel_pane',
        'path' => drupal_get_path('module', 'views_content') . '/plugins/views',
        'theme path' => drupal_get_path('module', 'views') . '/theme',
        'theme' => 'views_view',
        'use ajax' => TRUE,
        'use pager' => TRUE,
        'use more' => TRUE,
        'accept attachments' => TRUE,
        'help topic' => 'display-pane',
      ),
    ),
  );
}
