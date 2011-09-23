<?php
/**
 * @file Drupal action to set individual field values.
 */

define('VBO_ACTION_FIELDS_ALL', '_all_');

/**
 * Implementation of hook_action_info().
 * Called by VBO on its own hook_action_info().
 */
function views_bulk_operations_fields_action_info() {
  if (!module_exists('content')) return array();
  return array('views_bulk_operations_fields_action' => array(
    'type' => 'node',
    'description' => t('Modify node fields'),
    'configurable' => TRUE,
    'behavior' => array('changes_node_property'),
    'form properties' => array('#field_info'),
    'rules_ignore' => TRUE,
  ));
}

/**
 * Implementation of hook_theme().
 * Called by VBO on its own hook_theme().
 */
function views_bulk_operations_fields_action_theme() {
  return array(
    'views_bulk_operations_fields_action_form' => array(
      'arguments' => array('form' => NULL),
    ),
  );
}

/**
 * Action function.
 */
function views_bulk_operations_fields_action(&$node, $context) {
  foreach ($context['#field_info'] as $field_name => $field) {
    if (empty($context[$field_name . '_check'])) continue;

    // Get the value, either by PHP evaluation or literally.
    if (!empty($context[$field_name . '_code'])) {
      $value = eval('?>' . $context[$field_name . '_code']);
    }
    else {
      $value = $context[$field_name];
    }

    // Set the value.
    if ($field['type'] == 'non_cck') { // our hacked definition
      if (is_array($value)) foreach ($value as $v_key => $v_item) {
        $node->$v_key = _views_bulk_operations_fields_action_token($v_item, $node, $field);
      }
      else {
        $node->$field_name = _views_bulk_operations_fields_action_token($value, $node, $field);
      }
      if (is_array($field['submit'])) foreach ($field['submit'] as $function) {
        if (!function_exists($function)) continue;
        $function($node, $value, $field);
      }
    }
    else { // CCK
      if (empty($context[$field_name . '_add'])) {
        $node->$field_name = _views_bulk_operations_fields_action_token($value, $node, $field);
      }
      else if (is_array($value)) {
        // Adding to existing values: do it one by one.
        foreach ($value as $v_delta => $v_item) {
          if (is_string($v_delta)) {
            $node->{$field_name}[$v_delta] = _views_bulk_operations_fields_action_token($v_item, $node, $field, $v_delta);
          }
          else {
            $node->{$field_name}[] = _views_bulk_operations_fields_action_token($v_item, $node, $field, $v_delta);
          }
        }
      }
    }
  }
}

/**
 * Action form function.
 */
