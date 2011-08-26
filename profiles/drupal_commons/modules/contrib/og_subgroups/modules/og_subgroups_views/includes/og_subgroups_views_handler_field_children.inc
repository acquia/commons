<?php
class og_subgroups_views_handler_field_children extends views_handler_field_prerender_list {

  function init(&$view, $options) {
    parent::init($view, $options);
    $this->additional_fields['node_nid'] = array('table' => 'node', 'field' => 'nid');
    $this->additional_fields['og_subgroups_parent'] = array('table' => 'og_subgroups', 'field' => 'parent');
  }

  function query() {
    $this->add_additional_fields();
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link'] = array(
      '#type' => 'checkbox',
      '#title' => t('Link to the child groups'),
      '#default_value' => isset($this->options['link']) ? $this->options['link'] : 1,
    );
  }

  function pre_render($values) {
    og_subgroups_include('tree');
    // field_alias is used by the render method.
    $this->field_alias = $this->aliases['node_nid'];
    foreach ($values as $value) {
      $children = og_subgroups_get_group_children($value, FALSE);
      foreach ($children as $nid => $child) {
        $this->items[$value->nid][$child->nid] = $this->options['link'] ? l($child->title, "node/{$child->nid}") : $child->title;
      }
    }
  }
}
