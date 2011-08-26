<?php
// $Id: date_tools.event.inc,v 1.1.2.1 2010/03/08 23:39:42 karens Exp $

/**
 *  Event import form.
 */
function date_tools_copy_import_event_form($form_state) {
  // We can do an import if there are event fields available whether or not the event module is enabled
  // so we just check whether the table exists.
  if (!db_table_exists('event')) {
    drupal_set_message(t('There is no event table in this database. No event import options are available.'));
    return array();
  }

  if (empty($form_state['values']['step'])) {
    $form_state['values']['step'] = 0;
  }
  $step = intval($form_state['values']['step'] + 1);
  $form['step'] = array(
    '#type' => 'hidden',
    '#value' => $step,
  );

  switch ($step) {
    case 1: // Select a content type to import into.
      $node_types = node_get_types('names');
      $form['#prefix'] = '<p>' . t("Create a new CCK content type to import your events into, or, if you do not want to create new nodes for your events, add a date field to the existing event type. Make sure the target content type has a date field that has an optional or required To date so it can accept the From date and To date of the event. If your source event has its own timezone field, make sure you set the target date timezone handling to 'date'. Test the target type by trying to create a node manually and make sure all the right options are available in the form before attempting an import.") . '</p><p><strong>' . t('The import will create new nodes and trigger all related hooks, so you may want to turn off automatic email messaging for this node type while performing the import!') . '</strong></p>';
      $source_type_options = array();
      $result = db_query("SELECT DISTINCT n.type FROM {event} e INNER JOIN {node} n ON e.nid=n.nid");
      while ($arr = db_fetch_array($result)) {
        $source_type_options[$arr['type']] = $node_types[$arr['type']];
      }
      if (sizeof($source_type_options) < 1) {
        drupal_set_message(t('There are no event nodes in this database. No event import options are available.'));
        return array();
      }
      $form['source_type'] = array(
        '#type' => 'select',
        '#options' => $source_type_options,
        '#title' => t('Source type'),
        '#default_value' => '',
      );
      $form += date_tools_copy_type_form(TRUE);
      $form['submit'] = array('#type' => 'submit', '#value' => t('Import'));

      return $form;

    case 2: // Select the fields to import into.
      $type = $form_state['values']['target_type'];
      $form['target_type'] = array(
        '#value' => $type,
        '#type' => 'hidden',
      );
      $form['source_type'] = array(
        '#value' => $form_state['values']['source_type'],
        '#type' => 'hidden',
      );
      $form['fields'] = array(
        '#type' => 'fieldset',
        '#title' => t('!type Fields', array('!type' => $node_types[$type])),
        '#weight' => -1,
      );
      $form['fields'] += date_tools_copy_type_fields_form($type);
      $form['delete_old'] = array('#type' => 'select', '#options' => array(1 => t('Yes'), 0 => t('No')), '#title' => t('Delete original event?'), '#description' => t('Should the original entry be deleted once it has been copied to the new content type? If so, be sure to back up your database first.'));
      $form['max'] = array('#type' => 'textfield', '#title' => t('Limit'), '#description' => t('The maximum number of nodes to convert in this pass.'), '#required' => TRUE);
      $form['start_nid'] = array('#type' => 'textfield', '#title' => t('Starting nid'), '#default_value' => 0, '#description' => t('Convert nodes with nids greater than or equal to this number.'));
      $form['submit'] = array('#type' => 'submit', '#value' => t('Import'));
      return $form;
  }
}

/**
 *  Event import processing.
 */
function date_tools_copy_import_event_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  extract($form_state['values']);
  if ($step != 2) return;

  // workaround to disable drupal messages when nodes are created or deleted
  //$messages = drupal_get_messages();

  // The array that maps event timezone zids to timezone names is in
  // date_php4_tz_map.inc, need to reverse it so the zid is the key.
  require_once('./'. drupal_get_path('module', 'date_php4') .'/date_php4_tz_map.inc');
  $timezones = array('' => '');
  $map = $timezone_map;
  foreach ($map as $zone => $values) {
    if (!empty($values['zid'])) {
      $timezones[$values['zid']] = $zone;
    }
  }

  $rows = array();
  $i = 0;
  // Get $max records, 10 at a time.
  $limit = min(10, intval($max));
  while ($i < intval($max)) {
    $new_rows = date_tools_copy_convert_events($source_type, $target_type, $date_field, $description_field, $limit, $i, $delete_old, $start_nid, $timezones);
    $rows = array_merge($rows, $new_rows);
    $i += $limit;
  }

  // write back the old messages
  //$_SESSION['messages'] = $messages;

  if (!empty($rows)) {
    drupal_set_message(format_plural(sizeof($rows), '1 event has been converted.', '@count events have been converted.'));
    drupal_set_message(theme('table', array(t('Node Title'), t('Original Node ID'), t('New Node ID'), t('Start date'), t('End date')), $rows));
  }
  else {
    drupal_set_message(t('No events have been converted.'));
  }
  return;
}

