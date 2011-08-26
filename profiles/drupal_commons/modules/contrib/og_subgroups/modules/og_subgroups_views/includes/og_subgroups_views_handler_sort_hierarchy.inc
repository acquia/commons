<?php

class og_subgroups_views_handler_sort_hierarchy extends views_handler_sort {
  /**
   * The sort cannot be exposed
   */
  function can_expose() { return FALSE; }

  function query() {
    og_subgroups_include('tree');
    $tree = og_subgroups_get_tree();
    $groups = og_subgroups_flatten_tree($tree);

    if (!empty($groups)) {
      $sort_order = implode(',', array_keys($groups));
      $base_table = $this->query->base_table;
      $base_field = $this->query->base_field;
      $formula = "FIELD($base_table.$base_field, $sort_order)";

      $this->query->add_orderby(NULL, $formula, $this->options['order'], '_' . $this->field);
    }
  }
}