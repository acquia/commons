<?php
// $Id: onecol.inc,v 1.1.2.2 2010/01/13 06:25:15 merlinofchaos Exp $

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Single column'),
  'icon' => 'onecol.png',
  'theme' => 'panels_onecol',
  'css' => 'onecol.css',
  'panels' => array('middle' => t('Middle column')),
);
