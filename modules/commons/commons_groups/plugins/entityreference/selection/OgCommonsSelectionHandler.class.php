<?php

/**
 * @file
 * OG Commons groups selection handler.
 */

class OgCommonsSelectionHandler extends OgSelectionHandler {

  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new self($field, $instance, $entity_type, $entity);
  }

  /**
   * Overrides OgSelectionHandler::buildEntityFieldQuery().
   */
  public function buildEntityFieldQuery($match = NULL, $match_operator = 'CONTAINS') {
    $group_type = $this->field['settings']['target_type'];

    if (empty($this->instance['field_mode']) || $group_type != 'node' || user_is_anonymous()) {
      return parent::buildEntityFieldQuery($match, $match_operator);
    }

    $handler = EntityReference_SelectionHandler_Generic::getInstance($this->field, $this->instance, $this->entity_type, $this->entity);
    $query = $handler->buildEntityFieldQuery($match, $match_operator);

    // Show only the entities that are active groups.
    $query->fieldCondition(OG_GROUP_FIELD, 'value', 1);
    $query->fieldCondition('field_og_subscribe_settings', 'value', 'anyone');

    // Add this property to make sure we will have the {node} table later on in
    // OgCommonsSelectionHandler::entityFieldQueryAlter().
    $query->propertyCondition('nid', 0, '>');

    $query->addMetaData('entityreference_selection_handler', $this);

    // FIXME: http://drupal.org/node/1325628
    unset($query->tags['node_access']);

    $query->addTag('entity_field_access');
    $query->addTag('og');

    return $query;
  }

  /**
   * Overrides OgSelectionHandler::entityFieldQueryAlter().
   *
   * Add the user's groups along with the rest of the "public" groups.
   */
  public function entityFieldQueryAlter(SelectQueryInterface $query) {
    $gids = og_get_entity_groups();
    if (empty($gids['node'])) {
      return;
    }

    $conditions = &$query->conditions();
    // Find the condition for the "field_data_field_privacy_settings" query, and
    // the one for the "node.nid", so we can later db_or() them.
    $public_condition = array();
    foreach ($conditions as $key => $condition) {
      if ($key !== '#conjunction' && is_string($condition['field'])) {
        if (strpos($condition['field'], 'field_data_field_og_subscribe_settings') === 0) {
          $public_condition = $condition;
          unset($conditions[$key]);
        }

        if ($condition['field'] === 'node.nid') {
          unset($conditions[$key]);
        }
      }
    }

    if (!$public_condition) {
      return;
    }

    $or = db_or();
    $or->condition($public_condition['field'], $public_condition['value'], $public_condition['operator']);
    $or->condition('node.nid', $gids['node'], 'IN');
    $query->condition($or);
  }
}
