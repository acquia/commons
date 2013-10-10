<?php
/**
 * @file
 * commons_search_solr.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function commons_search_solr_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'pm_existing_pages_solr_search_panel_context';
  $handler->task = 'pm_existing_pages';
  $handler->subtask = 'solr_search';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'search',
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
  $display->layout = 'two_33_66';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'two_33_66_top' => NULL,
      'two_33_66_first' => NULL,
      'two_33_66_second' => NULL,
      'two_33_66_bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '06329041-e13c-1174-ed2a-d4a50d0aa4d2';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-463814d4-a8ba-7b94-c9d5-77faae3cea01';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = commons_search_solr_panel_facet_subtype(commons_search_solr_search_environment() . ':block:sm_og_group_ref');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => t('Groups'),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '463814d4-a8ba-7b94-c9d5-77faae3cea01';
    $display->content['new-463814d4-a8ba-7b94-c9d5-77faae3cea01'] = $pane;
    $display->panels['two_33_66_first'][0] = 'new-463814d4-a8ba-7b94-c9d5-77faae3cea01';
    $pane = new stdClass();
    $pane->pid = 'new-7accd7bf-9b29-ce34-8de0-528f3a89ba02';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = commons_search_solr_panel_facet_subtype(commons_search_solr_search_environment() . ':block:im_field_topics');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => t('Topics'),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '7accd7bf-9b29-ce34-8de0-528f3a89ba02';
    $display->content['new-7accd7bf-9b29-ce34-8de0-528f3a89ba02'] = $pane;
    $display->panels['two_33_66_first'][1] = 'new-7accd7bf-9b29-ce34-8de0-528f3a89ba02';
    $pane = new stdClass();
    $pane->pid = 'new-0ff4a758-76a3-1944-29fe-a19ae7f1abd1';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = commons_search_solr_panel_facet_subtype(commons_search_solr_search_environment() . ':block:bundle');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => t('Type'),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '0ff4a758-76a3-1944-29fe-a19ae7f1abd1';
    $display->content['new-0ff4a758-76a3-1944-29fe-a19ae7f1abd1'] = $pane;
    $display->panels['two_33_66_first'][2] = 'new-0ff4a758-76a3-1944-29fe-a19ae7f1abd1';
    $pane = new stdClass();
    $pane->pid = 'new-971af469-d142-9b34-4d91-7d2b2b06d750';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = commons_search_solr_panel_facet_subtype(commons_search_solr_search_environment() . ':block:author');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => t('Author'),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '971af469-d142-9b34-4d91-7d2b2b06d750';
    $display->content['new-971af469-d142-9b34-4d91-7d2b2b06d750'] = $pane;
    $display->panels['two_33_66_first'][3] = 'new-971af469-d142-9b34-4d91-7d2b2b06d750';
    $pane = new stdClass();
    $pane->pid = 'new-9580c1e3-390b-0954-65a6-3804ab628265';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = commons_search_solr_panel_facet_subtype(commons_search_solr_search_environment() . ':block:created');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => t('Date created'),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '9580c1e3-390b-0954-65a6-3804ab628265';
    $display->content['new-9580c1e3-390b-0954-65a6-3804ab628265'] = $pane;
    $display->panels['two_33_66_first'][4] = 'new-9580c1e3-390b-0954-65a6-3804ab628265';
    $pane = new stdClass();
    $pane->pid = 'new-036759bf-aab4-5b04-8d88-81e0debf0e23';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = commons_search_solr_panel_facet_subtype(commons_search_solr_search_environment() . ':block:changed');
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => t('Date changed'),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '036759bf-aab4-5b04-8d88-81e0debf0e23';
    $display->content['new-036759bf-aab4-5b04-8d88-81e0debf0e23'] = $pane;
    $display->panels['two_33_66_first'][5] = 'new-036759bf-aab4-5b04-8d88-81e0debf0e23';
    $pane = new stdClass();
    $pane->pid = 'new-da122a41-c889-4be4-519a-f29568f411ef';
    $pane->panel = 'two_33_66_second';
    $pane->type = 'pm_existing_pages';
    $pane->subtype = 'pm_existing_pages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      0 => 'task_id',
      1 => 'pane_title_from_menu',
      'task_id' => 'solr_search',
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
    $pane->uuid = 'da122a41-c889-4be4-519a-f29568f411ef';
    $display->content['new-da122a41-c889-4be4-519a-f29568f411ef'] = $pane;
    $display->panels['two_33_66_second'][0] = 'new-da122a41-c889-4be4-519a-f29568f411ef';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['pm_existing_pages_solr_search_panel_context'] = $handler;

  return $export;
}
