<?php
// $Id: getid3.admin.inc,v 1.1.2.2 2010/07/25 03:48:38 drewish Exp $

/**
 * @file
 * Admin pages.
 */

/**
 * Administration settings for getID3().
 */
function getid3_admin_settings_form() {
  $form['getid3_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#default_value' => getid3_get_path(),
    '#description' => t('The location where getID3() is installed. Relative paths are from the Drupal root directory.'),
    '#after_build' => array('_getid3_admin_settings_check_path'),
  );
  if ($version = getid3_get_version()) {
    $form['getid3_version'] = array(
      '#type' => 'item',
      '#title' => t('Version'),
      '#value' => '<pre>'. check_plain($version) .'</pre>',
      '#description' => t("If you're seeing this it indicates that the getID3 library was found."),
    );

    // Check for existence of the 'demos' folder, contained in the getID3
    // library. The contents of this folder create a potential securtiy hole,
    // so we recommend that the user delete it.
    $getid3_demos_path = getid3_get_path() .'/../demos';
    if (file_exists($getid3_demos_path)) {
      drupal_set_message(t("Your getID3 library is insecure! The demos distributed with getID3 contains code which creates a huge security hole. Remove the demos directory (%path) from beneath Drupal's directory.", array('%path' => realpath($getid3_demos_path))), 'error');
    }
  }
  $form['getid3_show_warnings'] = array(
    '#type' => 'checkbox',
    '#title' => t("Display Warnings"),
    '#default_value' => variable_get('getid3_show_warnings', FALSE),
    '#description' => t("Check this to display the warning messages from the getID3 library when reading and writing ID3 tags. Generally it's a good idea to leave this unchecked, getID3 reports warnings for several trivial problems and the warnings can be confusing to users. This setting can be useful when debugging problems with the ID3 tags."),
  );
  return system_settings_form($form);
}

/**
 * Checks the that the directory in $form_element exists and contains a file
 * named 'getid3.php'. If validation fails, the form element is flagged with an
 * error from within the file_check_directory function. See:
 * system_check_directory()
 *
 * @param $form_element
 *   The form element containing the name of the directory to check.
 */
function _getid3_admin_settings_check_path($form_element) {
  $path = $form_element['#value'];
  if (!is_dir($path) || !(file_exists($path .'/getid3.php') && file_exists($path .'/write.php'))) {
    form_set_error($form_element['#parents'][0], t('The getID3 files <em>getid3.php</em> and <em>write.php</em> could not be found in the %path directory.', array('%path' => $path)));
  }
  return $form_element;
}


