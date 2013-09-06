<?php
/**
 * @file
 * commons_search_core.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function commons_search_core_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'search_search_facetapi_panel_context';
  $handler->task = 'search';
  $handler->subtask = 'search_facetapi';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Non-empty keywords, two column',
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
          'name' => 'string_length',
          'settings' => array(
            'operator' => '>',
            'length' => '0',
          ),
          'context' => 'argument_string_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
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
  $display->uuid = '2d31d4ab-5756-44a4-f984-8107b8587b40';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-4be3b380-7f67-ecf4-6974-607450056b42';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-yz9XmKQdPPifJdPJudYeRDV3PpGykc25';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Topics',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '4be3b380-7f67-ecf4-6974-607450056b42';
    $display->content['new-4be3b380-7f67-ecf4-6974-607450056b42'] = $pane;
    $display->panels['two_33_66_first'][0] = 'new-4be3b380-7f67-ecf4-6974-607450056b42';
    $pane = new stdClass();
    $pane->pid = 'new-19883d03-0e72-1f84-4d13-5daf49510352';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-NjamMRlUSiv6J1uYtpZ6KmDlsOuSofFX';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Type',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '19883d03-0e72-1f84-4d13-5daf49510352';
    $display->content['new-19883d03-0e72-1f84-4d13-5daf49510352'] = $pane;
    $display->panels['two_33_66_first'][1] = 'new-19883d03-0e72-1f84-4d13-5daf49510352';
    $pane = new stdClass();
    $pane->pid = 'new-d8cfd787-a04d-ef94-dda0-a486cf0e46be';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-lyyyTQZmDqHX6b30Dx4mzfY6gEOR5Y0j';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Author',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'd8cfd787-a04d-ef94-dda0-a486cf0e46be';
    $display->content['new-d8cfd787-a04d-ef94-dda0-a486cf0e46be'] = $pane;
    $display->panels['two_33_66_first'][2] = 'new-d8cfd787-a04d-ef94-dda0-a486cf0e46be';
    $pane = new stdClass();
    $pane->pid = 'new-3c939ace-59f2-5ea4-5da0-d1450d651449';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-gw7MYX93nFUXP6kzts1Eay6QpCVVSaOt';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Date created',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '3c939ace-59f2-5ea4-5da0-d1450d651449';
    $display->content['new-3c939ace-59f2-5ea4-5da0-d1450d651449'] = $pane;
    $display->panels['two_33_66_first'][3] = 'new-3c939ace-59f2-5ea4-5da0-d1450d651449';
    $pane = new stdClass();
    $pane->pid = 'new-95278c06-53e1-a984-4139-71b99c4d3ddf';
    $pane->panel = 'two_33_66_first';
    $pane->type = 'block';
    $pane->subtype = 'facetapi-BFZ195FyIkWBzXNTaq3jevkbxSWXJpMb';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Date changed',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '95278c06-53e1-a984-4139-71b99c4d3ddf';
    $display->content['new-95278c06-53e1-a984-4139-71b99c4d3ddf'] = $pane;
    $display->panels['two_33_66_first'][4] = 'new-95278c06-53e1-a984-4139-71b99c4d3ddf';
    $pane = new stdClass();
    $pane->pid = 'new-2ed6ed31-b23a-50d4-dd1c-dd2eae53cedb';
    $pane->panel = 'two_33_66_second';
    $pane->type = 'search_result';
    $pane->subtype = 'search_result';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'search_facetapi',
      'log' => 0,
      'override_empty' => 0,
      'empty_title' => '',
      'empty' => '',
      'empty_format' => 'plain_text',
      'override_no_key' => 0,
      'no_key_title' => '',
      'no_key' => '',
      'no_key_format' => 'plain_text',
      'context' => 'argument_string_1',
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
    $pane->uuid = '2ed6ed31-b23a-50d4-dd1c-dd2eae53cedb';
    $display->content['new-2ed6ed31-b23a-50d4-dd1c-dd2eae53cedb'] = $pane;
    $display->panels['two_33_66_second'][0] = 'new-2ed6ed31-b23a-50d4-dd1c-dd2eae53cedb';
    $pane = new stdClass();
    $pane->pid = 'new-74dd20d4-0d10-dea4-019a-808cfe544eac';
    $pane->panel = 'two_33_66_top';
    $pane->type = 'search_form';
    $pane->subtype = 'search_form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'search_facetapi',
      'form' => 'simple',
      'path_type' => 'default',
      'path' => '',
      'override_prompt' => 0,
      'prompt' => '',
      'context' => 'argument_string_1',
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
    $pane->uuid = '74dd20d4-0d10-dea4-019a-808cfe544eac';
    $display->content['new-74dd20d4-0d10-dea4-019a-808cfe544eac'] = $pane;
    $display->panels['two_33_66_top'][0] = 'new-74dd20d4-0d10-dea4-019a-808cfe544eac';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-2ed6ed31-b23a-50d4-dd1c-dd2eae53cedb';
  $handler->conf['display'] = $display;
  $export['search_search_facetapi_panel_context'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'search_search_facetapi_panel_context_2';
  $handler->task = 'search';
  $handler->subtask = 'search_facetapi';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Empty keywords, single column',
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
          'name' => 'string_length',
          'settings' => array(
            'operator' => '=',
            'length' => '0',
          ),
          'context' => 'argument_string_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'one';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'two_33_66_top' => NULL,
      'two_33_66_first' => NULL,
      'two_33_66_second' => NULL,
      'two_33_66_bottom' => NULL,
      'one_main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '34b80be5-404f-b7d4-b167-a3be8362179a';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-c690489f-a85f-a4a4-050c-f542d996de37';
    $pane->panel = 'one_main';
    $pane->type = 'search_form';
    $pane->subtype = 'search_form';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'type' => 'search_facetapi',
      'form' => 'simple',
      'path_type' => 'default',
      'path' => '',
      'override_prompt' => 0,
      'prompt' => '',
      'context' => 'argument_string_1',
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
    $pane->uuid = 'c690489f-a85f-a4a4-050c-f542d996de37';
    $display->content['new-c690489f-a85f-a4a4-050c-f542d996de37'] = $pane;
    $display->panels['one_main'][0] = 'new-c690489f-a85f-a4a4-050c-f542d996de37';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['search_search_facetapi_panel_context_2'] = $handler;

  return $export;
}
