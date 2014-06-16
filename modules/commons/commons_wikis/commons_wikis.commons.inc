<?php
/**
 * @file
 * Commons module integration for the Commons Wikis module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_wikis_commons_entity_integration() {
  return array(
    'node' => array(
      'wiki' => array(
        'auto_title_instance' => FALSE,
        'is_group_content' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_commons_bw_group_widget().
 */
function commons_wikis_commons_bw_group_widget() {
  return array(
    'commons_wikis' => array(
      'title' => t('Wikis'),
      'type' => 'view',
      'vid' => 'commons_bw_wikis',
      'display' => 'default',
      'weight' => 8,
      'bundle' => 'wiki',
    ),
  );
}

/**
 * Implements hook_commons_bw_create_all_widget().
 */
function commons_wikis_commons_bw_create_all_widget($group) {
  if (og_user_access('node', $group->nid, 'create wiki content')) {
    $link = l(t('Start a wiki'), 'node/add/wiki',
      array('attributes' => array('class' => 'commons-wikis-create'), 'query' => array('og_group_ref' => $group->nid))
    );
    return array(
      'commons_wikis' => array(
        'link' => $link,
        'text' => t('Collaborate on a document'),
        '#weight' => 8,
      ),
    );
  }
}
