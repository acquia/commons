<?php
// $Id$

/**
 * @file
 *   Rules integration.
 */

/**
 * Implementation of hook_rules_condition_info().
 */
function fbss_privacy_rules_condition_info() {
  return array(
    'fbss_privacy_is_private' => array(
      'label' => t('Status was posted as private'),
      'arguments' => array(
        'status' => array('type' => 'facebook_status', 'label' => t('The status')),
      ),
      'module' => 'Facebook-style Statuses',
    ),
  );
}

/**
 * Checks if the status was posted to the user's own profile.
 */
function fbss_privacy_is_private($status) {
  return !empty($status->private);
}

