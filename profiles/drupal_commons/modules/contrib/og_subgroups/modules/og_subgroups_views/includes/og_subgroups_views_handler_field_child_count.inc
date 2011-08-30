<?php
class og_subgroups_views_handler_field_child_count extends views_handler_field {
  function query() {}
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['deep'] = array(
      '#type' => 'checkbox',
      '#title' => t('Count only immediate child groups.'),
      '#description' => t('If checked, the count will only include children that are one level down.'),
      '#default_value' => isset($this->options['deep']) ? $this->options['deep'] : 0,
    );
  }
  
  function render($value) {
    og_subgroups_include('tree');
    $children = og_subgroups_get_group_children($value, $this->options['deep']);
    return count($children);
  }
}
