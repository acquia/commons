<?php
// $Id: notifications_test_case.inc,v 1.1.2.1 2009/04/24 00:10:28 jareyero Exp $
/**
 * @file
 * Base class for Notifications Tests
 */
class NotificationsTestCase extends DrupalWebTestCase { 
  // Helper option for debugging
  function printDebug($data, $title = 'DEBUG') {
    $string = is_array($data) || is_object($data) ? print_r($data, TRUE) : $data;
    $this->assertTrue(TRUE, $title . ': ' . $string);
  }
  // Debug dump object with some formatting
  function printObject($object, $title = 'DEBUG Object') {
    $output = $title . ':';
    $output .= $this->formatTable($object);
    $this->assertTrue(TRUE, $output);
  }
  // Format object as table, recursive
  function formatTable($object) {
    foreach ($object as $key => $value) {
      $rows[] = array(
        $key,
        is_array($value) || is_object($value) ? $this->formatTable($value) : $value,
      );
    }
    if (!empty($rows)) {
      return theme('table', array(), $rows);
    }
    else {
      return 'No properties';
    }
  }
  // Assert number of rows in table
  function assertTableRows($table, $target, $conditions = NULL, $message = NULL) {
    $sql = 'SELECT COUNT(*) FROM {' . $table . '}';
    if ($conditions) {
      foreach ($conditions as $field => $value) {
        $where[] = "$field = '%s'";
        $print[] = "$field=$value";
      }
    }
    if (!empty($where)) {
      $sql .= ' WHERE ' . implode(' AND ', $where);
    }
    $count = db_result(db_query($sql, $conditions));
    $message = $message ? $message : 'Right number of rows in table ' . $table .'[' . implode(', ', $print) . ']=' . $target;
    $message .= " ($count)";
    $this->assertEqual($count, $target, $message);
  }
  // Assert number of rows in table for a user
  function assertUserRows($table, $target, $uid, $message = NULL) {
    $message = $message ? $message : "There are $target rows in table $table for user $uid";
    $this->assertTableRows($table, $target, array('uid' => $uid), $message);
  }
  // Dump table contents
  function dumpTable($table) {
    $result = db_query('SELECT * FROM {' . $table . '}');
    $output = 'Table dump <strong>' . $table . '</strong>:';
    while ($row = db_fetch_array($result)) {
      $rows[] = $row;
      if (empty($header)) {
        $header = array_keys($row);
      }
    }
    if (!empty($rows)) {
      $output .= theme('table', $header, $rows);
    } else {
      $output .= ' No rows';
    }
    $this->assertTrue(TRUE, $output);
  }
  // Dump Notifications log
  function dumpLogs() {
    if ($logs = notifications_log()) {
      $this->assertTrue(TRUE, theme('item_list', $logs, 'Notifications logs'));
    }
  }
}