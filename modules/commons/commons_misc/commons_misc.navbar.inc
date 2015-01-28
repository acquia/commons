<?php

/**
 * @file
 * Navbar hooks implemented by the Commons Miscellaneous module.
 */

/**
 * Implements hook_navbar().
 */
function commons_misc_navbar() {
  $items = array();

  // Add a link to the official commons documentation.
  $items['documentation'] = array(
    '#type' => 'navbar_item',
    'tab' => array(
      '#type' => 'link',
      '#title' => t('Documentation'),
      '#href' => 'https://docs.acquia.com/commons',
      '#options' => array(
        'attributes' => array(
          'title' => t('Commons Documentation'),
          'class' => array('navbar-icon', 'navbar-icon-help'),
          'target' => '_blank',
        ),
      ),
    ),
    '#weight' => 20,
  );

  return $items;
}
