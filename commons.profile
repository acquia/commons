<?php

/**
 * @file
 * Enables modules and site configuration for a Commons site installation.
 */

/*
 * Define commons minimum execution time required to operate.
 */
define('DRUPAL_MINIMUM_MAX_EXECUTION_TIME', 120);

/*
 * Define commons minimum APC cache required to operate.
 */
define('COMMONS_MINIMUM_APC_CACHE', 96);

/**
 * Implements hook_admin_paths_alter().
 */
function commons_admin_paths_alter(&$paths) {
  // Avoid switching between themes when users edit their account.
  $paths['user'] = FALSE;
  $paths['user/*'] = FALSE;
}

/**
 * Implements hook_update_projects_alter().
 */
function commons_update_projects_alter(&$projects) {
  // Enable update status for the Commons profile.
  $modules = system_rebuild_module_data();
  // The module object is shared in the request, so we need to clone it here.
  $commons = clone $modules['commons'];
  $commons->info['hidden'] = FALSE;
  _update_process_info_list($projects, array('commons' => $commons), 'module', TRUE);
}

/**
 * Implements hook_hook_info().
 */
function commons_hook_info() {
  $hooks = array(
    'commons_entity_integration',
    'commons_entity_integration_alter',
  );

  return array_fill_keys($hooks, array('group' => 'commons'));
}

/**
 * Get Commons entity integration information.
 *
 * @param $entity_type
 *   (optional) The entity type to load, e.g. node or user.
 *
 * @return
 *   An associative array of entity integrations whose keys define the entity
 *   type for each integration and whose values contain the bundles which have
 *   been integrated. Each bundle is itself an associative array, whose keys
 *   define the type of integration to enable and whose values contain the
 *   status of the integration. TRUE = enabled, FALSE = disabled.
 */
function commons_entity_integration_info($entity_type = NULL, $cache = TRUE) {
  $info = &drupal_static(__FUNCTION__);
  if (!$info || !$cache) {
    $info = module_invoke_all('commons_entity_integration');
    drupal_alter('commons_entity_integration', $info);
  }
  if ($entity_type) {
    return isset($info[$entity_type]) ? $info[$entity_type] : array();
  }
  else {
    return $info;
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function commons_form_install_configure_form_alter(&$form, $form_state) {
  // Clear all non-error messages that might be set by enabled modules
  drupal_get_messages('status', TRUE);
  drupal_get_messages('completed', TRUE);

  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];

  $form['admin_account']['field_name_first'] = array(
    '#type' => 'textfield',
    '#title' => 'First name',
    '#weight' => -10,
  );

  $form['admin_account']['field_name_last'] = array(
    '#type' => 'textfield',
    '#title' => 'Last name',
    '#weight' => -9,
  );
    // Acquia features
  $form['server_settings']['acquia_description'] = array(
    '#type' => 'fieldset',
    '#title' => st('Acquia'),
    '#description' => st('The !an can supplement the functionality of Commons by providing enhanced site search (faceted search, content recommendations, content biasing, multi-site search, and others using the Apache Solr service), spam protection (using the Mollom service), and more.  A free 30-day trial is available.', array('!an' => l(t('Acquia Network'), 'http://acquia.com/products-services/acquia-network', array('attributes' => array('target' => '_blank'))))),
    '#weight' => -11,
  );
  $form['server_settings']['enable_acquia_connector'] = array(
    '#type' => 'checkbox',
    '#title' => 'Use Acquia Network Connector',
    '#default_value' => 1,
    '#weight' => -10,
    '#return_value' => 1,
  );
  $form['server_settings']['acquia_connector_modules'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Acquia Network Connector Modules',
    '#options' => array(
      'acquia_agent' => 'Acquia Agent',
      'acquia_search' => 'Acquia Search',
      'acquia_spi' => 'Acquia SPI',
    ),
    '#default_value' => array(
      'acquia_agent',
      'acquia_spi',
    ),
    '#weight' => -9,
    '#states' => array(
      'visible' => array(
        ':input[name="enable_acquia_connector"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['#submit'][] = 'commons_admin_save_fullname';
  $form['#submit'][] = 'commons_check_acquia_connector';
}

/**
 * Save the full name of the first user.
 */
function commons_admin_save_fullname($form_id, &$form_state) {
  $values = $form_state['values'];
  if (!empty($values['field_name_first']) || !empty($values['field_name_last'])) {
    $account = user_load(1);
    $account->field_name_first[LANGUAGE_NONE][0]['value'] = $values['field_name_first'];
    $account->field_name_last[LANGUAGE_NONE][0]['value'] = $values['field_name_last'];
    user_save($account);
    realname_update($account);
  }
}

/**
 * Check if the Acquia Connector box was selected.
 */
function commons_check_acquia_connector($form_id, &$form_state) {
  if (!empty($form_state['values']['enable_acquia_connector'])) {
    $selected_extras = variable_get('commons_selected_extras', array());

    $modules = $form_state['values']['acquia_connector_modules'];

    if (!empty($modules['acquia_agent'])) {
      $selected_extras['acquia_agent'] = TRUE;
    }

    if (!empty($modules['acquia_search'])) {
      $selected_extras['acquia_search'] = TRUE;
    }

    if (!empty($modules['acquia_spi'])) {
      $selected_extras['acquia_spi'] = TRUE;
    }

    variable_set('commons_selected_extras', $selected_extras);
  }
}
