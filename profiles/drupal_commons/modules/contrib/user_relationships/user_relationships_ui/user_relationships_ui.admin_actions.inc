<?php
// $Id: user_relationships_ui.admin_actions.inc,v 1.1.2.16 2010/09/12 18:59:54 alexk Exp $
/**
 * @file
 * User Relationships admin submit handlers
 */

/**
 * Validate the submitted relationship type
 */
function user_relationships_ui_type_edit_validate($form, &$form_state) {
  // My god this is ugly
  if (
    (isset($form_state['values']['rtid']) &&
      db_result(db_query(
        "SELECT name FROM {user_relationship_types}
         WHERE LOWER(name) = LOWER('%s')
           AND rtid != %d",
        $form_state['values']['name'], $form_state['values']['rtid'])
      )
    ) ||
    (!isset($form_state['values']['rtid']) &&
      db_result(db_query("SELECT name FROM {user_relationship_types} WHERE LOWER(name) = LOWER('%s')", $form_state['values']['name']))
    )
  ) {
    form_set_error('name', t('%name has already been used.', array('%name' => $form_state['values']['name'])));
  }

  $expire = $form_state['values']['expires_val'];
  if (!is_numeric($expire) || (int)$expire < 0) {
    form_set_error('expires_val', t('Expiration period must be an integer greater than or equal to 0.'));
  }
}

/***
 * Generic settings validation.
 */
function user_relationships_ui_setting_validation($element, $validations) {
  foreach ($validations as $validation => $info) {
    $arguments = array($element['#value']);
    if (isset($info['valid_options'])) {
      $arguments[] = $info['valid_options'];
    }

    $valid = function_exists($validation) && call_user_func_array($validation, $arguments);
    $valid = !$valid ? ($validation == 'is_positive' && is_numeric($arguments) && (int)$arguments > 0) : FALSE;
    $valid = !$valid ? ($validation == 'is_non_negative' && is_numeric($arguments) && (int)$arguments > -1) : FALSE;

    if (!$valid) {
      form_set_error($element['#name'], $info['msg']);
    }
  }
}

/**
 * Process the relationship edit page form submission.
 */
function user_relationships_ui_type_edit_submit($form, &$form_state) {
  $relationship_type = (object)$form_state['values'];
  if ($form_state['values']['action'] == 'add') {
    //#348025 when editing a type, make sure that two-way relationships are not left as reciprocal, just in case, as the UI allows it.
    if (!$relationship_type->is_oneway) {
      $relationship_type->is_reciprocal = 0;
    }
    drupal_write_record('user_relationship_types', $relationship_type);

    // Update strings for translation
    _user_relationships_ui_update_translations($relationship_type);

    $form_state['values']['rtid'] = $relationship_type->rtid;
    _user_relationships_invoke('insert', $relationship_type, TRUE);

    drupal_set_message(t('Relationship %name has been added.', array('%name' => $relationship_type->name)));
    watchdog(
      'u_relationship',
      'User Relationships form: relationship %name added.', array('%name' => $relationship_type->name),
      WATCHDOG_NOTICE,
      l(t('view'), 'admin/user/user_relationship/types/'. $relationship_type->rtid .'/edit')
    );
  }
  else {
    //#348025 when editing a type, make sure that two-way relationships are not left as reciprocal, just in case, as the UI allows it.
    if (!$relationship_type->is_oneway) {
      $relationship_type->is_reciprocal = 0;
    }
    drupal_write_record('user_relationship_types', $relationship_type, 'rtid');

    // Update strings for translation
    _user_relationships_ui_update_translations($relationship_type);

    _user_relationships_invoke('update', $relationship_type, TRUE);

    drupal_set_message(t('Relationship %name has been updated.', array('%name' => $relationship_type->name)));
    watchdog(
      'u_relationship',
      'User Relationships form: relationship %name updated.', array('%name' => $relationship_type->name),
      WATCHDOG_NOTICE,
      l(t('view'), 'admin/user/relationships/'. $relationship_type->rtid .'/edit')
    );
  }
  
  //save role permissions for this rtype
  db_query('DELETE FROM {user_relationship_type_roles} WHERE rtid = %d', $relationship_type->rtid);
  if ($form_state['values']['roles']) {
    $role_record = new StdClass;
    $role_record->rtid = $relationship_type->rtid;
    foreach ($form_state['values']['roles'] as $rid => $selected) {
      if ($rid == $selected) {
        $role_record->rid = $selected;
        drupal_write_record('user_relationship_type_roles', $role_record);
      }
    }
  }

  //save role receive permissions for this rtype
  db_query('DELETE FROM {user_relationship_type_roles_receive} WHERE rtid = %d', $relationship_type->rtid);
  if ($form_state['values']['roles_receive']) {
    $role_receive_record = new StdClass;
    $role_receive_record->rtid = $relationship_type->rtid;
    foreach ($form_state['values']['roles_receive'] as $rid => $selected) {
      if ($rid == $selected) {
        $role_receive_record->rid = $selected;
        drupal_write_record('user_relationship_type_roles_receive', $role_receive_record);
      }
    }
  }

  user_relationships_types_load(TRUE);
  menu_rebuild();

  $form_state['redirect'] = 'admin/user/relationships';
}


/**
 * Process relationship delete form submission.
 */
function user_relationships_ui_type_delete_submit($form, &$form_state) {
  $relationship_type = user_relationships_type_load($form_state['values']['rtid']);

  db_query("DELETE FROM {user_relationship_types} WHERE rtid = %d", $relationship_type->rtid);
  db_query("DELETE FROM {user_relationships} WHERE rtid = %d", $relationship_type->rtid);
  db_query('DELETE FROM {user_relationship_type_roles} WHERE rtid = %d', $relationship_type->rtid);

  _user_relationships_invoke('delete', $relationship_type, TRUE);

  // #371311 force menu rebuild
  user_relationships_types_load(TRUE);
  menu_rebuild();

  drupal_set_message(t('Relationship %name has been deleted.', array('%name' => $relationship_type->name)));
  watchdog(
    'u_relationship',
    'User Relationships form: relationship %name deleted.', array('%name' => $relationship_type->name),
    WATCHDOG_NOTICE
  );

  $form_state['redirect'] = 'admin/user/relationships';
}

/**
 * Make relationship type available to translation by i18nstrings.module
 */
function _user_relationships_ui_update_translations(&$relationship_type) {
  if (function_exists('i18nstrings_update') && $relationship_type->rtid) {
    i18nstrings_update("user_relationships:rtid:$relationship_type->rtid:name", $relationship_type->name);
    i18nstrings_update("user_relationships:rtid:$relationship_type->rtid:plural_name", $relationship_type->plural_name);
  }
}