<?php
// $Id: book_parent.inc,v 1.2.2.2 2010/01/29 20:18:26 merlinofchaos Exp $

/**
 * @file
 * Plugin to provide an relationship handler for book parent.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Book parent'),
  'keyword' => 'book_parent',
  'description' => t('Adds a book parent from a node context.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'context' => 'ctools_book_parent_context',
  'settings form' => 'ctools_book_parent_settings_form',
  'settings form validate' => 'ctools_book_parent_settings_form_validate',
);

/**
 * Return a new context based on an existing context.
 */
function ctools_book_parent_context($context, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL.
  if (empty($context->data)) {
    return ctools_context_create_empty('node');
  }

  if (isset($context->data->parent)) {
    if ($conf['type'] == 'top') {
      // Search through the book tree to load the top level.
      $result = array('nid' => $context->data->nid, 'vid' => $context->data->vid, 'parent' => $context->data->parent);
      while (!empty($result['parent'])) {
        $result = db_fetch_array(db_query("SELECT * FROM {book} b INNER JOIN {node} n ON b.vid = n.nid WHERE b.nid = %d", $result['parent']));
      }
      $nid = $result['nid'];
    }
    else {
      // Just load the parent book.
      $nid = $context->data->parent;
    }

    if (!empty($nid)) {
      // Load the node.
      $node = node_load($nid);
      // Generate the context.
      return ctools_context_create('node', $node);
    }
  }
}

/**
 * Settings form for the relationship.
 */
function ctools_book_parent_settings_form($conf) {
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Relationship type'),
    '#options' => array('parent' => t('Immediate parent'), 'top' => t('Top level book')),
    '#default_value' => $conf['type'],
  );

  return $form;
}
