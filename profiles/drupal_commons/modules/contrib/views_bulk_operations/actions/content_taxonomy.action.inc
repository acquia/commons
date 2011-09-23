<?php

function views_bulk_operations_content_taxonomy_action_info() {
  if (!module_exists('content_taxonomy')) return array();
  return array('views_bulk_operations_content_taxonomy_action' => array(
    'type' => 'node',
    'description' => t('Modify content taxonomy terms'),
    'configurable' => TRUE,
    'behavior' => array('changes_node_property'),
  ));
}

function views_bulk_operations_content_taxonomy_action(&$node, $context) {
  switch ($context['do']) {
    case TAXONOMY_ACTION_REPLACE:
      foreach ($context['fields'] as $field => $terms) {
        $node->{$field} = array();
      }
      // Wanted fallback on next case, replace: no terms + the new ones (no break; please)
    case TAXONOMY_ACTION_ADD:
      foreach ($context['fields'] as $field => $terms) {
        foreach ($terms as $value) {
          if (!is_array($node->{$field})) {
            $node->{$field} = array();
          }
          // If the term ID is already in the array, it does not make sense to re-add
          foreach ($node->{$field} as $already) {
            if ($already['value'] == $value['value']) {
              // Continues at next new term
              continue 2;
            }
          }
          $node->{$field}[] = $value;
        }
      }
      break;
    case TAXONOMY_ACTION_DELETE:
      foreach ($context['fields'] as $field => $terms) {
        if (!is_array($node->{$field})) {
          continue;
        }
        if (empty($node->{$field})) {
          continue;
        }
        foreach ($terms as $term) {
          foreach ($node->{$field} as $k => $already) {
            if ($already['value'] == $term['value']) {
              unset($node->{$field}[$k]);
            }
          }
          // Reset numerical IDs to make it continous
          $node->{$field} = array_values($node->{$field});
        }
      }
      break;
  }
}

function views_bulk_operations_content_taxonomy_action_form($context) {
  module_load_include('inc', 'content', 'includes/content.node_form');

  if (isset($context['selection']) && isset($context['view'])) {
    $fields = array();
    $nids = array_map('_views_bulk_operations_get_oid', $context['selection'], array_fill(0, count($context['selection']), $context['view']->base_field));
    $placeholders = db_placeholders($nids);
    $result = db_query("SELECT field_name, label, type FROM {node} n LEFT JOIN {content_node_field_instance} ci ON n.type=ci.type_name WHERE nid IN ($placeholders) AND widget_module LIKE 'content_taxonomy_%' GROUP BY field_name", implode(',', $nids));
    while ($f = db_fetch_object($result)) {
      $fields[$f->field_name] = array('label' => $f->label, 'type' => $f->type);
    }
  }
  if (empty($fields)) {
    drupal_set_message(t('The selected nodes do not have any Content Taxonomy fields. Please select other nodes and try again.'), 'error');
    return array();
  }
  $form['fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content Taxonomy fields'),
    '#tree' => TRUE,
  );
  $form_state = array();
  foreach ($fields as $field => $details) {
    $info = content_types($details['type']);
    $form['#node'] = new stdClass();
    $form['#node']->type = $details['type'];
    $form['#node']->{$field} = NULL;
    $form['#field_info'][$field] = $info['fields'][$field];
    $form['fields'] += (array)content_field_form($form, $form_state, $info['fields'][$field]);
    $form['fields'][$field]['#required'] = FALSE;
  }
  $form['do'] = array(
    '#type' => 'radios',
    '#title' => t('Action to take'),
    '#default_value' => isset($context['do']) ? $context['do'] : TAXONOMY_ACTION_ADD,
    '#options' => array(
      TAXONOMY_ACTION_ADD => t('Add the selected terms'),
      TAXONOMY_ACTION_REPLACE => t('Replace existing terms with selected ones'),
      TAXONOMY_ACTION_DELETE => t('Delete selected terms')
    ),
    '#required' => TRUE,
    '#weight' => -2,
  );
  return $form;
}

function views_bulk_operations_content_taxonomy_action_submit($form, $form_state) {
  return array(
    'do' => $form_state['values']['do'],
    'fields' => $form_state['values']['fields'],
  );
}
