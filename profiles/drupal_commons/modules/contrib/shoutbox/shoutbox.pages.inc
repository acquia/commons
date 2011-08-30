<?php

/**
 * @file
 *   Page callbacks for the shoutbox module.
 */

/**
 * Admin settings form
 */
function shoutbox_admin_settings() {
  $form['display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display settings'),
    '#collapsible' => TRUE,
  );
  $form['display_settings']['shoutbox_max_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum amount of characters in a shout'),
    '#default_value' => variable_get('shoutbox_max_length', 255),
    '#size' => 5,
    '#required' => TRUE,
    '#description' => t('Set the amount of allowed characters per shout. Enter 0 for no limit. This will not affect existing shouts.'),
  );
  $form['display_settings']['shoutbox_showamount_block'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of posts to show in the block'),
    '#default_value' => variable_get('shoutbox_showamount_block', 10),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#description' => t('Set the number of shoutbox posts to show in the block.'),
  );
  $form['display_settings']['shoutbox_showamount_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of posts to show on the page'),
    '#default_value' => variable_get('shoutbox_showamount_page', 30),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#description' => t('Set the number of shoutbox posts to show on the page.'),
  );
  $form['display_settings']['shoutbox_ascending'] = array(
    '#type' => 'checkbox',
    '#title' => t('Post newest shouts on top'),
    '#default_value' => variable_get('shoutbox_ascending', 1),
    '#description' => t('When checked, new shouts will appear on the top instead of the bottom.'),
  );
  $form['display_settings']['shoutbox_widget_type'] = array(
    '#type' => 'radios',
    '#title' => t('Input form type'),
    '#default_value' => variable_get('shoutbox_widget_type', 'textfield'),
    '#description' => t('Choose the type of form widget used for entering a shout.'),
    '#options' => array(
      'textfield' => t('Textfield'),
      'textarea' => t('Textarea'),
    ),
  );
  $form['display_settings']['shoutbox_time_format'] = array(
    '#type' => 'select',
    '#title' => t('Time format'),
    '#default_value' => variable_get('shoutbox_time_format', 'ago'),
    '#description' => t('Choose the format which shout times will be rendered in.'),
    '#options' => array(
      'ago' => t('Time ago (1 hour 15 minutes ago)'),
      'small' => t('Small !time', array('!time' => '(' . format_date(time(), 'small') . ')')),
      'medium' => t('Medium !time', array('!time' => '(' . format_date(time(), 'medium') . ')')),
      'large' => t('Large !time', array('!time' => '(' . format_date(time(), 'large') . ')')),
    ),
  );
  $form['display_settings']['shoutbox_restrict_general_shouts'] = array(
    '#type' => 'checkbox',
    '#title' => t('Restrict general shouts'),
    '#default_value' => variable_get('shoutbox_restrict_general_shouts', 1),
    '#description' => t('When checked, shoutboxes outside of specific contexts will be restricted to general shouts. There are modules that utilize the Shoutbox API, such as Shoutbox group, that will enter shouts meant to only be displayed in certain locations. Checking this will insure that those shouts are only displayed by the modules responsible for creating them.'),
  );
  
  // Generate choices for profile fields
  if (module_exists('profile')) {
    $choices = array();
    $fields = db_query("SELECT name FROM {profile_fields} ORDER BY name ASC");
    while ($field = db_fetch_object($fields)) {
      $choices[$field->name] = $field->name;
    }
  
    $form['display_settings']['shoutbox_profile_name'] = array(
      '#type' => 'select',
      '#title' => t('Use profile field for user name'),
      '#options' => array(0 => '- None -') + $choices,
      '#default_value' => variable_get('shoutbox_profile_name', 0),
      '#description' => t('Select an existing custom profile field to use as the user name.'),
    );
  }
  else {
    $form['display_settings']['shoutbox_profile_name'] = array(
      '#type' => 'item',
      '#title' => t('Use profile field for user name'),
      '#description' => t('Enable the profile module to allow Shoutbox to use the user\'s real name instead of the username.'),
    );
  }

  $form['shoutbox_filter_format'] = _shoutbox_filter_form();
  $form['shoutbox_filter_format']['#collapsed'] = FALSE;
  $form['shoutbox_filter_format']['shoutbox_escape_html'] = array(
    '#type' => 'checkbox',
    '#title' => t('Escape all HTML & formatting'),
    '#default_value' => variable_get('shoutbox_escape_html', 1),
    '#description' => '<strong>' . t('Checking this will ignore the input format selected below, and escape all HTML from the shouts.') . '</strong>',
    '#weight' => -10,
  );

  $form['time_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Time settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['time_settings']['shoutbox_refresh'] = array(
    '#type' => 'textfield',
    '#title' => t('Auto refresh (in seconds)'),
    '#default_value' => shoutbox_get_refresh_rate(),
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('Shoutbox can be set to automatically refresh every x number of seconds.  Set to 0 to turn off the auto refresh.'),
  );
  $form['time_settings']['shoutbox_anonymous_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of minutes for which anonymous users may edit or delete their own posts'),
    '#default_value' => variable_get('shoutbox_anonymous_timeout', 20),
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('Anonymous users can edit or delete their post within this amount of time from it being posted, as long as they have the same IP address as when they posted it.  If you don\'t want shout editing and/or deleting, remove these permissions from Drupal\'s anonymous users role. Set 0 for no limit.'),
  );
  $form['time_settings']['shoutbox_registered_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of minutes for which registered users may edit or delete their own posts'),
    '#default_value' => variable_get('shoutbox_registered_timeout', 0),
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('Registered users can edit or delete their post within this amount of time from it being posted.  If you don\'t want editing and/or deleting, remove these permissions from Drupal\'s authenticated users role. Set 0 for no limit.'),
  );
  $form['time_settings']['shoutbox_expire'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of days after which shouts will be purged from the database'),
    '#default_value' => variable_get('shoutbox_expire', 0),
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('Shouts will be permanently deleted after the number of days specified.  Shouts will never expire when this is set to 0.'),
  );

  return system_settings_form($form);
}

