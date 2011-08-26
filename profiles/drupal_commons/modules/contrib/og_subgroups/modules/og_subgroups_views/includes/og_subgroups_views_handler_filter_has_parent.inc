<?php

/**
 * Filter handler based on if group has a parent
 */
class og_subgroups_views_handler_filter_has_parent extends views_handler_filter_boolean_operator {
  function construct() {
    parent::construct();
    $this->value_value = t('Does the group have a parent');
  }

  function query() {
    $this->ensure_my_table();
    $where = "$this->table_alias.$this->real_field ";

    if ($this->value) {
      $where .= 'IS NOT NULL';
    }
    else {
      $where .= 'IS NULL';
    }
    $this->query->add_where($this->options['group'], $where);    
  }
}
