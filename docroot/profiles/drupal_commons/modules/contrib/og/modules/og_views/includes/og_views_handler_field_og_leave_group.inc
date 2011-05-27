<?php
class og_views_handler_field_og_leave_group extends og_views_handler_field_og_uid {
  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => 'Leave group', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = array('table' => 'og_uid', 'field' => 'nid');
    $this->additional_fields['uid'] = array('table' => 'node', 'field' => 'uid');
  }

  function render($values) {
    if (isset($values->{$this->field_alias})) {
      $nid = $values->{$this->aliases['nid']};
      $uid = $values->{$this->aliases['uid']};
      global $user;
      // Make sure the user is a member
      if (in_array($nid, array_keys($user->og_groups))) {
        $text = !empty($this->options['text']) ? $this->options['text'] : t('Leave group');
        // If the user is the group owner, they can't leave, so send them
        // to the manage page so the message displays
        if ($user->uid == $uid) {
          return l($text, "og/manage/{$nid}", array('query' => drupal_get_destination()));
        }
        else {
          return l($text, "og/unsubscribe/{$nid}/{$user->uid}", array('query' => drupal_get_destination()));
        }
      }
    }
  }
}