function views_bulk_operations_fields_action_form($context) {
  module_load_include('inc', 'content', 'includes/content.node_form');

  // This action form uses static-time settings. If they were not set, pull the defaults now.
  if (!isset($context['settings'])) {
    $context['settings'] = views_bulk_operations_fields_action_views_bulk_operations_form_options();
  }
  $form['#settings'] = $context['settings'];
  $form['#theme'] = 'views_bulk_operations_fields_action_form';
  $form['#node'] = (object)array('type' => NULL);
  $form_state = array();
  $weight = -100;

  // Get the content types of the selected nodes if any. Otherwise, get all types.
  if (isset($context['selection']) && isset($context['view'])) {
    $nids = array_map('_views_bulk_operations_get_oid', $context['selection'], array_fill(0, count($context['selection']), $context['view']->base_field));
    $placeholders = db_placeholders($nids);
    $result = db_query("SELECT DISTINCT type FROM {node} WHERE nid IN ($placeholders)", implode(',', $nids));
  }
  else {
    $result = db_query("SELECT type FROM {node_type}");
  }

  // For each type, get its fields.
  $fields = array();
  while ($type = db_result($result)) {
    $fields += _views_bulk_operations_fields_action_non_cck($type);
    $type_info = content_types($type);
    $fields += $type_info['fields'];
  }
  if (empty($fields)) {
    form_set_error('', t('The selected nodes do not have any editable fields. Please select other nodes and try again.'));
    return array();
  }

  // Iterate on fields, creating the input widget for each.
  foreach ($fields as $field) {
    // Skip fields for which the user has no permission.
    if (module_exists('content_permissions') &&
        in_array('edit ' . $field['field_name'], module_invoke('content_permissions', 'perm')) &&
        !user_access('edit ' . $field['field_name'])) continue;

    // Skip fields that are not selected in VBO settings.
    if (!empty($context['settings']['display_fields']) &&
        !in_array($field['field_name'], $context['settings']['display_fields']) &&
        !in_array(VBO_ACTION_FIELDS_ALL, $context['settings']['display_fields'])) continue;

    // Set the default value in the synthesized node.
    $form['#node']->{$field['field_name']} = empty($context[$field['field_name'] . '_check']) ? NULL : $context[$field['field_name']];

    // The field info and widget.
    if ($field['type'] == 'non_cck') { // is it our hacked definition?
      $form += (array)$field['form'];
      if (is_array($form['#node']->{$field['field_name']})) {
        foreach ($form['#node']->{$field['field_name']} as $v_key => $v_item) {
          $form[$field['field_name']][$v_key]['#default_value'] = $v_item;
        }
      }
      else {
        $form[$field['field_name']]['#default_value'] = $form['#node']->{$field['field_name']};
      }
    }
    else { // no, it's CCK
      $field['required'] = FALSE;
      $form += (array)content_field_form($form, $form_state, $field);
    }
    if (empty($form[$field['field_name']])) continue;

    // CCK needs this to properly process its fields.
    $form['#field_info'][$field['field_name']] = $field;

    // Adjust some settings on the field itself.
    $form[$field['field_name']]['#weight'] = $weight++;
    $form[$field['field_name']]['#prefix'] = '<div class="fields-action-togglable">' . @$form[$field['field_name']]['#prefix'];
    $form[$field['field_name']]['#suffix'] = @$form[$field['field_name']]['#suffix'] . '</div>';

    // Checkbox to enable/disable this field.
    $form[$field['field_name'] . '_check'] = array(
      '#type' => 'checkbox',
      '#attributes' => array('class' => 'fields-action-toggler'),
      '#default_value' => !empty($context[$field['field_name'] . '_check']),
    );

    // Checkbox to add/overwrite values in this field.
    if (!empty($field['multiple'])) {
      $form[$field['field_name'] . '_add'] = array(
        '#type' => 'checkbox',
        '#prefix' => '<div class="fields-action-togglable">',
        '#suffix' => '</div>',
        '#attributes' => array(
          'title' => t('Check this box to add new values to this multi-valued field, instead of overwriting existing values.'),
        ),
        '#default_value' => !empty($context[$field['field_name'] . '_add']),
      );
    }
    else {
      $form[$field['field_name'] . '_add'] = array('#type' => 'value', '#value' => FALSE);
    }

    // PHP code to program the value.
    if (user_access('Use PHP input for field settings (dangerous - grant with care)') && $context['settings']['php_code']) {
      if ($field['type'] == 'non_cck') {
        $children = element_children($field['form'][$field['field_name']]);
        if (empty($children)) {
          $sample = t("&lt;?php\nreturn value; // value for @column\n?&gt;", array('@column' => $field['field_name']));
        }
        else {
          $columns = array();
          foreach ($children as $child) {
            if (!empty($field['form'][$field['field_name']][$child]['#ignore'])) continue;
            $columns[$child] = t("'@column' => value for @column", array('@column' => $child));
          }
          $sample = t(
            "&lt;?php\n" .
            "return array(\n" .
            "  @columns\n" .
            ");\n" .
            "?&gt;", array('@columns' => implode(",\n  ", $columns))
          );
        }
      }
      else {
        $db_info = content_database_info($field);
        $columns = array_keys($db_info['columns']);
        foreach ($columns as $key => $column) {
          $columns[$key] = t("'@column' => value for @column", array('@column' => $column));
        }
        $sample = t($field['multiple'] ?
          "&lt;?php\n" .
          "return array(\n" .
          "  0 => array(\n    @columns\n  ),\n" .
          "  1 => array(\n    @columns\n  ),\n" .
          "  2 => ...\n" .
          ");\n" .
          "?&gt;" :
          "&lt;?php\n" .
          "return array(\n" .
          "  0 => array(\n    @columns\n  ),\n" .
          ");\n" .
          "?&gt;", array('@columns' => implode(",\n    ", $columns))
        );
      }
      $form[$field['field_name'] . '_code'] = array(
        '#type' => 'textarea',
        '#default_value' => '',
        '#rows' => 6,
        '#description' => t('Expected format: <pre>!sample</pre>', array(
          '!sample' => $sample,
        )),
        '#prefix' => '<div class="fields-action-togglable">',
        '#suffix' => '</div>',
      );
    }
  }

  // Special case for only one field: convert the checkbox into a value that's TRUE by default.
  if (count($form['#field_info']) == 1) {
    $field_name = key($form['#field_info']);
    $form[$field_name . '_check'] = array('#type' => 'value', '#value' => TRUE);
  }

  return $form;
}

