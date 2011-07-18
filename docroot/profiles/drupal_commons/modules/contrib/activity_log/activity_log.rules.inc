<?php

/**
 * @file
 *   Rules integration for the Activity Log module.
 */

//==================
// ADMIN UI: STEP 1
//==================

/**
 * The form callback for the activity logging action.
 */
function activity_log_log_action_form($settings, &$form) {
  $languages = language_list();
  $translate = count($languages) > 1;
  $form['label']['#title'] = t('Administrative label');
  drupal_add_js(drupal_get_path('module', 'activity_log') .'/activity_log.admin.js');
  $settings += array(
    'placeholder' => '',
    'public_name' => '',
    'templates' => array(),
    'grouping' => array(
      'group_method' => 'none',
      'group_interval' => 86400,
      'group_max' => 100,
      'group_summary' => '',
      'collapse_method' => 'activity_log_collection_inline',
      'templates' => array(),
    ),
    'visibility' => array(
      'stream_owner_entity_group' => array('custom' => 'custom'), // defaults to acting user, but acting_uid field is hidden
      'stream_owner_id' => '',
      'stream_owner_type' => 'user',
      'viewer_entity_group' => array('everyone' => 'everyone'),
      'viewer_id' => '',
    ),
    'cache' => array(
      'cache' => TRUE,
    ),
    'acting_uid' => '',
  );
  $form['settings']['placeholder'] = array(
    '#type' => 'value',
    '#value' => '',
  );
  $form['settings']['public_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Public name of this activity type'),
    '#description' => t('The name of the activity as shown to users who have permission to disable certain activity types in their stream.') .' '.
      t('Leave this field blank if you do not want to allow users to disable viewing messages about this activity type.') .' '.
      t('This field does not accept tokens.'),
    '#default_value' => $settings['public_name'],
    '#autocomplete_path' => 'activity_log/autocomplete/public_name',
  );
  $form['settings']['templates'] = $translate ? array(
    '#type' => 'fieldset',
    '#title' => t('Language templates'),
    '#description' => t('Set the localized templates for messages for this activity type.') .' '.
      t("If a language has no translation, it will fall back to the template for the site's default language."),
    '#attributes' => array('id' => 'edit-settings-templates-fieldset'),
  ) : array(
    '#prefix' => '<div id="edit-settings-templates-fieldset">',
    '#suffix' => '</div>',
  );
  foreach ($languages as $name => $lang) {
    if (!isset($settings['templates'][$name])) {
      $settings['templates'][$name] = array('template' => '');
    }
    $is_default = language_default('language') == $name;
    $form['settings']['templates'][$name] = array(
      '#type' => 'fieldset',
      '#title' => filter_xss($lang->name),
      '#collapsible' => !$is_default || $translate,
      '#collapsed' => !$is_default,
    );
    $form['settings']['templates'][$name]['template'] = array(
      '#type' => 'textarea',
      '#title' => t('@lang activity message template', array('@lang' => $lang->name)),
      '#default_value' => $settings['templates'][$name]['template'],
      '#rows' => 3,
      '#required' => $is_default,
    );
  }
  $form['settings']['grouping'] = array(
    '#type' => 'fieldset',
    '#title' => t('Group similar messages'),
    '#collapsible' => TRUE,
    '#collapsed' => $settings['grouping']['group_method'] == 'none',
    '#description' => '<p>'. t('Filling in these settings will allow grouping activity messages of this type in activity streams.') .' '.
      t('That way, instead of saying e.g. "Jack likes this" and "Jill likes this" separately, only one message can appear saying "Jack and Jill like this."') .' '.
      t('Messages will be grouped if there are at least two similar messages.') .' '.
      t('<strong>Warning:</strong> displaying grouped messages is slower than displaying ungrouped messages.') .'</p>',
  );
  $form['settings']['grouping']['group_method'] = array(
    '#type' => 'radios',
    '#title' => t('Group by'),
    '#description' =>
      t('Grouping by the target entity shows multiple users who took the same action on an object, like "Jane and Joe commented on this node."') .' '.
      t('You may want to group by action in cases where the result is trivial, such as changing profile pictures.') .' '.
      t('Group by the acting user when the fact that the user took action is more important than the action taken.') .' '.
      t('For example, you might group by the acting user on that user\'s profile for a "joined a group" action in order to get a message like "John joined the groups Drupal and Web Development."'),
    '#required' => TRUE,
    '#default_value' => $settings['grouping']['group_method'],
    '#options' => array(
      'none' => t('Do not group actions of this type'),
      'target_action' => t('Group by action and the entity on which the action was performed'),
      'action' => t('Group by just the action'),
      'user_action' => t('Group by the acting user and the action performed'),
    ),
  );
  $form['settings']['grouping']['group_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum duration between activities to allow grouping'),
    '#description' => t('The oldest an activity record can be (in seconds) and still be grouped together with a new activity.'),
    '#field_suffix' => t('seconds'),
    '#default_value' => $settings['grouping']['group_interval'],
  );
  $form['settings']['grouping']['group_max'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of items allowed in a grouped message'),
    '#description' => t('Do not allow combining more than this many similar messages into the same message.'),
    '#default_value' => $settings['grouping']['group_max'],
  );
  $form['settings']['grouping']['group_summary'] = array(
    '#type' => 'textarea',
    '#title' => t('Grouped item name'),
    '#description' => t('A summary of one of the grouped items. For example, if you grouped by user on the "add node" action, you might enter "[node:title]" in this field.'),
    '#default_value' => $settings['grouping']['group_summary'],
    '#rows' => 1,
  );
  $options = module_invoke_all('activity_log_collapse_methods');
  $form['settings']['grouping']['collapse_method'] = array(
    '#type' => 'select',
    '#title' => t('Collection format'),
    '#description' => t('The format used to evaluate the [collection] token in the grouped message template below.'),
    '#required' => TRUE,
    '#default_value' => $settings['grouping']['collapse_method'],
    '#options' => $options,
  );
  $form['settings']['grouping']['templates'] = $translate ? array(
    '#type' => 'fieldset',
    '#title' => t('Language templates'),
    '#description' => t('Set the localized templates for grouped messages for this activity type.') .' '.
      t("If a language has no translation, it will fall back to the template for the site's default language."),
    '#attributes' => array('id' => 'edit-settings-grouping-templates-fieldset'),
  ) : array(
    '#prefix' => '<div id="edit-settings-grouping-templates-fieldset">',
    '#suffix' => '</div>',
  );
  foreach ($languages as $name => $lang) {
    if (!isset($settings['grouping']['templates'][$name])) {
      $settings['grouping']['templates'][$name] = array('template' => '');
    }
    $is_default = language_default('language') == $name;
    $form['settings']['grouping']['templates'][$name] = array(
      '#type' => 'fieldset',
      '#title' => filter_xss($lang->name),
      '#collapsible' => !$is_default || $translate,
      '#collapsed' => !$is_default,
    );
    $form['settings']['grouping']['templates'][$name]['template'] = array(
      '#type' => 'textarea',
      '#title' => t('@lang grouped message template', array('@lang' => $lang->name)),
      '#default_value' => $settings['grouping']['templates'][$name]['template'],
      '#rows' => 3,
      '#description' => '<p>'. t('The format of the grouped message.') .' '.
        t('The token <em>[names]</em> will be replaced with the names of the users who took this action.') .' '.
        '<span class="activity-log-admin-description">'.
          t('Additionally, the token <em>[collection]</em> will be replaced with summaries of the target objects formatted according to the "Grouped item name" setting above,') .' '.
          t('and the token <em>[count]</em> will be replaced with the number of items in this summary.')
        .'</span> '.
        t('For example, the template "[names] like the [node:type] [node:title]" might produce something like "Jack and Jill like the page Slippery Slopes."') .'</p>',
    );
  }
  $groups = module_invoke_all('activity_log_entity_groups');
  uasort($groups, 'activity_log_element_sort');
  $options = array();
  $expose_fields = array();
  foreach ($groups as $name => $group) {
    $options[$name] = $group['title'];
    if (!empty($group['expose fields'])) {
      $expose_fields[$name] = $group['expose fields'];
    }
  }
  drupal_add_js(array('activity_log' => array('stream_owner_expose_fields' => $expose_fields)), 'setting');
  $form['settings']['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility'),
    '#description' => t('Configure where and to whom the message will appear.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['settings']['visibility']['stream_owner_entity_group'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Entities in whose stream activity records generated from this template should appear'),
    '#description' => t('Not all available options make sense for every activity type.') .' '.
      t('<strong>Warning:</strong> Choosing multiple streams can cause recording and retrieving activities to be slower on large sites.'),
    '#required' => TRUE,
    '#default_value' => $settings['visibility']['stream_owner_entity_group'],
    '#options' => $options,
  );
  $form['settings']['visibility']['stream_owner_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom stream owner ID'),
    '#description' => t('Enter the ID of the entity in whose activity stream the activity records generated from this template should appear.') .' '.
      t('If not specified, defaults to the acting user.'),
    '#default_value' => $settings['visibility']['stream_owner_id'],
  );
  $form['settings']['visibility']['stream_owner_type'] = array(
    '#type' => 'select',
    '#title' => t('Custom stream owner type'),
    '#description' => t('The type of entity on whose stream the activity record will appear.'),
    '#default_value' => $settings['visibility']['stream_owner_type'],
    '#options' => activity_log_get_rules_data_types(),
  );
  $groups = module_invoke_all('activity_log_entity_groups', FALSE);
  uasort($groups, 'activity_log_element_sort');
  $options = array();
  $expose_fields = array();
  foreach ($groups as $name => $group) {
    $options[$name] = $group['title'];
    if (!empty($group['expose fields'])) {
      $expose_fields[$name] = $group['expose fields'];
    }
  }
  drupal_add_js(array('activity_log' => array('viewer_expose_fields' => $expose_fields)), 'setting');
  $form['settings']['visibility']['viewer_entity_group'] = array(
    '#type' => 'checkboxes',
    '#title' => t('The users who will be able to see this message'),
    '#description' => t('Not all available options make sense for every activity type.') .' '.
      t('<strong>Warning:</strong> Choosing multiple user groups can cause recording and retrieving activities to be slower on large sites.'),
    '#required' => TRUE,
    '#default_value' => $settings['visibility']['viewer_entity_group'],
    '#options' => $options,
  );
  $form['settings']['visibility']['viewer_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom viewing user ID'),
    '#description' => t('Enter the ID of the user who should be able to see this message.') .' '.
      t('If not specified, defaults to the acting user.'),
    '#default_value' => $settings['visibility']['viewer_id'],
  );
  $form['settings']['cache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cache'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['settings']['cache']['cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Cache messages generated by this action'),
    '#description' => t('Caching is <strong>strongly recommended</strong> for performance reasons.') .' '.
      t('However, you may want to turn off caching if you encounter problems with messages displaying stale information or if CSS or JS files are missing for cached messages.'),
    '#default_value' => $settings['cache']['cache'],
  );
  $form['settings']['cache']['resources'] = array(
    '#type' => 'textarea',
    '#title' => t('Load custom CSS or JS files for cached messages'),
    '#description' => t('If you notice that CSS or JS files are missing for cached messages for this action, you can force them to be loaded here.') .' '.
      t('Enter the path to each file from your Drupal root directory on separate lines.') .' '.
      t('For example, <code>!css</code>.', array('!css' => drupal_get_path('module', 'activity_log') .'/activity_log.css')),
    '#default_value' => $settings['cache']['resources'],
    '#rows' => 2,
    '#disabled' => user_access('administer loading arbitrary CSS and JS files for cached messages'),
  );
  $form['#old_resources'] = $settings['cache']['resources'];
  $form['settings']['acting_uid'] = array(
    '#type' => 'textfield',
    '#title' => t('Acting user'),
    '#description' => t('Enter the ID of the user taking the action. If not specified, defaults to the current user at the time the action occurred.'),
    '#default_value' => $settings['acting_uid'],
  );
}

