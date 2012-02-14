<?php

/**
 * @file
 *   Menu and related callback overrides for commons_core
 */
 
/**
 * Override of node_page_view() on /node/%node
 * 
 * We need this in order to handle group home pages
 */
function commons_core_node_page_view($node) {
  // If this node is a group
  if (og_is_group_type($node->type)) {
    // Make context aware of the node view since hook_nodeapi() won't
    // be triggered here
    context_node_condition($node, 'view');
    drupal_set_title(check_plain($node->title));
    // Return nothing, allowing context to handle the content
    return '';
  }
  
  // Pass the node to the normal callback
  return node_page_view($node);
}
 
/**
 * Minor override and alteration of comment_edit()
 * 
 * Allows group admins to edit comments in their group
 */
function commons_core_comment_edit($cid) {
  global $user;

  $comment = db_fetch_object(db_query('SELECT c.*, u.uid, u.name AS registered_name, u.data FROM {comments} c INNER JOIN {users} u ON c.uid = u.uid WHERE c.cid = %d', $cid));
  $comment = drupal_unpack($comment);
  $comment->name = $comment->uid ? $comment->registered_name : $comment->name;
  
  // See if the user can edit the comment
  if (_commons_core_can_admin_comment($comment)) {
    // We need to use our own comment form now
    return theme('box', NULL, drupal_get_form('commons_core_comment_form', (array)$comment, NULL));  
  }
  
  // If none of the above, fall back on what comment.module normally uses
  if (comment_access('edit', $comment)) {
    return comment_form_box((array)$comment);
  }
  else {
    drupal_access_denied();
  }
}

/**
 * Copied from comment_form()
 * 
 * We need to remove the check for administer comments permissions
 * because at this point, the current user is the group admin for the
 * node being comment on. We want to allow full edit access.
 */