function date_tools_copy_convert_events( $source_type, $target_type, $date_field, $description_field, $limit, $start = 0, $delete_old, $start_nid, $timezones) {

  // Get info about the field we are importing into
  $field   = content_fields($date_field);

  // Get date tz handling, could be date, site, GMT, or none.
  $tz_handling  = $field['tz_handling'];

  // Get event tz handling, could be event, site, or user.
  $event_tz_handling = variable_get('event_timezone_display', 'event');

  // Check which version of the Event module this database was built in.
  $event_version = 1;
  if (db_column_exists('event', 'has_time')) {
    $event_version = 2;
  }

  $rows = array();
  if ($start_nid) {
    $where = " AND n.nid >= $start_nid ";
  }
  if (!$result = db_query_range("SELECT * FROM {event} e INNER JOIN {node} n ON e.nid=n.nid WHERE n.type = '%s' $where ORDER BY n.nid", array($source_type, $start_nid), $start, $limit)) {
    return array();
  }
  while ($event = db_fetch_object($result)) {

    $source_nid = $event->nid;
    $event_node = node_load($source_nid, NULL, TRUE);

    // Creating new nodes or converting existing ones??
    if ($target_type != $source_type) {
      $target_node = new stdClass();
      $target_node->nid = 0;
      $target_node->type = $target_type;
      foreach ($event_node as $key => $val) {
        if ($key != 'nid' && $key != 'type') {
          $target_node->$key = $val;
        }
      }
    }
    else {
      $target_node = $event_node;
    }

    if ($description_field != 'body') {
      $target_node->$description_field = array(0 => array('value' => $event_node->body));
      unset($target_node->body);
    }

    // Set the date timezone value.
    $timezone = !empty($event->timezone) && $tz_handling == 'date' && $event_tz_handling == 'event' ? $timezones[$event->timezone] : date_default_timezone_name();

    // If this is a deprecated timezone, replace it.
    require_once(drupal_get_path('module', 'date_timezone') .'/date_timezone.install');
    $timezone = _date_timezone_replacement($timezone);

    // Find the original timezone value (might not be the same as the date timezone).
    $event_timezone = !empty($event->timezone) ? $timezones[$event->timezone] : date_default_timezone_name();
    // If this is a deprecated timezone, replace it.
    $event_timezone = _date_timezone_replacement($event_timezone);
    
    if ($event_version == 1) {
      // Version 1 stores the UTC value in the database as a timestamp.
      $date = array(0 => array());
      $data[0]['timezone'] = $timezone;
      $start = date_make_date($event->event_start, 'UTC', DATE_UNIX);
      date_timezone_set($start, timezone_open($timezone));
      $data[0]['offset'] = date_offset_get($start);
      $end = date_make_date($event->event_end, 'UTC', DATE_UNIX);
      date_timezone_set($end, timezone_open($timezone));
      $data[0]['offset2'] = date_offset_get($end);

      // If the original event had the wrong offset, the 'UTC' value it
      // created will also be wrong, correct it here.
      if ($event_node->start_offset != date_offset_get($start) || $event_node->end_offset != date_offset_get($end)) {
        $adj = $event_node->start_offset - date_offset_get($start);
        date_timezone_set($start, timezone_open('UTC'));
        date_modify($start, $adj .' seconds');
        $adj = $event_node->end_offset - date_offset_get($end);
        date_timezone_set($end, timezone_open('UTC'));
        date_modify($end, $adj .' seconds');
      }
      $data[0]['value'] = date_format($start, date_type_format($field['type']));
      $data[0]['value2'] = date_format($end, date_type_format($field['type']));
    }
    else {
      // Version 2 stores the local value in the database as a datetime field.
      $date = array(0 => array());
      $data[0]['timezone'] = $timezone;
      $start = date_make_date($event->event_start, $event_timezone, DATE_DATETIME);
      if ($event_timezone != $timezone) {
        date_timezone_set($start, timezone_open($timezone));
      }
      $data[0]['offset'] = date_offset_get($start);
      $end = date_make_date($event->event_end, $event_timezone, DATE_DATETIME);
      if ($event_timezone != $timezone) {
        date_timezone_set($end, timezone_open($timezone));
      }
      $data[0]['offset2'] = date_offset_get($end);

      date_timezone_set($start, timezone_open('UTC'));
      date_timezone_set($end, timezone_open('UTC'));
      $data[0]['value'] = date_format($start, date_type_format($field['type']));
      $data[0]['value2'] = date_format($end, date_type_format($field['type']));
    }

    $target_node->$date_field = $data;
    $event_fields = array(
      'event_start', 'event_end', 'timezone', 'start_offset',
      'start_format', 'start_time_format', 'end_offset',
      'end_format', 'end_time_format', 'event_node_title');
    foreach ($event_fields as $e) {
      unset($target_node->$e);
    }

    node_save($target_node);

    if ($target_type != $source_type) {
      watchdog('date_tools', '!type: %title has been created.', array(
        '!type' => t($target_type),
        '%title' => $target_node->title),
        WATCHDOG_NOTICE,
        l(t('view'), 'node/'. $target_node->nid));
      if ($delete_old) {
        node_delete($source_nid);
      }
    }
    else {
      watchdog('date_tools', '!type: %title has been updated.', array(
        '!type' => t($target_type),
        '%title' => $target_node->title),
        WATCHDOG_NOTICE,
        l(t('view'), 'node/'. $target_node->nid));
    }
    $new_field = $target_node->$date_field;
    $rows[] = array(
      l($target_node->title,
      'node/'. $target_node->nid),
      $source_nid,
      $target_node->nid,
      $new_field[0]['value'],
      $new_field[0]['value2']);
  }
  return $rows;
}

