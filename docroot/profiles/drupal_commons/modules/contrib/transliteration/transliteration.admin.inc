<?php
// $Id: transliteration.admin.inc,v 1.1.2.7 2010/07/16 13:36:16 smk Exp $

/**
 * @file
 * Retroactive transliteration and admin settings UI.
 */

/**
 * Form builder function; generate retroactive transliteration confirm form.
 *
 * @see transliteration_retroactive_submit()
 * @ingroup forms
 */
function transliteration_retroactive() {
  if (!$query = transliteration_file_query(TRUE)) {
    drupal_set_message(t('Database not supported.'), 'error');
    $form['description']['#value'] = t('Retroactive transliteration is not supported for the database system of this Drupal installation. If you think this should be fixed please <a href="@issues-url">file an issue</a> in the project issue queue.', array('@issues-url' => 'http://drupal.org/project/issues/transliteration'));
    return $form;
  }

  $count = db_result(db_query($query));
  if (!$count) {
    drupal_set_message(t('Transliteration is not required.'), 'status');
    $form['description']['#value'] = t('There are currently no files names containing non-ASCII characters.');
    return $form;
  }

  $form['#redirect'] = 'admin/settings/file-system/settings';
  $question = t('Are you sure you want to transliterate existing file names?');

  // Generate a sample list.
  $rows = array();
  $header = array(
    t('Original file name'),
    t('Transliterated file name')
  );
  $result = db_query_range(transliteration_file_query(), 0, 10);
  while($file = db_fetch_object($result)) {
    $filename = basename($file->filepath);
    $rows[] = array(l($filename, file_create_url($file->filepath)), transliteration_clean_filename($filename));
  }
  $description = '<p><strong>' . t('The database currently lists @x_filenames containing non-ASCII characters.', array('@x_filenames' => format_plural($count, '1 file name', '@count file names'))) . '</strong><br />';
  $description .= t('This count might be inaccurate, though, since some files may not need to be renamed.') . '</p>';
  $description .= theme('table', $header, $rows);
  if ($count > 10) {
    $description .= '<p>' . t('Note: table shows only the first 10 entries.') . '</p>';
  }
  $description .= '<p>' . t('<strong>WARNING:</strong> if you have manually entered image or file paths in text fields (for example, text areas or WYSIWYG editors), renaming the files will break these references. Since there is currently no automated way to also fix referenced files in textual contents, it is a very good idea to backup the database and %files directory beforehand. Modules accessing files using their internal system ids are not affected.', array('%files' => file_directory_path())) . '</p>';
  $description .= '<p style="color: red; font-weight: bold; font-size: 18px;">' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, $question, 'admin/settings/file-system/settings', $description, t('Transliterate'));
}

/**
 * Form submit function; retroactively transliterate existing file names.
 *
 * @see transliteration_retroactive()
 */
function transliteration_retroactive_submit($form, &$form_state) {
  $count = 0;
  $errors = array();
  $result = db_query(transliteration_file_query());

  while ($file = db_fetch_object($result)) {
    if (!file_exists('./'. $file->filepath)) {
      // Missing file.
      $errors[] = $file->filepath;
      continue;
    }

    // Sanitize file name.
    $filename = transliteration_clean_filename(basename($file->filepath));
    // Build destination path.
    $destination = dirname($file->filepath) . '/' . $filename;

    // Rename and update the file record accordingly.
    if (file_move($file->filepath, $destination, FILE_EXISTS_RENAME)) {
      db_query("UPDATE {files} SET filepath = '%s' WHERE fid = %d", $file->filepath, $file->fid);
      $count++;
    }
    else {
      $errors[] = $file->filepath;
    }
  }

  if ($errors) {
    $message = t('Not all file names could be converted. The following files could not be accessed and have been ignored:');
    $message .= theme('item_list', $errors);
    drupal_set_message($message, 'error');
  }
  else {
    drupal_set_message(t('@filenames have been successfully transliterated.', array('@filenames' => format_plural($count, '1 file name', '@count file names'))));
  }

  // Flush page cache.
  cache_clear_all();
}

/**
 * Build a query that returns all file names from the database containing non-ASCII characters.
 *
 * @param $count
 *   Set to TRUE to return a count query.
 */
function transliteration_file_query($count = FALSE) {
  // Regular expressions are not supported by Drupal's database layer and
  // operators differ between manufacturers.
  switch ($GLOBALS['db_type']) {
    case 'mysql':
    case 'mysqli':
      $operator = 'NOT REGEXP';
      $regex = '/[a-z0-9_.-]+$';
      break;

    case 'pgsql':
      $operator = '!~*';
      $regex = '/[a-z0-9_.-]+$';
      break;

    default:
      return FALSE;
  }

  $fields = ($count ? 'COUNT(*)' : '*');
  return "SELECT $fields FROM {files} WHERE filepath $operator '$regex'";
}