/**
 * The form validation callback for the activity logging action.
 */
function activity_log_log_action_validate($form, $form_state) {
  $v = $form_state['values']['settings']['grouping'];
  if (!empty($v['group_template'])) {
    if (!empty($v['group_interval']) && (!is_numeric($v['group_interval']) || $v['group_interval'] <= 0)) {
      form_set_error('settings][grouping][group_interval', t('The maximum duration between activities to allow grouping must be a positive number.'));
    }
    if (!empty($v['group_max']) && (!is_numeric($v['group_max']) && $v['group_max'] <= 0)) {
      form_set_error('settings][grouping][group_max', t('The maximum number of items allowed in a grouped message must be a positive number.'));
    }
    if ($v['group_method'] == 'action' || $v['group_method'] == 'user_action') {
      if (empty($v['group_interval'])) {
        form_set_error('settings][grouping][group_interval', t('You must enter a maximum duration between activities to allow grouping if you do not group by the target entity.'));
      }
      if (empty($v['group_max'])) {
        form_set_error('settings][grouping][group_max', t('You must enter a maximum number of items allowed in a grouped message if you do not group by the target entity.'));
      }
    }
  }
  if (!user_access('administer loading arbitrary CSS and JS files for cached messages')) {
    if ($form_state['values']['settings']['cache']['resources'] != $form['#old_resources']) {
      form_set_error('settings][cache][resources', t('Invalid submission detected: you do not have permission to edit the CSS and JS files that must be loaded with this activity.'));
    }
  }
}

