<?php
/**
 * @file
 * commons_events_solr.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function commons_events_solr_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'pm_existing_pages_solr_events_search_panel_context';
  $handler->task = 'pm_existing_pages';
  $handler->subtask = 'solr_events_search';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Event Search',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'three_25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'three_25_50_25_top' => NULL,
      'three_25_50_25_first' => NULL,
      'three_25_50_25_second' => NULL,
      'three_25_50_25_third' => NULL,
      'three_25_50_25_bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'bf4f354a-dc68-cab4-a139-49e172b1c4ed';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-2edbeade-1d05-fbd4-f526-68239a54433f';
    $pane->panel = 'three_25_50_25_first';
    $pane->type = 'block';
    $pane->subtype = commons_events_solr_panel_facet_subtype('sm_field_location');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Attendance',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '2edbeade-1d05-fbd4-f526-68239a54433f';
    $display->content['new-2edbeade-1d05-fbd4-f526-68239a54433f'] = $pane;
    $display->panels['three_25_50_25_first'][0] = 'new-2edbeade-1d05-fbd4-f526-68239a54433f';
    $pane = new stdClass();
    $pane->pid = 'new-06093184-ccdb-9a84-1da8-e9f2dff0d882';
    $pane->panel = 'three_25_50_25_first';
    $pane->type = 'block';
    $pane->subtype = commons_events_solr_panel_facet_subtype('dm_field_date');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Date',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '06093184-ccdb-9a84-1da8-e9f2dff0d882';
    $display->content['new-06093184-ccdb-9a84-1da8-e9f2dff0d882'] = $pane;
    $display->panels['three_25_50_25_first'][1] = 'new-06093184-ccdb-9a84-1da8-e9f2dff0d882';
    $pane = new stdClass();
    $pane->pid = 'new-c84b8b32-c6d5-9ce4-bdec-f2735c5045b8';
    $pane->panel = 'three_25_50_25_first';
    $pane->type = 'block';
    $pane->subtype = commons_events_solr_panel_facet_subtype('im_field_topics');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Topic',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'c84b8b32-c6d5-9ce4-bdec-f2735c5045b8';
    $display->content['new-c84b8b32-c6d5-9ce4-bdec-f2735c5045b8'] = $pane;
    $display->panels['three_25_50_25_first'][2] = 'new-c84b8b32-c6d5-9ce4-bdec-f2735c5045b8';
    $pane = new stdClass();
    $pane->pid = 'new-c46f0562-0218-76c4-b969-3abdc98f24fa';
    $pane->panel = 'three_25_50_25_first';
    $pane->type = 'block';
    $pane->subtype = commons_events_solr_panel_facet_subtype('sm_og_group_ref');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Group',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'c46f0562-0218-76c4-b969-3abdc98f24fa';
    $display->content['new-c46f0562-0218-76c4-b969-3abdc98f24fa'] = $pane;
    $display->panels['three_25_50_25_first'][3] = 'new-c46f0562-0218-76c4-b969-3abdc98f24fa';
    $pane = new stdClass();
    $pane->pid = 'new-ba67e9d1-00ed-07b4-49df-bff421094214';
    $pane->panel = 'three_25_50_25_second';
    $pane->type = 'pm_existing_pages';
    $pane->subtype = 'pm_existing_pages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      0 => 'task_id',
      1 => 'pane_title_from_menu',
      'task_id' => 'solr_events_search',
      'pane_title_from_menu' => 0,
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ba67e9d1-00ed-07b4-49df-bff421094214';
    $display->content['new-ba67e9d1-00ed-07b4-49df-bff421094214'] = $pane;
    $display->panels['three_25_50_25_second'][0] = 'new-ba67e9d1-00ed-07b4-49df-bff421094214';
    $pane = new stdClass();
    $pane->pid = 'new-f5cb9927-def5-8f94-098b-ca9d83eaf9fa';
    $pane->panel = 'three_25_50_25_third';
    $pane->type = 'block';
    $pane->subtype = 'commons_events-commons_events_create_event_link';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'f5cb9927-def5-8f94-098b-ca9d83eaf9fa';
    $display->content['new-f5cb9927-def5-8f94-098b-ca9d83eaf9fa'] = $pane;
    $display->panels['three_25_50_25_third'][0] = 'new-f5cb9927-def5-8f94-098b-ca9d83eaf9fa';
    $pane = new stdClass();
    $pane->pid = 'new-a9b484b9-8f95-46e4-d930-64dc3d093f3d';
    $pane->panel = 'three_25_50_25_third';
    $pane->type = 'block';
    $pane->subtype = 'commons_events-commons_events_anonymous_login';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'a9b484b9-8f95-46e4-d930-64dc3d093f3d';
    $display->content['new-a9b484b9-8f95-46e4-d930-64dc3d093f3d'] = $pane;
    $display->panels['three_25_50_25_third'][1] = 'new-a9b484b9-8f95-46e4-d930-64dc3d093f3d';
    $pane = new stdClass();
    $pane->pid = 'new-ae313741-a577-f194-9dd7-868986d44baf';
    $pane->panel = 'three_25_50_25_third';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_events_user_upcoming_events-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'ae313741-a577-f194-9dd7-868986d44baf';
    $display->content['new-ae313741-a577-f194-9dd7-868986d44baf'] = $pane;
    $display->panels['three_25_50_25_third'][2] = 'new-ae313741-a577-f194-9dd7-868986d44baf';
    $pane = new stdClass();
    $pane->pid = 'new-6c32c82b-82f2-97f4-55b1-bc38ddc2e4b6';
    $pane->panel = 'three_25_50_25_third';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_events_user_upcoming_events-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '6c32c82b-82f2-97f4-55b1-bc38ddc2e4b6';
    $display->content['new-6c32c82b-82f2-97f4-55b1-bc38ddc2e4b6'] = $pane;
    $display->panels['three_25_50_25_third'][3] = 'new-6c32c82b-82f2-97f4-55b1-bc38ddc2e4b6';
    $pane = new stdClass();
    $pane->pid = 'new-0e2c9d7d-abfe-e314-9dba-e9c8dae6fc74';
    $pane->panel = 'three_25_50_25_third';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_events_user_upcoming_events-panel_pane_3';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '0e2c9d7d-abfe-e314-9dba-e9c8dae6fc74';
    $display->content['new-0e2c9d7d-abfe-e314-9dba-e9c8dae6fc74'] = $pane;
    $display->panels['three_25_50_25_third'][4] = 'new-0e2c9d7d-abfe-e314-9dba-e9c8dae6fc74';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-ba67e9d1-00ed-07b4-49df-bff421094214';
  $handler->conf['display'] = $display;
  $export['pm_existing_pages_solr_events_search_panel_context'] = $handler;

  return $export;
}
