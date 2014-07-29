<?php
/**
 * @file
 * Commons Events form declarations.
 */

 /**
 * Form builder for Attend call to action on events, as long as registration
 * is available onsite.
 */
function commons_events_attend_event_form($form, &$form_state, $event_node, $registration = NULL, $attendee_count = 0) {
  $form_state['event_node'] = $event_node;
  if (!registration_status('node', $event_node->nid, TRUE)) {
    return array();
  }
  if (!isset($registration)) {
    $registration_type = registration_get_entity_registration_type('node', $event_node);
    $registration = entity_get_controller('registration')->create(array(
      'entity_type' => 'node',
      'entity_id' => $event_node->nid,
      'type' => $registration_type,
    ));
  }
  $form_state['registration'] = $registration;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Attend'),
  );
  $form['count'] = array(
    '#type' => 'textfield',
    '#default_value' => '0',
    '#description' => t('+ Guests'),
    '#size' => 2,
    '#maxlength' => 2,
    '#required' => false,
  );
  $form['attending'] = array(
    '#theme_wrappers' => array('container'),
    '#attributes' => array(
      'class' => array('commons-event-status'),
    ),
    '#markup' => format_plural($attendee_count, '<span class="commons-event-count">1</span> attendee', '<span class="commons-event-count">@count</span> attendees'),
  );
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'commons_events') . '/css/commons_events.css',
  );
  $form['#attributes'] = array('class' => array('commons-events-form-float'));
  return $form;
}

/**
 * Validation handler for attending an event.
 * Checks to make sure that space is available for attending, and that it
 * didn't fill up after the page load.
 */
function commons_events_attend_event_form_validate($form, &$form_state) {
  global $user;
  if ($form_state['values']['count'] == '') {
    $form_state['values']['count'] = 0;
  }

  if (!is_numeric($form_state['values']['count'])) {
    form_set_error('count', t('Guest count must be a number.'));
    return FALSE;
  }
  // Include the registrant in the count.
  $form_state['values']['count']++;

  if (!registration_has_room('node', $form_state['event_node']->nid, $form_state['values']['count'])) {
    form_set_error('count', t('Insufficient spaces remaining.'));
  }
  if (!registration_status('node', $form_state['event_node']->nid, TRUE)
    || !registration_has_room('node', $form_state['event_node']->nid)) {
    form_set_error('submit', t('The event you are registering for is unavailable.'));
    return FALSE;
  }
  elseif (registration_is_registered($form_state['registration'], NULL, $user->uid)) {
    form_set_error('submit', t('You are already registered for this event.'));
    return FALSE;
  }
  return TRUE;
}

/**
 * Submission handler for attending an event.
 */
function commons_events_attend_event_form_submit($form, $form_state) {
  global $user;
  $registration = $form_state['registration'];
  $registration->user_uid = $user->uid;
  $registration->author_uid = $user->uid;
  $registration->state = NULL;
  $registration->count = $form_state['values']['count'];
  if (registration_save($registration)) {
    drupal_set_message(t('Your registration was saved.'));

    // Have the user automatically follow the event if Commons Follow (Node) is
    // enabled.
    if (module_exists('commons_follow_node')) {
      commons_follow_node_follow_node($registration->entity_id, 'event', $user->uid);
    }
  }
  else {
    drupal_set_message(t('There was an error saving your registration.'));
  }
}

/**
 * Form to cancel a registration for an event.
 */
function commons_events_cancel_event_form($form, &$form_state, $event, $registrations) {
  $form_state['event'] = $event;

  $form['#attributes'] = array('class' => array('commons-events-form-float'));
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'commons_events') . '/css/commons_events.css',
  );
  $form['registration'] = array(
    '#type' => 'value',
    '#value' => $registrations,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
  );
  $form['submit']['#attributes']['class'][] = 'commons-events-button';

  $attendee_count = 0;
  foreach ($registrations as $registration) {
    $attendee_count += registration_event_count('node', $event->nid, $registration->registration_id);
  }
  // Remove registrant from count.
  $attendee_count--;
  if ($attendee_count > 1) {
    // Single attending message.
    $markup = t('You are attending with @guests', array('@guests' => format_plural($attendee_count, '1 guest', '@count guests')));
  }
  else {
    $markup = t('You are attending.');
  }

  $form['attending'] = array(
    '#theme_wrappers' => array('container'),
    '#attributes' => array(
      'class' => array('commons-event-status'),
    ),
    '#markup' => $markup,
  );
  return $form;
}

/**
 * Event cancel attendance form submit handler.
 */
function commons_events_cancel_event_form_submit($form, $form_state) {
  $event = $form_state['event'];
  if (isset($form_state['values']['registration'])) {
    registration_delete_multiple(array_keys($form_state['values']['registration']));
    drupal_set_message(t('Your registration has been cancelled.'));
  }
}
