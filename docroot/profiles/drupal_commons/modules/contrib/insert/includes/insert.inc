<?php

/**
 * @file
 * Insert support for generic files.
 */

/**
 * Implementation of hook_insert_styles().
 */
function insert_insert_styles() {
  $insert_styles = array();
  $insert_styles['auto'] = array('label' => t('Automatic'), 'weight' => -20);
  $insert_styles['link'] = array('label' => t('Link to file'), 'weight' => -11);
  $insert_styles['image'] = array('label' => t('Original image'), 'weight' => -10);
  return $insert_styles;
}

/**
 * Implementation of hook_insert_content().
 */
function insert_insert_content($item, $style, $widget) {
  $style_name = $style['name'];

  if ($style_name == 'auto') {
    $info = @pathinfo($item['filepath']);
    if (in_array(strtolower($info['extension']), array('png', 'jpg', 'jpeg', 'gif'))) {
      $style_name = 'image';
    }
  }

  if ($style_name == 'image') {
    return theme('insert_image', $item, $widget);
  }
  else {
    return theme('insert_link', $item, $widget);
  }
}

/**
 * Preprocess variables for the insert-image.tpl.php file.
 */
function template_preprocess_insert_image(&$vars) {
  $vars['url'] = insert_create_url($vars['item']['filepath']);
  $vars['class'] = !empty($vars['widget']['insert_class']) ? $vars['widget']['insert_class'] : '';
  $image_info = @image_get_info($vars['item']['filepath']);
  $vars['width'] = isset($image_info['width']) ? $image_info['width'] : '';
  $vars['height'] = isset($image_info['height']) ? $image_info['height'] : '';
}

/**
 * Preprocess variables for the insert-link.tpl.php file.
 */
function template_preprocess_insert_link(&$vars) {
  $vars['url'] = insert_create_url($vars['item']['filepath']);
  $vars['class'] = !empty($vars['widget']['insert_class']) ? $vars['widget']['insert_class'] : '';
  $vars['name'] = $vars['item']['filename'];
}
