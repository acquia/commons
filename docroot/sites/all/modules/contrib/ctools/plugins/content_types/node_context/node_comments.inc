<?php
// $Id: node_comments.inc,v 1.2.2.1 2010/01/29 20:18:25 merlinofchaos Exp $

if (module_exists('comment')) {
  /**
   * Plugins are described by creating a $plugin array which will be used
   * by the system that includes this file.
   */
  $plugin = array(
    'single' => TRUE,
    'title' => t('Node comments'),
    'icon' => 'icon_node.png',
    'description' => t('The comments of the referenced node.'),
    'required context' => new ctools_context_required(t('Node'), 'node'),
    'category' => t('Node'),
    'defaults' => array(
      'mode' => variable_get('comment_default_mode', COMMENT_MODE_THREADED_EXPANDED),
      'order' => variable_get('comment_default_order', COMMENT_ORDER_NEWEST_FIRST),
      'comments_per_page' => variable_get('comment_default_per_page', '50'),
    ),
  );
}

function ctools_node_comments_content_type_render($subtype, $conf, $panel_args, $context) {
  $node = isset($context->data) ? drupal_clone($context->data) : NULL;
  $block = new stdClass();
  $block->module = 'comments';
  $block->delta  = $node->nid;

  $block->title = t('Comments');
  if (empty($node)) {
    $block->content = t('Node comments go here.');
  }
  else {
    $block->content = ctools_comment_render($node, $conf);
    // Update the history table, stating that this user viewed this node.
    node_tag_new($node->nid);
  }

  return $block;
}

function ctools_node_comments_content_type_edit_form(&$form, &$form_state) {
  $conf = $form_state['conf'];
  $form['mode'] = array(
    '#type' => 'select',
    '#title' => t('Mode'),
    '#default_value' => $conf['mode'],
    '#options' => _comment_get_modes(),
    '#weight' => 1,
  );
  $form['order'] = array(
    '#type' => 'select',
    '#title' => t('Sort'),
    '#default_value' => $conf['order'],
    '#options' => _comment_get_orders(),
    '#weight' => 2,
  );
  foreach (_comment_per_page() as $i) {
    $options[$i] = t('!a comments per page', array('!a' => $i));
  }
  $form['comments_per_page'] = array('#type' => 'select',
    '#title' => t('Pager'),
    '#default_value' => $conf['comments_per_page'],
    '#options' => $options,
    '#weight' => 3,
  );
}

function ctools_node_comments_content_type_edit_form_submit(&$form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

function ctools_node_comments_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" comments', array('@s' => $context->identifier));
}

/**
 * This function is a somewhat stripped down version of comment_render
 * that removes a bunch of cruft that we both don't need, and makes it
 * difficult to modify this.
 */
function ctools_comment_render($node, $conf) {
  $output = '';
  if (!user_access('access comments')) {
    return;
  }

  $mode = $conf['mode'];
  $order = $conf['order'];
  $comments_per_page = $conf['comments_per_page'];

  // Multiple comment view
  $query_count = 'SELECT COUNT(*) FROM {comments} WHERE nid = %d';
  $query = 'SELECT c.cid AS cid, c.pid, c.nid, c.subject, c.comment, c.format, c.timestamp, c.name, c.mail, c.homepage, u.uid, u.name AS registered_name, u.picture, u.data, c.thread, c.status, parent_user.uid as parent_uid, parent_user.data as parent_data, parent_user.name as parent_name, parent_user.picture as parent_picture FROM {comments} c INNER JOIN {users} u ON c.uid = u.uid LEFT OUTER JOIN {comments} parent ON c.pid = parent.cid LEFT OUTER JOIN {users} parent_user ON parent.uid = parent_user.uid WHERE c.nid = %d';

  $query_args = array($node->nid);
  if (!user_access('administer comments')) {
    $query       .= ' AND c.status = %d';
    $query_count .= ' AND status = %d';
    $query_args[] = COMMENT_PUBLISHED;
  }

  if ($order == COMMENT_ORDER_NEWEST_FIRST) {
    if ($mode == COMMENT_MODE_FLAT_COLLAPSED || $mode == COMMENT_MODE_FLAT_EXPANDED) {
      $query .= ' ORDER BY c.timestamp DESC';
    }
    else {
      $query .= ' ORDER BY c.thread DESC';
    }
  }
  else if ($order == COMMENT_ORDER_OLDEST_FIRST) {
    if ($mode == COMMENT_MODE_FLAT_COLLAPSED || $mode == COMMENT_MODE_FLAT_EXPANDED) {
      $query .= ' ORDER BY c.timestamp';
    }
    else {
      $query .= ' ORDER BY SUBSTRING(c.thread, 1, (LENGTH(c.thread) - 1))';
    }
  }

  // Start a form, for use with comment control.
  $result = pager_query($query, $comments_per_page, 0, $query_count, $query_args);

  $divs = 0;
  $last_depth = 0;
  drupal_add_css(drupal_get_path('module', 'comment') .'/comment.css');
  while ($comment = db_fetch_object($result)) {
    $comment = drupal_unpack($comment);
    $comment->name  = $comment->uid ? $comment->registered_name : $comment->name;
    $comment->depth = count(explode('.', $comment->thread)) - 1;

    if ($mode == COMMENT_MODE_THREADED_COLLAPSED || $mode == COMMENT_MODE_THREADED_EXPANDED) {
      if ($comment->depth > $last_depth) {
        $divs++;
        $output .= '<div class="indented">';
        $last_depth++;
      }
      else {
        while ($comment->depth < $last_depth) {
          $divs--;
          $output .= '</div>';
          $last_depth--;
        }
      }
    }

    if ($mode == COMMENT_MODE_FLAT_COLLAPSED) {
      $output .= theme('comment_flat_collapsed', $comment, $node);
    }
    else if ($mode == COMMENT_MODE_FLAT_EXPANDED) {
      $output .= theme('comment_flat_expanded', $comment, $node);
    }
    else if ($mode == COMMENT_MODE_THREADED_COLLAPSED) {
      $output .= theme('comment_thread_collapsed', $comment, $node);
    }
    else if ($mode == COMMENT_MODE_THREADED_EXPANDED) {
      $output .= theme('comment_thread_expanded', $comment, $node);
    }
  }
  for ($i = 0; $i < $divs; $i++) {
    $output .= '</div>';
  }
  $output .= theme('pager', NULL, $comments_per_page, 0);

  return $output;
}

