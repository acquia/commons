<?php
// $Id: user_relationships_ui.admin.inc,v 1.1.2.23 2010/05/13 19:15:57 alexk Exp $

/**
 * @file
 * User Relationships admin settings and config forms
 */
module_load_include('inc', 'user_relationships_ui', 'user_relationships_ui.admin_actions');

/**
 * Main settings
 */
function user_relationships_ui_settings() {
  $form['general'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('General'),
    '#weight' => -10,
  );
  $form['general']['user_relationships_allow_multiple'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Allow multiple relationships'),
    '#description'    => t('Give users the option to create more than one relationship to each other.'),
    '#default_value'  => variable_get('user_relationships_allow_multiple', 1),
  );
  $form['general']['user_relationships_show_direct_links'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Show direct request links'),
    '#description'    => t("Show a 'create relationship with...' link for each available relationship type."),
    '#default_value'  => variable_get('user_relationships_show_direct_links', 1),
  );
  $form['general']['user_relationships_show_user_pictures'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Show user pictures in relationship pages'),
    '#description'    => t("This will show user's picture next to the user name on My relationships pages."),
    '#default_value'  => variable_get('user_relationships_show_user_pictures', 0),
  );
  $form['general']['user_relationships_allow_auto_approve'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Allow users to auto approve'),
    '#description'    => t('This will provide an option for users to set an "auto-approve" option to automatically approve to all requested relationships.'),
    '#default_value'  => variable_get('user_relationships_allow_auto_approve', 0),
  );
  $form['general']['user_relationships_relationships_per_page'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Relationships per page'),
    '#size'           => 4,
    '#description'    => t('Number of relationships to show per page. If set to 0 all will be shown.'),
    '#default_value'  => variable_get('user_relationships_relationships_per_page', 16),
    '#validate'       => array('user_relationships_setting_validation' => array(array(
      'is_numeric' => array('msg' => t('The relationships per page setting is not an integer'))
    )))
  );
  if (module_exists('privatemsg')) {
      $form['privatemsg'] = array(
        '#type'   => 'fieldset',
        '#title'  => t('Private messages'),
        '#description'    => t('Allow Privatemsg to work only between related users. Note that this setting does not affect the site\'s admin user.'),
      );
      $form['privatemsg']['user_relationships_restrict_privatemsg'] = array(
        '#type'           => 'radios',
        '#title'          => t('Restrict Private Messaging to only related users'),
        '#default_value'  => variable_get('user_relationships_restrict_privatemsg', 'all'),
        '#options' => array(
          'all' => t('Allow sending messages to all users'),
          'all_overridable' => t('Allow sending messages to all users, users have option to accept messages only from their confirmed relationships'),
          'relationships' => t('Allow sending messages only to confirmed relationships (You probably should enable "Suggest only relationships" below)'),
        ),
      );
      $form['privatemsg']['user_relationships_privatemsg_autocomplete_alter'] = array(
        '#type'           => 'checkbox',
        '#title'          => t('Suggest only relationships in To: field'),
        '#description'    => t("Show only user's relationships when autocompleting the To: field."),
        '#default_value'  => variable_get('user_relationships_privatemsg_autocomplete_alter', 0),
      );
      $form['privatemsg']['roles'] = array(
        '#title' => t('Role exclusions'),
        '#type' => 'fieldset',
        '#description' => t('You may choose which roles are allowed to send message to all users, even if it is otherwise restricted.'),
        'user_relationships_privatemsg_role_exclusions' => array(
          '#type' => 'checkboxes',
          '#options' => user_roles(TRUE),
          '#default_value' => variable_get('user_relationships_privatemsg_role_exclusions', array()),
        ),
      );
  }
  $form['positioning'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('AJAX Popup Positioning'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Some themes may require repositioning of AJAX confirmation dialogs. You may use these controls to set where the popup appears on the page or in relation to the mouse cursor.')
  );
  $form['positioning']['user_relationships_enable_ajax_popups'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show AJAX confirmation popups'),
    '#default_value' => variable_get('user_relationships_enable_ajax_popups', 1),
    '#description' => t('Other popup settings below will only take effect if popups are enabled.')
  );
  $form['positioning']['user_relationships_position'] = array(
    '#type' => 'select',
    '#title' => t("Elaboration form's css position"),
    '#default_value' => variable_get('user_relationships_position', 'absolute'),
    '#options' => array(
      'absolute' => t('Mouse cursor'),
      'fixed' => t('Fixed'),
    ),
    '#description' => t('Sets the css <em>position</em> property of AJAX confirmation popups.'),
  );
  $form['positioning']['user_relationships_left'] = array(
    '#type' => 'textfield',
    '#title' => t("Elaboration form's css left value"),
    '#default_value' => variable_get('user_relationships_left', '0'),
    '#size' => 4,
    '#description' => t("Sets the css <em>left</em> property of AJAX confirmation popups. Try the value of 0 for 'Mouse cursor', or 0.5 for 'Fixed'. You may enter a distance in pixels, or as a % using a value 1 or less. Relative positioning requires a fixed position."),
  );
  $form['positioning']['user_relationships_top'] = array(
    '#type' => 'textfield',
    '#title' => t("Elaboration form's css top value"),
    '#default_value'  => variable_get('user_relationships_top', '0'),
    '#size' => 4,
    '#description' => t("Sets the css <em>top</em> property of AJAX confirmation popups. Try the value of 0 for 'Mouse cursor', or 0.4 for 'Fixed'. You may enter a distance in pixels, or as a % using a value 1 or less. Relative positioning requires a fixed position."),
  );
  
  $replaceables = array(
    '!requester',
    '!requestee',
    '%relationship_name',
    '%relationship_plural_name',
    '!pending_relationship_requests',
  );

  $form['messages'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Messages'),
    '#weight'       => 0,
    '#description'  => t('Notifications to users. Replaceable tokens are: @replaceables', array('@replaceables' => implode($replaceables, ', '))),
  );
  
  $form['messages']['user_relationships_requests_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to relationship requests'),
    '#default_value'  => variable_get('user_relationships_requests_link', 'relationships/requests'),
    '#description' => t("replaces !pending_relationship_requests in messages such as what is shown to the user after login, change only if your requests list isn't 'relationships/requests'"),
  );

  $default_messages = _user_relationships_ui_default_messages(array());
  _user_relationships_ui_message_settings_form($form['messages'], $default_messages);

  return system_settings_form($form);
}


