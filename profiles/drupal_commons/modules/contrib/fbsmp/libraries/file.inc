<?php

/**
 * @file
 *   Common functionality for file handling. Mostly from field_file.inc
 */
 
 
/**
 * Load a file from the database.
 *
 * @param $fid
 *   A numeric file id or string containing the file path.
 * @param $reset
 *   Whether to reset the internal file_load cache.
 *
 * @return
 *   A file object.
 */
function _fbsmp_file_load($fid, $reset = NULL) {
  //Reset internal cache.
  if (isset($reset)) {
    _fbsmp_file_cache(NULL, TRUE);
  }

  if (empty($fid)) {
    return array('fid' => 0, 'filepath' => '', 'filename' => '', 'filemime' => '', 'filesize' => 0);
  }

  $files = _fbsmp_file_cache();
  //Serve file from internal cache if available.
  if (empty($files[$fid])) {
    if (is_numeric($fid)) {
      $file = db_fetch_object(db_query('SELECT f.* FROM {files} f WHERE f.fid = %d', $fid));
    }
    else {
      $file = db_fetch_object(db_query("SELECT f.* FROM {files} f WHERE f.filepath = '%s'", $fid));
    }
    if (!$file) {
      $file = array('fid' => 0, 'filepath' => '', 'filename' => '', 'filemime' => '', 'filesize' => 0);
    }

    foreach (module_implements('file_load') as $module) {
      $function =  $module .'_file_load';
      $function($file);
    }
    // Cache the fully loaded file for later use.
    $files = _fbsmp_file_cache($file);
  }
  return $files[$fid];
}

/**
 * Save a file upload to a new location.
 *
 * The file will be added to the files table as a temporary file. Temporary
 * files are periodically cleaned. To make the file permanent, call
 * file_set_status() to change its status.
 *
 * @param $source
 *   A string specifying the name of the upload field to save.
 * @param $validators
 *   An optional, associative array of callback functions used to validate the
 *   file. The keys are function names and the values arrays of callback
 *   parameters which will be passed in after the user and file objects. The
 *   functions should return an array of error messages, an empty array
 *   indicates that the file passed validation. The functions will be called in
 *   the order specified.
 * @param $dest
 *   A string containing the directory $source should be copied to. If this is
 *   not provided or is not writable, the temporary directory will be used.
 *
 * @return
 *   An object containing the file information, or 0 in the event of an error.
 */
function _fbsmp_file_save_upload($source, $validators = array(), $dest = FALSE) {
  if (!$file = file_save_upload($source, $validators, $dest, FILE_EXISTS_RENAME)) {
    return 0;
  }
  if (!@chmod($file->filepath, 0664)) {
    watchdog('fbsmp', 'Could not set permissons on destination file: %file', array('%file' => $file->filepath));
  }

  //Let modules add additional properties to the yet barebone file object.
  foreach (module_implements('file_insert') as $module) {
    $function =  $module .'_file_insert';
    $function($file);
  }
  _fbsmp_file_cache($file); //Cache the file in order to minimize load queries
  return $file;
}


/**
 * Delete a file and its database record.
 *
 * @param $file
 *   A file object.
 *
 * @return mixed
 *   TRUE for success or FALSE in the event of an error.
 */
function _fbsmp_file_delete($file) {
  $file = (object)$file;
  
  //Let other modules clean up on delete.
  module_invoke_all('file_delete', $file);

  //Make sure the file is deleted before removing its row from the
  //database, so UIs can still find the file in the database.
  if (file_delete($file->filepath)) {
    db_query('DELETE FROM {files} WHERE fid = %d', $file->fid);
    _fbsmp_file_cache(NULL, $file); //Delete the file from the cache
    return TRUE;
  }
  return FALSE;
}

/**
 * Internal cache, in order to minimize database queries for loading files.
 */
function _fbsmp_file_cache($file = NULL, $reset = FALSE) {
  static $files = array();

  //Reset internal cache.
  if (is_object($reset)) { // file object, uncache just that one
    unset($files[$reset->fid]);
    unset($files[$reset->filepath]);
  }
  elseif ($reset) { // TRUE, delete the whole cache
    $files = array();
  }

  //Cache the file by both fid and filepath.
  //Use non-copying objects to save memory.
  if (!empty($file->fid)) {
    $files[$file->fid] = $file;
    $files[$file->filepath] = $file;
  }
  return $files;
}

