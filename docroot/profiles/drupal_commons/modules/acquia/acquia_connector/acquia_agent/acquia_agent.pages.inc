<?php
// $Id: acquia_agent.pages.inc,v 1.5 2009/04/02 20:00:55 pwolanin Exp $

/**
 * @file
 *   Acquia Agent configuration page.
 */

/**
 * Menu callback for settings page.
 */
function acquia_agent_settings_page() {

  $identifier = acquia_agent_settings('acquia_identifier');
  $key = acquia_agent_settings('acquia_key');
  $change = FALSE;

  // Check $_POST so we don't send extra XML-RPC requests during form submission.
  if ($identifier && $key && empty($_POST)) {
    // Check our connection to the Acquia Network and validity of the crenditials.
    $acquia_network_address = acquia_agent_settings('acquia_network_address');
    if (acquia_agent_valid_credentials($identifier, $key, $acquia_network_address)) {
      drupal_set_message(t('You are successfully communicating with the Acquia Network. To change the subscription keys, click the %alter button.', array('%alter' => t('Alter settings'))), 'status', FALSE);
    }
    else {
      $error_message = acquia_agent_connection_error_message();
      drupal_set_message($error_message, 'error', FALSE);
      $change = TRUE;
    }
  }
  $link = '';
  $subscription = acquia_agent_settings('acquia_subscription_data');
  // Check $_POST so we don't tell people status about previously stored
  // credentials during form submission.
  if ($subscription['active'] && empty($_POST)) {
    $title = t("Subscription active. Click here to go to the Acquia Network.");
    $link .= "<p>". l($title, $subscription['href']) ."</p>\n";
  }

  $output = $link . drupal_get_form('acquia_agent_settings_form', $change);
  $output .= drupal_get_form('acquia_agent_communication_form');
  return $output;
}

/**
 * Settings form builder function.
 */
function acquia_agent_communication_form($form_state) {
  $ssl_available = (in_array('ssl', stream_get_transports(), TRUE) && !defined('ACQUIA_DEVELOPMENT_NOSSL'));

  $form['acquia_agent_verify_peer'] = array(
    '#type' => 'radios',
    '#title' => t('Enhanced SSL security'),
    '#default_value' => (int) (variable_get('acquia_agent_verify_peer', 0) && $ssl_available),
    '#options' => array(0 => t('Disabled'), 1 => t('Enabled')),
    '#description' => t('If enabled the Acquia Connector will attempty to verify Acquia server identities before sending data.  May cause communication to fail, however, depending on your local configuration.'),
    '#disabled' => !$ssl_available,

  );

  if ($ssl_available) {
    $form['acquia_agent_verify_peer']['#description'] .= ' <div class="ok">'. t('PHP has SSL support and may support this feature.') .'</div>';
  }
  else {
    $form['acquia_agent_verify_peer']['#description'] .= ' <div class="error">'. t('PHP does not have SSL support.') .'</div>';
  }

  return system_settings_form($form);
}

/**
 * Settings form builder function.
 */
function acquia_agent_settings_form($form_state, $change = FALSE) {
  $identifier = acquia_agent_settings('acquia_identifier');
  $key = acquia_agent_settings('acquia_key');

  // Alow changing settings if requested in the API, via a form button or
  // there is at least one value missing.
  $change = $change || isset($form_state['change_settings']) || (empty($identifier) || empty($key));

  // Help for copying the identifier and key.
  $copy_help = t('Copy from <a href="@subscriptions-overview">your subscriptions overview on the Acquia Network</a>.', array('@subscriptions-overview' => 'http://acquia.com/network/dashboard/subscription'));

  $form['acquia_identifier'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia subscription identifier'),
    '#default_value' => $identifier,
    // Disable field if not changing values, making this a display only field.
    '#disabled' => !$change,
    '#description' => t('Identifier of this website (a public key).') . ($change ? ' '. $copy_help : ''),
    '#required' => $change,
  );
  $form['acquia_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Acquia subscription key'),
    '#default_value' => $key,
    // Disallow access if not changing values. Only the identifier is shown then.
    '#access' => $change,
    '#description' => t('Key of this website (a private key).') . ($change ? ' '. $copy_help : ''),
    '#required' => $change,
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#validate' => array('acquia_agent_set_validate'),
    '#submit' => array('acquia_agent_set_submit'),
    // Only show this button if changing values.
    '#access' => $change,
  );
  $form['buttons']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete subscription information '),
    '#submit' => array('acquia_agent_delete_submit'),
    // Only show this button if changing values and we have existing settings to delete.
    '#access' => ($change && (!empty($identifier) || !empty($key))),
  );
  $form['buttons']['change'] = array(
    '#type' => 'submit',
    '#value' => t('Alter settings'),
    '#submit' => array('acquia_agent_change_submit'),
    // Only show this button if not already changing settings.
    '#access' => !$change,
  );
  return $form;
}

/**
 * Validate acquia_agent_settings form submissions.
 */
