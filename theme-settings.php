<?php

/**
 * @file
 * Implimentation of hook_form_system_theme_settings_alter()
 *
 * To use replace "adaptivetheme_subtheme" with your themeName and uncomment by
 * deleting the comment line to enable.
 *
 * @param $form: Nested array of form elements that comprise the form.
 * @param $form_state: A keyed array containing the current state of the form.
 */

function commons_origins_form_system_theme_settings_alter(&$form, &$form_state)  {
  //$form_state['values']['enable_extensions'] = 1;
  //$form_state['values']['enable_font_settings'] = 1;
  //$form['at-settings']['extend']['enable_extensions']['#default_value'] = 1;
  //$form['at-settings']['extend']['enable']['enable_font_settings']['#default_value'] = 1;
  //$form['at']['font']['base-font']['base_font_type']['#default_value'] = 'Websafe fonts';
  dpm($form, '$form');
  dpm($form_state, '$form_state');

}
// */