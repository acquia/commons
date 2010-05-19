<?php // $Id: fourcol_4x25.inc,v 1.1.2.2 2009/10/25 12:07:16 jmburnz Exp $
// adpativethemes.com

/**
 * @file fourcol_4x25.inc
 * Implementation of hook_panels_layouts()
 */
function adaptivetheme_fourcol_4x25_panels_layouts() {
  $items['fourcol_4x25'] = array(
    'title' => t('Four column AT 4x25'),
    'icon' => 'fourcol_4x25.png',
    'theme' => 'fourcol_4x25',
    'theme arguments' => array('id', 'content'),
    'css' => 'fourcol_4x25.css',
    'panels' => array(
      'col1' => t('Column 1'),
      'col2' => t('Column 2'),
      'col3' => t('Column 3'),
      'col4' => t('Column 4'),
    ),
  );

  return $items;
}
