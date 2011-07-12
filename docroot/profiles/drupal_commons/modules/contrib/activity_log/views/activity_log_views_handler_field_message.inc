<?php

/**
 * @file
 *   Displays a themed activity log message.
 */

class activity_log_views_handler_field_message extends views_handler_field {
  function construct() {
    parent::construct();
    $fields = array(
      'mid',
      'tid',
      'aids',
      'created',
      'last_updated',
      'stream_owner_id',
      'stream_owner_type',
      'viewer_id',
      'target_id',
      'target_type',
      'acting_uid',
      'cached',
    );
    foreach ($fields as $field) {
      $this->additional_fields[$field] = array('table' => 'activity_log_messages', 'field' => $field);
    }
    $fields = array(
      'tid',
      'rule',
      'action_label',
      'template',
      'group_template',
      'group_summary',
      'collapse_method',
      'pid',
      'eval_input',
      'resources',
      'cacheable',
    );
    foreach ($fields as $field) {
      $this->additional_fields[$field] = array('table' => 'activity_log_templates', 'field' => $field);
    }
  }
  function render($values) {
    return theme('activity_log_item', $this->activity_log_load($values));
  }
  function activity_log_load($values) {
    $record = new stdClass();
    foreach ($this->aliases as $name => $alias) {
      $record->$name = $values->$alias;
    }
    $record->eval_input = unserialize($record->eval_input);
    $record->resources = unserialize($record->resources);
    $record->aids = array_filter(explode(',', $record->aids));
    $record->events = array();
    $result = db_query("
      SELECT * FROM {activity_log_events} WHERE aid IN (". db_placeholders($record->aids) .")
    ", $record->aids);
    rules_include('rules');
    while ($event = db_fetch_object($result)) {
      $event->id_map = unserialize($event->id_map);
      $record->events[$event->aid] = $event;
    }
    return $record;
  }
}
