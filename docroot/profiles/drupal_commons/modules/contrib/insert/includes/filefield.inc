<?php

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
