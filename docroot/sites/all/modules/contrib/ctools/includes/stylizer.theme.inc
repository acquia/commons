<?php
// $Id: stylizer.theme.inc,v 1.1.2.2 2010/02/17 01:04:50 merlinofchaos Exp $

/**
 * @file
 * Contains theme registry and theme implementations for the content types.
 */

/**
 * Implementation of hook_theme to load all content plugins and pass thru if
 * necessary.
 */
function ctools_stylizer_theme(&$theme) {
  $theme['ctools_stylizer_color_scheme_form'] = array(
    'arguments' => array('form' => NULL),
    'file' => 'includes/stylizer.inc',
  );

  $theme['ctools_stylizer_preview_form'] = array(
    'arguments' => array('form' => NULL),
    'file' => 'includes/stylizer.inc',
  );

  $theme['ctools_style_icon'] = array(
    'arguments' => array('image' => NULL, 'title' => NULL),
    'file' => 'includes/stylizer.inc',
  );

}

