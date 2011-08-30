<?php
// $Id: views_slideshow.views.inc,v 1.1.2.1.2.1 2010/02/23 22:21:44 psynaptic Exp $

/**
 * @file
 * Defines the View Style Plugins for Views Slideshow module.
 */

/**
 * Implements hook_views_plugins().
 */
function views_slideshow_views_plugins() {
  return array(
    'style' => array(
      'slideshow' => array(
        'title' => t('Slideshow'),
        'help' => t('Display the results as a slideshow.'),
        'handler' => 'views_slideshow_plugin_style_slideshow',
        'theme' => 'views_slideshow',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'type' => 'normal',
        'parent' => 'list',
      ),
    ),
  );
}
