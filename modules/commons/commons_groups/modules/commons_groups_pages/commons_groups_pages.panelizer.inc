<?php
/**
 * @file
 * commons_groups_pages.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function commons_groups_pages_panelizer_defaults() {
  $export = array();

  $group_bundles = og_get_all_group_bundle();
  if (!empty($group_bundles['node'])) {
    foreach ($group_bundles['node'] as $bundle => $name) {
      $panelizer = new stdClass();
      $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
      $panelizer->api_version = 1;
      $panelizer->name = "node:$bundle:default";
      $panelizer->title = 'Default';
      $panelizer->panelizer_type = 'node';
      $panelizer->panelizer_key = $bundle;
      $panelizer->no_blocks = FALSE;
      $panelizer->css_id = '';
      $panelizer->css = '';
      $panelizer->pipeline = 'ipe';
      $panelizer->contexts = array();
      $panelizer->relationships = array();
      $panelizer->access = array();
      $panelizer->view_mode = 'page_manager';
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
      $display->title = '%node:title';
      $display->uuid = '819deb2a-c56c-2214-558d-c52460a89778';
      $display->content = array();
      $display->panels = array();
      $pane = new stdClass();
      $pane->pid = 'new-10f12c5b-679e-d294-b1bd-9aac845800f5';
      $pane->panel = 'two_66_33_first';
      $pane->type = 'node_content';
      $pane->subtype = 'node_content';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'links' => 1,
        'no_extras' => 0,
        'override_title' => 1,
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
      $pane->uuid = '10f12c5b-679e-d294-b1bd-9aac845800f5';
      $display->content['new-10f12c5b-679e-d294-b1bd-9aac845800f5'] = $pane;
      $display->panels['two_66_33_first'][0] = 'new-10f12c5b-679e-d294-b1bd-9aac845800f5';
      $pane = new stdClass();
      $pane->pid = 'new-80b62348-7cee-e304-5d65-0ce1b6bbb216';
      $pane->panel = 'two_66_33_first';
      $pane->type = 'commons_bw_group';
      $pane->subtype = 'commons_bw_group';
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
      $pane->uuid = '80b62348-7cee-e304-5d65-0ce1b6bbb216';
      $display->content['new-80b62348-7cee-e304-5d65-0ce1b6bbb216'] = $pane;
      $display->panels['two_66_33_first'][1] = 'new-80b62348-7cee-e304-5d65-0ce1b6bbb216';
      $pane = new stdClass();
      $pane->pid = 'new-13120946-03a1-bfc4-2d74-f39dd758ebce';
      $pane->panel = 'two_66_33_second';
      $pane->type = 'views_panes';
      $pane->subtype = 'commons_events_upcoming-panel_pane_1';
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
      $pane->uuid = '13120946-03a1-bfc4-2d74-f39dd758ebce';
      $display->content['new-13120946-03a1-bfc4-2d74-f39dd758ebce'] = $pane;
      $display->panels['two_66_33_second'][0] = 'new-13120946-03a1-bfc4-2d74-f39dd758ebce';
      $pane = new stdClass();
      $pane->pid = 'new-a7009535-0e2a-2c94-edd2-4ecc953c4ca2';
      $pane->panel = 'two_66_33_second';
      $pane->type = 'views_panes';
      $pane->subtype = 'activity_group-panel_pane_1';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'items_per_page' => '4',
        'arguments' => array(
          'gid' => '%node:nid',
        ),
      );
      $pane->cache = array();
      $pane->style = array(
        'settings' => NULL,
      );
      $pane->css = array();
      $pane->extras = array();
      $pane->position = 1;
      $pane->locks = array();
      $pane->uuid = 'a7009535-0e2a-2c94-edd2-4ecc953c4ca2';
      $display->content['new-a7009535-0e2a-2c94-edd2-4ecc953c4ca2'] = $pane;
      $display->panels['two_66_33_second'][1] = 'new-a7009535-0e2a-2c94-edd2-4ecc953c4ca2';

      if (module_exists('commons_radioactivity_groups')) {
        $pane = new stdClass();
        $pane->pid = 'new-ba735f2b-4734-7724-098d-1925c6a4bb47';
        $pane->panel = 'two_66_33_second';
        $pane->type = 'views_panes';
        $pane->subtype = 'commons_radioactivity_groups_active_in_group-panel_pane_1';
        $pane->shown = TRUE;
        $pane->access = array();
        $pane->configuration = array(
          'arguments' => array(
            'gid' => '%node:nid',
          ),
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
        $pane->position = 2;
        $pane->locks = array();
        $pane->uuid = 'ba735f2b-4734-7724-098d-1925c6a4bb47';
        $display->content['new-ba735f2b-4734-7724-098d-1925c6a4bb47'] = $pane;
        $display->panels['two_66_33_second'][2] = 'new-ba735f2b-4734-7724-098d-1925c6a4bb47';
      }

      $pane = new stdClass();
      $pane->pid = 'new-52796f83-93dd-2cf4-41aa-33520dc31e5f';
      $pane->panel = 'two_66_33_second';
      $pane->type = 'views_panes';
      $pane->subtype = 'commons_contributors_group-panel_pane_2';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'context' => array(
          0 => 'panelizer',
        ),
      );
      $pane->cache = array(
        'method' => 'simple',
        'settings' => array(
          'lifetime' => '15',
          'granularity' => 'context',
        ),
      );
      $pane->style = array(
        'settings' => NULL,
      );
      $pane->css = array();
      $pane->extras = array();
      $pane->position = 3;
      $pane->locks = array();
      $pane->uuid = '52796f83-93dd-2cf4-41aa-33520dc31e5f';
      $display->content['new-52796f83-93dd-2cf4-41aa-33520dc31e5f'] = $pane;
      $display->panels['two_66_33_second'][3] = 'new-52796f83-93dd-2cf4-41aa-33520dc31e5f';
      $display->hide_title = PANELS_TITLE_FIXED;
      $display->title_pane = '0';
      $panelizer->display = $display;
      $export["node:$bundle:default"] = $panelizer;

      $panelizer = new stdClass();
      $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
      $panelizer->api_version = 1;
      $panelizer->name = "node:$bundle:default:teaser";
      $panelizer->title = 'Default';
      $panelizer->panelizer_type = 'node';
      $panelizer->panelizer_key = "$bundle";
      $panelizer->no_blocks = FALSE;
      $panelizer->css_id = '';
      $panelizer->css = '';
      $panelizer->pipeline = 'standard';
      $panelizer->contexts = array();
      $panelizer->relationships = array();
      $panelizer->access = array();
      $panelizer->view_mode = 'teaser';
      $panelizer->css_class = '';
      $panelizer->title_element = 'H2';
      $panelizer->link_to_entity = TRUE;
      $panelizer->extra = array();
      $display = new panels_display();
      $display->layout = 'one';
      $display->layout_settings = array();
      $display->panel_settings = array(
        'style_settings' => array(
          'default' => NULL,
          'one_main' => NULL,
        ),
      );
      $display->cache = array();
      $display->title = '%node:title';
      $display->uuid = '2880dc3a-9be6-dc34-a563-b9748d152f92';
      $display->content = array();
      $display->panels = array();
      $pane = new stdClass();
      $pane->pid = 'new-026f9d2d-fd0e-d794-1971-47eb628a7f6e';
      $pane->panel = 'one_main';
      $pane->type = 'entity_field';
      $pane->subtype = 'node:group_group';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'label' => 'hidden',
        'formatter' => 'commons_groups_group_subscribe',
        'delta_limit' => 0,
        'delta_offset' => '0',
        'delta_reversed' => FALSE,
        'formatter_settings' => array(),
        'context' => 'panelizer',
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
      $pane->uuid = '026f9d2d-fd0e-d794-1971-47eb628a7f6e';
      $display->content['new-026f9d2d-fd0e-d794-1971-47eb628a7f6e'] = $pane;
      $display->panels['one_main'][0] = 'new-026f9d2d-fd0e-d794-1971-47eb628a7f6e';
      $pane = new stdClass();
      $pane->pid = 'new-13859111-e3fa-5e54-a93c-57f09d719e38';
      $pane->panel = 'one_main';
      $pane->type = 'token';
      $pane->subtype = 'node:commons-groups-group-contributors-count-topics';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'sanitize' => 0,
        'context' => 'panelizer',
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
      $pane->uuid = '13859111-e3fa-5e54-a93c-57f09d719e38';
      $display->content['new-13859111-e3fa-5e54-a93c-57f09d719e38'] = $pane;
      $display->panels['one_main'][1] = 'new-13859111-e3fa-5e54-a93c-57f09d719e38';
      $pane = new stdClass();
      $pane->pid = 'new-f7a3719c-d7be-f024-ed91-c8c0df943df4';
      $pane->panel = 'one_main';
      $pane->type = 'token';
      $pane->subtype = 'node:flag-commons-follow-group-link';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'sanitize' => 0,
        'context' => 'panelizer',
        'override_title' => 1,
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
      $pane->uuid = 'f7a3719c-d7be-f024-ed91-c8c0df943df4';
      $display->content['new-f7a3719c-d7be-f024-ed91-c8c0df943df4'] = $pane;
      $display->panels['one_main'][2] = 'new-f7a3719c-d7be-f024-ed91-c8c0df943df4';
      $pane = new stdClass();
      $pane->pid = 'new-926a99b3-8e75-aa14-2542-16f2ab9e70b3';
      $pane->panel = 'one_main';
      $pane->type = 'entity_field';
      $pane->subtype = 'node:field_group_logo';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'label' => 'hidden',
        'formatter' => 'image',
        'delta_limit' => 0,
        'delta_offset' => '0',
        'delta_reversed' => FALSE,
        'formatter_settings' => array(
          'image_style' => '50x50',
          'image_link' => 'content',
        ),
        'context' => 'panelizer',
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
      $pane->uuid = '926a99b3-8e75-aa14-2542-16f2ab9e70b3';
      $display->content['new-926a99b3-8e75-aa14-2542-16f2ab9e70b3'] = $pane;
      $display->panels['one_main'][3] = 'new-926a99b3-8e75-aa14-2542-16f2ab9e70b3';
      $pane = new stdClass();
      $pane->pid = 'new-c22911c5-3c21-75b4-c5f3-80efb733956b';
      $pane->panel = 'one_main';
      $pane->type = 'entity_field';
      $pane->subtype = 'node:body';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'label' => 'hidden',
        'formatter' => 'text_summary_or_trimmed',
        'delta_limit' => 0,
        'delta_offset' => '0',
        'delta_reversed' => FALSE,
        'formatter_settings' => array(
          'trim_length' => '600',
        ),
        'context' => 'panelizer',
        'override_title' => 0,
        'override_title_text' => 'Por que no se ve?',
      );
      $pane->cache = array();
      $pane->style = array(
        'settings' => NULL,
      );
      $pane->css = array();
      $pane->extras = array();
      $pane->position = 4;
      $pane->locks = array();
      $pane->uuid = 'c22911c5-3c21-75b4-c5f3-80efb733956b';
      $display->content['new-c22911c5-3c21-75b4-c5f3-80efb733956b'] = $pane;
      $display->panels['one_main'][4] = 'new-c22911c5-3c21-75b4-c5f3-80efb733956b';
      $pane = new stdClass();
      $pane->pid = 'new-cb706c02-36e8-a414-c9f5-c34bf15861ca';
      $pane->panel = 'one_main';
      $pane->type = 'views';
      $pane->subtype = 'commons_groups_recent_content';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'override_pager_settings' => 0,
        'use_pager' => 0,
        'nodes_per_page' => '5',
        'pager_id' => '0',
        'offset' => '0',
        'more_link' => 0,
        'feed_icons' => 0,
        'panel_args' => 0,
        'link_to_view' => 0,
        'args' => '',
        'url' => '',
        'display' => 'block',
        'context' => array(
          0 => 'panelizer.nid',
        ),
        'override_title' => 1,
        'override_title_text' => 'Recent content',
      );
      $pane->cache = array();
      $pane->style = array(
        'settings' => NULL,
      );
      $pane->css = array();
      $pane->extras = array();
      $pane->position = 5;
      $pane->locks = array();
      $pane->uuid = 'cb706c02-36e8-a414-c9f5-c34bf15861ca';
      $display->content['new-cb706c02-36e8-a414-c9f5-c34bf15861ca'] = $pane;
      $display->panels['one_main'][5] = 'new-cb706c02-36e8-a414-c9f5-c34bf15861ca';
      $pane = new stdClass();
      $pane->pid = 'new-6c3207ac-19f3-8184-11ba-e3aee789a9c8';
      $pane->panel = 'one_main';
      $pane->type = 'views_panes';
      $pane->subtype = 'commons_contributors_group-panel_pane_1';
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
      $pane->position = 6;
      $pane->locks = array();
      $pane->uuid = '6c3207ac-19f3-8184-11ba-e3aee789a9c8';
      $display->content['new-6c3207ac-19f3-8184-11ba-e3aee789a9c8'] = $pane;
      $display->panels['one_main'][6] = 'new-6c3207ac-19f3-8184-11ba-e3aee789a9c8';
      $display->hide_title = PANELS_TITLE_FIXED;
      $display->title_pane = '0';
      $panelizer->display = $display;
      $export["node:$bundle:default:teaser"] = $panelizer;
    }
  }


  return $export;
}
