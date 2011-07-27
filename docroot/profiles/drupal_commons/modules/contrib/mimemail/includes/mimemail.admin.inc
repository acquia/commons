<?php

/**
 * @file
 * Admin settings pages for sending Mime-encoded emails.
 */

/**
 * Administration settings.
 *
 * @return
 *   The administration from.
 */
function mimemail_admin_settings() {

  // override the smtp_library value if mimemail is chosen to handle all mail
  // this will cause drupal_mail to call mimemail()
  if (variable_get('mimemail_alter', 0)) {
    if (variable_get('smtp_library', '') != drupal_get_filename('module', 'mimemail')) {
      variable_set('smtp_library', drupal_get_filename('module', 'mimemail'));
    }
  }
  elseif (variable_get('smtp_library', '') == drupal_get_filename('module', 'mimemail')) {
    variable_del('smtp_library');
  }

  // Check for the existence of a mail.css file in the default theme folder.
  $theme = variable_get('theme_default', NULL);
  $mailstyle = drupal_get_path('theme', $theme) . '/mail.css';
  // Disable site style sheets including option if found.
  if (is_file($mailstyle)) {
    variable_set('mimemail_sitestyle', 0);
    $disable_sitestyle = TRUE;
  }

  $engines = mimemail_get_engines();

  $form = array();
  $form['mimemail']['mimemail_name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Sender name'),
    '#default_value' => variable_get('mimemail_name', variable_get('site_name', 'Drupal')),
    '#size'          => 60,
    '#maxlength'     => 128,
    '#description'   => t('The name that all site e-mails will be from when using default engine.'),
  );
  $form['mimemail']['mimemail_mail'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Sender e-mail address'),
    '#default_value' => variable_get('mimemail_mail', variable_get('site_mail', ini_get('sendmail_from'))),
    '#size'          => 60,
    '#maxlength'     => 128,
    '#description'   => t('The e-mail address that all site e-mails will be from when using default engine.'),
  );
  $form['mimemail']['mimemail_alter'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use mime mail for all messages'),
    '#default_value' => variable_get('mimemail_alter', 0),
    '#description'   => t('Use the mime mail module to deliver all site messages.  With this option, system emails will have styles and formatting'),
  );
  $form['mimemail']['mimemail_simple_address'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use simple address format'),
    '#default_value' => variable_get('mimemail_simple_address', 0),
    '#description' => t('Use the simple format of user@example.com for all email addresses.'),
  );
  $form['mimemail']['mimemail_sitestyle'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Include site style sheets'),
    '#default_value' => variable_get('mimemail_sitestyle', 1),
    '#description'   => t('Gather all style sheets when no mail.css found in the default theme directory.'),
    '#disabled'      => $disable_sitestyle,
  );

  $filter_format = variable_get('mimemail_format', FILTER_FORMAT_DEFAULT);
  $form['mimemail']['mimemail_format'] =  filter_form($filter_format, NULL, array("mimemail_format"));

  $form['mimemail']['mimemail_textonly'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Plaintext email only'),
    '#default_value' => variable_get('mimemail_textonly', 0),
    '#description'   => t('This option disables the use of email messages with graphics and styles.  All messages will be converted to plain text.'),
  );

  $form['mimemail']['incoming'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Advanced Settings'),
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['mimemail']['incoming']['mimemail_incoming'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Process incoming messages posted to this site'),
    '#default_value' => variable_get('mimemail_incoming', 0),
    '#description'   => t('This is an advanced setting that should not be enabled unless you know what you are doing'),
  );
  $form['mimemail']['incoming']['mimemail_key'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Message validation string'),
    '#default_value' => variable_get('mimemail_key', md5(rand())),
    '#required'      => TRUE,
    '#description'   => t('This string will be used to validate incoming messages.  It can be anything, but must be used on both sides of the transfer'),
  );

  // hide the settings if only 1 engine is available
  if (count($engines) == 1) {
    variable_set('mimemail_engine', key($engines));
    $form['mimemail_engine'] = array(
        '#type'          => 'hidden',
        '#title'         => t('E-mail engine'),
        '#default_value' => variable_get('mimemail_engine', 'mail'),
        '#options'       => $engines,
        '#description'   => t('Choose an e-mail engine for sending mails from your site.')
    );
  }
  else {
    $form['mimemail_engine'] = array(
        '#type'          => 'select',
        '#title'         => t('E-mail engine'),
        '#default_value' => variable_get('mimemail_engine', 'mail'),
        '#options'       => $engines,
        '#description'   => t('Choose an e-mail engine for sending mails from your site.')
    );
  }

  if (variable_get('mimemail_engine', 0)) {
    $settings = module_invoke(variable_get('mimemail_engine', 'mail'), 'mailengine', 'settings');
    if ($settings) {
        $form['mimemail_engine_settings'] = array(
          '#type'        => 'fieldset',
          '#title'       => t('Engine specific settings'),
      );
      foreach ($settings as $name => $value) {
        $form['mimemail_engine_settings'][$name] = $value;
      }
    }
  }
  else {
    drupal_set_message(t('Please choose a mail engine.'), 'error');
  }

  return system_settings_form($form);
}
