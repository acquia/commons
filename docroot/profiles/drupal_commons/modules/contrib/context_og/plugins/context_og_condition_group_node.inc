<?php
// $Id: context_og_condition_group_node.inc,v 1.1 2010/07/12 23:17:21 marcp Exp $

/**
 * Expose organic groups group nodes as a context condition.
 */
class context_og_condition_group_node extends context_condition {
  function condition_values() {
    $sql = "SELECT n.nid, n.title, n.type FROM {node} n INNER JOIN {og} o ON n.nid = o.nid ORDER BY n.type, n.title";
    $result = db_query(db_rewrite_sql($sql));

    $values = array();
    while ($group = db_fetch_object($result)) {
      $type = node_get_types('name', $group->type);
      $values[$group->nid] = $type . ': ' . $group->title;
    }

    return $values;
  }

  function condition_form($context) {
    $form = parent::condition_form($context);
    $form['#type'] = 'select';
    $form['#multiple'] = TRUE;
    return $form;
  }

  function options_form($context) {
    $defaults = $this->fetch_from_context($context, 'options');
    return array(
      'node_form' => array(
        '#title' => t('Set on node form'),
        '#type' => 'checkbox',
        '#description' => t('Set this context on node forms'),
        '#default_value' => isset($defaults['node_form']) ? $defaults['node_form'] : TRUE,
      ),
    );
  }

  function execute($group) {
    if (isset($group)) {
      $node_form = ((arg(0) == 'node') && ((is_numeric(arg(1)) && (arg(2) == 'edit')) || (arg(1) == 'add')));
      $contexts = $this->get_contexts($group->nid);
      $this->values[$group->nid] = array();
      foreach ($contexts as $context) {
        $options = $this->fetch_from_context($context, 'options');
        // The condition is met unless we are looking at a node form
        // and the "Set on node form" option is unchecked.
        if (!$node_form || !empty($options['node_form'])) {
          $this->condition_met($context, $group->nid);
        }
      }
    }
  }
}