function theme_views_bulk_operations_fields_action_form($form) {
  $output = '';
  if (module_exists('token') && !empty($form['#settings']['show_tokens'])) {
    $output .= t('<h3>Using tokens</h3>
                  In text fields, you can use the following tokens:
                  <fieldset class="collapsed collapsible"><legend>Available tokens</legend>!tokens</fieldset>', array('!tokens' => theme('token_help', 'node'))
    );
    drupal_add_js('misc/collapse.js');
  }
  $access = user_access('Use PHP input for field settings (dangerous - grant with care)');
  if ($access && $form['#settings']['php_code']) {
    $output .= t('<h3>Using the Code widget</h3>
                  <ul>
                  <li>Will override the value specified in the Field widget.</li>
                  <li>Should include &lt;?php ?&gt; delimiters.</li>
                  <li>If in doubt, refer to <a target="_blank" href="@link_devel">devel.module</a> \'Dev load\' tab on a content page to figure out the expected format.</li>
                  <li>The variables <code>$node</code> and <code>$context</code> are available to the script.</li>
                  </ul>', array('@link_devel' => 'http://www.drupal.org/project/devel')
    );
  }

  if (count($form['#field_info']) == 1) { // Special case for just one field: make the table more usable
    $field_name = key($form['#field_info']);
    $header = array();
    if ($form[$field_name . '_add']['#type'] == 'checkbox') {
      $row[] = drupal_render($form[$field_name . '_add']);
      $header[] = array('data' => t('Add?'), 'title' => t('Checkboxes in this column allow you to add new values to multi-valued fields, instead of overwriting existing values.'));
    }
    $row[] = drupal_render($form[$field_name]);
    $header[] = t('Field');
    if ($access && $form['#settings']['php_code']) {
      $row[] = drupal_render($form[$field_name . '_code']);
      $header[] = t('Code');
    }
    if (count($header) == 1) {
      $header = NULL;
    }
    $output .= theme('table', $header, array(array('class' => 'fields-action-row', 'id' => 'fields-action-row' . str_replace('_', '-', $field_name), 'data' => $row)));
  }
  else { // Many fields
    drupal_add_js(drupal_get_path('module', 'views_bulk_operations') . '/js/fields.action.js');

    $header = array(
      t('Select'),
      array('data' => t('Add?'), 'title' => t('Checkboxes in this column allow you to add new values to multi-valued fields, instead of overwriting existing values.')),
      t('Field')
    );
    if ($access && $form['#settings']['php_code']) {
      $header[] = t('Code');
    }
    if (!empty($form['#field_info'])) foreach ($form['#field_info'] as $field_name => $field) {
      $row = array(
        'class' => 'fields-action-row',
        'id' => 'fields-action-row-' . str_replace('_', '-', $field_name),
        'data' => array(
          drupal_render($form[$field_name . '_check']),
          drupal_render($form[$field_name . '_add']),
          drupal_render($form[$field_name]),
        ),
      );
      if ($access && $form['#settings']['php_code']) {
        $row['data'][] = drupal_render($form[$field_name . '_code']);
      }
      $rows[] = $row;
    }
    $output .= theme('table', $header, $rows);
  }
  $output .= drupal_render($form);
  return $output;
}

function views_bulk_operations_fields_action_validate($form, $form_state) {
  $chosen = 0;
  foreach ($form['#field_info'] as $field_name => $field) {
    if (empty($form_state['values'][$field_name . '_check'])) continue;
    $chosen++;
    if (!empty($form_state['values'][$field_name . '_code'])) continue;

    if ($field['type'] == 'non_cck') {
      if (is_array($field['validate'])) foreach ($field['validate'] as $function) {
        if (!function_exists($function)) continue;
        $function($form_state['values'][$field_name], $field);
      }
    }
    else {
      $function = $field['module'] .'_field';
      if (!function_exists($function)) continue;
      $form['#node']->$field_name = $form_state['values'][$field_name];
      $items = isset($form['#node']->$field_name) ? $form['#node']->$field_name : array();
      $function('validate', $form['#node'], $field, $items, $form, NULL);
      content_field('validate', $form['#node'], $field, $items, $form, NULL);
    }
  }
  if (!$chosen) {
    form_set_error('', t('You must select at least one field to modify.'));
  }
}

