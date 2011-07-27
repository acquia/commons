<?php
class og_subgroups_views_handler_argument_gid extends views_handler_argument_numeric {
  function option_definition() {
    $options = parent::option_definition();
    $options['build_directions'] = array('default' => array('children'));
    $options['include_argument'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove unwanted options
    unset($form['not']);

    $form['build_directions'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Build Direction'),
      '#description' => t('Retrieve groups in the direction specified using the argument(s) as a starting point.'),
      '#required' => TRUE,
      '#options' => array(
        'parents' => t('Parents'),
        'children' => t('Children'),
        'siblings' => t('Siblings'),
      ),
      '#default_value' => $this->options['build_directions']
    );

    $form['include_argument'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include the argument'),
      '#description' => t('If selected, the group(s) specified in the argument(s) will be added to the output.'),
      '#default_value' => $this->options['include_argument'],
    );
  }
  
  function get_subgroup_tree() {
    og_subgroups_include('tree');
    $tree = array();
    $directions = array_filter($this->options['build_directions']);
    $arguments = explode(',', $this->argument);

    // Get all group IDs that are in the argument's family
    foreach($arguments as $argument) {
      foreach ($directions as $direction) {
        // Build a group object to pass along
        $group = new stdClass;
        $group->nid = $argument;
        
        // Decide the function to use based on the direction
        $func = "og_subgroups_get_group_{$direction}";
        
        // Fetch the groups
        $groups = $func($group, ($direction == 'children') ? FALSE : NULL);
        
        // Add the groups to an array
        foreach ($groups as $group) {
          $tree[] = $group->nid;
        }
      }
    }
    
    return !empty($tree) ? $tree : array(-1);
  }

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
    $base_table = $this->query->base_table;
    $base_field = $this->query->base_field;
    $this->query->add_where(0, "$base_table.$base_field IN ($placeholders)", $tree);
  }
}
