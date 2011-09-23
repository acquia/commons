<?php

function views_bulk_operations_ruleset_action_info() {
  if (!module_exists('rules')) return array();

  $actions = array();
  foreach (rules_get_configured_items('rule_sets') as $ruleset_key => $ruleset) {
    if (count($ruleset['arguments']) == 1) { // One argument: typed action
      $arg = key($ruleset['arguments']);
      $actions["views_bulk_operations_ruleset_action_{$ruleset_key}"] = array(
        'type' => $ruleset['arguments'][$arg]['type'],
        'parameters' => array('ruleset' => $ruleset_key),
        'description' => $ruleset['label'],
        'configurable' => FALSE,
        'rules_ignore' => TRUE,
        'callback' => 'views_bulk_operations_ruleset_action_one',
      );
    }
    else if (!count($ruleset['arguments'])) { // No argument: system action
      $actions["views_bulk_operations_ruleset_action_{$ruleset_key}"] = array(
        'type' => 'system',
        'parameters' => array('ruleset' => $ruleset_key),
        'description' => $ruleset['label'],
        'configurable' => FALSE,
        'rules_ignore' => TRUE,
        'callback' => 'views_bulk_operations_ruleset_action_zero',
      );
    }
    else { // General case
      $actions["views_bulk_operations_ruleset_action_{$ruleset_key}"] = array(
        'type' => 'system',
        'parameters' => array('ruleset' => $ruleset_key),
        'description' => $ruleset['label'],
        'configurable' => TRUE,
        'rules_ignore' => TRUE,
        'callback' => "views_bulk_operations_ruleset_action",
        'form properties' => array('#arguments'),
      );
    }
  }
  return $actions;
}

function views_bulk_operations_ruleset_action_one(&$object, $context) {
  rules_invoke_rule_set($context['ruleset'], $object);
}

function views_bulk_operations_ruleset_action_zero(&$object, $context) {
  rules_invoke_rule_set($context['ruleset']);
}

function views_bulk_operations_ruleset_action(&$object, $context) {
  $ruleset = rules_get_rule_sets($context['ruleset']);
  $args = array();
  foreach ($ruleset['arguments'] as $key => $argument) {
    $args[$key] = @eval($context['args'][$key]);
  }
  rules_invoke_rule_set($context['ruleset'], $args);
}

function views_bulk_operations_ruleset_action_form($context) {
  $ruleset = rules_get_rule_sets($context['ruleset']);
  $form['#arguments'] = $ruleset['arguments'];
  foreach ($form['#arguments'] as $key => $argument) {
    $form[$key] = array(
      '#type' => 'textarea',
      '#title' => $argument['label'],
      '#description' => t('Argument of type %type. Enter PHP script that will return a value for this argument.
                           Note that Rules expects a entire object (e.g. <code>$node</code>) rather than an id (e.g. <code>$nid</code>).
                           The variables <code>$object</code> and <code>$context</code> are available to this script.
                           Do not include &lt;?php and ?&gt; tags.',
        array('%type' => $argument['type'])
      ),
      '#default_value' => @$context['args'][$key],
    );
  }
  return $form;
}

function views_bulk_operations_ruleset_action_validate($form, $form_state) {
}

function views_bulk_operations_ruleset_action_submit($form, $form_state) {
  $submit = array();
  foreach ($form['#arguments'] as $key => $argument) {
    $submit['args'][$key] = $form_state['values'][$key];
  }
  return $submit;
}
