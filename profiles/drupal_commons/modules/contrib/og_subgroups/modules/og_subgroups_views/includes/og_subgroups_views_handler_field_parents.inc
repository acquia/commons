<?php
class og_subgroups_views_handler_field_parents extends views_handler_field_prerender_list {

  function init(&$view, $options) {
    parent::init($view, $options);
    $this->additional_fields['node_nid'] = array('table' => 'node', 'field' => 'nid');
    $this->additional_fields['og_subgroups_parent'] = array('table' => 'og_subgroups', 'field' => 'parent');
  }

  function query() {
    $this->add_additional_fields();
  }

  function pre_render($values) {
    og_subgroups_include('tree');
    // field_alias is used by the render method.
    $this->field_alias = $this->aliases['node_nid'];
    foreach ($values as $value) {
      $parents = og_subgroups_get_group_parents($value);
      foreach ($parents as $nid => $parent) {
        $this->items[$value->nid][$parent->nid] = l($parent->title, "node/{$parent->nid}");
      }
    }
  }
}
