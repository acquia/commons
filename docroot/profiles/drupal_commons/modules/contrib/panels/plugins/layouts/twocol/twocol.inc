<?php
// $Id: twocol.inc,v 1.1.2.2 2010/01/13 06:25:15 merlinofchaos Exp $

// Plugin definition
$plugin = array(
  'title' => t('Two column'),
  'icon' => 'twocol.png',
  'theme' => 'panels_twocol',
  'css' => 'twocol.css',
  'panels' => array(
    'left' => t('Left side'),
    'right' => t('Right side')
  ),
);
