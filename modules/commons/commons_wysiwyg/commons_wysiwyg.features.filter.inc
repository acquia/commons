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
    'editor' => 'ckeditor',
    'editor_settings' => 'a:3:{s:7:"toolbar";a:1:{i:0;a:7:{i:0;a:2:{s:4:"name";s:6:"Format";s:5:"items";a:1:{i:0;s:6:"Format";}}i:1;a:2:{s:4:"name";s:4:"Text";s:5:"items";a:2:{i:0;s:4:"Bold";i:1;s:6:"Italic";}}i:2;a:2:{s:4:"name";s:5:"Lists";s:5:"items";a:2:{i:0;s:12:"BulletedList";i:1;s:12:"NumberedList";}}i:3;a:2:{s:4:"name";s:5:"Links";s:5:"items";a:2:{i:0;s:10:"DrupalLink";i:1;s:12:"DrupalUnlink";}}i:4;a:2:{s:4:"name";s:10:"Formatting";s:5:"items";a:2:{i:0;s:12:"RemoveFormat";i:1;s:10:"Blockquote";}}i:5;a:2:{s:4:"name";s:5:"Media";s:5:"items";a:1:{i:0;s:4:"file";}}i:6;a:2:{s:4:"name";s:5:"Tools";s:5:"items";a:2:{i:0;s:6:"Source";i:1;s:8:"Maximize";}}}}s:12:"image_upload";a:5:{s:6:"status";i:0;s:6:"scheme";s:6:"public";s:9:"directory";s:13:"inline-images";s:8:"max_size";s:0:"";s:14:"max_dimensions";a:2:{s:5:"width";s:0:"";s:6:"height";s:0:"";}}s:7:"plugins";a:1:{s:5:"style";a:1:{s:10:"style_list";a:0:{}}}}',
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
      'editor_align' => array(
        'weight' => 3,
        'status' => 1,
        'settings' => array(),
      ),
      'editor_caption' => array(
        'weight' => 4,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  // Exported format: Full HTML.
  $formats['full_html'] = array(
    'format' => 'full_html',
    'name' => 'Full HTML',
    'cache' => 1,
    'editor' => '',
    'editor_settings' => 'a:0:{}',
    'status' => 1,
    'weight' => 1,
    'filters' => array(),
  );

  return $formats;
}
