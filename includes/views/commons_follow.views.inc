<?php


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
      'commons_follow_message' => array(
        'title' => t('The message IDs the user is subscribed to'),
        'handler' => 'commons_follow_plugin_argument_default_message',
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

  $data['message']['cf_user_follow_message'] = array(
    'title' => t('User Follow'), // The item it appears as on the UI,
    'help' => t('Whether the user is following items related to this message.'), // The help that appears on the UI,
    'real field' => 'mid',
     // Information for displaying a title as a field
    'filter' => array(
      'handler' => 'commons_follow_user_follow_filter_message',
      'label' => t('Following'),
      'type' => 'yes-no',
    ),
  );

  return $data;
}
