<?php
// $Id: acquia_agent_drupal_version.inc,v 1.1 2008/12/30 16:51:45 pwolanin Exp $

/**
 * @file
 *   Include file to provide Acquia Drupal version number.
 *
 *   Used to tell Acquia Drupal and non-Acquia Drupal installations from each
 *   other. Version data here also used to inform users of updates and to detect
 *   file changes when running Acquia Drupal.
 */
 
/**
 * Is this an Acquia Drupal install?
 */
define('IS_ACQUIA_DRUPAL', FALSE);

/**
 * Acquia Drupal version information (only used if IS_ACQUIA_DRUPAL).
 */
define('ACQUIA_DRUPAL_VERSION' , 'ACQ_version_ACQ');
define('ACQUIA_DRUPAL_SERIES'  , 'ACQ_series_ACQ');
define('ACQUIA_DRUPAL_BRANCH'  , 'ACQ_branch_ACQ');
define('ACQUIA_DRUPAL_REVISION', 'ACQ_rev_ACQ');
