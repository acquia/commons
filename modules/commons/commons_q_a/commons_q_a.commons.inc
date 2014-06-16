<?php
/**
 * @file
 * Commons module integration for the Commons Q&A module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_q_a_commons_entity_integration() {
  return array(
    'node' => array(
      'question' => array(
        'media' => TRUE,
        'is_group_content' => TRUE,
      ),
      'answer' => array(
        'exclude_topics' => TRUE,
        'exclude_rate' => TRUE,
        'is_group_content' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_commons_bw_group_widget().
 */
function commons_q_a_commons_bw_group_widget() {
  return array(
    'commons_q_a' => array(
      'title' => t('Q & A'),
      'type' => 'view',
      'vid' => 'commons_bw_q_a',
      'display' => 'default',
      'weight' => 5,
      'bundle' => 'question',
    ),
  );
}

/**
 * Implements hook_commons_bw_create_all_widget().
 */
function commons_q_a_commons_bw_create_all_widget($group) {
  if (og_user_access('node', $group->nid, 'create question content')) {
    $link = l(t('Ask a question'),'node/add/question',
      array('attributes' => array('class' => 'commons-q-a-create'), 'query' => array('og_group_ref' => $group->nid))
    );
    return array(
      'commons_q_a' => array(
        'link' => $link,
        'text' => t('Learn the best answer'),
        '#weight' => 5,
      ),
    );
  }
}
