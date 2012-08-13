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
  $registration_type = registration_get_entity_registration_type('node', $event);
  $registration = entity_get_controller('registration')->create(array(
    'entity_type' => 'node',
    'entity_id' => $event->nid,
    'type' => $registration_type,
  ));
  $registration->user_uid = $user->uid;
  if (!registration_is_registered($registration, NULL, $user->uid)) {
    if (!function_exists('commons_events_attend_event_form')) {
      module_load_include('inc', 'commons_events', 'includes/commons_events.forms');
    }
    return drupal_get_form('commons_events_attend_event_form', $event, $registration);
  }
  $content['attending'] = array(
    '#markup' => '<p class="attendee">' . t('You are attending.') . '</p>',
  );
  return $content;
}