/**
 * Implementation of hook_form_alter().
 *
 * Do some magic to the Rules Activity Log action form so we can record all the
 * data we need about the template.
 *
 * We can put this in our rules.inc instead of .module file because the two
 * forms we need to alter only exist when all rules.inc files have already been
 * loaded.
 */
function activity_log_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'rules_admin_form_edit' || $form_id == 'rules_admin_form_add') {
    if ($form_state['storage']['element']['#name'] == 'activity_log_log_action') {
      // Hide stream owner / viewer entity groups that are not applicable to this rule.
      $rules = _rules_get_rule_sets();
      $stream_owner_groups = module_invoke_all('activity_log_entity_groups');
      $viewer_groups = module_invoke_all('activity_log_entity_groups', FALSE);
      foreach (array('stream_owner', 'viewer') as $type) {
        $options = array();
        foreach ($form['settings']['visibility'][$type .'_entity_group']['#options'] as $callback => $name) {
          foreach ($rules[$form_state['proxy']->_rule['#set']]['info']['arguments'] as $key => $info) {
            if (!isset($stream_owner_groups[$callback]['data types']) || in_array($info['type'], $stream_owner_groups[$callback]['data types'])) {
              $options[$callback] = $name;
            }
          }
        }
        $form['settings']['visibility'][$type .'_entity_group']['#options'] = $options;
      }
      // Run our custom submit hooks.
      array_unshift($form['submit']['#submit'], 'activity_log_rules_admin_form_submit_before');
      if ($form_id == 'rules_admin_form_add') {
        array_push($form['submit']['#submit'], 'activity_log_rules_admin_form_submit_eval_after');
      }
      else {
        $form['#tid'] = $form_state['element']['#settings']['tid'];
      }
      array_push($form['submit']['#submit'], 'activity_log_rules_admin_form_submit_label_after');
      // Undo the prefix we added so the input evaluator knows this is the placeholder.
      if (isset($form['settings']['placeholder']['#value']) && strpos($form['settings']['placeholder']['#value'], ACTIVITY_LOG_DELIMITER) === 0) {
        $form['settings']['placeholder']['#value'] = drupal_substr($form['settings']['placeholder']['#value'], drupal_strlen(ACTIVITY_LOG_DELIMITER));
      }
    }
    // Remove the help for our input evaluator (because it's internal, not user-facing).
    unset($form['input_help']['activity_log_input_evaluator_process']);
  }
  elseif ($form_id == 'rules_admin_form_delete') {
    if (!empty($form['#parameters'][3]) && !empty($form['#parameters'][3]['#name']) && $form['#parameters'][3]['#name'] == 'activity_log_log_action') {
      $form['#submit'][] = 'activity_log_rules_admin_form_delete';
    }
  }
}

