<?php

/**
 * @file
 * Contains the flag Ops field handler.
 */

/**
 * Views field handler for the Flag operations links (flag/unflag).
 *
 * @ingroup views
 */
class commons_follow_handler_field_ops extends flag_handler_field_ops {

  function render($values) {
    global $user;
    //If the passed in user doesn't match the current user
    if(isset($this->view->args[0]) && $user->uid != $this->view->args[0]) {

      if (!($flag = $this->get_flag())) {
        // get_flag() itself will print a more detailed message.
        return t('Missing flag');
      }
      $content_id = $values->{$this->aliases['content_id']};
      $is_flagged = $values->{$this->aliases['is_flagged']};

      if (empty($this->flag_applies[$content_id])) {
        // Flag does not apply to this content.
        return;
      }

      if (!empty($this->options['link_type'])) {
        $flag->link_type = $this->options['link_type'];
      }

      $variables = array();
      $action = $is_flagged ? 'unflag' : 'flag';
      $variables['flag_css_name'] = str_replace('_', '-', $flag->name);

      $flag_wrapper_classes_array = array();
      $flag_wrapper_classes_array[] = 'flag-wrapper';
      $flag_wrapper_classes_array[] = 'flag-' . $variables['flag_css_name'];
      $flag_wrapper_classes_array[] = 'flag-' . $variables['flag_css_name'] . '-' . $content_id;
      $variables['flag_wrapper_classes'] = implode(' ',$flag_wrapper_classes_array);

      $flag_classes_array = array();
      $flag_classes_array[] = 'flag';
      $flag_classes_array[] = $action . '-action';
      $flag_classes_array[] = 'flag-link-' . $flag->link_type;
      $variables['flag_classes'] = implode(' ', $flag_classes_array);
      $variables['is_flagged'] = $action;
      $variables['link_text'] = $flag->get_label($action . '_short', $content_id);

      return theme('commons_follow_otheruser_flag', $variables);
    }
    else {
      return parent::render($values);
    }

//    return $flag->theme($is_flagged ? 'unflag' : 'flag', $content_id);
  }
}
