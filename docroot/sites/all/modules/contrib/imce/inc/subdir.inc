<?php
// $Id: subdir.inc,v 1.3 2008/02/29 16:57:12 ufku Exp $

/**
 * Subdirectory creation form.
 */
function imce_form_subdirectory(&$form_state) {
  $form['help'] = array(
    '#type' => 'markup',
    '#value' => t('<p>Here you can create subdirectories for your users. Multiple directory creation is possible at a time with the <strong>*</strong> character. For example, specifying <strong>user*/foo</strong> will create <strong>foo</strong> named directories under each directory starting with <strong>user</strong>. */foo*/bar will create bar named directories under directories starting with foo in each directory of file system path.</p>'),
  );
  $form['path'] = array(
    '#title' => t('Directory path'),
    '#type' => 'textfield',
    '#default_value' => isset($form_state['values']['path']) ? $form_state['values']['path'] : '',
    '#maxlength' => 255,
    '#field_prefix' => file_directory_path() .'/',
  );
  $form['submit'] = array('#type' => 'submit', '#value' => t('Create'));
  return $form;
}

/**
 * Subdirectory form submit.
 */
function imce_form_subdirectory_submit($form, &$form_state) {
  imce_create_subdirectories($form_state['values']['path'], file_directory_path());
  $form_state['redirect'] = FALSE;
}

/**
 * Create directories under root according to path.
 */
function imce_create_subdirectories($path, $root) {
  $directories = explode('/', str_replace('\\', '/', $path));
  $paths = array($root);

  foreach ($directories as $directory) {

    //no asterisks. create the directory(s)
    if (strpos($directory, '*') === FALSE) {
      //check and create directories under each path.
      foreach ($paths as $i => $path) {
        $paths[$i] = $path = $path .'/'. $directory;
        if (!file_check_location($path, $root) || !file_check_directory($path, FILE_CREATE_DIRECTORY)) {
          drupal_set_message(t('Specified path must be under file sytem path.'), 'error');
          return FALSE;
        }
      }
    }

    //asterisks. get matching subdirectories and update paths.
    else {
      $newpaths = array();
      $regexp = str_replace('*', '.*', $directory);
      
      //add matching paths.
      foreach ($paths as $path) {
        $newpaths = array_merge($newpaths, imce_get_subdirectories($path, $regexp));
      }
      
      //no matching paths
      if (empty($newpaths)) {
        drupal_set_message(t('No matching subdirectories found.'), 'error');
        return FALSE;
      }
      
      $paths = $newpaths;
    }

  }

  return TRUE;
}

/**
 * Scan directory and return directories matching the expression.
 */
function imce_get_subdirectories($dir, $expr = '') {
  $directories = array();

  if ($handle = @opendir($dir)) {
    while (($file = readdir($handle)) !== FALSE) {
      if ($file != '.' && $file != '..' && is_dir($dir .'/'. $file) && preg_match('/^'. $expr .'$/', $file)) {
        $directories[] = $dir .'/'. $file;
      }
    }
    closedir($handle);
  }

  return $directories;
}