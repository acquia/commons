<?php
class og_subgroups_views_handler_argument_content extends og_subgroups_views_handler_argument_gid {
  function query() {
    $this->ensure_my_table();

    if (!empty($this->options['break_phrase'])) {
      views_break_phrase($this->argument, $this);
    }
    else {
      $this->value = array($this->argument);
    }

    $tree = $this->get_subgroup_tree();
    $arguments = explode(',', $this->argument);

    if ($this->options['include_argument']) {
      $tree = array_merge($tree, $arguments);
    }

    $placeholders = implode(', ', array_fill(0, sizeof($tree), '%d'));
    $this->query->add_where(0, "$this->table_alias.$this->real_field IN ($placeholders)", $tree);
  }
}