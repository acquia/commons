<?php

function views_bulk_operations_book_action_info() {
  if (!module_exists('book')) return array();
	return array(
    'views_bulk_operations_move_book_action' => array(
	    'type' => 'node',
		  'description' => t('Move book page to new parent'),
		  'configurable' => TRUE,
		  'behavior' => array('changes_node_property'),
	  ),
		'views_bulk_operations_remove_book_action' => array(
		  'type' => 'node',
		  'description' => t('Remove book page from outline'),
		  'configurable' => FALSE,
		  'behavior' => array('deletes_node_property'),
	  )
  );
}

function views_bulk_operations_move_book_action_form($context) {
	if (!isset($context['book'])) {
		$context['book'] = '';
	}
	$options = array();
	$books = book_get_books();
	foreach ($books as $value) {
		$options[$value['nid']] = $value['title'];
	}

	if (empty($options)) {
		drupal_set_message(t('You have no books.'), 'error');
		return array();
	}

	$form['book'] = array(
	  '#type' => 'select',
	  '#title' => t('Choose a parent book'),
	  '#options' => $options,
	  '#description' => t('Select the parent book page you wish to move the book page into.'),
	);
  return $form;
}

function views_bulk_operations_move_book_action_submit($form, $form_state) {
  return array(
    'book' => $form_state['values']['book'],
  );
}

function views_bulk_operations_move_book_action($node, $context) {
	if (isset($context['book'])) {
		$book_node = node_load($context['book']);
		$bid = $book_node->nid;
		$mlid = $book_node->book['mlid'];
		$node->book['bid'] = $bid;
		$node->book['plid'] = $mlid;
		$node->book['module'] = 'book';
		book_nodeapi($node, 'update', $a3 = NULL, $a4 = NULL);
		drupal_set_message(t('Book page %node was successfully added to %book_node.', array('%node' => $node->title, '%book_node' =>$book_node->title)));
	}
}

function views_bulk_operations_remove_book_action($node, $context) {
	$node->book['module'] = 'book';
	book_nodeapi($node, 'delete', $a3 = NULL, $a4 = NULL);
	drupal_set_message(t('%node was removed from outline.', array('%node' => $node->title, '%mlid' => $node->book['mlid'])));
}
