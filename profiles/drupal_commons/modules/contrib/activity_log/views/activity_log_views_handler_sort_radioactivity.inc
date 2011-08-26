<?php

/**
 * @file
 *   Handler for Activity Log views to sort by Radioactivity energy.
 */

/**
 * Sorts Activity Log views by Radioactivity energy.
 */
class activity_log_views_handler_sort_radioactivity extends views_handler_sort {
  function option_definition() {
    $options = parent::option_definition();
    $options['join_type'] = array('default' => 'left');
    return $options;
  }
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['join_type'] = array(
      '#type' => 'radios',
      '#title' => t('Join type'),
      '#options' => array(
        'left' => t('LEFT JOIN: Include all activities'),
        'inner' => t('INNER JOIN: Include only activities that have Radioactivity data (faster)'),
      ),
      '#description' => t('Select the join type for sorting.'),
      '#default_value' => $this->options['join_type'],
    );
  }
  function admin_summary() {
    $ret = parent::admin_summary();
    $type = t('!type JOIN', array('!type' => $this->options['join_type']));
    return $ret .', '. $type;
  }
  function ensure_my_table() {
    if (!isset($this->table_alias)) {
      $join = $this->get_join();
      $join->type = drupal_strtoupper($this->options['join_type']);
      $this->table_alias = $this->query->ensure_table($this->table, $this->relationship, $join);
    }
    return $this->table_alias;
  }
  function query() {
    if ($this->options['join_type'] == 'inner') {
      parent::query();
    }
    elseif ($this->options['join_type'] == 'left') {
      // NOTE: NULL energy (i.e. no energy row per node) is equivalent to 0
      // energy. So, add the sort key accordingly.
      $this->ensure_my_table();
      $this->query->add_orderby(
        NULL,
        'COALESCE('. $this->table_alias .'.'. $this->field .',0)',
        $this->options['order'],
        $this->table_alias .'_'. $this->field .'_sortkey'
      );
    }
  }
}
