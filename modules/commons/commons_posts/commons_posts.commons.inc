<?php
/**
 * @file
 * Commons module integration for the Commons Posts module.
 */

/**
 * Implements hook_commons_entity_integration().
 */
function commons_posts_commons_entity_integration() {
  return array(
    'node' => array(
      'post' => array(
        'media' => TRUE,
        'is_group_content' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_commons_bw_group_widget().
 */
function commons_posts_commons_bw_group_widget() {
  return array(
    'commons_posts' => array(
      'title' => t('Posts'),
      'type' => 'view',
      'vid' => 'commons_bw_posts',
      'display' => 'default',
      'weight' => -1,
      'bundle' => 'post',
    ),
  );
}

/**
 * Implements hook_commons_bw_create_all_widget().
 */
function commons_posts_commons_bw_create_all_widget($group) {
  if (og_user_access('node', $group->nid, 'create post content')) {
    $link = l(t('Create a post'),'node/add/post',
      array('attributes' => array('class' => 'commons-posts-create'), 'query' => array('og_group_ref' => $group->nid))
    );
    return array(
      'commons_posts' => array(
        'default' => TRUE,
        'link' => $link,
        'text' =>  t('Foster a topic through commenting'),
        '#weight' => -1,
      ),
    );
  }
}
