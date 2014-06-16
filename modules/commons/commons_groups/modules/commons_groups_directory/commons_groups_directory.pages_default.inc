<?php
/**
 * @file
 * commons_groups_directory.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function commons_groups_directory_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'groups_directory';
  $page->task = 'page';
  $page->admin_title = 'Groups Directory';
  $page->admin_description = 'A directory of groups.';
  $page->path = 'groups';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Groups',
    'name' => 'main-menu',
    'weight' => '-1',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '-1',
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
  $handler->name = 'page_groups_directory_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'groups_directory';
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
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
      'two_66_33_top' => NULL,
      'two_66_33_first' => NULL,
      'two_66_33_second' => NULL,
      'two_66_33_bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Groups';
  $display->uuid = 'b342a293-2541-cc64-1577-839054c92368';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-bf6c6f1b-08a6-3874-7186-c955c763c092';
    $pane->panel = 'two_66_33_first';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_groups_directory-panel_pane_1';
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
    $pane->uuid = 'bf6c6f1b-08a6-3874-7186-c955c763c092';
    $display->content['new-bf6c6f1b-08a6-3874-7186-c955c763c092'] = $pane;
    $display->panels['two_66_33_first'][0] = 'new-bf6c6f1b-08a6-3874-7186-c955c763c092';
    $pane = new stdClass();
    $pane->pid = 'new-3db36521-fb53-58a4-c9e2-137a2dacee07';
    $pane->panel = 'two_66_33_top';
    $pane->type = 'block';
    $pane->subtype = 'commons_groups-commons_groups_create_group';
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
    $pane->uuid = '3db36521-fb53-58a4-c9e2-137a2dacee07';
    $display->content['new-3db36521-fb53-58a4-c9e2-137a2dacee07'] = $pane;
    $display->panels['two_66_33_top'][0] = 'new-3db36521-fb53-58a4-c9e2-137a2dacee07';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-bf6c6f1b-08a6-3874-7186-c955c763c092';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['groups_directory'] = $page;

  return $pages;

}