/**
 * A silent version of file.inc's file_check_directory().
 *
 * This function differs from file_check_directory in that it checks for
 * files when doing the directory check and it does not use drupal_set_message()
 * when creating directories.
 *
 * Check that the directory exists and is writable. Directories need to
 * have execute permissions to be considered a directory by FTP servers, etc.
 *
 * @param $directory
 *   A string containing the name of a directory path.
 * @param $mode
 *   A Boolean value to indicate if the directory should be created
 *   if it does not exist or made writable if it is read-only.
 * @param $form_item
 *   An optional string containing the name of a form item that
 *   any errors will be attached to. This is useful for settings forms that
 *   require the user to specify a writable directory. If it can't be made to
 *   work, a form error will be set preventing them from saving the settings.
 *
 * @return FALSE when directory not found, or TRUE when directory exists.
 */
function _fbsmp_file_check_directory(&$directory, $mode = 0, $form_item = NULL) {
  $directory = rtrim($directory, '/\\');

  //Error if the directory is a file.
  if (is_file($directory)) {
    watchdog('file system', 'The path %directory was checked as a directory, but it is a file.',  array('%directory' => $directory), WATCHDOG_ERROR);
    if ($form_item) {
      form_set_error($form_item, t('The directory %directory is a file and cannot be overwritten.', array('%directory' => $directory)));
    }
    return FALSE;
  }

  //Create the directory if it is missing.
  if (!is_dir($directory) && $mode & FILE_CREATE_DIRECTORY && !@mkdir($directory, 0775, TRUE)) {
    watchdog('file system', 'The directory %directory does not exist.', array('%directory' => $directory), WATCHDOG_ERROR);
    if ($form_item) {
      form_set_error($form_item, t('The directory %directory does not exist.', array('%directory' => $directory)));
    }
    return FALSE;
  }

  //Check to see if the directory is writable.
  if (!is_writable($directory) && $mode & FILE_MODIFY_PERMISSIONS && !@chmod($directory, 0775)) {
    watchdog('file system', 'The directory %directory is not writable, because it does not have the correct permissions set.', array('%directory' => $directory), WATCHDOG_ERROR);
    if ($form_item) {
      form_set_error($form_item, t('The directory %directory is not writable', array('%directory' => $directory)));
    }
    return FALSE;
  }

  if ((file_directory_path() == $directory || file_directory_temp() == $directory) && !is_file("$directory/.htaccess")) {
    $htaccess_lines = "SetHandler Drupal_Security_Do_Not_Remove_See_SA_2006_006\nOptions None\nOptions +FollowSymLinks";
    if (($fp = fopen("$directory/.htaccess", 'w')) && fputs($fp, $htaccess_lines)) {
      fclose($fp);
      chmod($directory .'/.htaccess', 0664);
    }
    else {
      $repl = array('%directory' => $directory, '!htaccess' => nl2br(check_plain($htaccess_lines)));
      form_set_error($form_item, t("Security warning: Couldn't write .htaccess file. Please create a .htaccess file in your %directory directory which contains the following lines:<br /><code>!htaccess</code>", $repl));
      watchdog('security', "Security warning: Couldn't write .htaccess file. Please create a .htaccess file in your %directory directory which contains the following lines:<br /><code>!htaccess</code>", $repl, WATCHDOG_ERROR);
    }
  }

  return TRUE;
}

/**
 * Determine the destination directory given a path relative to
 * system files directory.
 *
 * @param $dest
 *   The destination path relative to the system files directory without
 *   preceeding or trailing slashes.
 * @param $account
 *   The user account object to calculate the file path for.
 * @return
 *   The destination directory path, with any tokens replaced.
 */
function _fbsmp_file_create_path($dest = '', $account = NULL) {
  $file_path = file_directory_path();
  if (!$dest) {
    return $file_path;
  }
  
  $account = isset($account) ? $account : $GLOBALS['user'];
  //Replace user level tokens.
  if (module_exists('token')) {
    $dest = token_replace($dest, 'user', $account);
  }
  //Replace nasty characters in the path if possible.
  if (module_exists('transliteration')) {
    module_load_include('inc', 'transliteration');
    $dest_array = array_filter(explode('/', $dest));
    foreach ($dest_array as $key => $directory) {
      $dest_array[$key] = transliteration_clean_filename($directory);
    }
    $dest = implode('/', $dest_array);
  }

  return  $file_path .'/'. $dest;
}

