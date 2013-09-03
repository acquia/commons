<?php
/**
 * @file
 * commons_activity_page.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function commons_activity_page_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'commons_activity_streams_activity';
  $page->task = 'page';
  $page->admin_title = 'Activity';
  $page->admin_description = '';
  $page->path = 'activity';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_commons_activity_streams_activity_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'commons_activity_streams_activity';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Activity',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'two_66_33';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'two_66_33_top' => NULL,
      'two_66_33_first' => NULL,
      'two_66_33_second' => NULL,
      'two_66_33_bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Recent site activity';
  $display->uuid = '5421dc96-4e35-5794-5539-fc6123374548';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-6251a6df-20d2-5034-f9d8-a66cd04f16e9';
    $pane->panel = 'two_66_33_first';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_activity_streams_activity-panel_pane_3';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '6251a6df-20d2-5034-f9d8-a66cd04f16e9';
    $display->content['new-6251a6df-20d2-5034-f9d8-a66cd04f16e9'] = $pane;
    $display->panels['two_66_33_first'][0] = 'new-6251a6df-20d2-5034-f9d8-a66cd04f16e9';
    $pane = new stdClass();
    $pane->pid = 'new-6668ecda-9f18-0744-71cb-afcb5fb5114d';
    $pane->panel = 'two_66_33_second';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_featured-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '6668ecda-9f18-0744-71cb-afcb5fb5114d';
    $display->content['new-6668ecda-9f18-0744-71cb-afcb5fb5114d'] = $pane;
    $display->panels['two_66_33_second'][0] = 'new-6668ecda-9f18-0744-71cb-afcb5fb5114d';
    $pane = new stdClass();
    $pane->pid = 'new-e5d75ae1-dae7-bb04-0977-6e6c5a230f3d';
    $pane->panel = 'two_66_33_second';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_groups_contributors-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'e5d75ae1-dae7-bb04-0977-6e6c5a230f3d';
    $display->content['new-e5d75ae1-dae7-bb04-0977-6e6c5a230f3d'] = $pane;
    $display->panels['two_66_33_second'][1] = 'new-e5d75ae1-dae7-bb04-0977-6e6c5a230f3d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-6251a6df-20d2-5034-f9d8-a66cd04f16e9';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['commons_activity_streams_activity'] = $page;

  return $pages;

}