function views_bulk_operations_fields_action_submit($form, $form_state) {
  $values = array();
  foreach ($form['#field_info'] as $field_name => $field) {
    if ($field['type'] == 'non_cck') {
      $values[$field_name] = $form_state['values'][$field_name];
    }
    else {
      unset($form_state['values'][$field_name][$field_name .'_add_more']);
      $values[$field_name] = content_set_empty($field, $form_state['values'][$field_name]);
    }
    $values[$field_name . '_check'] = $form_state['values'][$field_name . '_check'];
    $values[$field_name . '_add'] = $form_state['values'][$field_name . '_add'];
    if (isset($form_state['values'][$field_name . '_code'])) {
      $values[$field_name . '_code'] = $form_state['values'][$field_name . '_code'];
    }
  }
  $values['#field_info'] = $form['#field_info'];
  return $values;
}

/**
 * Implementation of hook_views_bulk_operations_fields().
 * Return field definitions for common Drupal node fields:
 * array(
 *   field_name => array(
 *     'label' => label to display in admin settings
 *     'form' => array of form elements
 *     'validate' => array of functions to handle validation of submitted values for the form elements
 *     'submit' => array of functions to handle further node changes after values have been copied over
 *   ),
 * )
 */
function views_bulk_operations_views_bulk_operations_fields($type) {
  $fields = array();
  $fields['title'] = array(
    'label' => t('Title'),
    'form' => array(
      'title' => array(
        '#type' => 'textfield',
        '#title' => t('Title'),
      ),
    ),
  );
  $fields['body_field'] = array(
    'label' => t('Body'),
    'form' => array(
      'body_field' => array(
        '#tree' => TRUE,
        'body' => array(
          '#type' => 'textarea',
          '#title' => t('Body'),
        ),
        'format' => filter_form(FILTER_FORMAT_DEFAULT, NULL, array('body_field', 'format')),
      ),
    ),
  );
  $fields['publishing'] = array(
    'label' => t('Publishing options'),
    'form' => array(
      'publishing' => array(
        '#tree' => TRUE,
        'publishing_options' => array(
          '#value' => t('Publishing options') . ':',
          '#prefix' => '<div class="form-item"><label>',
          '#suffix' => '</label></div>',
          '#ignore' => TRUE,
        ),
        'status' => array(
          '#type' => 'checkbox',
          '#title' => t('Published'),
        ),
        'promote' => array(
          '#type' => 'checkbox',
          '#title' => t('Promoted to front page'),
        ),
        'sticky' => array(
          '#type' => 'checkbox',
          '#title' => t('Sticky at top of lists'),
        ),
      ),
    ),
  );
  $fields['authoring'] = array(
    'label' => t('Authoring information'),
    'form' => array(
      'authoring' => array(
        '#tree' => TRUE,
        'name' => array(
          '#type' => 'textfield',
          '#title' => t('Authored by'),
          '#maxlength' => 60,
          '#autocomplete_path' => 'user/autocomplete',
          '#weight' => -1,
          '#description' => t('Leave blank for %anonymous.', array('%anonymous' => variable_get('anonymous', t('Anonymous')))),
        ),
        'date' => array(
          '#type' => 'textfield',
          '#title' => t('Authored on'),
          '#maxlength' => 25,
          '#description' => t('Format: %time. Leave blank to use the time of form submission.', array('%time' => '2011-01-25 12:00:00 +0200')),
        ),
      ),
    ),
    'validate' => array('_views_bulk_operations_field_action_validate_authoring'),
    'submit' => array('_views_bulk_operations_field_action_submit_authoring'),
  );
  if (module_exists('comment')) {
    $fields['comment'] = array(
      'label' => t('Comment settings'),
      'form' => array(
        'comment' => array(
          '#title' => t('Comment settings'),
          '#type' => 'radios',
          '#parents' => array('comment'),
          '#options' => array(t('Disabled'), t('Read only'), t('Read/Write')),
        ),
      ),
    );
  }
  if (module_exists('locale')) {
    $fields['language'] = array(
      'label' => t('Language'),
      'form' => array(
        'language' => array(
          '#type' => 'select',
          '#title' => t('Language'),
          '#options' => array('' => t('Language neutral')) + locale_language_list('name'),
        ),
      ),
    );
  }
  return $fields;
}

