<?php
class og_subgroups_views_handler_field_parent_title extends views_handler_field {
  function render($value) {
    og_subgroups_include('tree');
    $parent = og_subgroups_get_group_parent($value);
    return $parent ? $parent->title : NULL;
  }
}
