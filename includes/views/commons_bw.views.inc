<?php

/**
 * Implements hook_views_data()
 */
function commons_bw_views_data() {
  $data = array();

  $data['views']['commons_bw_node_partial_form'] = array(
    'title' => t('Node partial form'),
    'help' => t('Display a minified node creation form.'),
    'area' => array(
      'handler' => 'commons_bw_handler_node_partial_form',
    ),
  );

  return $data;
}
