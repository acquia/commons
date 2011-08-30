<?php
// $Id: textrender.inc,v 1.1.2.5 2009/10/30 13:55:59 dman Exp $
/**
 * @file Helper functions for imagecache_textactions
 * 
 * Static rendertext and dynamic caption functions
 * 
 * This is a rewrite of textactions to consolidate various text effects into a
 * new SVG-like syntax. Not compatible with earlier efforts. HOPEFULLY
 * compatible with broader imageapi efforts and signwriter, menuwriter usage
 * etc.
 * Quite simply, CSS is not good enough a syntax to do half the effects we want.
 * That's why we are doing images, right?
 * SVG however does have enough bells to make this worthwhile.
 * 
 * Contains a stub for imageapi functions : imageapi_image_create_text that may
 * be ported over to there if that makes sense.
 */

/**
 * Place text on top of the current canvas
 *
 * Implementation of imagecache_hook_form()
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function textactions_rendertext_form($action) {

  $defaults = array(
    'xpos' => 'left+10',
    'ypos' => 'bottom-10',
    'textstyle' => array(
      'fontfile' => drupal_get_path('module', 'imageapi_text') . '/fonts/liberation-fonts-1.04/LiberationSans-Regular.ttf',
      'style' => "font-size:12px;\nfill:#333333;\ntop:10px;\nright:10px;",
    ),
    'text' => 'Hello World!',
    'evaluate_text' => FALSE,
  );
  // Our 'textstyle' parameter is a nested array - reflecting the wiget fieldset structure
  // only because imagecache sets the form
  // #tree to true, and unsetting it doesn't work.
  
  $action = array_merge($defaults, (array)$action);
  $form = array(
    'textstyle' => imageapi_text_style_widget($action['textstyle']),
    
    'text' => array(
      '#type' => 'textarea',
      '#rows' => 7,
      '#title' => t('Text'),
      '#default_value' => $action['text'],
      '#description' => t('The text string. If you are using a WYSIWYG editor, you should disable it for this field!'),
      '#wysiwyg' => FALSE,
    ),
    'evaluate_text' => array(
      '#type' => 'checkbox',
      '#title' => t('Evaluate text as PHP code'),
      '#default_value' => $action['evaluate_text'],
      '#description' => t('If selected, the text will be treated as PHP code.'),
    ),
    'php_help' => array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE, 
      '#collapsed' => TRUE, 
      '#title' => t('PHP code help'),
      '#value' => file_get_contents(drupal_get_path('module', 'imagecache_text') .'/help/textrender_syntax.html'),
    ),
  );
  if (! user_access('administer site configuration')) {
    $form['evaluate_text']['#disabled'] = TRUE;
    $form['text']['#disabled'] = $action['evaluate_text']; // lock this if an admin has enabled evaluation.
    $form['evaluate_text']['#description'] = 'requires <b>administer site configuration</b> permissions.';
  }
  #$form['#tree'] = FALSE;
  #$form['textstyle']['#tree'] = FALSE;

  return $form;
}



/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_textactions_rendertext($element) {
  $data = $element['#value'];
  $style_atts = imageapi_text_parse_style($data['textstyle']['style']);
  return t("<em>\"<strong>@data</strong>\"</em><br/>%style<br/>%font", array(
    '@data'  => $data['text'], 
    '%style' => $data['textstyle']['style'], 
    '%font'  => basename($data['textstyle']['fontfile'])
  )) ;
}

/**
 * Place the text defined in the action onto the current background
 *
 * Implementation of hook_image()
 *
 * @param $image
 * @param $action
 */
function textactions_rendertext_image(&$image, $action = array()) {

  if (!empty($action['evaluate_text'])) {
    $text = textactions_evaluate_text($image, $action);
  }
  else {
    $text = $action['text'];
  }
  
  if (empty($text)) {
    // Do nothing, carry on
    return TRUE;
  }

  $style = imageapi_text_parse_style($action['textstyle']['style']);
  $fontfile = $action['textstyle']['fontfile'];

  // Calculate position by first creating a temp image 
  // containing the text and then accessing its dimensions.
  // Inefficient, but reliable.

  // $textimage is a placeholder that will get the image created in it - an object to work like the rest of the imageapi functions.
  // We really need to force the toolkit to GD, but even then it can't be merged back into imagemagick
  $textimage = (object) array(
    'toolkit' => $image->toolkit,
  );
  
  if (! imageapi_image_create_text($textimage, $text, $fontfile, $style) || empty($textimage->info) ) {
    drupal_set_message(t('Failed to generate text image using %toolkit. Not overlaying text.', array('%toolkit' => $textimage->toolkit )), 'error');
    return FALSE;
  }

  // $textimage should now have its size info available.
  // Calc the position on the canvas
  $xy = imagecache_actions_calculate_relative_position($image, $textimage, $style);
#dpm(get_defined_vars());
  return imageapi_image_overlay($image, $textimage, $xy['x'], $xy['y']);
}

