<?php
// $Id: pathauto.admin.inc,v 1.10.2.3 2010/02/20 18:27:45 davereid Exp $

/**
 * @file
 * Admin page callbacks for the Pathauto module.
 *
 * @ingroup pathauto
 */

/**
 * Form builder; Configure the Pathauto system.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function pathauto_admin_settings() {
  _pathauto_include();

  // Make sure they have token
  if (!function_exists('token_get_list')) {
    drupal_set_message(t('It appears that the <a href="@token_link">Token module</a> is not installed. Please ensure that you have it installed so that Pathauto can work properly. You may need to disable Pathauto and re-enable it to get Token enabled.', array('@token_link' => 'http://drupal.org/project/token')), 'error');
    return;
  }

  // Default words to ignore
  $ignore_words = array(
    'a', 'an', 'as', 'at', 'before', 'but', 'by', 'for', 'from', 'is', 'in',
    'into', 'like', 'of', 'off', 'on', 'onto', 'per', 'since', 'than', 'the',
    'this', 'that', 'to', 'up', 'via', 'with',
  );

  // Generate the form - settings applying to all patterns first
  $group_weight = -20;
  $form['general'] = array(
    '#type' => 'fieldset',
    '#weight' => $group_weight,
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $group_weight++;

  $form['general']['pathauto_verbose'] = array(
    '#type' => 'checkbox',
    '#title' => t('Verbose'),
    '#default_value' => variable_get('pathauto_verbose', FALSE),
    '#description' => t('Display alias changes (except during bulk updates).'),
  );

  $form['general']['pathauto_separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Separator'),
    '#size' => 1,
    '#maxlength' => 1,
    '#default_value' => variable_get('pathauto_separator', '-'),
    '#description' => t('Character used to separate words in titles. This will replace any spaces and punctuation characters. Using a space or + character can cause unexpected results.'),
  );

  $form['general']['pathauto_case'] = array(
    '#type' => 'radios',
    '#title' => t('Character case'),
    '#default_value' => variable_get('pathauto_case', 1),
    '#options' => array(t('Leave case the same as source token values.'), t('Change to lower case')),
  );

  $form['general']['pathauto_max_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum alias length'),
    '#size' => 3,
    '#maxlength' => 3,
    '#default_value' => variable_get('pathauto_max_length', 100),
    '#description' => t('Maximum length of aliases to generate. 100 is recommended. See <a href="@pathauto-help">Pathauto help</a> for details.', array('@pathauto-help' => url('admin/help/pathauto'))),
  );

  $form['general']['pathauto_max_component_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum component length'),
    '#size' => 3,
    '#maxlength' => 3,
    '#default_value' => variable_get('pathauto_max_component_length', 100),
    '#description' => t('Maximum text length of any component in the alias (e.g., [title]). 100 is recommended. See <a href="@pathauto-help">Pathauto help</a> for details.', array('@pathauto-help' => url('admin/help/pathauto'))),
  );

  $form['general']['pathauto_max_bulk_update'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of objects to alias in a bulk update'),
    '#size' => 4,
    '#maxlength' => 4,
    '#default_value' => variable_get('pathauto_max_bulk_update', 50),
    '#description' => t('Maximum number of objects of a given type which should be aliased during a bulk update. The default is 50 and the recommended number depends on the speed of your server. If bulk updates "time out" or result in a "white screen" then reduce the number.'),
  );

  $actions = array(
    t('Do nothing. Leave the old alias intact.'),
    t('Create a new alias. Leave the existing alias functioning.'),
    t('Create a new alias. Delete the old alias.'));

  if (function_exists('path_redirect_save')) {
    $actions[] = t('Create a new alias. Redirect from old alias.');
  }
  elseif (variable_get('pathauto_update_action', 2) == 3) {
    // the redirect action is selected, but path_redirect is not enabled
    // let's set the variable back to the default
    variable_set('pathauto_update_action', 2);
  }

  $form['general']['pathauto_update_action'] = array(
    '#type' => 'radios',
    '#title' => t('Update action'),
    '#default_value' => variable_get('pathauto_update_action', 2),
    '#options' => $actions,
    '#description' => t('What should pathauto do when updating an existing content item which already has an alias?'),
  );

  $disable_transliteration = TRUE;
  $path = drupal_get_path('module', 'pathauto');
  $transliteration_help = t('When a pattern includes certain characters (such as those with accents) should Pathauto attempt to transliterate them into the ASCII-96 alphabet? Transliteration is determined by the i18n-ascii.txt file in the Pathauto directory. <strong>This option is disabled on your site because you do not have an i18n-ascii.txt file in the Pathauto directory.</strong>');
  if (is_file($path .'/i18n-ascii.txt')) {
    $disable_transliteration = FALSE;
    $transliteration_help = t('When a pattern includes certain characters (such as those with accents) should Pathauto attempt to transliterate them into the ASCII-96 alphabet? Transliteration is determined by the i18n-ascii.txt file in the Pathauto directory.');
  }
  else {
    // Perhaps they've removed the file, set the transliterate option to FALSE
    variable_set('pathauto_transliterate', FALSE);
  }
  $form['general']['pathauto_transliterate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Transliterate prior to creating alias'),
    '#default_value' => variable_get('pathauto_transliterate', FALSE),
    '#description' => $transliteration_help,
    '#disabled' => $disable_transliteration,
  );
  $form['general']['pathauto_reduce_ascii'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reduce strings to letters and numbers from ASCII-96'),
    '#default_value' => variable_get('pathauto_reduce_ascii', FALSE),
    '#description' => t('Filters the new alias to only letters and numbers found in the ASCII-96 set.'),
  );

  $form['general']['pathauto_ignore_words'] = array(
    '#type' => 'textarea',
    '#title' => t('Strings to Remove'),
    '#default_value' => variable_get('pathauto_ignore_words', implode(',', $ignore_words)),
    '#description' => t('Words to strip out of the URL alias, separated by commas. Do not place punctuation in here and do not use WYSIWYG editors on this field.'),
    '#wysiwyg' => FALSE,
  );

  $form['punctuation'] = array(
    '#type' => 'fieldset',
    '#weight' => $group_weight,
    '#title' => t('Punctuation settings'), '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $group_weight++;

  $punctuation = pathauto_punctuation_chars();
  foreach ($punctuation as $name => $details) {
    $details['default'] = 0;
    if ($details['value'] == variable_get('pathauto_separator', '-')) {
      $details['default'] = 1;
    }
    $form['punctuation']['pathauto_punctuation_'. $name] = array(
      '#type' => 'select',
      '#title' => $details['name'],
      '#default_value' => variable_get('pathauto_punctuation_'. $name, $details['default']),
      '#options' => array(
        '0' => t('Remove'),
        '1' => t('Replace by separator'),
        '2' => t('No action (do not replace)'),
      ),
    );
  }

  // Call the hook on all modules - an array of 'settings' objects is returned
  $all_settings = module_invoke_all('pathauto', 'settings');
  $modulelist = '';
  $indexcount = 0;
  foreach ($all_settings as $settings) {
    $items = '';
    $module = $settings->module;
    $modulelist[] = $module;
    $patterndescr = $settings->patterndescr;
    $patterndefault = $settings->patterndefault;
    $groupheader = $settings->groupheader;
    $supportsfeeds = isset($settings->supportsfeeds) ? $settings->supportsfeeds : NULL;
    variable_set('pathauto_'. $module .'_supportsfeeds', $supportsfeeds);

    $form[$module] = array(
      '#type' => 'fieldset',
      '#title' => $groupheader,
      '#weight' => $group_weight,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $group_weight++;

    // Prompt for the default pattern for this module
    $variable = 'pathauto_'. $module .'_pattern';
    $description = '';
    if (!count($_POST)) {
      $error = _pathauto_check_pattern(variable_get($variable, $patterndefault), $settings->token_type);
      if ($error) {
        $form[$module]['#collapsed'] = FALSE;
        $description = $error;
      }
    }
    $form[$module][$variable] = array(
      '#type' => 'textfield',
      '#title' => $patterndescr,
      '#default_value' => variable_get($variable, $patterndefault),
      '#description' => $description,
      '#size' => 65,
      '#maxlength' => 1280,
    );

    // If the module supports a set of specialized patterns, set
    // them up here
    if (isset($settings->patternitems)) {
      foreach ($settings->patternitems as $itemname => $itemlabel) {
        $variable = 'pathauto_'. $module .'_'. $itemname .'_pattern';
        $description = '';
        if (!count($_POST)) {
          $error = _pathauto_check_pattern(variable_get($variable, $patterndefault), $settings->token_type);
          if ($error) {
            $form[$module]['#collapsed'] = FALSE;
            $description = $error;
          }
        }

        $form[$module][$variable] = array('#type' => 'textfield',
          '#title' => $itemlabel,
          '#default_value' => variable_get($variable, ''),
          '#description' => $description,
          '#size' => 65,
          '#maxlength' => 1280);
      }
    }

    // Display the user documentation of placeholders supported by
    // this module, as a description on the last pattern
    $doc = "<dl>\n";
    foreach ($settings->placeholders as $name => $description) {
      $doc .= '<dt>'. $name .'</dt>';
      $doc .= '<dd>'. $description .'</dd>';
    }
    $doc .= "</dl>\n";
    $form[$module]['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t('Use -raw replacements for text to avoid problems with HTML entities.'),
    );
    $form[$module]['token_help']['help'] = array(
      '#value' => $doc,
    );

    // If the module supports bulk updates, offer the update action here
    if ($settings->bulkname) {
      $variable = 'pathauto_'. $module .'_bulkupdate';
      if (variable_get($variable, FALSE)) {
        variable_set($variable, FALSE);
        $function = $module .'_pathauto_bulkupdate';
        call_user_func($function);
      }
      $form[$module][$variable] = array(
        '#type' => 'checkbox',
        '#title' => $settings->bulkname,
        '#default_value' => FALSE,
        '#description' => $settings->bulkdescr,
      );
    }

    // If the module supports feeds, offer to generate aliases for them
    if ($supportsfeeds) {
      $variable = 'pathauto_'. $module .'_applytofeeds';
      $current = variable_get($variable, $supportsfeeds);
      // This checks for the old style from 2.0 and earlier. TODO: At some point we can drop that.
      if (is_numeric($current)) {
        $current = $supportsfeeds;
      }

      $form[$module][$variable] = array(
        '#type' => 'textfield',
        '#title' => t('Internal feed alias text (leave blank to disable)'),
        '#size' => 65,
        '#maxlength' => 1280,
        '#default_value' => $current,
        '#description' => t('The text to use for aliases for RSS feeds. Examples are "feed" and "0/feed".'),
      );
    }

  }

  if (isset($do_index_bulkupdate) && $do_index_bulkupdate) {
    drupal_set_message(format_plural($indexcount,
      'Bulk generation of index aliases completed, one alias generated.',
      'Bulk generation of index aliases completed, @count aliases generated.'));
  }

  // Keep track of which modules currently support pathauto
  variable_set('pathauto_modulelist', $modulelist);

  return system_settings_form($form);
}

/**
 * Helper function for pathauto_admin_settings().
 *
 * See if they are using all -raw tokens available
 * and if all the tokens are valid in the given context.
 *
 * @param $pattern
 *   A string containing the pattern to be tested.
 * @param $type
 *   A flag indicating the class of substitution tokens to use.
 * @return
 *   A status flag, telling whether there is an error or not.
 * @see token_get_list()
 *   For more information on the $type parameter.
 */
