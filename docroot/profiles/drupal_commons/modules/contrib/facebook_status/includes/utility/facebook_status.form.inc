<?php

/**
 * @file
 *   Functions related to the status update form itself.
 */

/**
 * Returns the status update form.
 *
 * @param $context
 *   One of the following:
 *   - A fully qualified context array
 *   - NULL, to have the context automatically determined
 *   - An object representing the owner of the status stream, i.e. the entity
 *     to which status messages will be posted using this form.
 * @param $type
 *   The context stream type. Only applicable if a recipient object is
 *   specified for $context, but it is required in that case.
 * @param $view
 *   The machine name of the view to display with the form. Overrides the one
 *   requested by the context.
 * @param $display
 *   The machine name of the view display. This is not used internally but
 *   provided in case any external applications need it. There is no error
 *   checking on this parameter; it is the caller's responsibility to ensure
 *   that the specified display is valid and belongs to the relevant view.
 * @return
 *   HTML to display the status update form, or FALSE if:
 *   - The current user has no access to both the form and the associated
 *     status messages, OR
 *   - There are no relevant status messages and the current user does not
 *     have access to use the form
 */
function theme_facebook_status_form_display($context = NULL, $type = NULL, $view = NULL, $display = 'default') {
  global $user;
  // $context is NULL, so find everything.
  if (empty($context)) {
    $context = facebook_status_determine_context();
    $recipient = $context['handler']->find_recipient();
    $type = $context['handler']->type();
  }
  // Neither $context nor $type is NULL, so $context is really $recipient.
  elseif (!empty($type)) {
    $recipient = $context;
    $context = facebook_status_determine_context($type);
  }
  // $type is NULL and $context is not, so $context is a full context array.
  else {
    $recipient = $context['handler']->find_recipient();
    $type = $context['handler']->type();
  }
  if (empty($view) && isset($context['view'])) {
    $view = $context['view'];
    // Special case, user context has 2 default views
    if ($type == 'user' && $user->uid != $context['handler']->recipient_id($recipient)) {
      $view = variable_get('facebook_status_user_other_view', 'facebook_status_stream');
    }
  }
  $selectors = module_invoke_all('facebook_status_refresh_selectors', $recipient, $type) + explode("\n", $context['selectors']);
  $conversation = (arg(0) == 'statuses' && arg(1) == 'conversation' && $type == 'user');
  $output = '';
  if (facebook_status_user_access('add', $recipient, $type, $user)) {
    $self = '';
    if ($type == 'user' && $user->uid == $recipient->uid) {
      $self = ' facebook-status-form-self-update';
    }
    $converse = '';
    if ($conversation) {
      $converse = ' facebook-status-conversation-form';
    }
    $output .= '<div class="clear-block facebook-status-update facebook-status-update-main facebook-status-form-type-'. $type . $self . $converse .'">'.
      drupal_get_form('facebook_status_box', $recipient, $type) .'</div>';
  }
  if ($conversation) {
    $args = explode(',', arg(2));
    $count = count($args);
    if (($count === 1 && $args[0] != $user->uid) || ($count === 2 && is_numeric($args[1])) && is_numeric($args[0])) {
      if (count($args) === 1) {
        $args[1] = $user->uid;
      }
      $output .= views_embed_view('facebook_status_conversation', $display, $args[0], $args[1]);
      $selectors[] = '.view-id-facebook_status_conversation';
    }
  }
  elseif (!empty($view) && facebook_status_user_access('view_stream', $recipient, $type, $user)) {
    if ($view == 'activity_log_stream') {
      $al_type = ($type == 'og' ? 'node' : ($type == 'term' ? 'taxonomy_term' : $type));
      $output .= views_embed_view($view, $display, $al_type, $context['handler']->recipient_id($recipient));
    }
    else {
      $output .= views_embed_view($view, $display, $context['handler']->recipient_id($recipient), $type);
    }
    $selectors[] = '.view-id-'. $view;
  }
  if (!empty($selectors)) {
    drupal_alter('facebook_status_refresh_selectors', $selectors, $recipient, $type);
    drupal_add_js(array('facebook_status' => array(
      'refreshIDs' => array_unique($selectors)
    )), 'setting');
  }
  return $output;
}