function acquia_agent_set_validate($form, &$form_state) {
  // Trim all input to get rid of possible whitespace pasted from the website.
  foreach ($form_state['values'] as $key => $value) {
    $form_state['values'][$key] = trim($value);
  }
  $identifier = $form_state['values']['acquia_identifier'];
  $key = $form_state['values']['acquia_key'];

  // Don't make the XML-RPC call with empty values.
  if (!empty($identifier) && !empty($key)) {
    if (!acquia_agent_valid_credentials($identifier, $key)) {
      $error_message = acquia_agent_connection_error_message();
      form_error($form, $error_message);
    }
  }
}

/**
 * Save acquia_agent_settings form submissions.
 */
function acquia_agent_set_submit($form, &$form_state) {
  variable_set('acquia_key', $form_state['values']['acquia_key']);
  variable_set('acquia_identifier', $form_state['values']['acquia_identifier']);
  drupal_set_message(t('The Acquia configuration options have been saved.'));
  // Check subscription and send a heartbeat to Acquia Network via XML-RPC.
  // Our status gets updated locally via the return data.
  acquia_agent_check_subscription();
  cache_clear_all();
}

/**
 * Delete acquia_agent settings.
 */
function acquia_agent_delete_submit($form, &$form_state) {
  variable_del('acquia_key');
  variable_del('acquia_identifier');
  variable_del('acquia_network_address');
  variable_del('acquia_subscription_data');
  drupal_set_message(t('Your Acquia configuration has been deleted.'));
  cache_clear_all();
}

/**
 * Submit function for the "Change settings" button.
 */
function acquia_agent_change_submit($form, &$form_state) {
  // Go back to the form and let the user change settings there.
  $form_state['change_settings'] = TRUE;
  $form_state['rebuild'] = TRUE;
}


/**
 * Override of the theme callback for the modules form.
 *
 * Used add extra rows when $form['description][$key]['#extra'] is set.
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @ingroup themeable
 */
function acquia_agent_system_modules($form) {
  if (isset($form['confirm'])) {
    return drupal_render($form);
  }

  // Individual table headers.
  $header = array();
  $header[] = array('data' => t('Enabled'), 'class' => 'checkbox');
  if (module_exists('throttle')) {
    $header[] = array('data' => t('Throttle'), 'class' => 'checkbox');
  }
  $header[] = t('Name');
  $header[] = t('Version');
  $header[] = t('Description');

  // Pull package information from module list and start grouping modules.
  $modules = $form['validation_modules']['#value'];
  foreach ($modules as $module) {
    if (!isset($module->info['package']) || !$module->info['package']) {
      $module->info['package'] = t('Other');
    }
    $packages[$module->info['package']][$module->name] = $module->info;
  }
  ksort($packages);

  // Display packages.
  $output = '';
  foreach ($packages as $package => $modules) {
    $rows = array();
    foreach ($modules as $key => $module) {
      $row = array();
      $description = drupal_render($form['description'][$key]);
      if (isset($form['status']['#incompatible_modules_core'][$key])) {
        unset($form['status'][$key]);
        $status = theme('image', 'misc/watchdog-error.png', t('incompatible'), t('Incompatible with this version of Drupal core'));
        $description .= '<div class="incompatible">'. t('This version is incompatible with the !core_version version of Drupal core.', array('!core_version' => VERSION)) .'</div>';
      }
      elseif (isset($form['status']['#incompatible_modules_php'][$key])) {
        unset($form['status'][$key]);
        $status = theme('image', 'misc/watchdog-error.png', t('incompatible'), t('Incompatible with this version of PHP'));
        $php_required = $form['status']['#incompatible_modules_php'][$key];
        if (substr_count($php_required, '.') < 2) {
          $php_required .= '.*';
        }
        $description .= '<div class="incompatible">'. t('This module requires PHP version @php_required and is incompatible with PHP version !php_version.', array('@php_required' => $php_required, '!php_version' => phpversion())) .'</div>';
      }
      else {
        $status = drupal_render($form['status'][$key]);
      }
      $row[] = array('data' => $status, 'class' => 'checkbox');
      if (module_exists('throttle')) {
        $row[] = array('data' => drupal_render($form['throttle'][$key]), 'class' => 'checkbox');
      }

      // Add labels only when there is also a checkbox.
      if (isset($form['status'][$key])) {
        $row[] = '<strong><label for="'. $form['status'][$key]['#id'] .'">'. drupal_render($form['name'][$key]) .'</label></strong>';
      }
      else {
        $row[] = '<strong>'. drupal_render($form['name'][$key]) .'</strong>';
      }

      $row[] = array('data' => drupal_render($form['version'][$key]), 'class' => 'version');
      $row[] = array('data' => $description, 'class' => 'description');

      // Add the extra info inline above the affected module row
      if (isset($form['description'][$key]['#extra'])) {
        $extra_row[] = array(
          'data' => $form['description'][$key]['#extra'],
          'colspan' => '4',
          'style' => 'padding:0',
        );
        $rows[] = array(
          'style' => 'padding:0',
          'data' => $extra_row,
        );
      }

      $rows[] = $row;
    }
    $fieldset = array(
      '#title' => t($package),
      '#collapsible' => TRUE,
      '#collapsed' => ($package == 'Core - required'),
      '#value' => theme('table', $header, $rows, array('class' => 'package')),
    );
    $output .= theme('fieldset', $fieldset);
  }

  $output .= drupal_render($form);
  return $output;
}
