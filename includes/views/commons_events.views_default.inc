<?php
/**
 * @file
 * Commons Events default views.
 */

/**
 * Implements hook_views_default_views().
 */
function commons_events_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'commons_events_event_attendee_list';
  $view->description = 'List attendees for a given event.';
  $view->tag = 'commons_events';
  $view->base_table = 'registration';
  $view->human_name = 'Commons Events - Event Attendee List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Attendees';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '12';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Registration: User user_uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'registration';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  $handler->display->display_options['relationships']['user']['required'] = TRUE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'user';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'user';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['empty'] = '<img src="/profiles/commons/modules/contrib/commons_events/profile_empty.png" height="60" width="60" /><br />[name]';
  $handler->display->display_options['fields']['picture']['hide_alter_empty'] = FALSE;
  /* Contextual filter: Registration: Entity_type */
  $handler->display->display_options['arguments']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['arguments']['entity_type']['table'] = 'registration';
  $handler->display->display_options['arguments']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['arguments']['entity_type']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['entity_type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['entity_type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['entity_type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['entity_type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['entity_type']['limit'] = '0';
  /* Contextual filter: Registration: Entity_id */
  $handler->display->display_options['arguments']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['arguments']['entity_id']['table'] = 'registration';
  $handler->display->display_options['arguments']['entity_id']['field'] = 'entity_id';
  $handler->display->display_options['arguments']['entity_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['entity_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['entity_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['entity_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['entity_id']['summary_options']['items_per_page'] = '25';

  /* Display: Full Attendee List Block */
  $handler = $view->new_display('block', 'Full Attendee List Block', 'commons_events_full_attendee_list');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';

  $views['commons_events_event_attendee_list'] = $view;

  return $views;
}
