<?php // $Id: fivecol_5x20.inc,v 1.1.2.2 2009/10/25 12:07:16 jmburnz Exp $
// adpativethemes.com

/**
 * @file fivecol_5x20.inc
 * Implementation of hook_panels_layouts()
 */
function adaptivetheme_fivecol_5x20_panels_layouts() {
  $items['fivecol_5x20'] = array(
    'title' => t('Five column AT 5x20'),
    'icon' => 'fivecol_5x20.png',
    'theme' => 'fivecol_5x20',
    'theme arguments' => array('id', 'content'),
    'css' => 'fivecol_5x20.css',
    'panels' => array(
      'col1' => t('Column 1'),
      'col2' => t('Column 2'),
      'col3' => t('Column 3'),
      'col4' => t('Column 4'),
      'col5' => t('Column 5'),
    ),
  );

  return $items;
}
