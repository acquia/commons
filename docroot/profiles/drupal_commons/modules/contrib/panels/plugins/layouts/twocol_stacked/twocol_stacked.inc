<?php
// $Id: twocol_stacked.inc,v 1.1.2.2 2010/01/13 06:25:15 merlinofchaos Exp $

// Plugin definition
$plugin = array(
  'title' => t('Two column stacked'),
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
