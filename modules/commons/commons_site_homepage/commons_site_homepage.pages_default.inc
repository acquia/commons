<?php
/**
 * @file
 * commons_site_homepage.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function commons_site_homepage_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'commons_home';
  $page->task = 'page';
  $page->admin_title = 'Home';
  $page->admin_description = 'Site home page for anonymous and authenticated users.';
  $page->path = 'home';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Home',
    'weight' => '-10',
    'name' => 'main-menu',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'weight' => 0,
      'name' => 'navigation',
    ),
  );
  $page->arguments = array();
  $page->conf = array();
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_commons_home_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'commons_home';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Home (authenticated)',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 2,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
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
  $display->title = 'What\'s going on?';
  $display->uuid = '84741210-79de-a174-5d6f-8ebfcb061f03';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-97c7ce09-3cb1-6b34-a940-8fda43e609cc';
    $pane->panel = 'two_66_33_first';
    $pane->type = 'commons_bw_group';
    $pane->subtype = 'commons_bw_group';
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
    $pane->uuid = '97c7ce09-3cb1-6b34-a940-8fda43e609cc';
    $display->content['new-97c7ce09-3cb1-6b34-a940-8fda43e609cc'] = $pane;
    $display->panels['two_66_33_first'][0] = 'new-97c7ce09-3cb1-6b34-a940-8fda43e609cc';
    $pane = new stdClass();
    $pane->pid = 'new-b20add8c-2daf-4684-45f3-212d60c7f31e';
    $pane->panel = 'two_66_33_second';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_activity_streams_activity-panel_pane_1';
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
    $pane->uuid = 'b20add8c-2daf-4684-45f3-212d60c7f31e';
    $display->content['new-b20add8c-2daf-4684-45f3-212d60c7f31e'] = $pane;
    $display->panels['two_66_33_second'][0] = 'new-b20add8c-2daf-4684-45f3-212d60c7f31e';
    $pane = new stdClass();
    $pane->pid = 'new-da301a84-b9a5-8664-cd4b-1e84d7dd9f42';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'da301a84-b9a5-8664-cd4b-1e84d7dd9f42';
    $display->content['new-da301a84-b9a5-8664-cd4b-1e84d7dd9f42'] = $pane;
    $display->panels['two_66_33_second'][1] = 'new-da301a84-b9a5-8664-cd4b-1e84d7dd9f42';
    $pane = new stdClass();
    $pane->pid = 'new-895dfc63-a30f-f734-3185-c40c407b4af0';
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
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '895dfc63-a30f-f734-3185-c40c407b4af0';
    $display->content['new-895dfc63-a30f-f734-3185-c40c407b4af0'] = $pane;
    $display->panels['two_66_33_second'][2] = 'new-895dfc63-a30f-f734-3185-c40c407b4af0';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_commons_home_panel_context_2';
  $handler->task = 'page';
  $handler->subtask = 'commons_home';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Home (anonymous)',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 1,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'three_3x33';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'two_66_33_top' => NULL,
      'two_66_33_first' => NULL,
      'two_66_33_second' => NULL,
      'two_66_33_bottom' => NULL,
      'three_33_top' => NULL,
      'three_33_first' => NULL,
      'three_33_second' => NULL,
      'three_33_third' => NULL,
      'three_33_bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'afa005f6-cf15-78e4-d53d-8885db3cde39';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-0ae8e5a2-44f6-8584-21f2-8be6e340e62f';
    $pane->panel = 'three_33_first';
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0ae8e5a2-44f6-8584-21f2-8be6e340e62f';
    $display->content['new-0ae8e5a2-44f6-8584-21f2-8be6e340e62f'] = $pane;
    $display->panels['three_33_first'][0] = 'new-0ae8e5a2-44f6-8584-21f2-8be6e340e62f';
    $pane = new stdClass();
    $pane->pid = 'new-800b2f8a-307f-0e14-4174-626a1c5c4cd9';
    $pane->panel = 'three_33_third';
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
    $pane->uuid = '800b2f8a-307f-0e14-4174-626a1c5c4cd9';
    $display->content['new-800b2f8a-307f-0e14-4174-626a1c5c4cd9'] = $pane;
    $display->panels['three_33_third'][0] = 'new-800b2f8a-307f-0e14-4174-626a1c5c4cd9';
    $pane = new stdClass();
    $pane->pid = 'new-58e71a00-2b87-ab64-31c5-4fdc9e99a2d4';
    $pane->panel = 'three_33_third';
    $pane->type = 'views_panes';
    $pane->subtype = 'commons_activity_streams_activity-panel_pane_1';
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
    $pane->uuid = '58e71a00-2b87-ab64-31c5-4fdc9e99a2d4';
    $display->content['new-58e71a00-2b87-ab64-31c5-4fdc9e99a2d4'] = $pane;
    $display->panels['three_33_third'][1] = 'new-58e71a00-2b87-ab64-31c5-4fdc9e99a2d4';
    $pane = new stdClass();
    $pane->pid = 'new-7d40d7ca-0ea5-9a54-4d1f-8b6240e72bf0';
    $pane->panel = 'three_33_top';
    $pane->type = 'block';
    $pane->subtype = 'commons_site_homepage-commons_site_homepage';
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
    $pane->uuid = '7d40d7ca-0ea5-9a54-4d1f-8b6240e72bf0';
    $display->content['new-7d40d7ca-0ea5-9a54-4d1f-8b6240e72bf0'] = $pane;
    $display->panels['three_33_top'][0] = 'new-7d40d7ca-0ea5-9a54-4d1f-8b6240e72bf0';
    $pane = new stdClass();
    $pane->pid = 'new-2ab570f0-8498-44f4-e9d0-9977e3d8d4df';
    $pane->panel = 'three_33_top';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Anonymous homepage welcome text',
      'title' => 'Welcome to our community',
      'body' => 'Share your thoughts, find answers to your questions.',
      'format' => 'filtered_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '2ab570f0-8498-44f4-e9d0-9977e3d8d4df';
    $display->content['new-2ab570f0-8498-44f4-e9d0-9977e3d8d4df'] = $pane;
    $display->panels['three_33_top'][1] = 'new-2ab570f0-8498-44f4-e9d0-9977e3d8d4df';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['commons_home'] = $page;

  return $pages;

}
