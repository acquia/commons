<?php
/**
 * @file
 * commons_user_profile_pages.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function commons_user_profile_pages_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view_panel_context';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -99;
  $handler->conf = array(
    'title' => 'User profile',
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
  $display->layout = 'three_3x33';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'three_33_top' => NULL,
      'three_33_first' => NULL,
      'three_33_second' => NULL,
      'three_33_third' => NULL,
      'three_33_bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '8b3ae903-c1dc-bcc4-71b3-a1bdd65c494d';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-cde013ca-1d6e-1e14-9171-8ccb1331008f';
    $pane->panel = 'three_33_first';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_activity_streams_user_activity-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:user_1',
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
    $pane->uuid = 'cde013ca-1d6e-1e14-9171-8ccb1331008f';
    $display->content['new-cde013ca-1d6e-1e14-9171-8ccb1331008f'] = $pane;
    $display->panels['three_33_first'][0] = 'new-cde013ca-1d6e-1e14-9171-8ccb1331008f';
    $pane = new stdClass();
    $pane->pid = 'new-f4cdb777-e56d-b974-4953-9b5f2dc9b594';
    $pane->panel = 'three_33_second';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_groups_user_groups-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:user_1',
      ),
      'override_title' => 1,
      'override_title_text' => 'Groups %user:field_name_first contributes to',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'f4cdb777-e56d-b974-4953-9b5f2dc9b594';
    $display->content['new-f4cdb777-e56d-b974-4953-9b5f2dc9b594'] = $pane;
    $display->panels['three_33_second'][0] = 'new-f4cdb777-e56d-b974-4953-9b5f2dc9b594';
    $pane = new stdClass();
    $pane->pid = 'new-2183ff7a-9286-81a4-39fb-25b7d4973c3b';
    $pane->panel = 'three_33_third';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_follow_user_following-panel_pane_1';
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
    $pane->uuid = '2183ff7a-9286-81a4-39fb-25b7d4973c3b';
    $display->content['new-2183ff7a-9286-81a4-39fb-25b7d4973c3b'] = $pane;
    $display->panels['three_33_third'][0] = 'new-2183ff7a-9286-81a4-39fb-25b7d4973c3b';
    $pane = new stdClass();
    $pane->pid = 'new-b0ac54f1-a0c8-a334-a53d-47581e23257d';
    $pane->panel = 'three_33_third';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_follow_user_followers-panel_pane_1';
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
    $pane->uuid = 'b0ac54f1-a0c8-a334-a53d-47581e23257d';
    $display->content['new-b0ac54f1-a0c8-a334-a53d-47581e23257d'] = $pane;
    $display->panels['three_33_third'][1] = 'new-b0ac54f1-a0c8-a334-a53d-47581e23257d';
    $pane = new stdClass();
    $pane->pid = 'new-d3fbb9db-cd0f-b8f4-1572-0e80c4a66c83';
    $pane->panel = 'three_33_top';
    $pane->type = 'user_picture';
    $pane->subtype = 'user_picture';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_entity_id:user_1',
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
    $pane->uuid = 'd3fbb9db-cd0f-b8f4-1572-0e80c4a66c83';
    $display->content['new-d3fbb9db-cd0f-b8f4-1572-0e80c4a66c83'] = $pane;
    $display->panels['three_33_top'][0] = 'new-d3fbb9db-cd0f-b8f4-1572-0e80c4a66c83';
    $pane = new stdClass();
    $pane->pid = 'new-918d67a4-4642-0364-a570-10f387184ae1';
    $pane->panel = 'three_33_top';
    $pane->type = 'entity_field';
    $pane->subtype = 'user:field_bio';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:user_1',
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
    $pane->uuid = '918d67a4-4642-0364-a570-10f387184ae1';
    $display->content['new-918d67a4-4642-0364-a570-10f387184ae1'] = $pane;
    $display->panels['three_33_top'][1] = 'new-918d67a4-4642-0364-a570-10f387184ae1';
    $pane = new stdClass();
    $pane->pid = 'new-b51e0fa8-7402-1104-3597-9bd7665546ae';
    $pane->panel = 'three_33_top';
    $pane->type = 'entity_field';
    $pane->subtype = 'user:field_facebook_url';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'link_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:user_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'b51e0fa8-7402-1104-3597-9bd7665546ae';
    $display->content['new-b51e0fa8-7402-1104-3597-9bd7665546ae'] = $pane;
    $display->panels['three_33_top'][2] = 'new-b51e0fa8-7402-1104-3597-9bd7665546ae';
    $pane = new stdClass();
    $pane->pid = 'new-20f47a2e-7cb8-a944-8944-3f15009131f7';
    $pane->panel = 'three_33_top';
    $pane->type = 'entity_field';
    $pane->subtype = 'user:field_linkedin_url';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'link_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:user_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '20f47a2e-7cb8-a944-8944-3f15009131f7';
    $display->content['new-20f47a2e-7cb8-a944-8944-3f15009131f7'] = $pane;
    $display->panels['three_33_top'][3] = 'new-20f47a2e-7cb8-a944-8944-3f15009131f7';
    $pane = new stdClass();
    $pane->pid = 'new-ac8d8150-6ff4-8654-c594-9c46cfe746d3';
    $pane->panel = 'three_33_top';
    $pane->type = 'entity_field';
    $pane->subtype = 'user:field_twitter_url';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'link_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:user_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'ac8d8150-6ff4-8654-c594-9c46cfe746d3';
    $display->content['new-ac8d8150-6ff4-8654-c594-9c46cfe746d3'] = $pane;
    $display->panels['three_33_top'][4] = 'new-ac8d8150-6ff4-8654-c594-9c46cfe746d3';
    $pane = new stdClass();
    $pane->pid = 'new-67c3df7b-1a3b-db24-f974-a3b27f8988d9';
    $pane->panel = 'three_33_top';
    $pane->type = 'token';
    $pane->subtype = 'user:flag-commons-follow-user-link';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'sanitize' => 1,
      'context' => 'argument_entity_id:user_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '67c3df7b-1a3b-db24-f974-a3b27f8988d9';
    $display->content['new-67c3df7b-1a3b-db24-f974-a3b27f8988d9'] = $pane;
    $display->panels['three_33_top'][5] = 'new-67c3df7b-1a3b-db24-f974-a3b27f8988d9';
    $pane = new stdClass();
    $pane->pid = 'new-38b23f27-878a-f264-dd90-e55305d0f70c';
    $pane->panel = 'three_33_top';
    $pane->type = 'entity_field';
    $pane->subtype = 'user:group_group';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'trusted_contact',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:user_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 6;
    $pane->locks = array();
    $pane->uuid = '38b23f27-878a-f264-dd90-e55305d0f70c';
    $display->content['new-38b23f27-878a-f264-dd90-e55305d0f70c'] = $pane;
    $display->panels['three_33_top'][6] = 'new-38b23f27-878a-f264-dd90-e55305d0f70c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_view_panel_context'] = $handler;

  return $export;
}