/**
 * Relationship type edit page.
 */
function user_relationships_ui_type_edit(&$form_state, $relationship_type = NULL) {
  $form['name'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Name'),
    '#maxlength'      => 255,
    '#default_value'  => $relationship_type->name,
    '#description'    => t("Example: buddy, friend, coworker, spouse."),
    '#required'       => TRUE,
    '#weight'         => -10,
  );
  $form['plural_name'] = array(
    '#type'           => 'textfield',
    '#title'          => t('Plural name'),
    '#maxlength'      => 255,
    '#default_value'  => $relationship_type->plural_name,
    '#description'    => t("Example: buddies, friends, coworkers, spouses."),
    '#weight'         => -9,
  );
  $form['requires_approval'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Requires Approval'),
    '#default_value'  => (isset($relationship_type->requires_approval) ? $relationship_type->requires_approval : 1),
    '#description'    => t('Check this if the requestee must approve the relationship'),
    '#weight'         => -8,
  );
  $form['expires_val'] = array(
    '#title'          => t('Request expires in'),
    '#field_suffix'   => t('days'),
    '#type'           => 'textfield',
    '#size'           => 4,
    '#default_value'  => isset($relationship_type->expires_val) ? $relationship_type->expires_val : 0,
    '#description'    => t('After how many days should a request of this type be removed? (0 for never)'),
    '#weight'         => -7,
  );
  $form['is_oneway'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('This is a one-way relationship'),
    '#default_value'  => $relationship_type->is_oneway,
    '#description'    => t('Check this if this relationship should only go one way (ex Manager, Subscriber)'),
    '#weight'         => -6,
  );
  $form['is_reciprocal'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('This one-way relationship can be reciprocated'),
    '#default_value'  => $relationship_type->is_reciprocal,
    '#description'    => t('Check if this one-way relationship can go either way'),
    '#weight'         => -5,
  );
  $form['roles'] = array(
    '#title' => t('Role access'),
    '#type' => 'fieldset',
    '#description' => t('You may choose which roles are allowed to request this relationship. If none are selected, all roles are allowed.'),
    'roles' => array(
      '#type' => 'checkboxes',
      '#options' => user_roles(TRUE),
      '#default_value' => isset($relationship_type->roles) ? $relationship_type->roles : array(),
    ),
  );
  $form['roles_receive'] = array(
    '#title' => t('Role receive access'),
    '#type' => 'fieldset',
    '#description' => t('You may choose which roles are allowed to receive this relationship. If none are selected, all roles are allowed to receive the relationship.'),
    'roles_receive' => array(
      '#type' => 'checkboxes',
      '#options' => user_roles(TRUE),
      '#default_value' => is_array($relationship_type->roles_receive) ? $relationship_type->roles_receive : array(),
    ),
  );
  $form['rtid'] = array(
    '#type'   => 'value',
    '#value'  => (int)$relationship_type->rtid,
  );
  $form['action'] = array(
    '#type'   => 'value',
    '#value'  => ($relationship_type ? 'edit' : 'add'),
  );

  $form['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Submit'),
    '#weight' => 10,
  );

  return $form;
}


/**
 * Relationship type delete page.
 */
function user_relationships_ui_type_delete(&$form_state, $relationship_type = NULL) {
  if ($relationship_type) {
    $form['rtid'] = array(
      '#type'   => 'value',
      '#value'  => (int)$relationship_type->rtid,
    );

    return confirm_form(
      $form,
      t('Are you sure you want to delete %name?', array('%name' => ur_tt("user_relationships:rtid:$relationship_type->rtid:name", $relationship_type->name))),
      'admin/user/relationships',
      t('This action cannot be undone.'),
      t('Delete'), t('Cancel')
    );
  }
  else {
    drupal_set_message(user_relationships_ui_get_message('non_existent_type'));
    drupal_goto('admin/user/relationships');
  }
}
