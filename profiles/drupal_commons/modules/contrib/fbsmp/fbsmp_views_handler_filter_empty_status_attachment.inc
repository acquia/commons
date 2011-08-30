<?php

/**
 * @file
 *   Filter to allow each status to have at least status text or attachment.
 */

/**
 * Filter handler to show status with at least one of status text and attachment.
 */
class fbsmp_views_handler_filter_empty_status_attachment extends views_handler_filter_boolean_operator {
  function construct() {
    $this->definition['type'] = 'yes-no';
    $this->definition['label'] = t('Show status only if status text is not blank or has an attachment');
    $this->value_value = $this->definition['label'];
    parent::construct();
  }

  function query() {
    if ($this->value) {
      $table = $this->ensure_my_table();
      $fbss = $this->query->ensure_table('facebook_status');
      $query = "$fbss.message <> ''";
      
      $plugins = fbsmp_get_plugins();
      if (is_array($plugins) && count($plugins) > 0) {
        $subquery = "$table.type IN (". db_placeholders(array_keys($plugins), 'text') .")";
        $query .= " OR ( $table.type IS NOT NULL AND $subquery )";
      }
      
      $this->query->add_where(0, $query, array_keys($plugins));
    }
  }
}