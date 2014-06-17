<?php
/**
 * @file
 * commons_radioactivity.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function commons_radioactivity_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'commons_radioactivity_admin';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Commons Radioactivity Admin';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Commons Radioactivity Administrative page';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer content types';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'type' => 'type',
    'name' => 'name',
    'field_radioactivity' => 'field_radioactivity',
    'created' => 'created',
    'last_updated' => 'last_updated',
  );
  $handler->display->display_options['style_options']['default'] = 'field_radioactivity';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_radioactivity' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_updated' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_field']['id'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field']['field'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['label'] = '';
  $handler->display->display_options['fields']['title_field']['link_to_entity'] = 1;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Author';
  /* Field: Content: Radioactivity */
  $handler->display->display_options['fields']['field_radioactivity']['id'] = 'field_radioactivity';
  $handler->display->display_options['fields']['field_radioactivity']['table'] = 'field_data_field_radioactivity';
  $handler->display->display_options['fields']['field_radioactivity']['field'] = 'field_radioactivity';
  $handler->display->display_options['fields']['field_radioactivity']['click_sort_column'] = 'radioactivity_energy';
  $handler->display->display_options['fields']['field_radioactivity']['settings'] = array(
    'energy' => '0',
    'type' => 'energy',
  );
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Content: Updated/commented date */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Last update/comment';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'short';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Radioactivity (field_radioactivity:radioactivity_energy) */
  $handler->display->display_options['filters']['field_radioactivity_radioactivity_energy']['id'] = 'field_radioactivity_radioactivity_energy';
  $handler->display->display_options['filters']['field_radioactivity_radioactivity_energy']['table'] = 'field_data_field_radioactivity';
  $handler->display->display_options['filters']['field_radioactivity_radioactivity_energy']['field'] = 'field_radioactivity_radioactivity_energy';
  $handler->display->display_options['filters']['field_radioactivity_radioactivity_energy']['operator'] = '>';
  $handler->display->display_options['filters']['field_radioactivity_radioactivity_energy']['value']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'commons-radioactivity-admin';
  $translatables['commons_radioactivity_admin'] = array(
    t('Master'),
    t('Commons Radioactivity Administrative page'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('author'),
    t('Title'),
    t('Type'),
    t('Author'),
    t('Radioactivity'),
    t('Created'),
    t('Last update/comment'),
    t('Page'),
  );
  $export['commons_radioactivity_admin'] = $view;

  return $export;
}

/**
 * Implements hook_views_default_views_alter().
 */
function commons_radioactivity_views_default_views_alter(&$views) {
  // Add a "most active" exposed sort to Commons BW views.
  foreach ($views as $view_id => $view) {
    if (strpos($view_id, 'commons_bw_') === 0) {
      $views[$view_id]->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['id'] = 'field_radioactivity_radioactivity_energy';
      $views[$view_id]->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['table'] = 'field_data_field_radioactivity';
      $views[$view_id]->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['field'] = 'field_radioactivity_radioactivity_energy';
      $views[$view_id]->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['order'] = 'DESC';
      $views[$view_id]->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['exposed'] = TRUE;
      $views[$view_id]->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['expose']['label'] = 'most active';
    }
  }

  // Add a 'most active' exposed sort to the homepage content view.
  if (!empty($views['commons_homepage_content'])) {
    /* Sort criterion: Content: Radioactivity (field_radioactivity:radioactivity_energy) */
    $views['commons_homepage_content']->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['id'] = 'field_radioactivity_radioactivity_energy';
    $views['commons_homepage_content']->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['table'] = 'field_data_field_radioactivity';
    $views['commons_homepage_content']->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['field'] = 'field_radioactivity_radioactivity_energy';
    $views['commons_homepage_content']->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['order'] = 'DESC';
    $views['commons_homepage_content']->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['exposed'] = TRUE;
    $views['commons_homepage_content']->display['default']->display_options['sorts']['field_radioactivity_radioactivity_energy']['expose']['label'] = 'most active';
  }
}
