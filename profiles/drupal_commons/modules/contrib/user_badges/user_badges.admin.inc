<?php
// $Id: user_badges.admin.inc,v 1.1.2.11 2010/10/13 04:20:19 nancyw Exp $

/**
 * @file
 * @brief User Badges admin functions
 *
 * This file contains all the admin functions used by the module.
 *
 * @author Jeff Robbins (jjeff), http://drupal.org/user/17190
 * @author Chad Phillips (hunmonk), http://drupal.org/user/22079
 * @author Heine Deelstra (Heine), http://drupal.org/user/17943
 * @author Nuno Veloso (nunoveloso18), http://drupal.org/user/80656
 * @author Richard Skinner (Likeless), http://drupal.org/user/310635
 *
 * @warning For more information on licensing, read the LICENCE.txt file.
 *
 */


/**
 * Form builder; list of badges
 */
function user_badges_badgelist_form() {

  // load the badges that we want to display
  $form['header'] = array('#type' => 'value', '#value' => array(
    array('data' => t('Name'), 'field' => 'name'),
    array('data' => t('Badge')),
    array('data' => t('Weight'), 'field' => 'weight', 'sort' => 'asc'),
    array('data' => t('Edit')),
    array('data' => t('Delete'))
  ));

  $result = pager_query('SELECT bid, name, image, weight, href FROM {user_badges_badges} ubb '. tablesort_sql($form['header']['#value']), 50 );

  // build a table listing the appropriate badges
  while ($badge = db_fetch_object($result)) {
    $form['name'][$badge->bid] = array('#value' => check_plain($badge->name));
    $form['badge'][$badge->bid] = array('#value' => theme('user_badge', $badge));
    $form['weight'][$badge->bid] = array('#type' => 'textfield', '#size' => 4, '#maxlength' => 255, '#default_value' => $badge->weight );
    $form['edit'][$badge->bid] = array('#value' => l(t('edit'), 'admin/user/user_badges/edit/'. $badge->bid));
    $form['delete'][$badge->bid] = array('#value' => l(t('delete'), 'admin/user/user_badges/delete/'. $badge->bid));
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Update'));

  $form['pager'] = array('#value' => theme('pager', NULL, 50, 0));

  return $form;
}

/**
 * Validate user_badges_badgelist_form form submissions.
 *
 * All weights should be numeric
 */
function user_badges_badgelist_form_validate($form, &$form_state) {
  if (isset($form['weight']) && is_array($form['weight'])) {
    foreach (element_children($form['weight']) as $bid) {
      if (!is_numeric($form_state['values'][$bid])) {
        form_set_error($bid, t('All weight values must be numeric.'));
      }
    }
  }
}

/**
 * Process user_badges_badgelist_form form submissions.
 *
 * Update the badge weights
 */
function user_badges_badgelist_form_submit($form, &$form_state) {
  if (isset($form['weight']) && is_array($form['weight'])) {
    foreach (element_children($form['weight']) as $bid) {
      db_query("UPDATE {user_badges_badges} SET weight = %d WHERE bid = %d",
      $form_state['values'][$bid],
      $bid
      );
    }
    drupal_set_message(t('The badge weights have been updated.'));
  }
}

/**
 * Theme the badge list form.
 *
 * @param $form
 *   An associative array containing the structure of the form.
 * @ingroup themeable
 */
function theme_user_badges_badgelist_form($form) {

  //Loop through the array items in the name array to get all the bids for our listed badges
  if (isset($form['name']) && is_array($form['name'])) {
    foreach (element_children($form['name']) as $key) {
      //We only want bids as values of $key
      if (!is_numeric($key)) {
        continue;
      }

      //Create the rows array for the table theme
      $row = array();
      $row[] = drupal_render($form['name'][$key]);
      $row[] = drupal_render($form['badge'][$key]);
      $row[] = drupal_render($form['weight'][$key]);
      $row[] = drupal_render($form['edit'][$key]);
      $row[] = drupal_render($form['delete'][$key]);
      $rows[] = $row;
    }

    //Add the submit button
    $row = array();
    $row[] = '';
    $row[] = '';
    $row[] = drupal_render($form['submit']);
    $row[] = '';
    $row[] = '';
    $rows[] = $row;

  }
  else {
    $rows[] = array(array('data' => t('No badges available.'), 'colspan' => '5'));
  }

  //Theme all that we have processed so far into a table
  $output .= theme('table', $form['header']['#value'], $rows);

  //Create the table's pager
  if ($form['pager']['#value']) {
    $output .= drupal_render($form['pager']);
  }

  //Render any remaining form elements
  $output .= drupal_render($form);

  return $output;
}

/**
 * Define the edit form for userbadges.
 */
function user_badges_edit_form($form_state, $bid = NULL) {

  //If we have been given an existing badge (bid) then get all the badge info into $edit
  if (is_numeric($bid)) {
    $edit = db_fetch_object(db_query('SELECT * FROM {user_badges_badges} WHERE bid = %d', $bid));
    if (is_numeric($edit->bid)) {
      $form['bid'] = array(
        '#type' => 'value',
        '#value' => $edit->bid,
      );
    }
  }

  //Are we using a library image or an image URL?
  if ( isset($edit) && valid_url($edit->image, TRUE) ) {
    $imageurl = $edit->image;
    $libraryimage = '';
  }
  else {
    $libraryimage = $edit->image;
    $imageurl = '';
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($edit) ? $edit->name : '',
    '#size' => 40,
    '#maxlength' => 100,
    '#description' => t('Name for the badge. Will be displayed as a tooltip when rolling over the badge.'),
    '#required' => TRUE,
  );
  $form['imageurl'] = array(
    '#type' => 'textfield',
    '#title' => t('Image URL'),
    '#default_value' => $imageurl,
    '#size' => 60,
    '#maxlength' => 255,
    '#description' => t('The image URL for this badge. If you want to use an image from the user badges image library, select from the list below.'),
  );
  $form['weight'] = array(
    '#type' => 'textfield',
    '#title' => t('Weight'),
    '#size' => 4,
    '#maxlength' => 10,
    '#default_value' => isset($edit) ? $edit->weight : 0,
    '#description' => t('Lighter weighted items float to the top of lists. Heavier items go to the bottom. You must enter a number (negative values are allowed).'),
    '#required' => TRUE,
  );
  $form['href'] = array(
    '#type' => 'textfield',
    '#title' => t('Description URL'),
    '#size' => 60,
    '#maxlength' => 255,
    '#description' => t('You can specify here the link where your badge will redirect your user.
      This is useful for explanation pages about the badge, for instance. If you do not wish
      your badge to be clickable, please leave this field empty.') .'<br />'.
      '<u>'. t('Tips:') .'</u>'.'<ul>'.
        '<li>'. t('If you provide the full URL, it will be considered an external URL.') .'</li>'.
        '<li>'. t('If you provide only the path (e.g. "admin/content/node"), it is considered an
          internal link.') .'</li>'.
        '<li>'. t('Use %none to override a default link in the settings tab with no link for this badge.', array('%none' => '<none>')) .'</li>'.
      '</ul>',
    '#default_value' => $edit->href,
  );

  //Tokens help
  if (module_exists('token')) {
    $form['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['token_help']['help'] = array(
      '#value' => theme('token_help', array('userbadge', 'user')),
    );
  }
  else {
    $form['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['token_help']['help'] = array(
      // Ignore Coder flag on the link.
      '#value' => t('Install the !link module if you want this URL to include dynamic elements such as badge ID numbers.', array('!link' => l('Token', 'http://drupal.org/project/token', array('absolute' => TRUE)))),
      );
  }

  if (module_exists('taxonomy')) {
    if (variable_get('user_badges_vid', '')) {
      $form['tid'] = taxonomy_form(variable_get('user_badges_vid', ''), $edit->tid);
      //taxonomy sets the weight to -15, so we should get rid of it to preserve the ordering
      unset($form['tid']['#weight']);
    }
    else {
      $form['tid']['help'] = array(
        '#value' => t('Activate the taxonomy module if you want to associate badges with taxonomy terms.'),
      );
    }
  }

  $form['unhideable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Cannot be Hidden'),
    '#default_value' => $edit->unhideable,
    '#description' => t('If this is set, the badge cannot be hidden by being moved down in weight. It will always show up.'),
  );
  $form['fixedweight'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fixed Weight'),
    '#default_value' => $edit->fixedweight,
    '#description' => t('If this is set, the badge cannot have a user assigned weight, regardless of settings.'),
  );
  $form['doesnotcounttolimit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Does Not Count to Limit'),
    '#default_value' => $edit->doesnotcounttolimit,
    '#description' => t('If this is set, the badge does not count towards the limit for number of badges to display per user.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $selects = array('' => t('Use the image URL above instead of a library image.')) + user_badges_image_selects();
  if (count($selects)) {
    $form['image'] = array(
      '#type' => 'radios',
      '#title' => t('Image Library'),
      '#default_value' => $libraryimage,
      '#options' => $selects,
      '#description' => t('If you have not entered an image URL above, you can select an image from this user badges image library to associate with this badge. You can upload additional images to the library under the <a href="@url">images</a> tab.', array('@url' => url("admin/user/user_badges/images"))),
    );
  }
  else {
    $form['noimages'] = array(
      '#type' => 'item',
      '#title' => t('Image'),
      '#value' => t('No badge images uploaded.'),
      '#description' => t('You can enter an image URL directly above, but if you want to instead upload your image to the user badges image library, use <a href="@upload_link">this link</a>. Note that private download is incompatible with this library and should use direct URL entry instead.', array('@upload_link' => url("admin/user/user_badges/images"))),
    );
  }
  $form['submit2'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Validate user_badges_edit_form form submissions.
 *
 */
function user_badges_edit_form_validate($form, &$form_state) {
  //Either a URL or an item from the image library should be selected, but not both
  if ($form_state['values']['imageurl'] && $form_state['values']['image']) {
    form_set_error('image', t('You cannot both enter an image URL and select an image from the library too. A badge can only have one image.'));
  }
  elseif (!$form_state['values']['imageurl'] && !$form_state['values']['image']) {
    form_set_error('image', t('You need to either enter an image URL or select an image from the library. Your badge needs an image.'));
  }

  //The image URL must be a valid url
  if ($form_state['values']['imageurl'] && !valid_url($form_state['values']['imageurl'], TRUE)) {
    form_set_error('imageurl', t('This is not a valid image URL. You need to enter a complete image URL, including the "http://" at the start.'));
  }

  //Weights must be numeric
  if (!is_numeric($form_state['values']['weight'])) {
    form_set_error('weight', t('Your value for the weight must be a number. Negative numbers are allowed, but not decimals.'));
  }

}

/**
 * Process user_badges_edit_form form submissions.
 *
 * Inserts the badge into the DB and sets a success message
 */
function user_badges_edit_form_submit($form, &$form_state) {
  $edit = $form_state['values'];
  $edit = (object)$edit;

  $image = $edit->imageurl ? trim($edit->imageurl) : $edit->image;

  //If the badge already exists, delete it and re-insert it
  if (isset($edit->bid) && preg_match("/^[0-9]+$/D", $edit->bid)) {
    db_query('DELETE FROM {user_badges_badges} WHERE bid = %d', $edit->bid);
    $result = db_query("
      INSERT INTO {user_badges_badges} (bid, name, image, weight, href, unhideable, fixedweight, doesnotcounttolimit, tid)
      VALUES (%d, '%s', '%s', %d, '%s', %d, %d, %d, %d)",
      $edit->bid, trim($edit->name), $image, $edit->weight, trim($edit->href), $edit->unhideable, $edit->fixedweight, $edit->doesnotcounttolimit, $edit->tid
    );
  }
  //If the badge does not already exist, create it anew
  else {
    $result = db_query("
      INSERT INTO {user_badges_badges} (name, image, weight, href, unhideable, fixedweight, doesnotcounttolimit, tid)
      VALUES ('%s', '%s', %d, '%s', %d, %d, %d, %d)",
      trim($edit->name), $image, $edit->weight, trim($edit->href), $edit->unhideable, $edit->fixedweight, $edit->doesnotcounttolimit, $edit->tid
    );
  }
  if ($result) {
    drupal_set_message(t('Badge %badgename saved.', array('%badgename' => $edit->name)));
  }
  else {
    drupal_set_message(t('There was a problem saving the badge information into the database.'));
  }
  $form_state['redirect'] = 'admin/user/user_badges';
}

/**
 * form to upload the badge images or to delete existing ones
 */
function user_badges_images_form($form_state) {
  $form = array('#skip_duplicate_check' => TRUE);
  if (module_exists('upload')) {
    $form['new']['upload'] = array('#type' => 'file', '#title' => t('Upload image'), '#size' => 40);
    $form['new']['attach'] = array('#type' => 'submit', '#value' => t('Upload'));
  }
  else {
    drupal_set_message(t('Upload of images requires the upload module to be enabled.'), 'error');
  }

  $form['#attributes']['enctype'] = 'multipart/form-data';

  $selects = user_badges_image_selects();
  if (count($selects)) {
    $form['images'] = array('#tree' => TRUE);
    foreach ($selects as $imagepath => $imageimg) {
      $form['images'][$imagepath] = array(
        '#type' => 'checkbox',
        '#title' => $imageimg,
        '#return_value' => 1,
        '#default_value' => FALSE,
        '#description' => check_plain($imagepath),
      );
    }
    $form['delete_image'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
  }
  return $form;
}

/**
 * Validate the uploaded image
 *
 * Check whether:
 * Delete has been chosen AND a checkbox has been selected
 * OR
 * Upload has been chosen AND the file upload form is not empty.
 */
function user_badges_images_form_validate($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  if ($op == t('Upload')) {
    $dir = file_create_path('badges');
    $is_writable = file_check_directory($dir, 1);
    if ($is_writable) {
      $validators = array(
        'file_validate_extensions' => array('png jpg jpeg gif'),
      );
      if ($file = file_save_upload('upload', $validators, $dir)) {
        if (!image_get_info($file->filepath)) {
          file_delete($file->filepath);
          form_set_error('upload', t('Uploaded image file does not appear to be a valid image file.  Please try again'));
        }
        else {
          user_badges_hold_temporary_file($file);
          $form_state['values']['file_image'] = $file;
        }
      }
      else {
        form_set_error('upload', t('Cannot save image.  Enter the path to an image and try again.'));
      }
    }
    else {
      form_set_error('upload', t('Cannot save image - directory not writable'));
    }
  }
  elseif ($op == t('Delete')) {
    if (count(array_filter($form_state['values']['images'])) == 0) {
      form_set_error('images', t('Please select images to delete.'));
    }
  }
}

function user_badges_hold_temporary_file($file = NULL) {
  static $static_file;
  if (isset($file)) {
    $static_file = $file;
  }
  return $file;
}

/**
 * Submission action for user_badges_images_form
 *
 * Save the uploaded file or delete the selected one
 */
function user_badges_images_form_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  // Save uploaded files
  if ($op == t('Upload')) {
    $file = $form_state['values']['file_image'];
    file_set_status($file, FILE_STATUS_PERMANENT);
  }
  elseif ($op == t('Delete')) {
    foreach ($form_state['values']['images'] as $path => $is_removed) {
      if ($is_removed) {
        $to_delete[] = $path;
      }
    }
    if (is_array($to_delete)) {
      user_badges_image_delete($to_delete);
    }
  }
}

/**
 * Delete the specified image
 */
function user_badges_image_delete($to_delete) {
  foreach ($to_delete as $path) {
    if (file_check_location($path, file_create_path('badges'))) {
      file_delete($path);
    }
  }
}

/**
 * form to associated badges with roles
 */
function user_badges_roles_form() {
  $roles = user_roles();
  $badges = user_badges_get_roles(NULL, array('returnbadges' => TRUE));

  $form['blocked'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blocked Badge'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );
  $form['blocked'][0] = array(
    '#type' => 'textfield',
    '#title' => t('blocked user'),
    '#size' => 40,
    '#maxlength' => 255,
    '#autocomplete_path' => 'user_badges/autocomplete',
    '#default_value' => isset($badges[0]) ? $badges[0]->name . ' ' . t('(Badge ID') . ' ' . $badges[0]->bid .')' : '',
    '#field_suffix' => isset($badges[0]) ? ' ' . t('Current:') . ' ' . theme('image', $badges[0]->image, $badges[0]->image, $badges[0]->image) : '',
  );

  $form['roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role Badges'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  foreach ($roles as $rid => $role) {
    if ($rid != 1) { // no badges for the anonymous role
      $form['roles'][$rid] = array(
        '#type' => 'textfield',
        '#title' => $role,
        '#size' => 40,
        '#maxlength' => 255,
        '#autocomplete_path' => 'user_badges/autocomplete',
        '#default_value' => isset($badges[$rid]) ? $badges[$rid]->name . ' ' . t('(Badge ID') . ' ' . $badges[$rid]->bid .')' : '',
        '#field_suffix' => isset($badges[$rid]) ? ' ' . t('Current:') . ' ' . theme('image', $badges[$rid]->image, $badges[$rid]->image, $badges[$rid]->image) : '',
      );
    }
  }
  $form[] = array(
    '#type' => 'submit',
    '#value' => t('Save Role Badges'),
  );
  return $form;
}

/**
 * validation function for user_badges_roles_form
 */
function user_badges_roles_form_validate($form, &$form_state) {
  $array = $form_state['values']['roles'] + $form_state['values']['blocked'];
  //Go through all the entries and make sure they all have a valid badge ID
  foreach ($array as $field => $value) {
    if (!empty($value)) {
      //The field isn't empty, so we should validate it
      $validation = user_badges_badge_autocomplete_validation($value);
      //Is it correctly formatted?
      if ($validation[1] == 'string') {
        if ($field == 0) {
          form_set_error('blocked]['. $field, t('"@value" is not a valid badge name. Try using the autocomplete function (requires javascript).', array('@value' => $value)));
        }
        else {
          form_set_error('roles]['. $field, t('"@value" is not a valid badge name. Try using the autocomplete function (requires javascript).', array('@value' => $value)));
        }
      }
      //The format was correct, but we need to check the bid exists
      elseif ($validation[1] == 'nobid') {
        if ($field == 0) {
          form_set_error('blocked]['. $field, t('@value is not a valid badge ID. Try using the autocomplete function (requires javascript).', array('@value' => $validation[0])));
        }
        else {
          form_set_error('roles]['. $field, t('@value is not a valid badge ID. Try using the autocomplete function (requires javascript).', array('@value' => $validation[0])));
        }
      }
    }
  }
}

/**
 * submission function for user_badges_roles_form
 */
function user_badges_roles_form_submit($form, &$form_state) {
  $array = $form_state['values']['roles'] + $form_state['values']['blocked'];
  foreach ($array as $field => &$value) {
    //We now have a string as our badge, so just extract the bid
    preg_match('/\('. t('Badge ID') .' (\d+)\)/', $value, $matches);
    //Transform our value into just the bid
    $value = $matches[1];
  }
  user_badges_save_roles($array);
}

/**
 * Form for general module settings.
 */
function user_badges_settings_form() {
  $noyes = array(t('No'), t('Yes'));

  $form['showone'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of badges to display'),
    '#size' => 4,
    '#maxlength' => 4,
    '#default_value' => variable_get('user_badges_showone', 0),
    '#description' => t('Only this many badges with the lightest weights will be shown.') .'<br/>'.
      t('Set to zero to apply no limit.') .'<br/>'.
      t('Note that if multiple badges have the same lightest weight, only one of them will appear (first by alphabetical order).'),
    );

  $form['showblocked'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#title' => t('Only show blocked user badge'),
    '#default_value' => variable_get('user_badges_showblocked', 0),
    '#description' => t('If checked, only the badge associated to blocked users will be shown, overriding other badges the user eventually has as well as any other settings.') .' <br />'.
      t('Note that if there is no badge associated to blocked users, no badges will appear.') .' <br />'.
      t('This option only acts on blocked users and has no repercussions on active user badges.'),
    '#attributes' => array('class' => 'container-inline'),
    );

  $form['userweight'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#title' => t('Allow users to reorder badges'),
    '#default_value' => variable_get('user_badges_userweight', 0),
    '#description' => t('If checked, users will have the ability to reweight their badges in their profile, enabling them to set what order their badges display, and also which badges will display if a limit is set above.') .' <br />'.
      t('Note that you can make individual badges exempt from this function, allowing you to force them to the top or bottom of the list by giving them a very high or low weight value.') .' <br />',
    '#attributes' => array('class' => 'container-inline'),
    );

  if (module_exists('imagecache')) {
    $form['imagecache'] = array(
      '#type' => 'radios',
      '#options' => $noyes,
      '#title' => t('Allow ImageCache to size badges'),
      '#default_value' => variable_get('user_badges_imagecache', 0),
      '#description' => t('The ImageCache module is available, if you choose this option, it will be used to format the badge image. The preset name is "user-badges".'),
      '#attributes' => array('class' => 'container-inline'),
      );
  }
  else {
    $form['imagecache'] = array('#type' => 'value', '#value' => 0);
  }

  $form['defaulthref'] = array(
    '#type' => 'textfield',
    '#title' => t('Default badge link URL'),
    '#size' => 60,
    '#maxlength' => 500,
    '#default_value' => variable_get('user_badges_defaulthref', ''),
    '#description' => t('Enter a default URL to link all badges to. You can override this for individual badges.'),
    );

  // Tokens help.
  if (module_exists('token')) {
    $form['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      );
    $form['token_help']['help'] = array(
      '#value' => theme('token_help', array('userbadge', 'user')),
      );
  }
  else {
    $form['token_help']['help'] = array(
      // Ignore Coder flag on link.
      '#value' => t('Install the !link module if you want this URL to include dynamic elements such as badge ID numbers.', array('!link' => l('Token', 'http://drupal.org/project/token', array('absolute' => TRUE)))),
      );
  }

  //Let the user select a vocabulary to associate with badges
  if (module_exists('taxonomy')) {
    //Build the options for the element
    $vocabs = taxonomy_get_vocabularies();
    $selects = array('' => t('&lt;none&gt;'));
    foreach ($vocabs as $vid => $vocab) {
      $selects[$vid] = $vocab->name;
    }

    $form['vid'] = array(
      '#type' => 'radios',
      '#title' => t('Vocabulary'),
      '#default_value' => variable_get('user_badges_vid', ''),
      '#options' => $selects,
      '#description' => t('Optional. Select a vocabulary to associate badges with. You can optionally associate each badge with one term in this vocabulary.'),
      '#attributes' => array('class' => 'container-inline'),
      );
  }

  $form[] = array('#type' => 'submit', '#value' => t('Save configuration'));
  return $form;
}

/**
 * validate user_badges_settings_form input
 */
function user_badges_settings_form_validate($form, $form_state) {
  //'showone' must be numeric
  if ( !is_numeric($form_state['values']['showone']) || $form_state['values']['showone'] < 0 ) {
    form_set_error('showone', t('Must be a positive number.'));
  }
}

/**
 * submission function for user_badges_settings_form
 *
 * Set the variables and display a message about the set values.
 */
function user_badges_settings_form_submit($form, $form_state) {
  variable_set('user_badges_showone', $form_state['values']['showone']);
  variable_set('user_badges_showblocked', $form_state['values']['showblocked']);
  variable_set('user_badges_userweight', $form_state['values']['userweight']);
  variable_set('user_badges_imagecache', $form_state['values']['imagecache']);

  //Only set a defaulthref if we have some non-whitespace in there
  if (preg_match("/\S/", $form_state['values']['defaulthref'])) {
    variable_set('user_badges_defaulthref', $form_state['values']['defaulthref']);
  }

  //Only set a vid if we have a value, otherwise wipe it for none/no taxonomy
  if ($form_state['values']['vid']) {
    variable_set('user_badges_vid', $form_state['values']['vid']);
  }
  else {
    variable_del('user_badges_vid');
  }

  drupal_set_message(t('Configuration saved.'));
}

/**
 * Select options for printing a list of images in the image library
 *
 * @return
 *   An array of images from the image library, in the form $filename => $image_html
 */
function user_badges_image_selects() {
  $selects = array();
  $dir = file_create_path('badges');
  $files = file_scan_directory($dir, '.*\.(((J|j)(p|P)(g|G))|((p|P)(n|N)(g|G))|((g|G)(i|I)(f|F)))', array('.', '..', 'CVS'), 0, FALSE);
  foreach ($files as $file) {
    $selects[$file->filename] = theme('image', $file->filename, $file->filename, $file->filename);
  }

  return $selects;
}

