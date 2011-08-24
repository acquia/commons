<?php

/**
 * @file
 *   Admin callbacks for commons_core
 */
 
/**
 * Admin settings form
 */
function commons_core_admin_settings() {
  $form = array();
  
  $form['login_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['login_settings']['commons_force_login'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force users to login'),
    '#default_value' => variable_get('commons_force_login', 0),
    '#description' => t('If checked, anonymous users will be redirected from all pages to a log in page. Select this setting if your Commons site must be closed to the public, such as a company intranet.'),
  );
  
  $form['login_settings']['commons_force_login_allowed_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Allowed paths'),
    '#default_value' => variable_get('commons_force_login_allowed_paths', ''),
    '#description' => t('If users are forced to login (by checking the previous checkbox), you may specify a list of paths which will not redirect to a login page. Use internal addresses, such as, node/123. Enter each path on a new line.'),
  );
  
  $form['group_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Group settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['group_settings']['commons_group_tab_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Group homepage tab'),
    '#default_value' => variable_get('commons_group_tab_title', 'Home'),
    '#description' => t('Specify what the group homepage tab title should be. If left empty, the tab title will be <i>View</i>.'),
  );
  
  $form['group_settings']['commons_search_group_title_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Line length limit for search widget'),
    '#default_value' => variable_get('commons_search_group_title_length', 30),
    '#description' => t('This value is used to truncate group names when being displayed in the site search widget, so that the search widget is no wider than the search field itself. If your theme has a narrower or wider search widget, you may wish to adjust the value in this field. If set to zero, there will be no limit.'),
  );
  
  $form['group_settings']['commons_force_unique_groups'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force unique group names'),
    '#default_value' => variable_get('commons_force_unique_groups', 1),
    '#description' => t('If checked, group names must be unique. This will not affect existing groups.'),
  );
  
  $form['group_settings']['commons_email_selective_group'] = array(
    '#type' => 'checkbox',
    '#title' => t('Alert users when added to a selective group'),
    '#default_value' => variable_get('commons_email_selective_group', 1),
    '#description' => t('If checked, an email alert will be sent to users that are added to groups that are marked as either invite-only or closed.'),
  );
  
  $form['group_settings']['commons_group_admin_edit_comments'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow group admins to edit all group comments'),
    '#default_value' => variable_get('commons_group_admin_edit_comments', 0),
    '#description' => t('If checked, group admins will have the ability to edit any comments on content items inside their groups.'),
  );
  
  $form['group_settings']['commons_group_prevent_open_voting'] = array(
    '#type' => 'checkbox',
    '#title' => t('Restrict voting to group members'),
    '#default_value' => variable_get('commons_group_prevent_open_voting', 0),
    '#description' => t('If checked, only group members will be able to vote on polls that are part of a given group.'),
  );
  
  $form['group_settings']['commons_group_prevent_open_commenting'] = array(
    '#type' => 'checkbox',
    '#title' => t('Restrict commenting to group members'),
    '#default_value' => variable_get('commons_group_prevent_open_commenting', 0),
    '#description' => t('If checked, only group members will be able to comment on nodes that are part of a given group.'),
  );

  return system_settings_form($form); 
}

/**
 * Validate the admin settings form
 */
function commons_core_admin_settings_validate(&$form, &$form_state) {
  // Make sure the group search title max length is numeric
  if (!is_numeric($form_state['values']['commons_search_group_title_length'])) {
    form_set_error('commons_search_group_title_length', t('The maximum title length must be a numeric value.'));
  }
}