function _pathauto_check_pattern($pattern, $type) {
  // Hold items we've warned about so we only warn once per token
  static $warned;
  $return = FALSE;

  // Build up a set of all tokens in a format that's easy to search
  $all_tokens = array();
  $tokens = token_get_list($type);
  foreach ($tokens as $actual_tokens) {
    foreach (array_keys($actual_tokens) as $token) {
      $all_tokens[$token] = $token;
    }
  }

  // Now, search the pattern and evaluate its contents.
  $matches = array();
  if (preg_match_all('/\[[a-zA-z_\-]+?\]/i', $pattern, $matches)) {
    // Loop over each found token.
    foreach ($matches[0] as $id => $token) {
      $token = str_replace('[', '', str_replace(']', '', $token));
      // Check if the token is even valid in this context.
      if (!array_key_exists($token, $all_tokens)) {
        drupal_set_message(t('You are using the token [%token] which is not valid within the scope of tokens where you are using it.', array('%token' => $token)), 'error');
        $return[] = $token;
      }
      // Check if there is a raw companion that they should be using.
      elseif (!preg_match('/\-raw/i', $token)) {
        $raw_token = $token .'-raw';
        if (array_key_exists($raw_token, $all_tokens)) {
          if (!isset($warned) || !array_key_exists($token, $warned)) {
            drupal_set_message(t('You are using the token [%token] which has a -raw companion available [%raw_token]. For Pathauto patterns you should use the -raw version of tokens unless you really know what you are doing. See the <a href="@pathauto-help">Pathauto help</a> for more details.', array('%token' => $token, '%raw_token' => $raw_token, '@pathauto-help' => url('admin/help/pathauto'))), 'error');
            $warned[$token] = $token;
          }
          $return[] = $token;
        }
      }
    }
  }

  if ($return) {
    $description = t('NOTE: This field contains potentially incorrect patterns. ');
    $description .= format_plural(count($return), 'Problem token: ', 'Problem tokens: ');
    $description .= t('%problems', array('%problems' => implode(', ', $return)));
    $return = $description;
  }

  return $return;
}

