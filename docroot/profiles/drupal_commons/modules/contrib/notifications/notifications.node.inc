<?php
// $Id: notifications.node.inc,v 1.1.2.2.2.2 2009/09/22 11:49:07 jareyero Exp $
/**
 * @file
 * Notifications node API for use by plug-in modules providing node related features
 * 
 * So far, this is used by:
 * - notifications_content
 * - notifications_feed
 */

/**
 * Mapping from node nid to title
 */
function notifications_node_nid2title($nid, $html = FALSE) {
  if ($node = node_load($nid)) {
    return $html ? l($node->title, "node/$nid") : check_plain($node->title);
  }
  else {
    return t('Not found');
  }
}

/**
 * Reverse mapping from node title to nid
 * 
 * We also handle autocomplete values (title [nid:x]) and validate the form
 */
function notifications_node_title2nid($name, $field = NULL, $types = array()) {
  if (!empty($name)) {
    preg_match('/^(?:\s*|(.*) )?\[\s*nid\s*:\s*(\d+)\s*\]$/', $name, $matches);
    if (!empty($matches)) {
      // Explicit [nid:n].
      list(, $title, $nid) = $matches;
      if (!empty($title) && ($node = node_load($nid)) && $title != $node->title) {
        if ($field) {
          form_set_error($field, t('Node title mismatch. Please check your selection.'));
        }
        $nid = NULL;
      }
    }
    else {
      // No explicit nid.
      $reference = _notifications_node_references($name, 'equals', $types, 1);
      if (!empty($reference)) {
        $nid = key($reference);
      }
      elseif ($field) {
        form_set_error($field, t('Found no valid post with that title: %title', array('%title' => $name)));
      }
    }
  }
  return !empty($nid) ? $nid : NULL;  
}

/**
 * Generates 'title [nid:$nid]' for the autocomplete field
 */
function notifications_node_nid2autocomplete($nid) {
  if ($node = node_load($nid)) {
    return check_plain($node->title) . ' [nid:' . $nid .']';
  }
  else {
    return t('Not found');
  }
}

/**
 * Menu callback; Retrieve a pipe delimited string of autocomplete suggestions for existing users
 */
function notifications_node_autocomplete_title($string = '') {
  $matches = array();

  foreach (_notifications_node_references($string) as $id => $row) {
    // Add a class wrapper for a few required CSS overrides.
    $matches[$row['title'] ." [nid:$id]"] = '<div class="reference-autocomplete">'. $row['rendered'] . '</div>';
  }
  drupal_json($matches);
}

/**
 * Menu callback; Retrieve a pipe delimited string of autocomplete suggestions for existing users
 * 
 * @param $node_types
 *   Comma separated node types to query
 */
function notifications_node_autocomplete_type($node_types, $string = '') {
  $matches = array();
  $types = split(',', $node_types);
  foreach (_notifications_node_references($string, 'contains', $types) as $id => $row) {
    // Add a class wrapper for a few required CSS overrides.
    $matches[$row['title'] ." [nid:$id]"] = '<div class="reference-autocomplete">'. $row['rendered'] . '</div>';
  }
  drupal_json($matches);
}

/**
 * Find node title matches.
 * 
 * Some code from CCK's nodereference.module
 */
function _notifications_node_references($string, $match = 'contains', $types = array(), $limit = 10) {
  $match_operators = array(
    'contains' => "LIKE '%%%s%%'",
    'equals' => "= '%s'",
    'starts_with' => "LIKE '%s%%'",
  );
  if ($types) {
    $where[] = 'n.type IN (' . db_placeholders($types, 'char') . ') ';
    $args = $types;
  }
  $where[] = 'n.title '. (isset($match_operators[$match]) ? $match_operators[$match] : $match_operators['contains']);
  $args[] = $string;
  $sql = db_rewrite_sql('SELECT n.nid, n.title, n.type FROM {node} n WHERE ' . implode(' AND ', $where) . ' ORDER BY n.title, n.type');
  $result = db_query_range($sql, $args, 0, $limit) ;
  $references = array();
  while ($node = db_fetch_object($result)) {
    $references[$node->nid] = array(
      'title' => $node->title,
      'rendered' => check_plain($node->title),
    );
  }
  return $references; 
}

