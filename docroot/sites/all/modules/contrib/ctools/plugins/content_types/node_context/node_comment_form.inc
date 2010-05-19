<?php
// $Id: node_comment_form.inc,v 1.1.2.1 2010/01/29 20:18:25 merlinofchaos Exp $

if (module_exists('comment')) {
  /**
   * Plugins are described by creating a $plugin array which will be used
   * by the system that includes this file.
   */
  $plugin = array(
    'single' => TRUE,
    'title' => t('Comment form'),
    'icon' => 'icon_node.png',
    'description' => t('A form to add a new comment.'),
    'required context' => new ctools_context_required(t('Node'), 'node'),
    'category' => t('Node'),
  );
}

function ctools_node_comment_form_content_type_render($subtype, $conf, $panel_args, $context) {
  $node = isset($context->data) ? drupal_clone($context->data) : NULL;
  $block = new stdClass();
  $block->module = 'comments';
  $block->delta  = $node->nid;

  $block->title = t('Add comment');

  if (empty($node)) {
    $block->content = t('Comment form here.');
  }
  else {
    if (user_access('post comments') && node_comment_mode($node->nid) == COMMENT_NODE_READ_WRITE) {
      ctools_include('form');
      $form_state = array(
        'ctools comment alter' => TRUE,
        'node' => $node,
        'args' => array(array('nid' => $node->nid))
      );
      $block->content = ctools_build_form('comment_form', $form_state);
    }
  }

  return $block;
}

function ctools_node_comment_form_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" comment form', array('@s' => $context->identifier));
}

function ctools_node_comment_form_content_type_edit_form(&$form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
}

/**
 * Alter the comment form to get a little more control over it.
 */
function ctools_form_comment_form_alter(&$form, &$form_state) {
  if (!empty($form_state['ctools comment alter'])) {
    $node =
    // force the form to post back to wherever we are.
    $url = parse_url($_GET['q']);
    $form['#action'] = url($url['path'], array('fragment' => 'comment-form'));
    if (empty($form['#submit'])) {
      $form['#submit'] = array('comment_form_submit');
    }
    $form['#submit'][] = 'ctools_node_comment_form_submit';
  }
}

function ctools_node_comment_form_submit(&$form, &$form_state) {
  $form_state['redirect'][0] = $_GET['q'];
}
