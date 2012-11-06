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