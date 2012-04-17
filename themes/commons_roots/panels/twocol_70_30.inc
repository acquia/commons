<?php // $Id $

/**
 * @file twocol_70_30.inc
 * Implementation of hook_panels_layouts()
 */
function acquia_commons_twocol_70_30_panels_layouts() {
  $items['twocol_70_30'] = array(
    'title' => t('Drupal Commons - Two column 70/30'),
    'icon' => 'twocol_70_30.png',
    'theme' => 'twocol_70_30',
    'theme arguments' => array('id', 'content'),
    'css' => 'twocol_70_30.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side'),
    ),
  );

  return $items;
}
