<?php

/**
 * @file
 *  Contains administration pages.
 */

/**
 * Settings form for this module.
 *
 */
function og_invite_link_admin() {
  $form = array();
  //Provide an option for site administrators to choose
  //how long the invitations are valid. Expired ones are
  //just purged at cron.
  $options = array(1 => 1, 2 => 2, 5 => 5, 10 => 10, 15 => 15, 30 => 30, 45 => 45, 60 => 60, 90 => 90, 0 => t('Never'));
  $form['og_invite_link_expiration'] = array(
    '#type' => 'select',
    '#title' => t('Valid for number of days'),
    '#description' => t('Select the number of days after which the invitations will become expired.'),
    '#default_value' => variable_get('og_invite_link_expiration', 30),
    '#options' => $options,
  );
  return system_settings_form($form);
}