<?php
// $Id: messaging.admin.inc,v 1.1.2.13.2.2 2009/04/30 10:42:35 jareyero Exp $
/**
 * @file
 * Messaging Framework - Admin UI
 * 
 * This file includes the settings page and administration for message templates
 * 
 * By Development Seed, http://wwww.developmentseed.org
 */

/**
 * Aditional help for admin pages, will be called from messaging_help().
 * 
 * All paths here start with 'admin/messaging'
 */
function messaging_admin_help($path, $arg) {
  switch ($path) {
    case 'admin/messaging/template':
      $output = '<p>' . t('Configure the templates for different types of messages. Each message group is defined by other modules using the Messaging Framework. A typical message consists on the following parts:') . '</p>';
      $output .= '<small><table>';
      $output .= '<tr><td colspan="2"><em>' . t('Subject') . '</em></td><td>' . t('Single line with a short description') . '</td></tr>';
      $output .= '<tr><td rowspan="3">' . t('Body') . '</td><td><em>' . t('Header') . '</em></td><td>' . t('Greetings line') . '</td></tr>';
      $output .= '<tr><td><em>' . t('Content') . '</em></td><td>' . t('Message main content, usually longer with the full description'). '</td></tr>';
      $output .= '<tr><td><em>' . t('Footer') . '</em></td><td>' .  t('Closing part with site information, unsubscribe links, etc...') . '</td></tr>';
      $output .= '</table></small>';
      $output .= '<p>' . t('Here you\'ll be able to configure each of these parts for each sending method. When one of these parts is left blank, there is a fallback system which goes as follows:') . '</p>';
      $output .= '<ul>';
      $output .= '<li>' . t('If a message part is left blank for a sending method, the text part from Default sending method will be used.') . '</li>';
      $output .= '<li>' . t('If the Default part is blank too, the fallback template (the parent in this tree) will be used.') . '</li>';
      $output .= '</ul>';
      return $output;
    case 'admin/messaging/settings/method':
      $output = '<p>' . t('Depending on your content format and the tokens you are using for messages it is important that you use the right filtering for the message body. Set up the filters you need using the <a href="@input_formats">Input formats</a> page', array('@input_formats' => url('admin/settings/filters'))) . '</p>';
      return $output; 
    default:
      // Edit template groups
      if ($arg[3] == 'edit' && ($group = $arg[4])) {
        $info = messaging_message_group($group);
        $output = '<p>'. t('These are the message parts for %group.', array('%group' => messaging_message_group($group, 'name')));
        if (!empty($info['description'])) {
          $output .= ' ' . $info['description'];
        }
        $output .= '</p>';
        if (!empty($info['help'])) {
          $output .= '<p>'. $info['help'] .'</p>';
        }
        $output .= '<p>' . t('Leave blank to use the default texts or use \'%empty\' for an empty message part, preventing fallback to default message texts.', array('%empty' => MESSAGING_EMPTY));
        if (!empty($info['fallback'])) {
          $output .= ' ' . t('The fallback template from which message parts will be taken if left blank is <a href="@template_edit">%template_name</a>', array('@template_edit' => url('admin/messaging/template/edit/' . $info['fallback']), '%template_name' => messaging_message_group($info['fallback'], 'name') ));
        }
        $output .= '</p>';
        return $output;
      }
  }
}

/*
 * Overview of message parts and sending methods
 */
function messaging_admin_template() {
  $output = '';
  // List message groups
  $groups = module_invoke_all('messaging', 'message groups');
  // Check fallbacks and get root templates for tree-like display
  $root = array();
  foreach ($groups as $group => $group_info) {
    if (empty($group_info['fallback'])) {
      $root[] = $group;
    } else {
      $groups[$group_info['fallback']]['children'][] = $group;
    }
  }
  // Now build table which will have some indentation
  $rows = messaging_admin_template_tree($root, $groups);
  $header = array(t('Message groups'), t('Description'), t('Parts'));
  $output .= theme('table', $header, $rows);

  // List sending methods
  $rows = array();
  messaging_method_list();
  foreach (messaging_method_info() as $method => $info) {
    $rows[] = array(
      '<strong>'. $info['name'] .'</strong>',
      !empty($info['description']) ? $info['description'] : ''
    );
  }
  $output .= theme('box', t('Sending methods'), theme('table', NULL, $rows));
  return $output;
}

