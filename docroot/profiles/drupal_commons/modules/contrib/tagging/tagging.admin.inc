<?php
// $Id: tagging.admin.inc,v 1.5.2.4 2010/10/17 10:23:24 eugenmayer Exp $

// Author: Eugen Mayer (http://kontextwork.de)
// Copyright 2010

/*
 * Providing a administration interface for tagging.
 */
function tagging_admin_settings() {
  $form['tagging_show_max_suggestion'] = array(
      '#type' => 'textfield',
      '#title' => t('Maximum suggestions'),
      '#description' => t('Maximum suggestions to show in the user-interface. Please use a number. Put "0" for no limit'),
      '#valid' => 'integer',
      '#default_value' => variable_get('tagging_show_max_suggestion', 20)
  );

  $form['tagging_show_suggestion_example'] = array(
      '#type' => 'checkbox',
      '#title' => t('Provide example suggestions (example implementation of hook_tagging_suggestion)'),
      '#description' => t('This will show a set of static suggestion in the user-interface. This should be only an example, you have to implement your own proper suggestion handler afterward and deacativate this one!'),
      '#default_value' => variable_get('tagging_show_suggestion_example', 1)
  );

  return system_settings_form($form);
}