/**
 * The status form.
 *
 * @param $recipient
 *   An object representing the recipient of the status message.
 * @param $type
 *   The stream type.
 * @return
 *   A $form array.
 */
function facebook_status_box(&$form_state, $recipient, $type = 'user') {
  global $user;
  _facebook_status_use_autogrow();
  if (isset($form_state['facebook_status'])) {
    $type = $form_state['facebook_status']['type'];
    $context = facebook_status_determine_context($type);
    $rid = $form_state['facebook_status']['recipient'];
    $recipient = $context['handler']->load_recipient($rid);
  }
  else {
    $context = facebook_status_determine_context($type);
    $rid = $context['handler']->recipient_id($recipient);
  }

  $default = variable_get('facebook_status_default_text'. ($type == 'user' && $user->uid == $recipient->uid ? '' : '_other'), '');
  $intro = '';
  if (arg(0) == 'statuses' && (arg(1) == 'share' || arg(1) == 'conversation')) {
    // This page is autofocused. We don't want default text there since the user would have to manually remove it.
    $default = '';
  }
  if (isset($_GET['s']) && arg(0) == 'statuses' && arg(1) == 'share') {
    // Other modules might use "s," so only accept it on the share-status page.
    $default = $_GET['s'];
  }
  elseif (isset($_GET['share-status'])) {
    $default = $_GET['share-status'];
  }
  // @todo: Replace with a "true" re-posting system.
  if (isset($_GET['sid']) && is_numeric($_GET['sid'])) {
    $rs = facebook_status_load($_GET['sid']);
    $sender = _facebook_status_user_load($rs->sender);
    if ($sender->uid != $user->uid && $rs->message) {
      $name = '@'. $sender->name;
      // Properly reference tags with word-break characters in them.
      if (preg_match('/.+\b.+/', $sender->name)) {
        $name = '['. $name .']';
      }
      $default = str_replace(array('@name', '@message'), array($name, $rs->message), variable_get('facebook_status_repost', 'Re: @name @message '));
      $intro = '';
    }
  }
  elseif (isset($_GET['rsid']) && is_numeric($_GET['rsid'])) {
    $status = facebook_status_load($_GET['rsid']);
    if ($status->sid) {
      $sender = user_load(array('uid' => $status->sender));
      if ($sender->uid != $user->uid) {
        $name = '@'. $sender->name;
        // Properly reference tags with word-break characters in them.
        if (preg_match('/.+\b.+/', $sender->name)) {
          $name = '['. $name .']';
        }
        $default = $name .' ';
      }
      $intro = t('In response to: !status', array('!status' => facebook_status_show($status, array('links' => FALSE, 'extras' => FALSE))));
    }
  }

  $path = drupal_get_path('module', 'facebook_status') .'/resources';
  drupal_add_js($path .'/facebook_status.js');
  if (variable_get('facebook_status_enter', 0)) {
    drupal_add_js($path .'/facebook_status_enter.js');
  }
  drupal_add_js($path .'/facebook_status_ahah.js', 'module', 'footer');
  drupal_add_css($path .'/facebook_status.css');
  // Form elements between ['opendiv'] and ['closediv'] will be refreshed via AHAH on form submission.
  $form['opendiv'] = array(
    '#value' => '<div id="facebook-status-replace" class="facebook-status-form">',
    '#weight' => -50,
  );
  if (!empty($intro)) {
    $form['intro'] = array(
      '#value' => '<span class="facebook-status-intro">'. $intro .'</span>',
      '#weight' => -45,
    );
  }
  if (variable_get('facebook_status_length', 140) > 0) {
    $form['chars'] = array(
      '#value' => '<span class="facebook-status-chars">'. t('%chars characters allowed', array('%chars' => variable_get('facebook_status_length', 140))) .'</span>',
      '#weight' => module_exists('fbss_privacy') ? -41 : -24,
    );
  }
  $form['fbss-status'] = array(
    '#type' => 'textarea',
    '#rows' => variable_get('facebook_status_box_rows', 2),
    '#default_value' => $default,
    '#attributes' => array('class' => 'facebook-status-text facebook-status-text-main'),
    '#resizable' => FALSE,
    '#prefix' => '<div class="facebook-status-textarea-wrapper">',
    '#suffix' => '</div>',
    '#weight' => -40,
  );
  $form['fbss-submit'] = array(
    '#type' => 'submit',
    '#value' => t('Share'),
    '#submit' => array('facebook_status_box_submit'),
    '#attributes' => array('class' => 'facebook-status-submit button primary'),
    '#weight' => -25,
  );
  if (variable_get('facebook_status_ahah', 1)) {
    $form['fbss-submit']['#ahah'] = array(
      'path' => 'facebook_status/js',
      'wrapper' => 'facebook-status-replace',
      'effect' => 'fade',
      'method' => 'replace',
    );
  }
  $form['sdefault'] = array(
    '#type' => 'value',
    '#value' => $default,
    '#weight' => -10,
  );
  // Form elements between ['opendiv'] and ['closediv'] will be refreshed via AHAH on form submission.
  $form['closediv'] = array(
    '#value' => '</div>',
    '#weight' => -1,
  );
  $form['recipient'] = array(
    '#type' => 'value',
    '#value' => $context['handler']->recipient_id($recipient),
    '#weight' => 10,
  );
  $form['type'] = array(
    '#type' => 'value',
    '#value' => $type,
    '#weight' => 10,
  );
  if (arg(0) == 'statuses' && arg(1) == 'share' && !empty($_GET['destination']) && $_GET['destination'] != $_GET['q']) {
    $form['back'] = array(
      '#value' => l(t('Back'), $_GET['destination'], array('attributes' => array('class' => 'facebook-status-back'))),
      '#weight' => 20,
    );
  }
  return $form;
}