/**
 * Validate the admin settings form
 */
function shoutbox_admin_settings_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['shoutbox_showamount_block'])) {
    form_set_error('shoutbox_showamount_block', t('Block amount must be numeric'));
  }
  
  if (!is_numeric($form_state['values']['shoutbox_showamount_page'])) {
    form_set_error('shoutbox_showamount_page', t('Page amount must be numeric'));
  }
  
  if (!is_numeric($form_state['values']['shoutbox_max_length'])) {
    form_set_error('shoutbox_max_length', t('Shoutbox length must be numeric'));
  }
  
  if (!is_numeric($form_state['values']['shoutbox_refresh'])) {
    form_set_error('shoutbox_refresh', t('Refresh setting must be a numeric value'));
  }
  
  if (!is_numeric($form_state['values']['shoutbox_anonymous_timeout'])) {
    form_set_error('shoutbox_anonymous_timeout', t('Anonymous timeout setting must be a numeric value'));
  }
  
  if (!is_numeric($form_state['values']['shoutbox_registered_timeout'])) {
    form_set_error('shoutbox_registered_timeout', t('Registered timeout setting must be a numeric value'));
  }
  
  if (!is_numeric($form_state['values']['shoutbox_expire'])) {
    form_set_error('shoutbox_expire', t('Expiration setting must be a numeric value'));
  }
}

/**
 * Shout delete confirmation form
 *
 * @param shout_id
 *   The shout id of the shout being edited.
 */
function shoutbox_delete_form(&$form_state, $shout) {
  theme('shoutbox_external_files');
  _shoutbox_sanitize_shout($shout);
  
  $form['shout_preview'] = array(
    '#type' => 'item',
    '#value' => theme('shoutbox_post', $shout),
  );
  $form['shout_id'] = array(
    '#type' => 'value',
    '#value' => $shout->shout_id,
  );
  $form = confirm_form($form, t('Are you sure you want to delete this shout?'), $_GET['destination']);
  return $form;
}

/**
 * Handle the delete form submission.
 */
function shoutbox_delete_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Confirm')) {
    if (is_numeric($form_state['values']['shout_id'])) {
      //  Load the shout
      $shout = shoutbox_load($form_state['values']['shout_id']);
      
      //  Delete the shout
      shoutbox_delete_shout($shout);
      
      drupal_set_message(t('Your shout was deleted.'));
      $form_state['redirect'] = '';
    }
    else {
      return drupal_not_found();
    }
  }
}

/**
 * Shout publish confirmation form
 *
 * @param shout_id
 *   The shout id of the shout being published.
 */
