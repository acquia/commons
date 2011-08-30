<?php
// $Id: user_relationships_ui.pages.inc,v 1.1.2.7 2009/11/07 21:24:54 alexk Exp $
/**
 * @file
 * Various user relationships admin and user pages
 */

/**
 * Relationship Types List
 */
function user_relationships_ui_types_list_page() {
  $relationship_types = user_relationships_types_load();

  $table['headers'] = array(t('Name'), t('Plural'), t('Type'), t('Requires Approval'), t('Expiration'), t('Operations'));
  $table['data'] = array();
  $table['rows'] = array();

  foreach ($relationship_types as $relationship) {
    $table['data'][] = $relationship;
    $table['rows'][] = array(
      $relationship->name,
      $relationship->plural_name,
      ($relationship->is_oneway ? ($relationship->is_reciprocal ? t('reciprocal') : t('one way')) : t('mutual')),
      ($relationship->requires_approval ? t('yes') : t('no')),
      ($relationship->expires_val ? t('@expires_val', array('@expires_val' => format_plural($relationship->expires_val, '1 day', '@count days'))) : t('Never')),
      l(t('edit'),    "admin/user/relationships/{$relationship->rtid}/edit") .' | '.
      l(t('delete'),  "admin/user/relationships/{$relationship->rtid}/delete")
    );
  }

  foreach (module_implements('user_relationships_page_alter') as $module) {
    $function = "{$module}_user_relationships_page_alter";
    $function('types list', $page, $table);
  }

  if (!sizeof($table['rows'])) {
    $table['rows'][] = array(array('data' => t('No relationships available.'), 'colspan' => sizeof($table['headers'])));
  }

  $page['relationships'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('Relationship Types'),
    '#weight' => 0
  );
    $page['relationships']['list'] = array(
      '#value' => theme('table', $table['headers'], $table['rows'])
    );

  return drupal_render($page);
}

/**
 * Main list of relationships for a specified user
 */
function user_relationships_page($account = NULL, $rtid = NULL) {
  if (!$account) {
    global $user;
    $account = $user;
  }

  return theme('user_relationships', $account, $rtid);
}

/**
 * List of pending requests from other users
 */
function user_relationships_pending_requests_page($account = NULL) {
  // Check that the uid is valid, not the anonymous user, and the user exists
  if (!$account) {
    global $user;
    $account = $user;
  }

  return theme('user_relationships_pending_requests', $account);
}