function commons_core_comment_form(&$form_state, $edit, $title = NULL) {
  global $user;

  $op = isset($_POST['op']) ? $_POST['op'] : '';
  $node = node_load($edit['nid']);

  if (!$user->uid && variable_get('comment_anonymous_'. $node->type, COMMENT_ANONYMOUS_MAYNOT_CONTACT) != COMMENT_ANONYMOUS_MAYNOT_CONTACT) {
    drupal_add_js(drupal_get_path('module', 'comment') .'/comment.js');
  }
  $edit += array('name' => '', 'mail' => '', 'homepage' => '');
  if ($user->uid) {
    // The check for administer comments was removed from here
    // We must trust the user if they've reached this form
    if (!empty($edit['cid'])) {
      if (!empty($edit['author'])) {
        $author = $edit['author'];
      }
      elseif (!empty($edit['name'])) {
        $author = $edit['name'];
      }
      else {
        $author = $edit['registered_name'];
      }

      if (!empty($edit['status'])) {
        $status = $edit['status'];
      }
      else {
        $status = 0;
      }

      if (!empty($edit['date'])) {
        $date = $edit['date'];
      }
      else {
        $date = format_date($edit['timestamp'], 'custom', 'Y-m-d H:i O');
      }

      $form['admin'] = array(
        '#type' => 'fieldset',
        '#title' => t('Administration'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#weight' => -2,
      );

      if ($edit['registered_name'] != '') {
        // The comment is by a registered user
        $form['admin']['author'] = array(
          '#type' => 'textfield',
          '#title' => t('Authored by'),
          '#size' => 30,
          '#maxlength' => 60,
          '#autocomplete_path' => 'user/autocomplete',
          '#default_value' => $author,
          '#weight' => -1,
        );
      }
      else {
        // The comment is by an anonymous user
        $form['is_anonymous'] = array(
          '#type' => 'value',
          '#value' => TRUE,
        );
        $form['admin']['name'] = array(
          '#type' => 'textfield',
          '#title' => t('Authored by'),
          '#size' => 30,
          '#maxlength' => 60,
          '#default_value' => $author,
          '#weight' => -1,
        );
        $form['admin']['mail'] = array(
          '#type' => 'textfield',
          '#title' => t('E-mail'),
          '#maxlength' => 64,
          '#size' => 30,
          '#default_value' => $edit['mail'],
          '#description' => t('The content of this field is kept private and will not be shown publicly.'),
        );

        $form['admin']['homepage'] = array(
          '#type' => 'textfield',
          '#title' => t('Homepage'),
          '#maxlength' => 255,
          '#size' => 30,
          '#default_value' => $edit['homepage'],
        );
      }

      $form['admin']['date'] = array('#type' => 'textfield', '#parents' => array('date'), '#title' => t('Authored on'), '#size' => 20, '#maxlength' => 25, '#default_value' => $date, '#weight' => -1);

      $form['admin']['status'] = array('#type' => 'radios', '#parents' => array('status'), '#title' => t('Status'), '#default_value' =>  $status, '#options' => array(t('Published'), t('Not published')), '#weight' => -1);

    }
    else {
      $form['_author'] = array('#type' => 'item', '#title' => t('Your name'), '#value' => theme('username', $user)
      );
      $form['author'] = array('#type' => 'value', '#value' => $user->name);
    }
  }
  else if (variable_get('comment_anonymous_'. $node->type, COMMENT_ANONYMOUS_MAYNOT_CONTACT) == COMMENT_ANONYMOUS_MAY_CONTACT) {
    $form['name'] = array('#type' => 'textfield', '#title' => t('Your name'), '#maxlength' => 60, '#size' => 30, '#default_value' => $edit['name'] ? $edit['name'] : variable_get('anonymous', t('Anonymous'))
    );

    $form['mail'] = array('#type' => 'textfield', '#title' => t('E-mail'), '#maxlength' => 64, '#size' => 30, '#default_value' => $edit['mail'], '#description' => t('The content of this field is kept private and will not be shown publicly.')
    );

    $form['homepage'] = array('#type' => 'textfield', '#title' => t('Homepage'), '#maxlength' => 255, '#size' => 30, '#default_value' => $edit['homepage']);
  }
  else if (variable_get('comment_anonymous_'. $node->type, COMMENT_ANONYMOUS_MAYNOT_CONTACT) == COMMENT_ANONYMOUS_MUST_CONTACT) {
    $form['name'] = array('#type' => 'textfield', '#title' => t('Your name'), '#maxlength' => 60, '#size' => 30, '#default_value' => $edit['name'] ? $edit['name'] : variable_get('anonymous', t('Anonymous')), '#required' => TRUE);

    $form['mail'] = array('#type' => 'textfield', '#title' => t('E-mail'), '#maxlength' => 64, '#size' => 30, '#default_value' => $edit['mail'], '#description' => t('The content of this field is kept private and will not be shown publicly.'), '#required' => TRUE);

    $form['homepage'] = array('#type' => 'textfield', '#title' => t('Homepage'), '#maxlength' => 255, '#size' => 30, '#default_value' => $edit['homepage']);
  }

  if (variable_get('comment_subject_field_'. $node->type, 1) == 1) {
    $form['subject'] = array('#type' => 'textfield', '#title' => t('Subject'), '#maxlength' => 64, '#default_value' => !empty($edit['subject']) ? $edit['subject'] : '');
  }

  if (!empty($edit['comment'])) {
    $default = $edit['comment'];
  }
  else {
    $default = '';
  }

  $form['comment_filter']['comment'] = array(
    '#type' => 'textarea',
    '#title' => t('Comment'),
    '#rows' => 15,
    '#default_value' => $default,
    '#required' => TRUE,
  );
  if (!isset($edit['format'])) {
    $edit['format'] = FILTER_FORMAT_DEFAULT;
  }
  $form['comment_filter']['format'] = filter_form($edit['format']);

  $form['cid'] = array('#type' => 'value', '#value' => !empty($edit['cid']) ? $edit['cid'] : NULL);
  $form['pid'] = array('#type' => 'value', '#value' => !empty($edit['pid']) ? $edit['pid'] : NULL);
  $form['nid'] = array('#type' => 'value', '#value' => $edit['nid']);
  $form['uid'] = array('#type' => 'value', '#value' => !empty($edit['uid']) ? $edit['uid'] : 0);

  // Only show save button if preview is optional or if we are in preview mode.
  // We show the save button in preview mode even if there are form errors so that
  // optional form elements (e.g., captcha) can be updated in preview mode.
  if (!form_get_errors() && ((variable_get('comment_preview_'. $node->type, COMMENT_PREVIEW_REQUIRED) == COMMENT_PREVIEW_OPTIONAL) || ($op == t('Preview')) || ($op == t('Save')))) {
    $form['submit'] = array('#type' => 'submit', '#value' => t('Save'), '#weight' => 19);
  }

  $form['preview'] = array('#type' => 'button', '#value' => t('Preview'), '#weight' => 20);
  $form['#token'] = 'comment'. $edit['nid'] . (isset($edit['pid']) ? $edit['pid'] : '');

  if ($op == t('Preview')) {
    $form['#after_build'] = array('comment_form_add_preview');
  }

  if (empty($edit['cid']) && empty($edit['pid'])) {
    $form['#action'] = url('comment/reply/'. $edit['nid']);
  }

  return $form;
}
