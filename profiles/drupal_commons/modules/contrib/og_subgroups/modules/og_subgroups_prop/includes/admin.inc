<?php

/**
 * Menu callback for admin settings form
 */
function og_subgroups_prop_settings() {
  $form = array();
  $form['propagte_content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Group posts propagation'),
    '#description' => t('Content can be propagated through the subgroups tree.'),
    '#collapsible' => TRUE,
  );
  $form['propagte_content']['og_subgroups_propagate_content'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content propagation'),
    '#description' => t('Determine the propagation path content will take if posted inside a group. For example, if children is selected, a post inside a group will also be propagated to all the children, so the node appears in those groups too.'),
    '#options' => array(
      'parents' => t('Parents'),
      'children' => t('Children'),
      'siblings' => t('Siblings'),
    ),
    '#default_value' => variable_get('og_subgroups_propagate_content', array()),
  );
  $form['propagte_user'] = array(
    '#type' => 'fieldset',
    '#title' => t('User propagation'),
    '#description' => t('Group members can be propagated through the subgroups tree.'),
    '#collapsible' => TRUE,
  );
  $form['propagte_user']['og_subgroups_propagate_members'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Subscribing Members'),
    '#description' => t('Determine the propagation path membership will take along the group hierarchy. For example, if children is selected, any user that joins a given group will also become a member of the child groups.'),
    '#options' => array(
      'parents' => t('Parents'),
      'children' => t('Children'),
      'siblings' => t('Siblings'),
    ),
    '#default_value' => variable_get('og_subgroups_propagate_members', array()),
  );
  $form['propagte_user']['og_subgroups_propagate_members_unsubscribe'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Unsubscribing Members'),
    '#description' => t('Determine the propagation path that unsubscribing from a group will follow along the group hierarchy. For example, if children is selected, any user that unsubscribes from a group will also be unsubscribed from the children of that group.'),
    '#options' => array(
      'parents' => t('Parents'),
      'children' => t('Children'),
      'siblings' => t('Siblings'),
    ),
    '#default_value' => variable_get('og_subgroups_propagate_members_unsubscribe', array()),
  );
  
  return system_settings_form($form);
}
