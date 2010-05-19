<?php // $Id: sixcol_6x16.inc,v 1.1.2.2 2009/10/25 12:07:16 jmburnz Exp $
// adpativethemes.com

/**
 * @file sixcol_60x16.inc
 * Implementation of hook_panels_layouts()
 */
function adaptivetheme_sixcol_6x16_panels_layouts() {
  $items['sixcol_6x16'] = array(
    'title' => t('Six column AT 6x16'),
    'icon' => 'sixcol_6x16.png',
    'theme' => 'sixcol_6x16',
    'theme arguments' => array('id', 'content'),
    'css' => 'sixcol_6x16.css',
    'panels' => array(
      'col1' => t('Column 1'),
      'col2' => t('Column 2'),
      'col3' => t('Column 3'),
      'col4' => t('Column 4'),
      'col5' => t('Column 5'),
      'col6' => t('Column 6'),
    ),
  );

  return $items;
}
