<?php
// $Id: context_og_reaction_set_group_context.inc,v 1.1 2010/07/12 23:17:21 marcp Exp $

/**
 * Expose organic groups as context reactions.
 */
class context_og_reaction_set_group_context extends context_reaction {
  /**
   * Choose a group whose OG context will be set for this reaction.
   */
  function options_form($context) {
    $sql = "SELECT n.nid, n.title, n.type FROM {node} n INNER JOIN {og} o ON n.nid = o.nid ORDER BY n.type, n.title";
    $result = db_query(db_rewrite_sql($sql));

    $options = array();
    while ($group = db_fetch_object($result)) {
      $type = node_get_types('name', $group->type);
      $options[$group->nid] = $type . ': ' . $group->title;
    }

    $values = $this->fetch_from_context($context);

    $form = array(
      'group' => array(
        '#title' => t('Group'),
        '#description' => t('Set the group context to the selected group.'),
        '#type' => 'select',
        '#multiple' => FALSE,
        '#options' => $options,
        '#default_value' => isset($values['group']) ? $values['group'] : '',
      ),
    );
    return $form;
  }

  function execute() {
    $contexts = context_active_contexts();
    $classes = array();

    foreach ($contexts as $k => $v) {
      if (!empty($v->reactions[$this->plugin]['group'])) {
        $group_node = node_load(array('nid' => $v->reactions[$this->plugin]['group']));
        og_set_group_context($group_node);
      }
    }
  }
}