function shoutbox_publish_form(&$form_state, $shout) {
  theme('shoutbox_external_files');
  _shoutbox_sanitize_shout($shout);
  
  $form['shout_preview'] = array(
    '#type' => 'item',
    '#value' => theme('shoutbox_post', $shout),
  );
  $form['shout_id'] = array(
    '#type' => 'value',
    '#value' => $shout->shout_id,
  );
  $form = confirm_form($form, t('Are you sure you want to publish this shout?'), $_GET['destination']);
  return $form;
}

/**
 * Handle the publish form submission
 */
function shoutbox_publish_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Confirm')) {
    $form_state['redirect'] = '';
    return shoutbox_moderate_shout($form_state['values']['shout_id'], FALSE);
  }
}

/**
 * Shout unpublish confirmation form
 *
 * @param shout_id
 *   The shout id of the shout being unpublished.
 */
function shoutbox_unpublish_form(&$form_state, $shout) {
  theme('shoutbox_external_files');
  _shoutbox_sanitize_shout($shout);
  
  $form['shout_preview'] = array(
    '#type' => 'item',
    '#value' => theme('shoutbox_post', $shout),
  );
  $form['shout_id'] = array(
    '#type' => 'value',
    '#value' => $shout->shout_id,
  );
  
  $form = confirm_form($form, t('Are you sure you want to unpublish this shout?'), $_GET['destination']);
  return $form;
}

/**
 * Handle the unpublish form submission
 */
function shoutbox_unpublish_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Confirm')) {
    $form_state['redirect'] = '';
    return shoutbox_moderate_shout($form_state['values']['shout_id'], TRUE);
  }
}

/**
 * Form for editing shouts.
 *
 * @param shout_id
 *   The shout id of the shout being edited.
 */
function shoutbox_edit_form(&$form_state, $shout) {
  global $user;
  
  $form[] = array(
    '#type' => 'item',
    '#title' => t('Author'),
    '#value' => l($shout->nick, 'user/' . $shout->uid),
  );
  $form[] = array(
    '#type' => 'item',
    '#title' => t('Created'),
    '#value' => date('m/d/y h:i:sa', $shout->created),
  );
  $form[] = array(
    '#type' => 'item',
    '#title' => t('Changed'),
    '#value' => date('m/d/y h:i:sa', $shout->changed),
  );
  
  if (_shoutbox_user_access('administer shoutbox') || _shoutbox_user_access('moderate shoutbox')) {
    $form['moderate'] = array(
      '#type' => 'radios',
      '#title' => t('Moderation status'),
      '#default_value' => $shout->moderate,
      '#options' => array('published', 'not published'),
    );
  }  
    
  if (_shoutbox_user_access('edit own shouts', $shout)) {
    $max = variable_get('shoutbox_max_length', 255);
    $form['shout'] = array(
      '#type' => variable_get('shoutbox_widget_type', 'textfield'),
      '#title' => t('Shout'),
      '#default_value' => $shout->shout,
      '#cols' => 13,
      '#required' => TRUE,
      '#rows' => 7,
      '#maxlength' => $max ? $max : NULL,
    );

    $form['shout_id'] = array(
      '#type' => 'value',
      '#value' => $shout->shout_id,
    );
  }

  $form = confirm_form($form, '', $_GET['destination'], '', t('Update'), t('Cancel'));
  return $form;
}

/**
 * Handle the edit form submission
 *
 * @param $form_id
 *   The form ID of the form.
 * @param $form_values
 *   Form values.
 */
function shoutbox_edit_form_submit($form, &$form_state) {
  if (is_numeric($form_state['values']['shout_id'])) {
    // Load the existing shout
    $shout = shoutbox_load($form_state['values']['shout_id']);
  
    // Edit the shout object
    $shout->shout = $form_state['values']['shout'];
    $shout->moderate = $form_state['values']['moderate'];
    $shout->changed = time();
    
    // Alert other modules about the update
    shoutbox_invoke('edit', $shout, $a1 = NULL, $form_state);
    
    // Update the shout
    db_query("UPDATE {shoutbox} SET shout = '%s', moderate = %d, changed = %d WHERE shout_id = %d", $shout->shout, $shout->moderate, $shout->changed, $shout->shout_id);
    
    drupal_set_message(t('Your shout has been saved.'));
    $form_state['redirect'] = '';
  }
  else {
    return drupal_not_found();
  }
}
