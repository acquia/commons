<?php
// $Id: twocol_stacked.inc,v 1.1.2.3 2010/06/22 15:54:25 merlinofchaos Exp $

// Plugin definition
$plugin = array(
  'title' => t('Two column stacked'),
  'category' => t('Columns: 2'),
  'icon' => 'twocol_stacked.png',
  'theme' => 'panels_twocol_stacked',
  'css' => 'twocol_stacked.css',
  'panels' => array(
    'top' => t('Top'),
    'left' => t('Left side'),
    'right' => t('Right side'),
    'bottom' => t('Bottom')
  ),
);
