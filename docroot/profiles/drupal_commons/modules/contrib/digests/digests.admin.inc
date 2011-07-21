<?php

/**
 * @file
 *   Administrative settings for the Activity Digests module.
 */

/**
 * Administrative options.
 */
function digests_admin($form_state) {
  $form = array();
  $form['digests_send_time'] = array(
    '#type' => 'select',
    '#title' => t('Send digests after'),
    '#description' => t('Select an hour of the day'),
    '#options' => _digests_get_hours(),
    '#default_value' => variable_get('digests_send_time', 18),
    '#required' => TRUE,
  );
  $form['digests_local'] = array(
    '#type' => 'radios',
    '#title' => t('Send digests'),
    '#default_value' => variable_get('digests_local', 'local'),
    '#options' => array(
      'local' => t("using users' local timezones"),
      'site' => t("using the site's timezone"),
    ),
    '#required' => TRUE,
  );
  $form['digests_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('The maximum number of users to which to send digests each time cron runs'),
    '#description' => t('Leave this field blank or enter 0 to process all users.'),
    '#default_value' => variable_get('digests_limit', 250),
    '#size' => 11,
    '#maxlength' => 15,
  );
  $form['digests_css'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS to include in digest emails'),
    '#description' => t('If this field is empty, Mime Mail will use its default CSS handling.') .' '.
      t('This behavior is to look for a mail.css file in your default theme.') .' '.
      t('If no mail.css is found, all CSS files in your default theme will be used.'),
    '#rows' => 8,
    '#default_value' => variable_get('digests_css', ''),
    '#access' => user_access('set custom CSS for digests'),
  );
  $form['digests_logo'] = array(
    '#type' => 'textfield',
    '#title' => t('Logo image'),
    '#description' => t('The path to your logo image from your Drupal root.') .' '.
      t('If you use this, the logo will appear at the top of digest emails.'),
    '#default_value' => variable_get('digests_logo', ''),
  );
  if (module_exists('token')) {
    $form['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['token_help']['global'] = array(
      '#title' => t('Global'),
      '#description' => t('You can use these tokens in the email header or footer.'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['token_help']['global']['help'] = array(
      '#value' => theme('token_help', 'global'),
    );
    $form['token_help']['user'] = array(
      '#title' => t('Recipient user'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['token_help']['user']['help'] = array(
      '#value' => theme('token_help', 'user'),
    );
  }
  $form['digests_header'] = array(
    '#type' => 'textarea',
    '#title' => t('Email header'),
    '#rows' => 2,
    '#default_value' => variable_get('digests_header', ''),
  );
  $form['digests_footer'] = array(
    '#type' => 'textarea',
    '#title' => t('Email footer'),
    '#rows' => 2,
    '#default_value' => variable_get('digests_footer', ''),
  );
  return system_settings_form($form);
}

/**
 * Validates the administrative options.
 */
function digests_admin_validate($form, $form_state) {
  $v = $form_state['values']['digests_limit'];
  if (!empty($v) && (!is_numeric($v) || $v < 0)) {
    form_set_error('digests_limit', t('The maximum number of users to which to send digests per cron run must be a positive integer.'));
  }
}

/**
 * Returns a list of the hours of the day formatted by the site's preference.
 */
function _digests_get_hours() {
  $range = range(0, 23);
  $date_format = variable_get('date_format_long', 'l, F j, Y - H:i');
  $hour_format = 'H'; // e.g. 00
  foreach (array('a', 'A', 'g', 'h') as $c) {
    if (strpos($date_format, $c) !== FALSE) {
      $hour_format = 'ga'; // e.g. 12am
      break;
    }
  }
  $options = array();
  foreach ($range as $num) {
    $options[$num] = date($hour_format, mktime($num, 0, 0));
  }
  return $options;
}
