<?php
/**
 * Filter for permissions of a user, probably not all that reliable, use with caution.
 */
class notifications_views_handler_filter_perm extends views_handler_filter_many_to_one {
  function get_value_options() {
    $opt = module_invoke_all('perm');
    $this->value_options = array();
    foreach($opt as $opt) {
      $this->value_options[$opt] = $opt;
    }
  }
  
  function operators() {
    $operators = array(
      'like' => array(
        'title' => t('Has permission'),
        'short' => t('has'),
        'short_single' => t('='),
        'method' => 'op_like',
        'values' => 1,
      ),
      'not like' => array(
        'title' => t('Does not have permission'),
        'short' => t('lacks'),
        'short_single' => t('<>'),
        'method' => 'op_like',
        'values' => 1,
      ),
    );
    return $operators;
  }
  
  function op_like() {
    if (empty($this->value)) {
      return;
    }
    $permtable = $this->query->ensure_table('permission');
    $replace = array_fill(0, sizeof($this->value), "$permtable.perm " . $this->operator ." '%%%s%%'");
    
    $this->ensure_my_table();
    $replace[] = "$this->table_alias.$this->real_field = 1";
    $in = implode($this->operator == 'not like' ? ' AND ' : ' OR ', $replace);

    // We use array_values() because the checkboxes keep keys and that can cause
    // array addition problems.
    $this->query->add_where($this->options['group'], $in, array_values($this->value));
  }
}
