<?php
// $Id:

/**
 * Filter handler for usernames
 */
class realname_handler_filter_user_name extends views_handler_filter_user_name {
  var $no_single = TRUE;

  function value_form(&$form, &$form_state) {
    $values = array();
    if ($this->value) {
      $result = db_query("SELECT u.*, ru.realname FROM {users} u LEFT JOIN {realname} ru ON ru.uid=u.uid WHERE u.uid IN ("  . implode(', ', $this->value) . ")");
      while ($account = db_fetch_object($result)) {
        if ($account->uid) {
          $values[] = $account->realname;
        }
        else {
          $values[] = 'Anonymous'; // Intentionally NOT translated.
        }
      }
    }

    sort($values);
    $default_value = implode(', ', $values);
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Realnames'),
      '#description' => t('Enter a comma separated list of user real names.'),
      '#default_value' => $default_value,
      '#autocomplete_path' => 'admin/user/realname/ajax/autocomplete/user',
    );

    if (!empty($form_state['exposed']) && !isset($form_state['input'][$this->options['expose']['identifier']])) {
      $form_state['input'][$this->options['expose']['identifier']] = $default_value;
    }
  }

  /**
   * Validate the user string. Since this can come from either the form
   * or the exposed filter, this is abstracted out a bit so it can
   * handle the multiple input sources.
   */
  function validate_user_strings(&$form, $values) {
    $uids = array();
    $placeholders = array();
    $args = array();
    $results = array();
    foreach ($values as $value) {
      if (strtolower($value) == 'anonymous') {
        $uids[] = 0;
      }
      else {
        $missing[strtolower($value)] = TRUE;
        $args[] = $value;
        $placeholders[] = "'%s'";
      }
    }

    if (!$args) {
      return $uids;
    }

    $result = db_query("SELECT u.*, ru.realname FROM {users} u LEFT JOIN {realname} ru ON ru.uid=u.uid WHERE ru.realname IN (" . implode(', ', $placeholders) . ")", $args);
    while ($account = db_fetch_object($result)) {
      unset($missing[strtolower($account->realname)]);
      $uids[] = $account->uid;
    }

    if ($missing) {
      form_error($form, format_plural(count($missing), 'Unable to find user: @users', 'Unable to find users: @users', array('@users' => implode(', ', array_keys($missing)))));
    }

    return $uids;
  }

  function admin_summary() {
    // set up $this->value_options for the parent summary
    $this->value_options = array();

    if ($this->value) {
      $result = db_query("SELECT u.*, ru.realname FROM {users} u LEFT JOIN {realname} ru ON ru.uid=u.uid WHERE u.uid IN ("  . implode(', ', $this->value) . ")");

      while ($account = db_fetch_object($result)) {
        if ($account->uid) {
          $this->value_options[$account->uid] = $account->realname;
        }
        else {
          $this->value_options[$account->uid] = 'Anonymous'; // Intentionally NOT translated.
        }
      }
    }

    return parent::admin_summary();
  }
}
