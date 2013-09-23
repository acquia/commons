<?php
/**
 * @file
 * commons_wysiwyg.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function commons_wysiwyg_filter_default_formats() {
  $formats = array();

  // Exported format: Filtered HTML.
  $formats['filtered_html'] = array(
    'format' => 'filtered_html',
    'name' => 'Filtered HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_html' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <em> <strong> <u> <cite> <blockquote> <code> <ul> <ol> <li> <dl> <dt> <dd> <h4> <h5> <h6>  <p> <br> <img> <strike>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
    ),
  );

  // Exported format: Full HTML.
  $formats['full_html'] = array(
    'format' => 'full_html',
    'name' => 'Full HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 1,
    'filters' => array(),
  );

  return $formats;
}
