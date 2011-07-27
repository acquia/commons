<?php

/**
 * @file
 *   Integrates Facebook-style Statuses Private Statuses with Views.
 */

/**
 * Implementation of hook_views_query_alter().
 */
function fbss_privacy_views_query_alter(&$view, &$query) {
  global $user;
  // Alter any view that shows status updates and exclude private statuses (unless we've already set a related filter).
  foreach ($query->table_queue as $table) {
    if ($table['table'] == 'facebook_status' && !isset($query->where['fbss_privacy']) && !user_access('view all private status messages')) {
      $query->add_where('fbss_privacy',
        $table['alias'] .'.private = 0 OR '.
        $table['alias'] .'.sender = %d OR ('.
          $table['alias'] .".type = 'user' AND ". $table['alias'] .".recipient = %d)",
        $user->uid, $user->uid);
      break;
    }
  }
}

/**
 * Implementation of hook_views_data().
 */
function fbss_privacy_views_data() {
  $data = array();
  $data['facebook_status']['private'] = array(
    'title' => t('Show private status messages'),
    'help' => t('Enable showing private status messages in this view.'),
    'field' => array(
      'handler' => 'fbss_privacy_views_handler_field',
      'label' => t('The word "%private" if the status message is private', array('%private' => t('(Private)'))),
    ),
    'filter' => array(
      'handler' => 'fbss_privacy_views_handler_filter',
      'label' => t('Show private status messages'),
    ),
    'argument' => array(
      'handler' => 'fbss_privacy_views_handler_argument',
      'label' => t('Show private status messages'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
      'label' => t('Private messages first'),
    ),
  );
  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function fbss_privacy_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'fbss_privacy'),
    ),
    'handlers' => array(
      'fbss_privacy_views_handler_argument' => array(
        'parent' => 'views_handler_argument',
      ),
      'fbss_privacy_views_handler_field' => array(
        'parent' => 'views_handler_field',
      ),
      'fbss_privacy_views_handler_filter' => array(
        'parent' => 'views_handler_filter',
      ),
    ),
  );
}
