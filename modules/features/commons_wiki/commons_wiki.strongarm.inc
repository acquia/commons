<?php

/**
 * Implementation of hook_strongarm().
 */
function commons_wiki_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_wiki';
  $strongarm->value = 0;

  $export['comment_anonymous_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_wiki';
  $strongarm->value = '3';

  $export['comment_controls_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_wiki';
  $strongarm->value = '4';

  $export['comment_default_mode_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_wiki';
  $strongarm->value = '2';

  $export['comment_default_order_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_wiki';
  $strongarm->value = '50';

  $export['comment_default_per_page_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_wiki';
  $strongarm->value = '0';

  $export['comment_form_location_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_wiki';
  $strongarm->value = '0';

  $export['comment_preview_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_wiki';
  $strongarm->value = '1';

  $export['comment_subject_field_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_wiki';
  $strongarm->value = '2';

  $export['comment_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_wiki';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-3',
    'revision_information' => '3',
    'author' => '4',
    'options' => '5',
    'comment_settings' => '7',
    'menu' => '2',
    'taxonomy' => '-4',
    'path' => '6',
    'flag' => '1',
    'og_nodeapi' => '0',
  );

  $export['content_extra_weights_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_camelcase';
  $strongarm->value = 0;

  $export['freelinking_camelcase'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_nodetype';
  $strongarm->value = 'wiki';

  $export['freelinking_nodetype'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_notfound';
  $strongarm->value = 'no access search';

  $export['freelinking_notfound'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_onceonly';
  $strongarm->value = 0;

  $export['freelinking_onceonly'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_restriction';
  $strongarm->value = array(
    'wiki' => 'wiki',
  );

  $export['freelinking_restriction'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_wiki';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
    2 => 'revision',
  );

  $export['node_options_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_wiki';
  $strongarm->value = 'group_post_wiki';

  $export['og_content_type_usage_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'remove_markup_default_wiki';
  $strongarm->value = 1;

  $export['remove_markup_default_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_404_type';
  $strongarm->value = array(
    'Link to creation' => 'Link to creation',
    'Link to search' => 0,
    'Creation form' => 0,
  );

  $export['wikitools_404_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_disallowed_characters';
  $strongarm->value = '[]{}|';

  $export['wikitools_disallowed_characters'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_main_page_title';
  $strongarm->value = 'Main Page';

  $export['wikitools_main_page_title'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_node_types';
  $strongarm->value = array(
    'wiki' => 'wiki',
    'blog' => 0,
    'discussion' => 0,
    'document' => 0,
    'event' => 0,
    'group' => 0,
    'notice' => 0,
    'page' => 0,
    'poll' => 0,
  );

  $export['wikitools_node_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_options';
  $strongarm->value = array(
    'node creation' => 'node creation',
    'node search' => 'node search',
    'unique titles' => 'unique titles',
    'underscore as space' => 'underscore as space',
    'auto redirect' => 0,
    'move protection' => 0,
    'dash as space' => 0,
  );

  $export['wikitools_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_path';
  $strongarm->value = 'wiki';

  $export['wikitools_path'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_subpages';
  $strongarm->value = 'edit, delete, view, revisions';

  $export['wikitools_subpages'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_subpages_handling';
  $strongarm->value = 'disabled';

  $export['wikitools_subpages_handling'] = $strongarm;
  return $export;
}