/**
 * Recursively build a table tree for fallback methods
 */
function messaging_admin_template_tree($parents, $groups, $depth = 0) {
  $rows = array();
  foreach ($parents as $key) {
    $info = $groups[$key];    
    $rows[] = array(
      theme('indentation', $depth) . l($info['name'], 'admin/messaging/template/edit/'.$key),
      !empty($info['description']) ? $info['description'] : '',
      ($parts = module_invoke_all('messaging', 'message keys', $key)) ? implode(', ', $parts) : '',
    );
    if (!empty($info['children'])) {
      $rows = array_merge($rows, messaging_admin_template_tree($info['children'], $groups, $depth + 1));
    }
  }
  return $rows;
}

/**
 * Message groups edit page
 */
function messaging_admin_template_edit($group) {
  $output = '';
  $groups = module_invoke_all('messaging', 'message groups');
  if (isset($groups[$group])) {
    drupal_set_title(t('Message template for %name', array('%name' => $groups[$group]['name'])));
    $output .= drupal_get_form('messaging_admin_message_form', $group, $groups[$group]);

  }
  return $output;
}

/**
 * Edit message formats
 */
function messaging_admin_message_form($form_state, $group, $group_info) {
  $form['group'] = array('#type' => 'value', '#value' => $group);
  $keylist = module_invoke_all('messaging', 'message keys', $group);
  $send_methods = array('default' => t('Default'));
  $send_methods += messaging_method_list();
  $form['messages'] = array('#tree' => TRUE);
  foreach ($keylist as $key => $keyname) {
    $form['messages'][$key] = array(
      '#type' => 'fieldset',
      '#title' => $keyname,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    foreach ($send_methods as $method => $methodname) {
      $text = messaging_message_part($group, $key, $method, FALSE);
      $form['messages'][$key][$method] = array(
        '#title' => $methodname,
        '#type' => 'textarea',
        '#default_value' => $text,
        // Adjust size to actual number of lines
        '#rows' => count(explode("\n", $text)),        
      );
      
    }
  }
  // Tokens for text replacement
  if ($tokens = messaging_tokens_get_list($group)) {
    $headers = array(t('Token'), t('Replacement value'));
    $rows = array();
    foreach ($tokens as $token => $token_description) {
        $row = array();
        $row[] = '[' . $token . ']';
        $row[] = $token_description;
        $rows[] = $row;
    }
    $form['tokens'] = array(
      '#title' => t('Available tokens'),
      '#type' => 'fieldset',
      '#description' => t('These special strings will be replaced by their real value at run time.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['tokens']['list'] = array(
      '#value' => theme('table', $headers, $rows, array('class' => 'description'))
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Get list of tokens for text replacement
 *
 * @param $group
 *   Message group to get tokens for
 * @param $tokens
 *
 */
function messaging_tokens_get_list($group) {
  // First compile token types for this message group
  $type_list = module_invoke_all('messaging', 'tokens', $group);
  // Add known global tokens, will be always available
  $type_list[] = 'global';

  // Now get token list from token module for each type
  $return = array();
  foreach ($type_list as $type) {
    // This is a shortcut for single tokens for digests, with the form (token, description)
    if (is_array($type)) {
      list($type, $token) = $type;
      $list = token_get_list($type);
      $return[$token] = $list[$type][$token];
    }
    elseif ($list = token_get_list($type)) {
      foreach ($list as $category => $tokens) {
        foreach ($tokens as $token => $description) {
          $return[$token] = $description;
        }
      }
    }
  }
  return $return;
}

/**
 * Process and save message parts
 */
function messaging_admin_message_form_submit($form, &$form_state) {
  $group = $form_state['values']['group'];
  foreach ($form_state['values']['messages'] as $key => $messages) {
    foreach ($messages as $method => $text) {
      db_query("DELETE FROM {messaging_message_parts} WHERE type = '%s' AND msgkey = '%s' AND method = '%s'", $group, $key, $method);
      if (trim($text)) {
        db_query("INSERT INTO {messaging_message_parts} (type, msgkey, method, module, message) VALUES('%s', '%s', '%s', '', '%s')", $group, $key, $method, $text);
      }
    }
  }
  drupal_set_message('The message templates have been updated');
}

/**
 * Admin settings form
 */
function messaging_admin_settings() {
  // Get plug-in information and produce big warning if none enabled.
  $methods = messaging_method_list();
  if (!$methods) {
    // Get message from requirements
    if ($reqs = messaging_requirements('runtime')) {
      drupal_set_message($reqs['messaging']['value'], 'error');
    }    
  }  
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );
  $form['general']['messaging_default_method'] = array(
    '#title' => t('Default send method'),
    '#type' => 'radios',
    '#options' => $methods,
    '#default_value' => variable_get('messaging_default_method', ''),
  );
  // Logging settings  
  $period = array(0 => t('Disabled')) + drupal_map_assoc(array(3600, 10800, 21600, 32400, 43200, 86400, 172800, 259200, 604800, 1209600, 2419200, 4838400, 9676800), 'format_interval');
  $form['general']['messaging_log'] = array(
    '#title' => t('Logging'),
    '#type' => 'select',
    '#options' => $period,
    '#default_value' => variable_get('messaging_log', 0),
    '#description' => t('If enabled all messages will be logged and kept for the specified time after they\'re sent.'),
  );

  // Processing limits
  $limit = variable_get('messaging_process_limit', array('message' => 0, 'percent' => 0, 'time' => 0));
  $form['messaging_process_limit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Limits for queue processing'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('These are the limits for each cron run on queue processing. The process will stop when it first meets any of them. Set to 0 for no limit.'),
  );
  $form['messaging_process_limit']['message'] = array(
    '#title' => t('Number of messages sent'),
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => $limit['message'],
  );
  $form['messaging_process_limit']['time'] = array(
    '#title' => t('Time (seconds)'),
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => $limit['time'],
  );
  $form['messaging_process_limit']['percent'] = array(
    '#title' => t('Time (% of cron time)'),
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => $limit['percent'],
    '#description' => t('Maximum percentage of cron time the process may use.'),
  );
  return system_settings_form($form);
}

/**
 * Default sending methods settings
 */
function messaging_admin_method_settings() {
  // Sending methods settings
  if ($info = messaging_method_info()) {
    foreach (filter_formats() as $format) {
      $format_options[$format->format] = $format->name;
    }
    // We add this last for it not bo be default
    $format_options[0] = t('None (Insecure)');
    $form['methods'] = array('#theme' => 'messaging_admin_method_settings');
    foreach ($info as $method => $options) {
      $key = 'messaging_method_'.$method;
      // This will preserve settings for disabled modules
      $form['methods'][$key]['#tree'] = TRUE;
      $form['methods'][$key]['title'] = array(
        '#value' => $options['title'],
      );
      // Display name
      $form['methods'][$key]['name'] = array(
        '#type' => 'textfield',
        '#default_value' => $options['name'],
        '#size'          => 40,
      );      
      // Output filter applied to message body
      $form['methods'][$key]['filter'] = array(
        '#type' => 'select',
        '#default_value' => isset($options['filter']) ? $options['filter'] : variable_get('messaging_default_filter', ''),
        '#options' => $format_options,
      );
    }
  } else {
    $form['warning'] = array('#value' => t('You should enable some messaging method plug-ins for this to work.'));
  }
  return system_settings_form($form);  
}

/**
 * Theme method settings
 */
function theme_messaging_admin_method_settings(&$form) {
  $header = array(t('Method'), t('Name for display'), t('Message body filter'));
  $rows = array();
  foreach (element_children($form) as $key) {
    $rows[] = array(
      drupal_render($form[$key]['title']),
      drupal_render($form[$key]['name']),
      drupal_render($form[$key]),
    );
  }
  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);
  return $output;
}