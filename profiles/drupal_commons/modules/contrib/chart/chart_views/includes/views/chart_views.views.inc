<?php
// $Id;
/**
 * @file
 * Chart API Views Integration
 */

/**
* Implementation of hook_views_plugins().
*
* Define chart_views style for Views.
*/
function chart_views_views_plugins() {
  // Views support is only possible if Views Calc module is enabled. It
  // is responsible for turn the Views values into a aggregates.
  if (!module_exists('views_calc')) {
    return;
  }

  return array(
    'module' => 'chart_views',
    'style'  => array(     // Declare the chart_views style plugin
      'chart_views' => array(
        'handler'         => 'chart_views_plugin_style_chart',
        'help'            => t('Displays the content in several chart styles.'),
        'path'            => drupal_get_path('module', 'chart_views') .'/includes/views',
        'parent'          => 'parent',
        'title'           => t('Google chart'),
        'type'            => 'normal',
        'uses fields'     => TRUE,
        'uses options'    => TRUE,
        'uses row plugin' => FALSE,
      ),
    )
  );
}
