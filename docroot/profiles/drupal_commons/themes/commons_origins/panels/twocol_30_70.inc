<?php // $Id $

/**
 * @file twocol_70_30.inc
 * Implementation of hook_panels_layouts()
 */
function acquia_commons_twocol_30_70_panels_layouts() {
  $items['twocol_30_70'] = array(
    'title' => t('Acquia Commons - Two column 30/70'),
    'icon' => 'twocol_30_70.png',
    'theme' => 'twocol_30_70',
    'theme arguments' => array('id', 'content'),
    'css' => 'twocol_30_70.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side'),
    ),
  );

  return $items;
}
