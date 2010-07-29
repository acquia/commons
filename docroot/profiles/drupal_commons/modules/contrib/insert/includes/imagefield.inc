<?php
// $Id: imagefield.inc,v 1.3 2010/03/13 21:06:52 quicksketch Exp $

/**
 * @file
 * Insert support for ImageField module.
 */

/**
 * Implementation of hook_insert_widgets().
 */
function imagefield_insert_widgets() {
  return array(
    'imagefield_widget' => array(
      'wrapper' => '.filefield-element',
      'fields' => array(
        'alt' => 'input[name$="[alt]"], textarea[name$="[alt]"]',
        'title' => 'input[name$="[title]"], textarea[name$="[title]"]',
        'description' => 'input[name$="[description]"], textarea[name$="[description]"]',
      ),
    ),
  );
}