/**
 * A silent version of file.inc's file_destination().
 *
 * Determines the destination path for a file depending on how replacement of
 * existing files should be handled. It does not uses drupal_set_message() if 
 * the file already exists and FILE_EXISTS_ERROR was specified.
 *
 * @param $destination
 *   A string specifying the desired path.
 * @param $replace 
 *   Replace behavior when the destination file already exists.
 *   - FILE_EXISTS_REPLACE - Replace the existing file
 *   - FILE_EXISTS_RENAME - Append _{incrementing number} until the filename is
 *     unique
 *   - FILE_EXISTS_ERROR - Do nothing and return FALSE.
 * @return The destination file path or FALSE if the file already exists and
 *   FILE_EXISTS_ERROR was specified.
 */
function _fbsmp_file_destination($destination, $replace) {
  if (file_exists($destination)) {
    switch ($replace) {
      case FILE_EXISTS_RENAME:
        $basename = basename($destination);
        $directory = dirname($destination);
        $destination = file_create_filename($basename, $directory);
        break;

      case FILE_EXISTS_ERROR:
        return FALSE;
    }
  }
  return $destination;
}

/**
 * Save a file into a file node after running all the associated validators.
 *
 * This function is usually used to move a file from the temporary file
 * directory to a permanent location. It may be used by import scripts or other
 * modules that want to save an existing file into the database.
 *
 * @param $filepath
 *   The local file path of the file to be saved.
 * @param $validators
 *   An optional, associative array of callback functions used to validate the
 *   file. The keys are function names and the values arrays of callback
 *   parameters which will be passed in after the user and file objects. The
 *   functions should return an array of error messages, an empty array
 *   indicates that the file passed validation. The functions will be called in
 *   the order specified.
 * @param $dest
 *   A string containing the directory $source should be copied to. If this is
 *   not provided or is not writable, the temporary directory will be used.
 * @param $account
 *   The user account object that should associated with the uploaded file.
 * @param $replace 
 *   Replace behavior when the destination file already exists.
 *   - FILE_EXISTS_REPLACE - Replace the existing file
 *   - FILE_EXISTS_RENAME - Append _{incrementing number} until the filename is
 *     unique
 *   - FILE_EXISTS_ERROR - Do nothing and return 0.
 *
 * @return
 *   An object containing the file information, or 0 in the event of an error.
 */
function _fbsmp_file_save_file($filepath, $validators = array(), $dest = FALSE, $replace = FILE_EXISTS_RENAME, $account = NULL) {
  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }

  //Add in our check of the the file name length.
  $validators['file_validate_name_length'] = array();

  //Begin building file object.
  $file = new stdClass();
  $file->uid = $account->uid;
  $file->filename = basename($filepath);
  $file->filepath = $filepath;
  $file->filemime = module_exists('mimedetect') ? mimedetect_mime($file) : file_get_mimetype($file->filename);

  //Rename potentially executable files, to help prevent exploits.
  if (preg_match('/\.(php|pl|py|cgi|asp|js)$/i', $file->filename) && (substr($file->filename, -4) != '.txt')) {
    $file->filemime = 'text/plain';
    $file->filepath .= '.txt';
    $file->filename .= '.txt';
  }

  //If the destination is not provided, or is not writable, then use the
  //temporary directory.
  if (empty($dest) || file_check_path($dest) === FALSE) {
    $dest = file_directory_temp();
  }

  $file->source = '_fbsmp_file_save_file';
  $file->destination = _fbsmp_file_destination(file_create_path($dest .'/'. $file->filename), $replace);
  $file->filesize = filesize($filepath);

  //Call the validation functions.
  $errors = array();
  foreach ($validators as $function => $args) {
    array_unshift($args, $file);
    $errors = array_merge($errors, call_user_func_array($function, $args));
  }

  // Check for validation errors.
  if (!empty($errors)) {
    $message = t('The selected file %name could not be saved.', array('%name' => $file->filename));
    if (count($errors) > 1) {
      $message .= '<ul><li>'. implode('</li><li>', $errors) .'</li></ul>';
    }
    else {
      $message .= ' '. array_pop($errors);
    }
    form_set_error($file->source, $message);
    return 0;
  }

  if (!file_copy($file, $file->destination, $replace)) {
    watchdog('file', 'Upload error. Could not move file %file to destination %destination.', array('%file' => $file->filename, '%destination' => $file->destination));
    return 0;
  }

  // If we made it this far it's safe to record this file in the database.
  $file->status = FILE_STATUS_TEMPORARY;
  $file->timestamp = time();
  // Insert new record to the database.
  drupal_write_record('files', $file);

  // Let modules add additional properties to the yet barebone file object.
  foreach (module_implements('file_insert') as $module) {
    $function =  $module .'_file_insert';
    $function($file);
  }
  _fbsmp_file_cache($file); // cache the file in order to minimize load queries
  return $file;
}

