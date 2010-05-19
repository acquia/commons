<?php
// $Id: threecol_33_34_33_stacked.inc,v 1.1.2.1 2008/12/16 21:27:58 merlinofchaos Exp $


/**
 * Implementation of hook_panels_layouts().
 */
function panels_threecol_33_34_33_stacked_panels_layouts() {
  $items['threecol_33_34_33_stacked'] = array(
    'title' => t('Three column 33/34/33 stacked'),
    'icon' => 'threecol_33_34_33_stacked.png',
    'theme' => 'panels_threecol_33_34_33_stacked',
    'css' => 'threecol_33_34_33_stacked.css',
    'panels' => array(
      'top' => t('Top'),
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