/**
 * Validate function for the status update form.
 */
function facebook_status_box_validate($form, &$form_state) {
  $maxlen = variable_get('facebook_status_length', 140);
  $len = drupal_strlen($form_state['values']['fbss-status']);
  if ($len > $maxlen && $maxlen != 0) {
    form_set_error('status',
      t('You may use a maximum of %maxchars characters, but you are using %chars characters.',
        array('%maxchars' => $maxlen, '%chars' => $len)
      )
    );
  }
}

/**
 * Submit function for the status update form.
 */
function facebook_status_box_submit($form, &$form_state) {
  $type = $form_state['values']['type'];
  $rid = $form_state['values']['recipient'];
  $context = facebook_status_determine_context($type);
  $recipient = $context['handler']->load_recipient($rid);
  $new_status = trim($form_state['values']['fbss-status']);
  $default = $form_state['values']['sdefault'];
  $form_state['facebook_status'] = array();
  // Don't save the status if it wasn't changed from the default.
  if ($new_status != $default) {
    $new_status_obj = facebook_status_save_status($recipient, $type, $new_status, $GLOBALS['user'], array('form_state' => $form_state));
    if (isset($new_status_obj->sid)) {
      $form_state['facebook_status']['sid'] = $new_status_obj->sid;
    }
  }
  $form_state['facebook_status']['type'] = $type;
  $form_state['facebook_status']['recipient'] = $rid;
  $form_state['rebuild'] = TRUE;
  if (!variable_get('facebook_status_ahah', 1)) {
    $form_state['redirect'] = array($_GET['q']);
    $form_state['rebuild'] = FALSE;
  }
}

/**
 * Adds the Autogrow jQuery extension.
 */
function _facebook_status_use_autogrow() {
  $path = cache_get('fbss:autogrow');
  if (!empty($path)) {
    drupal_add_js($path->data);
    return;
  }
  if (module_exists('libraries')) {
    $path = libraries_get_path('autogrow') .'/jquery.autogrow.js';
    if (file_exists($path)) {
      drupal_add_js($path);
      cache_set('fbss:autogrow', $path);
      return;
    }
  }
  if (file_exists('sites/all/libraries/jquery.autogrow.js')) {
    drupal_add_js('sites/all/libraries/jquery.autogrow.js');
    cache_set('fbss:autogrow', 'sites/all/libraries/jquery.autogrow.js');
  }
  elseif (file_exists('libraries/jquery.autogrow.js')) {
    drupal_add_js('libraries/jquery.autogrow.js');
    cache_set('fbss:autogrow', 'libraries/jquery.autogrow.js');
  }
  else {
    $path = drupal_get_path('profile', $GLOBALS['profile']) .'/libraries/jquery.autogrow.js';
    if (file_exists($path)) {
      drupal_add_js($path);
      cache_set('fbss:autogrow', $path);
    }
  }
}
