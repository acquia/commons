<?php // $Id: threecol_at_50_25_25.inc,v 1.1.2.2 2009/10/25 12:07:16 jmburnz Exp $
// adpativethemes.com

/**
 * @file twocol_at_50_25_25.inc
 * Implementation of hook_panels_layouts()
 */
function adaptivetheme_threecol_at_50_25_25_panels_layouts() {
  $items['threecol_at_50_25_25'] = array(
    'title' => t('Three column AT 50/25/25'),
    'icon' => 'threecol_at_50_25_25.png',
    'theme' => 'threecol_at_50_25_25',
    'theme arguments' => array('id', 'content'),
    'css' => 'threecol_at_50_25_25.css',
    'panels' => array(
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side'),
    ),
  );

  return $items;
}
