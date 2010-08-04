<?php
// $Id: tagadelic_views.views.inc,v 1.1.2.1 2009/01/30 00:12:49 indytechcook Exp $
/**
 * @file
 * Main views plugin, creates Tagadelic as an option under the Style options when a view is created.
 * Created for Drupal 6 by Mark Fairbairn
 * Reviewed by Nathan Burles
 */
function tagadelic_views_views_plugins() {
  $path = drupal_get_path('module', 'tagadelic_views');
  $views_path = drupal_get_path('module', 'views');
  
  return array(
    'module' => 'tagadelic_views', // This just tells our themes are elsewhere.
    'display' => array(
      // Parents are not really displays, just needed so the files can
      // be included.
      'parent' => array(
        'no ui' => TRUE,
        'handler' => 'views_plugin_display',
        'path' => "$views_path/plugins",
        'parent' => '',
      ),
      'page' => array(
        'no ui' => TRUE,
        'handler' => 'views_plugin_display_page',
        'path' => "$views_path/plugins",
        'parent' => 'parent',
      ),
      'block' => array(
        'no ui' => TRUE,
        'handler' => 'views_plugin_display_block',
        'path' => "$views_path/plugins",
        'parent' => 'parent',
      ),
      'attachment' => array(
        'no ui' => TRUE,
        'handler' => 'views_plugin_display_attachment',
        'path' => "$views_path/plugins",
        'parent' => 'parent',
      ),
    ),
    'style' => array(
      'parent' => array(
        // this isn't really a display but is necessary so the file can
        // be included.
        'no ui' => TRUE,
        'handler' => 'views_plugin_style',
        'path' => "$views_path/plugins",
        'parent' => '',
      ), 
      'tagadelic_views' => array(
      'title' => t('Tagadelic'),
      'help' => t('TODO'),
      'handler' => 'views_plugin_style_tagadelic',
      'path' => "$path/includes",
      'theme' => 'views_view_tagadelic',
      'theme file' => 'theme.inc',
      'theme path' => "$path/theme",
      'uses row plugin' => FALSE,
      'uses fields' => FALSE,
      'uses options' => TRUE,
      'type' => 'normal',
      ),
    ),    
  );
}