/**
 * Validate pathauto_admin_settings form submissions.
 */
function pathauto_admin_settings_validate($form, &$form_state) {
  // Validate that the separator is not set to be removed per http://drupal.org/node/184119
  // This isn't really all that bad so warn, but still allow them to save the value.
  $separator = $form_state['values']['pathauto_separator'];
  $punctuation = pathauto_punctuation_chars();
  foreach ($punctuation as $name => $details) {
    if ($details['value'] == $separator) {
      $action = $form_state['values']['pathauto_punctuation_'. $name];
      if ($action == 0) {
        drupal_set_message(t('You have configured the @name to be the separator and to be removed when encountered in strings. This can cause problems with your patterns and especially with the catpath and termpath patterns. You should probably set the action for @name to be "replace by separator"', array('@name' => $details['name'])), 'error');
      }
    }
  }
}

/**
 * Menu callback; select certain alias types to delete.
 */
function pathauto_admin_delete() {
  /* TODO:
   1) all - DONE
   2) all node aliases - DONE
   4) all user aliases - DONE
   5) all taxonomy aliases - DONE
   6) by node type
   7) by taxonomy vocabulary
   8) no longer existing aliases (see http://drupal.org/node/128366 )
   9) where src like 'pattern' - DON'T DO
   10) where dst like 'pattern' - DON'T DO
  */

  $form = array();
  $form['delete'] = array(
    '#type' => 'fieldset',
    '#title' => t('Choose Aliases to Delete'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  // First we do the "all" case
  $total_count = db_result(db_query('SELECT count(1) FROM {url_alias}'));
  $form['delete']['all_aliases'] = array(
    '#type' => 'checkbox',
    '#title' => t('all aliases'),
    '#default_value' => FALSE,
    '#description' => t('Delete all aliases. Number of aliases which will be deleted: %count.', array('%count' => $total_count)),
  );

  // Next, iterate over an array of objects/alias types which can be deleted and provide checkboxes
  $objects = module_invoke_all('path_alias_types');
  foreach ($objects as $internal_name => $label) {
    $count = db_result(db_query("SELECT count(1) FROM {url_alias} WHERE src LIKE '%s%%'", $internal_name));
    $form['delete'][$internal_name] = array(
      '#type' => 'checkbox',
      '#title' => $label, // This label is sent through t() in the hard coded function where it is defined
      '#default_value' => FALSE,
      '#description' => t('Delete aliases for all @label. Number of aliases which will be deleted: %count.', array('@label' => $label, '%count' => $count)),
    );
  }

  // Warn them and give a button that shows we mean business
  $form['warning'] = array('#value' => t('<p><strong>Note:</strong> there is no confirmation. Be sure of your action before clicking the "Delete aliases now!" button.<br />You may want to make a backup of the database and/or the url_alias table prior to using this feature.</p>'));
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete aliases now!'),
  );

  return $form;
}

/**
 * Process pathauto_admin_delete form submissions.
 */
function pathauto_admin_delete_submit($form, &$form_state) {
  foreach ($form_state['values'] as $key => $value) {
    if ($value) {
      if ($key === 'all_aliases') {
        db_query('DELETE FROM {url_alias}');
        drupal_set_message(t('All of your path aliases have been deleted.'));
      }
      $objects = module_invoke_all('path_alias_types');
      if (array_key_exists($key, $objects)) {
        db_query("DELETE FROM {url_alias} WHERE src LIKE '%s%%'", $key);
        drupal_set_message(t('All of your %type path aliases have been deleted.', array('%type' => $objects[$key])));
      }
    }
  }
  $form_state['redirect'] = 'admin/build/path/delete_bulk';
}
