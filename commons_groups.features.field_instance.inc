<?php
/**
 * @file
 * commons_groups.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_groups_field_default_field_instances() {
  // Get a list of content types that should have the og_groups_ref field added.
  // Modules can alter this list by implementing hook_strongarm_alter().
  $commons_groups_entity_types = variable_get('commons_groups_entity_types', array());
  if (!empty($commons_groups_entity_types['node'])) {
    $field_instances = array();
    foreach($commons_groups_entity_types['node'] as $key => $type) {
      commons_groups_field_definition($field_instances, $type);
    }
    return $field_instances;  
  }
}

function commons_groups_field_definition(&$field_instances, $type) {
 // Exported field_instance: 'node-post-og_group_ref'
  $field_instances['node-post-og_group_ref'] = array(
    'bundle' => 'post',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'og_ui',
        'settings' => array(),
        'type' => 'og_list_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'og_group_ref',
    'label' => 'Groups audience',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'disable',
          'fallback' => 'none',
          'skip_perm' => 'administer blocks',
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'view modes' => array(
      'full' => array(
        'custom settings' => FALSE,
        'label' => 'Full',
        'type' => 'og_list_default',
      ),
      'teaser' => array(
        'custom settings' => FALSE,
        'label' => 'Teaser',
        'type' => 'og_list_default',
      ),
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => '60',
      ),
      'type' => 'entityreference_autocomplete_tags',
      'weight' => '0',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Groups audience');
}