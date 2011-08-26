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
      'display_type',
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
    activity_log_record_unpack($record);
    return $record;
  }
}
