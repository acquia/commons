<?php

/**
* Implements hook_views_data_alter().
*/
function commons_follow_views_data_alter(&$data) {
  $data['message']['mid_follow'] = array(
    'title' => 'Message id Follow',
    'help' => 'Filter messages based on what the current user is following.',
    'filter' => array(
      'handler' => 'commons_follow_handler_filter_follow',
      'real field' => 'mid',
    ),
  );
}



/**
 * Implements hook_views_plugins().
 */
function commons_follow_views_plugins() {
  // This handler requires message_subscribe module.
  return array(
    'argument default' => array(
      'commons_follow_node' => array(
        'title' => t('The node IDs the user is subscribed to'),
        'handler' => 'commons_follow_plugin_argument_default_node',
      ),
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function commons_follow_views_data() {
  $data['node']['cf_user_follow'] = array(
    'title' => t('User Follow'), // The item it appears as on the UI,
    'help' => t('Whether the user is following this content.'), // The help that appears on the UI,
    'real field' => 'nid',
     // Information for displaying a title as a field
    'filter' => array(
      'handler' => 'commons_follow_user_follow_filter',
      'label' => t('Following'),
      'type' => 'yes-no',
    ),
  );

  return $data;
}
