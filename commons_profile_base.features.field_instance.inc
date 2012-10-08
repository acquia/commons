<?php
/**
 * @file
 * commons_profile_base.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_profile_base_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_bio'
  $field_instances['user-user-field_bio'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_bio',
    'label' => 'Bio',
    'required' => 0,
    'settings' => array(
      'text_processing' => '0',
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => '5',
      ),
      'type' => 'text_textarea',
      'weight' => '5',
    ),
  );

  // Exported field_instance: 'user-user-field_name_first'
  $field_instances['user-user-field_name_first'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_name_first',
    'label' => 'First Name',
    'required' => 0,
    'settings' => array(
      'text_processing' => '0',
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => '60',
      ),
      'type' => 'text_textfield',
      'weight' => '3',
    ),
  );

  // Exported field_instance: 'user-user-field_name_last'
  $field_instances['user-user-field_name_last'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_name_last',
    'label' => 'Last Name',
    'required' => 0,
    'settings' => array(
      'text_processing' => '0',
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => '60',
      ),
      'type' => 'text_textfield',
      'weight' => '4',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Bio');
  t('First Name');
  t('Last Name');

  return $field_instances;
}