/**
 * A form to select a content type.
 */
function date_tools_copy_type_form($target = TRUE) {
  $form = array();
  $node_types = node_get_types('names');
  $fields = content_fields();
  $type_options = array();

  // Find out what content types contain date fields and set them up as target options.
  foreach ($fields as $field_name => $field) {
    if ($field['type'] == 'date' || $field['type'] == 'datestamp') {
      $type_options[$field['type_name']] = $node_types[$field['type_name']];
    }
  }

  if (sizeof($type_options) < 1) {
    drupal_set_message(t('There are no date fields in this database to import the data into. Please add a date field to the desired node types and be sure to indicate it uses both a "from" and a "to" date.'));
    return $form;
  }
  $type = $target ? 'target_type' : 'source_type';
  $label = $target ? t('Target type') : t('Source type');
  $form[$type] = array(
    '#type' => 'select',
    '#options' => $type_options,
    '#title' => $label,
    '#description' => t('Only content types with date fields appear in this list as possible target types.'),
    '#default_value' => '',
    );

  // If Content Copy is enabled, offer an import link.
  if (module_exists('content_copy')) {
    $form['macro'] = array(
      '#type' => 'fieldset',
      '#title' => t('Add'),
      '#description' => t('If your desired target type does not already have a date field, follow this link and select a content type to add a date field to that type.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['macro']['link'] = array(
      '#type' => 'markup',
      '#value' => l(t('Add new date field'), 'admin/content/types/import', array('query' => 'macro_file='. drupal_get_path('module', 'date_tools') .'/date_field.php')),
    );
  }
  return $form;
}

/**
 * A form to select fields from a content type.
 */
function date_tools_copy_type_fields_form($type, $extended = FALSE) {
  $form = array();
  $fields = content_fields();
  $date_options = array();
  $description_options = array('' => '');
  $uid_options = array('' => '');
  $url_options = array('' => '');
  $location_options = array('' => '');

  // Find out what content types contain date fields and set them up as target options.
  foreach ($fields as $field_name => $field) {
    if ($field['type_name'] == $type) {
      if ($field['type'] == 'date' || $field['type'] == 'datestamp') {
        $date_options[$field_name] = $field['widget']['label'];
      }
      if ($field['type'] == 'text') {
        $description_options[$field_name] = $field['widget']['label'];
        $location_options[$field_name] = $field['widget']['label'];
        $uid_options[$field_name] = $field['widget']['label'];
        $url_options[$field_name] = $field['widget']['label'];
      }
      if ($field['type'] == 'link') {
        $url_options[$field_name] = $field['widget']['label'];
      }
    }
  }
  // The body field is also available as an option for the description.
  $description_options['body'] = t('body');
  if (sizeof($date_options) < 1) {
    drupal_set_message(t('There are no date fields in this database to import the data into. Please add a date field to the desired node types and be sure to indicate it uses both a "from" and a "to" date.'));
    return $form;
  }
  $form['date_field'] = array(
    '#type' => 'select',
    '#options' => $date_options,
    '#title' => t('Date field'),
    '#default_value' => '',
    '#description' => t('The field which will contain the source dates in target content type.'),
    );
  $form['description_field'] = array(
    '#type' => 'select',
    '#options' => $description_options,
    '#title' => t('Description field'),
    '#default_value' => '',
    '#description' => t('The text or body field which will contain the source description in the target content type.'),
    );
  if ($extended) {
    $form['url_field'] = array(
      '#type' => 'select',
      '#options' => $url_options,
      '#title' => t('Url field'),
      '#default_value' => '',
      '#description' => t('The text or link field which will contain the source url in the target content type.'),
      );
    $form['location_field'] = array(
      '#type' => 'select',
      '#options' => $location_options,
      '#title' => t('Location field'),
      '#default_value' => '',
      '#description' => t('The text field which will contain the source location text in the target content type.'),
      );
    $form['uid_field'] = array(
      '#type' => 'select',
      '#options' => $uid_options,
      '#title' => t('Uid field'),
      '#default_value' => '',
      '#description' => t('The text field which will contain the source uid in the target content type.'),
      );
  }
  return $form;
}
