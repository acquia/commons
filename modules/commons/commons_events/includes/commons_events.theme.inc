<?php
/**
 * @file
 * Commons Events theme functions.
 */

/**
 * Theme callback to display that a user is attending an event.
 */
function theme_commons_events_attending_event($variables = array()) {
  global $user;
  $event = $variables['event'];
  if (!$event->nid) {
    return '';
  }

  $attendee_count = isset($variables['attendee_count']) ? $variables['attendee_count'] : 0;

  $registration_type = registration_get_entity_registration_type('node', $event);
  $registration = entity_get_controller('registration')->create(array(
    'entity_type' => 'node',
    'entity_id' => $event->nid,
    'type' => $registration_type,
    'author_uid' => $user->uid,
  ));

  if (!function_exists('commons_events_attend_event_form')
    || !function_exists('commons_events_cancel_event_form')) {
    module_load_include('inc', 'commons_events', 'includes/commons_events.forms');
  }
  if (!registration_is_registered($registration, NULL, $user->uid)
    && registration_access('create', $registration, $user, $registration->type)
    && registration_status('node', $event->nid, TRUE)) {
    return drupal_get_form('commons_events_attend_event_form_' . $event->nid, $event, $registration, $attendee_count);
  }
  elseif (registration_is_registered($registration, NULL, $user->uid) &&
    registration_access('delete', $registration, $user, $registration->type)) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'registration')
      ->propertyCondition('user_uid', $user->uid)
      ->propertyCondition('entity_id', $event->nid)
      ->propertyCondition('entity_type', 'node');
    $result = $query->execute();

    return drupal_get_form('commons_events_cancel_event_form_' . $event->nid, $event, $result['registration']);
  }
  return "";
}

/**
 * Theme the event attendees list.
 */
function theme_commons_events_event_attendees($variables = array()) {
  $title = '<p class="commons-events-attendees-title">' . t('Attendees') . '</p>';
  $event_nid = $variables['event_nid'];
  if (!isset($variables['display'])
    || $variables['display'] != 'full') {
    return $title . views_embed_view('commons_events_event_attendee_list', 'default', $event_nid)
      . '<p class="commons-events-all-attendees"><a href="/node/' . $event_nid . '/attendees">'
      . t('See all attendees') . '</a></p>';
  }
  return $title . views_embed_view(
    'commons_events_event_attendee_list',
    'commons_events_full_attendee_list',
    $event_nid);
}
