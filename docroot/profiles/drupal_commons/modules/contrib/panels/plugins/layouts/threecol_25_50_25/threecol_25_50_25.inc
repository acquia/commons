<?php
// $Id: threecol_25_50_25.inc,v 1.1.2.3 2010/01/13 06:25:15 merlinofchaos Exp $

/**
 * implementation of hook_panels_layouts
 */
// Plugin definition
$plugin = array(
  'title' => t('Three column 25/50/25'),
  'icon' => 'threecol_25_50_25.png',
  'theme' => 'panels_threecol_25_50_25',
  'theme arguments' => array('id', 'content'),
  'css' => 'threecol_25_50_25.css',
  'panels' => array(
    'left' => t('Left side'),
    'middle' => t('Middle column'),
    'right' => t('Right side')
  ),
);

