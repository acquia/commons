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

/**
 * Theme the event attendees list.
 */
function theme_commons_events_event_attendees($variables = array()) {
  $event_nid = $variables['event_nid'];
  $attendeesQuery = new EntityFieldQuery();
  $attendeesQuery->entityCondition('entity_type', 'registration')
    ->propertyCondition('entity_id', $event_nid)
    ->propertyCondition('entity_type', 'node')
    ->range(0, 12);
  $attendees = $attendeesQuery->execute();
  if (isset($attendees['registration'])) {
    $tableData = array(
      'attributes' => array(),
      'caption' => NULL,
      'colgroups' => array(),
      'sticky' => FALSE,
      'empty' => NULL,
      'header' => array(
        0 => array(
          'colspan' => 4,
          'data' => t('Attendees'),
        ),
      ),
      'rows' => array(),
    );
    $rows = &$tableData['rows'];
    $registrations = entity_load('registration', array_keys($attendees['registration']));
    $row = 0;
    $count = 1;
    foreach ($registrations as $registration_id => $registration) {
      $user_uri = entity_uri('user', $registration->user);
      $rows[$row][] = array(
        'data' => l($registration->user->name, $user_uri['path']),
        'width' => '25%',
      );
      $count++;
      if ($count >= 4) {
        $row++;
        $count = 1;
      }
    }
    $rows[] = array(
      0 => array(
        'data' => l('See all attendees', 'node/' . $event_nid . '/attendees'),
        'colspan' => 4,
        'class' => array('all-attendees-link'),
      ),
    );
    return theme_table($tableData);
  }
  else {
    return "";
  }
}