/**
 * Validate function for authoring form element.
 */
function _views_bulk_operations_field_action_validate_authoring($value, $field) {
  if (!($account = user_load(array('name' => $value['name'])))) {
    form_set_error('authoring][name', t('This username does not exist. Please select an existing user.'));
  }
}

/**
 * Submit function for authoring form element.
 */
function _views_bulk_operations_field_action_submit_authoring(&$node, $value, $field) {
  if ($account = user_load(array('name' => $node->name))) {
    $node->uid = $account->uid;
  }
  else {
    $node->uid = 0;
  }
  $node->created = !empty($node->date) ? strtotime($node->date) : time();
}

/**
 * VBO settings form function.
 */
function views_bulk_operations_fields_action_views_bulk_operations_form_options() {
  $options['php_code'] = FALSE;
  $options['display_fields'] = array(VBO_ACTION_FIELDS_ALL);
  $options['show_tokens'] = TRUE;
  return $options;
}

function views_bulk_operations_fields_action_views_bulk_operations_form($options) {
  $form['php_code'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show PHP code area'),
    '#description' => t('Check this ON to show a textarea for each field to allow the user to write a PHP script that will populate the value of this field.'),
    '#default_value' => $options['php_code'],
  );
  $form['show_tokens'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show available tokens'),
    '#description' => t('Check this ON to show tokens that are available for replacement in text fields. Only works with Token module enabled.'),
    '#default_value' => $options['show_tokens'],
  );
  $fields = array(VBO_ACTION_FIELDS_ALL => t('- All fields -'));
  foreach (node_get_types() as $type => $info) {
    foreach (_views_bulk_operations_fields_action_non_cck($type) as $field) {
      $fields[$field['field_name']] = $field['label'] .' ('. $field['field_name'] .')';
    }
  }
  foreach (content_fields() as $field) {
    $fields[$field['field_name']] = $field['widget']['label'] .' ('. $field['field_name'] .')';
  }
  if (empty($options['display_fields'])) {
    $options['display_fields'] = array(VBO_ACTION_FIELDS_ALL);
  }
  $form['display_fields'] = array(
    '#type' => 'select',
    '#title' => t('Display fields'),
    '#options' => $fields,
    '#multiple' => TRUE,
    '#description' => t('Select which field(s) the action form should present to the user.'),
    '#default_value' => $options['display_fields'],
  );
  return $form;
}

function views_bulk_operations_fields_action_views_bulk_operations_form_validate($form, $form_state) {
  if (empty($form_state['values']['display_fields'])) {
    form_set_error($form_state['values']['_error_element_base'] . 'display_fields', t('You must select at least one field to be shown to the user.'));
  }
}

function _views_bulk_operations_fields_action_token($value, $node, $field, $delta = NULL) {
  if (module_exists('token')) {
    if (isset($delta) && isset($field['columns']) && is_array($value)) {
      foreach (array_keys($field['columns']) as $column) {
        if (isset($value[$column])) {
          $value[$column] = token_replace($value[$column], 'node', $node);
        }
      }
    }
    else if (is_array($value)) foreach ($value as $v_delta => $v_item) {
      if (is_array($v_item) && isset($field['columns'])) foreach (array_keys($field['columns']) as $column) {
        if (isset($v_item[$column])) {
          $value[$v_delta][$column] = token_replace($v_item[$column], 'node', $node);
        }
      }
      else {
        $value[$v_delta] = token_replace($v_item, 'node', $node);
      }
    }
    else {
      $value = token_replace($value, 'node', $node);
    }
  }
  return $value;
}

function _views_bulk_operations_fields_action_non_cck($type, $reset = FALSE) {
  static $fields = NULL;
  if (empty($fields[$type]) || $reset) {
    foreach (module_invoke_all('views_bulk_operations_fields', $type) as $field_name => $field) {
      $field['field_name'] = $field_name;
      $field['type'] = 'non_cck';
      $fields[$type][$field_name] = $field;
    }
  }
  drupal_alter('views_bulk_operations_fields', $fields, $type);
  return $fields[$type];
}
