<?php
/**
 * @file
 * Commons module integration for the Commons Documents module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_documents_commons_entity_integration() {
  return array(
    'node' => array(
      'document' => array(
        'is_group_content' => TRUE,
        'exclude_rate' => TRUE,
        'exclude_rate_comments' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_commons_bw_group_widget().
 */
function commons_documents_commons_bw_group_widget() {
  return array(
    'commons_documents' => array(
      'title' => t('Docs'),
      'type' => 'view',
      'vid' => 'commons_bw_documents',
      'display' => 'default',
      'weight' => 6,
      'bundle' => 'document',
    ),
  );
}

/**
 * Implements hook_commons_bw_create_all_widget().
 */
function commons_documents_commons_bw_create_all_widget($group) {
  if (og_user_access('node', $group->nid, 'create document content')) {
    $link = l(t('Create a document'),'node/add/document',
      array('attributes' => array('class' => 'commons-documents-create'), 'query' => array('og_group_ref' => $group->nid))
    );
    return array(
      'commons_documents' => array(
        'link' => $link,
        'text' => t('Share a document'),
        '#weight' => 6,
      ),
    );
  }
}
