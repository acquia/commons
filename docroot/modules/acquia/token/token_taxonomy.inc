<?php
// $Id: token_taxonomy.inc,v 1.3.4.3 2008/06/28 15:10:22 greggles Exp $

/**
 * @file
 * Implementations of token module hooks for the core taxonomy module.
 *
 * The token module requires specific hooks to be added to modules
 * so that those modules can return data about their objects to the
 * token API.  Until and unless token becomes a part of core, the
 * implementations of the token hooks for core modules are provided
 * in the token module itself.
 *
 * @ingroup token
 */

/**
 * Implementation of hook_token_values().
 */
function taxonomy_token_values($type, $object = NULL, $options = array()) {
  $values = array();
  switch ($type) {
    case 'taxonomy':
      $category = $object;
      $vid = $category->vid;
      $vocabulary = taxonomy_vocabulary_load($vid);

      $values['vid'] = $vid;
      $values['vocab'] = check_plain($vocabulary->name);
      $values['cat'] = check_plain($category->name);
      $values['tid'] = $category->tid;
      $values['vocab-raw'] = $vocabulary->name;
      $values['cat-raw'] = $category->name;

      break;
  }
  return $values;
}

/**
 * Implementation of hook_token_list().
 */
function taxonomy_token_list($type = 'all') {
  if ($type == 'taxonomy' || $type == 'all') {
    $tokens['taxonomy']['vid'] = t("The id number of the category's parent vocabulary.");
    $tokens['taxonomy']['vocab'] = t("The vocabulary that the page's first category belongs to.");
    $tokens['taxonomy']['cat'] = t('The name of the category.');
    $tokens['taxonomy']['tid'] = t('The id number of the category.');
    $tokens['taxonomy']['vocab-raw'] = t("The unfiltered vocabulary that the page's first category belongs to. WARNING - raw user input.");
    $tokens['taxonomy']['cat-raw'] = t('The unfiltered name of the category. WARNING - raw user input.');

    return $tokens;
  }
}