/**
 * Submit callback for the Rules action edit form.
 *
 * Record all of the information we need about a template.
 * This has to run before the Rules hooks so we can modify the settings values
 * before they get saved.
 */
function activity_log_rules_admin_form_submit_before($form, &$form_state) {
  $v = $form_state['values']['settings'];
  // If we're updating, find the existing template and public name.
  $rule = $form_state['proxy']->_rule_name;
  $pid = 0;
  $name = new stdClass();
  if (!empty($form['#tid'])) {
      $name = db_fetch_object(db_query("
        SELECT n.*
        FROM {activity_log_templates} t
        LEFT JOIN {activity_log_action_names} n
          ON t.pid = n.pid
        WHERE tid = %d
      ", $form['#tid']));
      $pid = $name->pid;
  }
  // If this is a new action or we changed the public name, check if the new name exists. If it doesn't, save the new value.
  if (empty($name) || $name->public_name != $v['public_name']) {
    $pid = db_result(db_query("SELECT pid FROM {activity_log_action_names} WHERE public_name = '%s'", $v['public_name']));
    if (empty($pid) && !empty($v['public_name'])) {
      $rec = (object) array('public_name' => $v['public_name']);
      drupal_write_record('activity_log_action_names', $rec);
      $pid = $rec->pid;
    }
  }
  // Determine the resources that need to be loaded for cached messages.
  $resources = _activity_log_determine_resources($v['templates'], $v['grouping']['templates'], $v['grouping']['group_summary'], $v['cache']['resources']);
  // Save the template.
  $record = (object) array(
    'rule' => $rule,
    'template' => serialize($v['templates']),
    'group_template' => serialize($v['grouping']['templates']),
    'group_summary' => $v['grouping']['group_summary'],
    'collapse_method' => $v['grouping']['collapse_method'],
    'pid' => $pid,
    'eval_input' => empty($form_state['element']['#settings']['#eval input']) ? '' : serialize($form_state['element']['#settings']['#eval input']),
    'resources' => serialize($resources),
    'cacheable' => $v['cache']['cache'] && !_activity_log_has_uncacheable_tokens($v['templates'], $v['grouping']['templates'], $v['grouping']['group_summary']),
  );
  if (!empty($form['#tid'])) {
    $record->tid = $form['#tid'];
    drupal_write_record('activity_log_templates', $record, array('tid'));
  }
  else {
    drupal_write_record('activity_log_templates', $record);
  }
  $form_state['values']['settings']['tid'] = $record->tid;
  // If switching values means that we've now abandoned an action name, remove it.
  if (isset($name->pid) && $name->pid != $pid) {
    db_query("
      DELETE {activity_log_disabled_types}
      FROM {activity_log_disabled_types}
      LEFT JOIN {activity_log_templates}
        ON {activity_log_disabled_types}.pid = {activity_log_templates}.pid
      WHERE {activity_log_templates}.tid IS NULL
    ");
    db_query("
      DELETE {activity_log_action_names}
      FROM {activity_log_action_names}
      LEFT JOIN {activity_log_templates}
        ON {activity_log_action_names}.pid = {activity_log_templates}.pid
      WHERE {activity_log_templates}.tid IS NULL
    ");
  }
  // Designate that the template should be processed later in activity_log_input_evaluator_process_apply().
  $form_state['values']['settings']['placeholder'] = ACTIVITY_LOG_DELIMITER . $v['placeholder'];
}

/**
 * Submit callback for the Rules action edit form.
 *
 * Set the eval input field when the action is first created.
 * We have to do this after the Rules submit callbacks run so that eval input
 * has already been computed.
 */
function activity_log_rules_admin_form_submit_eval_after($form, &$form_state) {
  db_query("
    UPDATE {activity_log_templates} SET eval_input = '%s' WHERE tid = %d
  ", serialize($form_state['element']['#settings']['#eval input']), $form_state['values']['settings']['tid']);
}

/**
 * Submit callback for the Rules action edit form.
 *
 * The label of the form may have changed between the first submit callback and
 * now if the label wasn't customized and a label callback was used.
 */
function activity_log_rules_admin_form_submit_label_after($form, $form_state) {
  if ($form_state['#action_label'] != $form_state['element']['#info']['label']) {
    db_query("
      UPDATE {activity_log_templates} SET action_label = '%s' WHERE tid = %d
    ", $form_state['element']['#info']['label'], $form_state['values']['settings']['tid']);
  }
}

/**
 * Delete callback for the Rules action edit form.
 *
 * Clean up when our Activity Log action is deleted by deleting the associated
 * template.
 */
function activity_log_rules_admin_form_delete($form, $form_state) {
  if (!empty($form['#parameters'][3])) {
    $tid = $form['#parameters'][3]['#settings']['tid'];
    db_query("DELETE FROM {activity_log_messages} WHERE tid = %d", $tid);
    db_query("DELETE FROM {activity_log_events} WHERE tid = %d", $tid);
    db_query("DELETE FROM {activity_log_templates} WHERE tid = %d", $tid);
  }
}

/**
 * Autocomplete callback for the Rules action public name.
 */
function activity_log_autocomplete_public_name($string = '') {
  $matches = array();
  if ($string) {
    $result = db_query_range("SELECT public_name FROM {activity_log_action_names} WHERE LOWER(public_name) LIKE LOWER('%s%%')", $string, 0, 10);
    while ($row = db_fetch_object($result)) {
      $matches[$row->public_name] = check_plain($row->public_name);
    }
  }
  drupal_json($matches);
}

/**
 * Determines which CSS and JS resources are required for a template.
 */
function _activity_log_determine_resources($templates, $group_templates, $group_summary, $extra) {
  $resources = array();
  foreach (module_invoke_all('activity_log_token_resources') as $token => $sources) {
    if (_activity_log_has_token($token, $templates, $group_templates, $group_summary)) {
      $resources = array_merge_recursive($resources, $sources);
    }
  }
  // Determine the resources that need to be loaded for cached messages.
  $files = explode("\n", $extra);
  foreach ($files as $file) {
    $extension = drupal_substr($file, strrpos($file, '.')+1);
    if (file_exists($file)) {
      if (!isset($resources[$extension])) {
        $resources[$extension] = array();
      }
      $resources[$extension][] = $file;
    }
  }
  return $resources;
}

/**
 * Implementation of hook_activity_log_token_resources().
 */
function activity_log_activity_log_token_resources() {
  $activity_log_path = drupal_get_path('module', 'activity_log');
  $resources = array();
  if (module_exists('facebook_status')) {
    $fbss_path = drupal_get_path('module', 'facebook_status') .'/resources';
    $resources['[status:status-themed]'] = array(
      'css' => array($fbss_path .'/facebook_status.css'),
      'js' => array($fbss_path .'/facebook_status.js'),
    );
    if (module_exists('fbss_comments')) {
      $fbssc_path = drupal_get_path('module', 'fbss_comments');
      $resources['[status:status-themed]']['css'][] = $fbssc_path .'/fbss_comments.css';
      $resources['[status:status-themed]']['js'][] = $fbssc_path .'/fbss_comments.js';
      $resources['[status:status-themed]']['js'][] = $fbssc_path .'/fbss_comments_views_ahah.js';
      if (variable_get('fbss_comments_enter', 0)) {
        $resources['[status:status-themed]']['js'][] = $fbssc_path .'/fbss_comments_enter.js';
      }
    }
  }
  if (module_exists('flag')) {
    $flag_path = drupal_get_path('module', 'flag') .'/theme';
    $resources[':flag-'] = array(
      'css' => array($flag_path .'/flag.css'),
      'js' => array($flag_path .'/flag.js'),
    );
  }
  $resources['[names]'] = array(
    'css' => array($activity_log_path .'/activity_log.css'),
    'js' => array($activity_log_path .'/activity_log.js'),
  );
  $resources['[collection]'] = array(
    'css' => array($activity_log_path .'/activity_log.css'),
    'js' => array($activity_log_path .'/activity_log.js'),
  );
  return $resources;
}

/**
 * Determines whether an Activity Log Rules action has tokens that make it uncacheable.
 */
function _activity_log_has_uncacheable_tokens($templates, $group_templates, $group_summary) {
  foreach (module_invoke_all('activity_log_uncacheable_tokens') as $token) {
    if (_activity_log_has_token($token, $templates, $group_templates, $group_summary)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Implementation of hook_activity_log_uncacheable_tokens().
 */
function activity_log_activity_log_uncacheable_tokens() {
  return array(
    '[:global:user-id]',
    '[:global:user-mail]',
    '[:global:user-name]',
    ':userpoints]',
  );
}

/**
 * Determines whether an Activity Log Rules action has used a given token.
 */
function _activity_log_has_token($token, $templates, $group_templates, $group_summary) {
  if (strpos($group_summary, $token) !== FALSE) {
    return TRUE;
  }
  foreach ($templates as $lang => $info) {
    if (strpos($info['template'], $token) !== FALSE) {
      return TRUE;
    }
  }
  foreach ($group_templates as $lang => $info) {
    if (strpos($info['template'], $token) !== FALSE) {
      return TRUE;
    }
  }
}

//=============================
// RECORDING THE EVENT: STEP 2
//=============================

// INPUT EVALUATION: STEP 2 PART 1

/**
 * Implementation of hook_rules_evaluator().
 *
 * We use a heavy weight so that we run last. We want to run last because we
 * add text to the end of the string that should not be evaluated by other
 * input evaluators.
 */
function activity_log_rules_evaluator() {
  return array(
    'activity_log_input_evaluator_process' => array(
      'label' => t('Activity Log'),
      'weight' => 100,
    ),
  );
}

/**
 * Implementation of callback_prepare().
 */
function activity_log_input_evaluator_process_prepare($string, $variables) {
  return TRUE;
}

/**
 * Implementation of callback_apply().
 *
 * Get information about all the variables that should be available when
 * evaluating input and make it available somewhere we have access to in the
 * action callback.
 */
function activity_log_input_evaluator_process_apply($string, $data = NULL, &$state, $return_output = TRUE) {
  // Only process the Log Activity action's Template setting.
  if (strpos($string, ACTIVITY_LOG_DELIMITER) !== 0) {
    return $string;
  }
  else {
    $string = drupal_substr($string, drupal_strlen(ACTIVITY_LOG_DELIMITER));
  }
  // Get information about all the variables that should be available when evaluating input.
  $map = array();
  foreach ($state['variables'] as $name => $info) {
    if (!empty($info->data) && is_object($info->data->_data)) {
      $map[$name] = array(
        'id' => activity_log_get_id($info->data->_data),
        'type' => $info->info['type'],
        'class' => (empty($info->data->_data->class) ? 'rules_data_type_'. $info->info['type'] : $info->data->_data->class),
      );
    }
  }
  drupal_alter('activity_log_id_map', $map);
  $map['state'] = $state;
  $serialized = serialize($map);
  // Remove any instances of our delimiting string so we don't get anything mixed up.
  if (strpos($serialized, ACTIVITY_LOG_DELIMITER) !== FALSE) {
    str_replace(ACTIVITY_LOG_DELIMITER, substr_replace(ACTIVITY_LOG_DELIMITER, '#! ', 0, 2), $serialized);
  }
  // Store the variable information so we have it available in the action callback.
  return $string . ACTIVITY_LOG_DELIMITER . $serialized;
}

/**
 * Attempt to extract the ID of an object.
 *
 * It is sad that we have to do it this way but unfortunately there is no
 * widely implemented, standard way to do this. Rules would need to add an
 * extract_id($object) property to its rules_data_type class.
 */
function activity_log_get_id($data) {
  // See if any of a list of pre-determined IDs exists as a property of $the object.
  foreach (array('tid', 'cid', 'nid', 'sid', 'vid', 'fid', 'rid', 'aid', 'eid', 'oid', 'uid') as $key) {
    if (isset($data->$key)) {
      return $data->$key;
    }
  }
  // Look for a property that seems like it could be an ID.
  foreach ($data as $key => $value) {
    if ((drupal_strlen($key) < 5 && drupal_substr($key, -2) == 'id') || drupal_substr($key, -3) == '_id') {
      return $value;
    }
  }
}


/**
 * Implementation of callback_help().
 */
function activity_log_input_evaluator_process_help($variables) {
  // Our evaluator is for internal processing. The user doesn't need to know anything about it.
  return array();
}

// EXECUTE ACTION: STEP 2 PART 2

/**
 * Implementation of hook_rules_action_info().
 */
function activity_log_rules_action_info() {
  $eval_input = array('placeholder', 'grouping|group_summary', 'visibility|stream_owner_id', 'visibility|viewer_id', 'acting_uid');
  foreach (language_list() as $name => $lang) {
    $eval_input[] = 'templates|'. $name .'|template';
    $eval_input[] = 'grouping|templates|'. $name .'|template';
  }
  return array(
    'activity_log_log_action' => array(
      'label' => t('Log activity'),
      'module' => 'Activity Log',
      'eval input' => $eval_input,
    ),
  );
}

/**
 * Log activity.
 */
function activity_log_log_action($settings) {
  global $user;
  $time = time();
  // Get the value of the settings set via the UI.
  $pos = strrpos($settings['placeholder'], ACTIVITY_LOG_DELIMITER);
  $map_serialized = drupal_substr($settings['placeholder'], $pos + drupal_strlen(ACTIVITY_LOG_DELIMITER));
  $map = unserialize($map_serialized);
  $target = reset($map); // returns the first element
  // Default empty fields to the current user.
  if (empty($settings['acting_uid'])) {
    $settings['acting_uid'] = $user->uid;
  }
  if (empty($settings['visibility']['stream_owner_id'])) {
    $settings['visibility']['stream_owner_id'] = $user->uid;
    $settings['visibility']['stream_owner_type'] = 'user';
  }
  if (empty($settings['visibility']['viewer_id'])) {
    $settings['visibility']['viewer_id'] = $user->uid;
  }
  // Store the event record.
  $event = (object) array(
    'tid' => $settings['tid'],
    'created' => $time,
    'acting_uid' => $settings['acting_uid'],
    'target_id' => $target['id'],
    'target_type' => $target['type'],
    'target_class' => $target['class'],
    'id_map' => $map_serialized,
  );
  drupal_write_record('activity_log_events', $event);
  // Determine who the stream owners and viewers are.
  $stream_owner_entity_groups = module_invoke_all('activity_log_entity_groups');
  $viewer_entity_groups = module_invoke_all('activity_log_entity_groups', FALSE);
  $results = array();
  foreach (array('stream_owner', 'viewer') as $type) {
    $results[$type] = array();
    $groups = $type == 'viewer' ? $viewer_entity_groups : $stream_owner_entity_groups;
    foreach (array_filter($settings['visibility'][$type .'_entity_group']) as $name) {
      $group = $groups[$name];
      if (isset($group['file']) && file_exists($group['file'])) {
        require_once $group['file'];
      }
      $args = array($event, $settings);
      if (isset($group['expose fields'])) {
        while ($item = array_shift($group['expose fields'])) {
          if ($item == 'id') {
            $args[] = $settings['visibility'][$type .'_id'];
          }
          elseif ($item == 'type') {
            $args[] = $type == 'stream_owner' ? $settings['visibility'][$type .'_type'] : 'user';
          }
          elseif ($item == 'acting_uid') {
            $args[] = $settings['acting_uid'];
          }
        }
      }
      if (isset($group['additional arguments'])) {
        $args = array_merge($args, $group['additional arguments']);
      }
      $results[$type] = array_merge_recursive($results[$type], (array) call_user_func_array($group['items callback'], $args));
    }
  }
  foreach ($results['stream_owner'] as $owner_type => $ids) {
    $results['stream_owner'][$owner_type] = array_unique($ids);
  }
  $owners = $results['stream_owner'];
  $viewers = array_unique($results['viewer']['user']);
  // If "everyone" is a valid viewer, we don't need to save records for specific users.
  if (in_array(0, $viewers)) {
    $viewers = array(0);
  }
  // Find similar events based on the grouping method.
  $group_method = $settings['grouping']['group_method'];
  if ($group_method != 'none') {
    $query = "SELECT mid FROM {activity_log_messages} WHERE ";
    $where = array(
      "tid = %d", // filter by action type
      "viewer_id IN (". db_placeholders($viewers) .")", // filter by viewer
    );
    $args = array_merge(array($event->tid), $viewers);
    $or = array(); // filter by stream owner
    foreach ($owners as $type => $ids) {
      $ids = array_unique($ids);
      $or[] = "(stream_owner_type = '%s' AND stream_owner_id IN (". db_placeholders($ids) ."))";
      $args = array_merge($args, array($type), $ids);
    }
    if (!empty($or)) {
      $where[] = "(". implode(" OR ", $or) .")";
    }
    if ($group_method == 'target_action') {
      $where[] = "target_id = %d"; // filter by target entity
      $where[] = "target_type = '%s'";
      $args[] = $event->target_id;
      $args[] = $event->target_type;
    }
    elseif ($group_method == 'action' || $group_method == 'user_action') {
      if ($group_method == 'user_action') {
        $where[] = "acting_uid = %d"; // filter by acting user
        $args[] = $event->acting_uid;
      }
      $where[] = "created > %d"; // filter by recency
      $where[] = "LENGTH(aids) - LENGTH(REPLACE(aids, ',', '')) - 2 < %d"; // don't allow adding too many events per group
      $args[] = $time - $settings['grouping']['group_interval'];
      $args[] = $settings['grouping']['group_max'];
    }
    $query .= implode(" AND ", $where);
    $result = db_query($query, $args);
    $mids = array();
    while ($message = db_fetch_object($result)) {
      $mids[] = $message->mid;
    }
  }
  // If we found similar events, group with them. If not, save new messages.
  $messages = array();
  if (!empty($mids)) {
    db_query("
      UPDATE {activity_log_messages}
      SET aids = CONCAT(aids, %d, ','), last_updated = %d, cached = ''
      WHERE mid IN (". db_placeholders($mids) .")"
    , array_merge(array($event->aid, $event->created), $mids));
    $result = db_query("SELECT * FROM {activity_log_messages} WHERE mid IN (". db_placeholders($mids) .")", $mids);
    while ($message = db_fetch_object($result)) {
      $messages[] = $message;
    }
  }
  else {
    foreach ($owners as $type => $ids) {
      foreach (array_unique($ids) as $id) {
        foreach ($viewers as $viewer) {
          if (!is_numeric($viewer) && $type != 'user') {
            continue;
          }
          elseif ($viewer == 'stream owner') {
            $viewer = $id;
          }
          elseif ($viewer == 'not stream owner') {
            $viewer = -$id;
          }
          $message = (object) array(
            'tid' => $event->tid,
            'aids' => ','. $event->aid .',',
            'created' => $event->created,
            'last_updated' => $event->created,
            'stream_owner_id' => $id,
            'stream_owner_type' => $type,
            'viewer_id' => $viewer,
            'target_id' => $event->target_id,
            'target_type' => $event->target_type,
            'acting_uid' => $event->acting_uid,
            'cached' => '',
          );
          drupal_write_record('activity_log_messages', $message);
          $messages[] = $message;
        }
      }
    }
  }
  // Invokes hook_activity_log_event($event, $messages, $settings).
  module_invoke_all('activity_log_event', $event, $messages, $settings);
}
