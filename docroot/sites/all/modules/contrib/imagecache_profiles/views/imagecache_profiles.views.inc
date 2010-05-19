<?php
// $Id: imagecache_profiles.views.inc,v 1.1.2.2 2009/08/29 14:02:17 andypost Exp $

function imagecache_profiles_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'imagecache_profiles') .'/views',
    ),
    'handlers' => array(
      'imagecache_profiles_handler_field_user_picture' => array(
        'parent' => 'views_handler_field_user_picture',
      ),
    ),
  );
}

function imagecache_profiles_views_data_alter(&$data) {
  $data['users']['picture']['field']['handler'] = 'imagecache_profiles_handler_field_user_picture';
}
