<?php

/**
 * @file
 * Hooks provided by the Commons module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Define entity integrations.
 *
 * This hook allows modules to register entity types and/or bundles that they
 * provide for integration with Commons functionality. For example, a webform
 * module could use it to register a form entity type and its "Test", "Survey"
 * and "Suggestion" bundles.
 *
 * @return
 *   An associative array of entity integrations whose keys define the entity
 *   type for each integration and whose values contain the bundles which have
 *   been integrated. Each bundle is itself an associative array, whose keys
 *   define the type of integration to enable and whose values contain the
 *   status of the integration. TRUE = enabled, FALSE = disabled.
 *
 * For a detailed usage example, see commons_q_a.module.
 *
 * @see hook_commons_entity_integration_alter()
 */
function hook_commons_entity_integration() {
  // Register three of the webform entity's bundles for various integrations.
  return array(
    'webform' => array(
      'test' => array(
        'exclude_rate' => TRUE,
        'is_group_content' => FALSE,
      ),
      'survey' => array(
        'is_group_content' => TRUE,
        'exclude_topics' => TRUE,
      ),
      'suggestion' => array(
        'media' => TRUE,
        'is_group_content' => TRUE,
        'exclude_commons_follow' => TRUE,
      ),
    ),
    'node' => array(
      'group' => array(
        'is_group_content' => FALSE,
        'is_group' => TRUE,
        'exclude_commons_follow' => TRUE,
      ),
    ),
  );
}

/**
 * Perform alterations on entity integrations.
 *
 * @param $integrations
 *   An associative array of entity integrations whose keys define the entity
 *   type for each integration and whose values contain the bundles which have
 *   been integrated. Each bundle is itself an associative array, whose keys
 *   define the type of integration to enable and whose values contain the
 *   status of the integration. TRUE = enabled, FALSE = disabled.
 *
 * @see hook_commons_entity_integration()
 */
function hook_commons_entity_integration_alter(&$integrations) {
  // Disable Media integration for the post content type.
  $integrations['node']['post']['media'] = FALSE;
}

/**
 * @} End of "addtogroup hooks".
 */
