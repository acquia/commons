<?php
/**
 * @file
 * commons_wikis_pages.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function commons_wikis_pages_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:wiki:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'wiki';
  $panelizer->no_blocks = FALSE;
  $panelizer->css_id = '';
  $panelizer->css = '';
  $panelizer->pipeline = 'ipe';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $panelizer->access = '';
  $panelizer->view_mode = '';
  $panelizer->css_class = '';
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = '';
  $display = new panels_display();
  $display->layout = 'two_66_33';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'two_66_33_top' => NULL,
      'two_66_33_first' => NULL,
      'two_66_33_second' => NULL,
      'two_66_33_bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = 'bc4d1b4e-c149-dbf4-c1d9-20655cf95f31';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8006578b-1091-e734-6d38-3c6a8052ccbd';
    $pane->panel = 'two_66_33_first';
    $pane->type = 'node_content';
    $pane->subtype = 'node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'links' => 1,
      'no_extras' => 0,
      'override_title' => 0,
      'override_title_text' => '',
      'identifier' => '',
      'link' => 0,
      'leave_node_title' => 0,
      'build_mode' => 'full',
      'context' => 'panelizer',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8006578b-1091-e734-6d38-3c6a8052ccbd';
    $display->content['new-8006578b-1091-e734-6d38-3c6a8052ccbd'] = $pane;
    $display->panels['two_66_33_first'][0] = 'new-8006578b-1091-e734-6d38-3c6a8052ccbd';
    $pane = new stdClass();
    $pane->pid = 'new-bab0455d-e26a-6974-bd77-1e04bb5aece9';
    $pane->panel = 'two_66_33_second';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_wikis_contributor_list-commons_wikis_contributor_pane';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'panelizer',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'bab0455d-e26a-6974-bd77-1e04bb5aece9';
    $display->content['new-bab0455d-e26a-6974-bd77-1e04bb5aece9'] = $pane;
    $display->panels['two_66_33_second'][0] = 'new-bab0455d-e26a-6974-bd77-1e04bb5aece9';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:wiki:default'] = $panelizer;

  return $export;
}
