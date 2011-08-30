<?php

/**
 * Implementation of hook_homebox().
 */
function commons_dashboard_homebox() {
  $homeboxes = array();

  $homeboxes['dashboard'] = array (
    'regions' => 2,
    'cache' => 0,
    'color' => 0,
    'colors' => 
    array (
      0 => '#E4F0F8',
      1 => '#E4F0F8',
      2 => '#E4F0F8',
      3 => '#E4F0F8',
      4 => '#E4F0F8',
      5 => '#E4F0F8',
    ),
    'blocks' => 
    array (
      'views_a63079788b0d983bea5a09b9eaa5671b' => 
      array (
        'module' => 'views',
        'delta' => 'a63079788b0d983bea5a09b9eaa5671b',
        'region' => 1,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -63,
      ),
      'views_recent_notices-block_1' => 
      array (
        'module' => 'views',
        'delta' => 'recent_notices-block_1',
        'region' => 2,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -63,
      ),
      'views_users_online-block_1' => 
      array (
        'module' => 'views',
        'delta' => 'users_online-block_1',
        'region' => 2,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -62,
      ),
      'user_relationship_blocks_user-1' => 
      array (
        'module' => 'user_relationship_blocks',
        'delta' => 'user-1',
        'region' => 2,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => 'My friends',
        'weight' => -61,
      ),
      'views_upcoming_events-block_2' => 
      array (
        'module' => 'views',
        'delta' => 'upcoming_events-block_2',
        'region' => 2,
        'movable' => 1,
        'status' => 1,
        'open' => 0,
        'closable' => 1,
        'title' => '',
        'weight' => -60,
      ),
      'views_profile_user_groups-block_1' => 
      array (
        'module' => 'views',
        'delta' => 'profile_user_groups-block_1',
        'region' => 2,
        'movable' => 1,
        'status' => 1,
        'open' => 0,
        'closable' => 1,
        'title' => '',
        'weight' => -59,
      ),
      'og_3' => 
      array (
        'module' => 'og',
        'delta' => '3',
        'region' => 2,
        'movable' => 1,
        'status' => 1,
        'open' => 1,
        'closable' => 1,
        'title' => '',
        'weight' => -58,
      ),
      'views_my_recent_items-block_1' => 
      array (
        'module' => 'views',
        'delta' => 'my_recent_items-block_1',
        'region' => 2,
        'movable' => 1,
        'status' => 1,
        'open' => 0,
        'closable' => 1,
        'title' => '',
        'weight' => -57,
      ),
    ),
    'widths' => 
    array (
      1 => 70,
      2 => 30,
    ),
    'title' => 'Dashboard',
    'path' => 'dashboard',
    'menu' => 0,
    'enabled' => 1,
    'full' => 1,
    'custom' => 0,
    'roles' => 
    array (
      0 => 'authenticated user',
    ),
  );


  return $homeboxes;
}

/**
 * Implementation of hook_views_api().
 */
function commons_dashboard_views_api() {
  return array(
    'api' => '2',
  );
}
