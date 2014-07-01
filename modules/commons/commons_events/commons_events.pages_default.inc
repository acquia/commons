<?php
/**
 * @file
 * commons_events.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function commons_events_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'views_events_landing_page';
  $page->task = 'page';
  $page->admin_title = 'Views Events Landing Page';
  $page->admin_description = '';
  $page->path = 'events';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Events',
    'weight' => '2',
    'name' => 'main-menu',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'weight' => 0,
      'name' => 'navigation',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_views_events_landing_page_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'views_events_landing_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
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
  $display->title = 'Events';
  $display->uuid = 'f084cd6c-0d66-7ca4-c971-3c5cf182d2ec';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-e72884a7-369b-1954-2d1f-d69207c4d6ff';
    $pane->panel = 'two_66_33_first';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_events_upcoming-panel_pane_2';
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
    $pane->uuid = 'e72884a7-369b-1954-2d1f-d69207c4d6ff';
    $display->content['new-e72884a7-369b-1954-2d1f-d69207c4d6ff'] = $pane;
    $display->panels['two_66_33_first'][0] = 'new-e72884a7-369b-1954-2d1f-d69207c4d6ff';
    $pane = new stdClass();
    $pane->pid = 'new-b91ad246-669c-2e14-fd32-5728153b0ed8';
    $pane->panel = 'two_66_33_second';
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
    $pane->uuid = 'b91ad246-669c-2e14-fd32-5728153b0ed8';
    $display->content['new-b91ad246-669c-2e14-fd32-5728153b0ed8'] = $pane;
    $display->panels['two_66_33_second'][0] = 'new-b91ad246-669c-2e14-fd32-5728153b0ed8';
    $pane = new stdClass();
    $pane->pid = 'new-d776b637-24a9-7e74-712c-8bc27d399c3e';
    $pane->panel = 'two_66_33_second';
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
    $pane->uuid = 'd776b637-24a9-7e74-712c-8bc27d399c3e';
    $display->content['new-d776b637-24a9-7e74-712c-8bc27d399c3e'] = $pane;
    $display->panels['two_66_33_second'][1] = 'new-d776b637-24a9-7e74-712c-8bc27d399c3e';
    $pane = new stdClass();
    $pane->pid = 'new-9118fc7d-3da5-cf54-5152-5d66043812b2';
    $pane->panel = 'two_66_33_second';
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
    $pane->uuid = '9118fc7d-3da5-cf54-5152-5d66043812b2';
    $display->content['new-9118fc7d-3da5-cf54-5152-5d66043812b2'] = $pane;
    $display->panels['two_66_33_second'][2] = 'new-9118fc7d-3da5-cf54-5152-5d66043812b2';
    $pane = new stdClass();
    $pane->pid = 'new-ef7caf29-a6a8-e654-5997-6b969eba407a';
    $pane->panel = 'two_66_33_second';
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
    $pane->uuid = 'ef7caf29-a6a8-e654-5997-6b969eba407a';
    $display->content['new-ef7caf29-a6a8-e654-5997-6b969eba407a'] = $pane;
    $display->panels['two_66_33_second'][3] = 'new-ef7caf29-a6a8-e654-5997-6b969eba407a';
    $pane = new stdClass();
    $pane->pid = 'new-80f087dc-fe84-7354-e19b-23e398080db9';
    $pane->panel = 'two_66_33_second';
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
    $pane->uuid = '80f087dc-fe84-7354-e19b-23e398080db9';
    $display->content['new-80f087dc-fe84-7354-e19b-23e398080db9'] = $pane;
    $display->panels['two_66_33_second'][4] = 'new-80f087dc-fe84-7354-e19b-23e398080db9';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-9118fc7d-3da5-cf54-5152-5d66043812b2';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['views_events_landing_page'] = $page;

  return $pages;

}
