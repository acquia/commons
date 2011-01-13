<?php
// $Id: filefield.inc,v 1.1 2009/10/21 06:23:43 quicksketch Exp $

/**
 * @file
 * Insert support for FileField module.
 */

/**
 * Implementation of hook_insert_widgets().
 */
function filefield_insert_widgets() {
  return array(
    'filefield_widget' => array(
      'wrapper' => '.filefield-element',
      'fields' => array(
        'description' => 'input[name$="[description]"]',
      ),
    ),
  );
}
