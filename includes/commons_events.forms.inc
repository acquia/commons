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
  if (!registration_status('node', $form_state['event_node']->nid, TRUE)
    || !registration_has_room('node', $form_state['event_node']->nid)) {
    form_set_error('submit', t('The event you are registering for is unavailable.'));
    return FALSE;
  }
  else if (registration_is_registered($form_state['registration'], NULL, $user->uid)) {
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
  $registration->count = 1;
  if (registration_save($registration)) {
    drupal_set_message(t('Your registration was saved.'));
    commons_follow_node_follow_node($registration->entity_id, 'event', $user->uid);
  }
  else {
    drupal_set_message(t('There was an error saving your registration.'));
  }
}

/**
 * Form to cancel a registration for an event.
 */
function commons_events_cancel_event_form($form, &$form_state, $event) {
  $form_state['event'] = $event;
  $form['#attributes'] = array('class' => array('commons-events-form-float'));
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'commons_events') . '/css/commons_events.css',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
  );
  $form['submit']['#attributes']['class'][] = 'commons-events-button';
  $form['attending'] = array(
    '#theme_wrappers' => array('container'),
    '#attributes' => array(
      'class' => array('commons-event-status'),
    ),
    '#markup' => t('You are attending.'),
  );
  return $form;
}

/**
 * Event cancel attendance form submit handler.
 */
function commons_events_cancel_event_form_submit($form, $form_state) {
  global $user;
  $event = $form_state['event'];
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'registration')
    ->propertyCondition('user_uid', $user->uid)
    ->propertyCondition('entity_id', $event->nid)
    ->propertyCondition('entity_type', 'node');
  $result = $query->execute();
  if (isset($result['registration'])) {
    registration_delete_multiple(array_keys($result['registration']));
    drupal_set_message(t('Your registration has been cancelled.'));
  }
}
