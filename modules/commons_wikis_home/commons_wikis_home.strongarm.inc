<?php
/**
 * @file
 * commons_wikis_home.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commons_wikis_home_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_wiki';
  $strongarm->value = array(
    'status' => 1,
    'default' => 1,
    'choice' => 0,
  );
  $export['panelizer_defaults_node_wiki'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:wiki_allowed_layouts';
  $strongarm->value = 'O:22:"panels_allowed_layouts":4:{s:9:"allow_new";b:1;s:11:"module_name";s:19:"panelizer_node:wiki";s:23:"allowed_layout_settings";a:23:{s:8:"flexible";b:0;s:14:"twocol_stacked";b:0;s:13:"twocol_bricks";b:0;s:6:"twocol";b:0;s:25:"threecol_33_34_33_stacked";b:0;s:17:"threecol_33_34_33";b:0;s:25:"threecol_25_50_25_stacked";b:0;s:17:"threecol_25_50_25";b:0;s:6:"onecol";b:0;s:9:"two_brick";b:0;s:9:"two_66_33";b:1;s:6:"two_50";b:0;s:9:"two_33_66";b:0;s:17:"three_inset_right";b:0;s:16:"three_inset_left";b:0;s:14:"three_50_25_25";b:0;s:10:"three_3x33";b:0;s:14:"three_25_50_25";b:0;s:14:"three_25_25_50";b:0;s:8:"six_6x16";b:0;s:3:"one";b:0;s:9:"four_4x25";b:0;s:9:"five_5x20";b:0;}s:10:"form_state";N;}';
  $export['panelizer_node:wiki_allowed_layouts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:wiki_default';
  $strongarm->value = array(
    'token' => 'token',
    'entity_form_field' => 'entity_form_field',
    'entity_field' => 'entity_field',
    'entity_field_extra' => 'entity_field_extra',
    'custom' => 'custom',
    'block' => 'block',
    'entity_view' => 'entity_view',
    'views' => 'views',
    'views_panes' => 'views_panes',
    'other' => 'other',
  );
  $export['panelizer_node:wiki_default'] = $strongarm;

  return $export;
}