/**
 * An #upload_validators callback. Check the file matches an allowed extension.
 *
 * If the mimedetect module is available, this will also validate that the
 * content of the file matches the extension. User #1 is included in this check.
 *
 * @param $file
 *   A Drupal file object.
 * @param $extensions
 *   A string with a space separated list of allowed extensions.
 * @return
 *   An array of any errors cause by this file if it failed validation.
 */
function _fbsmp_file_validate_extensions($file, $extensions) {
  global $user;
  $errors = array();

  if (!empty($extensions)) {
    $regex = '/\.('. ereg_replace(' +', '|', preg_quote($extensions)) .')$/i';
    $matches = array();
    if (preg_match($regex, $file->filename, $matches)) {
      $extension = $matches[1];
      //If the extension validates, check that the mimetype matches.
      if (module_exists('mimedetect')) {
        $type = mimedetect_mime($file);
        if ($type != $file->filemime) {
          $errors[] = t('The file contents (@type) do not match its extension (@extension).', array('@type' => $type, '@extension' => $extension));
        }
      }
    }
    else {
      $errors[] = t('Only files with the following extensions are allowed: %files-allowed.', array('%files-allowed' => $extensions));
    }
  }

  return $errors;
}


/**
 * An #upload_validators callback. Check the file size does not exceed a limit.
 *
 * @param $file
 *   A Drupal file object.
 * @param $file_limit
 *   An integer value limiting the maximum file size in bytes.
 * @param $file_limit
 *   An integer value limiting the maximum size in bytes a user can upload on
 *   the entire site.
 * @return
 *   An array of any errors cause by this file if it failed validation.
 */
function _fbsmp_file_validate_size($file, $file_limit = 0, $user_limit = 0) {
  global $user;

  $errors = array();

  if ($file_limit && $file->filesize > $file_limit) {
    $errors[] = t('The file is %filesize exceeding the maximum file size of %maxsize.', array('%filesize' => format_size($file->filesize), '%maxsize' => format_size($file_limit)));
  }

  //Bypass user limits for uid = 1.
  if ($user->uid != 1) {
    $total_size = file_space_used($user->uid) + $file->filesize;
    if ($user_limit && $total_size > $user_limit) {
      $errors[] = t('The file is %filesize which would exceed your disk quota of %quota.', array('%filesize' => format_size($file->filesize), '%quota' => format_size($user_limit)));
    }
  }
  return $errors;
}

/**
 * An #upload_validators callback. Check that a file is an image.
 *
 * This check should allow any image that PHP can identify, including png, jpg,
 * gif, tif, bmp, psd, swc, iff, jpc, jp2, jpx, jb2, xbm, and wbmp.
 *
 * @param $file
 *   A Drupal file object.
 * @return
 *   An array of any errors cause by this file if it failed validation.
 */
function _fbsmp_file_validate_is_image(&$file) {
  $errors = array();
  $info = image_get_info($file->filepath);
  if (!$info || empty($info['extension'])) {
    $errors[] = t('The file is not a known image format.');
  }
  return $errors;
}

/**
 * An #upload_validators callback. Check an image resolution.
 *
 * @param $file
 *   A Drupal file object.
 * @param $max_size
 *   A string in the format WIDTHxHEIGHT. If the image is larger than this size
 *   the image will be scaled to fit within these dimensions.
 * @param $min_size
 *   A string in the format WIDTHxHEIGHT. If the image is smaller than this size
 *   a validation error will be returned.
 * @return
 *   An array of any errors cause by this file if it failed validation.
 */
function _fbsmp_file_validate_image_resolution(&$file, $maximum_dimensions = 0, $minimum_dimensions = 0) {
  $errors = array();

  list($max_width, $max_height) = explode('x', $maximum_dimensions);
  list($min_width, $min_height) = explode('x', $minimum_dimensions);

  //Check first that the file is an image.
  if ($info = image_get_info($file->filepath)) {
    if ($maximum_dimensions) {
      //Check that it is larger than the given dimensions.
      if ($info['width'] > $max_width || $info['height'] > $max_height) {
          $errors[] = t('The image is too large; the maximum dimensions are %dimensions pixels.', array('%dimensions' => $maximum_dimensions));
      }
    }
    if ($minimum_dimensions && empty($errors)) {
      //Check that it is smaller than the given dimensions.
      if ($info['width'] < $min_width || $info['height'] < $min_height) {
        $errors[] = t('The image is too small; the minimum dimensions are %dimensions pixels.', array('%dimensions' => $minimum_dimensions));
      }
    }
  }

  return $errors;
}