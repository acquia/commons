<?php
/**
 * @file
 * commons_follow_user.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_follow_user_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'message-commons_follow_user_user_followed-field_target_users'
  $field_instances['message-commons_follow_user_user_followed-field_target_users'] = array(
    'bundle' => 'commons_follow_user_user_followed',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'message_notify_email_body' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'message_notify_email_subject' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_target_users',
    'label' => 'Target users',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Target users');

  return $field_instances;
}
