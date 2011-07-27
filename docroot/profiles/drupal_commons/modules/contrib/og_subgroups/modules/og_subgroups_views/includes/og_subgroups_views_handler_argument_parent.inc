<?php
class og_subgroups_views_handler_argument_parent extends views_handler_argument_numeric {
  function option_definition() {
    $options = parent::option_definition();
    $options['include_parent'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove unwanted options
    unset($form['not']);

    $form['include_parent'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include the parent'),
      '#description' => t('If selected, the parent group specified in the argument will be added to the output.'),
      '#default_value' => $this->options['include_parent'],
    );
  }

  function default_actions($which=null){
    $defaults = parent::default_actions();
    $defaults += array(
      'roots-only' => array(
        'title' => t('OG Subgroups: Display top level groups only'),
        'method' => 'default_roots_only',
        'breadcrumb' => TRUE, // generate a breadcrumb to here
        ),
    );

    if ($which) {
      if (!empty($defaults[$which])) {
        return $defaults[$which];
      }
    }
    else {
      return $defaults;
    }
  }
  
  function default_roots_only() {
    module_load_include('module', 'og_subgroups', 'og_subgroups');
    $allowed_types = array();
    foreach(node_get_types('types') as $type) {
      if (og_subgroups_is_subgroup_type($type->type)) {
       $allowed_types[] = $type->type;
      }
    }
   
    $allowed_types = implode("','", $allowed_types);
    $this->query->add_where(0, "node.nid NOT IN (select gid from {og_subgroups})");
    $this->query->add_where(0, "node.type IN ('$allowed_types')");

    return TRUE;
  }

  function query() {
    $this->ensure_my_table();

    if (!empty($this->options['break_phrase'])) {
      views_break_phrase($this->argument, $this);
    }
    else {
      $this->value = array($this->argument);
    }

    $arguments = explode(',', $this->argument);
    $placeholders = implode(', ', array_fill(0, sizeof($arguments), '%d'));
    if ($this->options['include_parent']) {
      $base_table = $this->query->base_table;
      $base_field = $this->query->base_field;

      foreach ($arguments as $arg) {
        $arguments[] = $arg;
      }

      $this->query->add_where(0, "$this->table_alias.$this->real_field IN ($placeholders) OR $base_table.$base_field IN ($placeholders)", $arguments);
    }
    else {
      $this->query->add_where(0, "$this->table_alias.$this->real_field IN ($placeholders)", $arguments);
    }
  }
}