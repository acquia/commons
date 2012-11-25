<?php
/**
 * @file
 * commons_notify.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_notify_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'message-commons_notify_node_created-field_message_rendered_body'
  $field_instances['message-commons_notify_node_created-field_message_rendered_body'] = array(
    'bundle' => 'commons_notify_node_created',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '0',
      ),
      'message_notify_email_body' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '1',
      ),
      'message_notify_email_subject' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '3',
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_message_rendered_body',
    'label' => 'Body',
    'required' => FALSE,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => '4',
    ),
  );

  // Exported field_instance: 'message-commons_notify_node_created-field_message_rendered_subject'
  $field_instances['message-commons_notify_node_created-field_message_rendered_subject'] = array(
    'bundle' => 'commons_notify_node_created',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '2',
      ),
      'message_notify_email_body' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '3',
      ),
      'message_notify_email_subject' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '1',
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_message_rendered_subject',
    'label' => 'Subject',
    'required' => 0,
    'settings' => array(
      'text_processing' => '0',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => '255',
      ),
      'type' => 'text_textfield',
      'weight' => '3',
    ),
  );

  // Exported field_instance: 'message-commons_notify_node_created-field_target_nodes'
  $field_instances['message-commons_notify_node_created-field_target_nodes'] = array(
    'bundle' => 'commons_notify_node_created',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '3',
      ),
      'message_notify_email_body' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '4',
      ),
      'message_notify_email_subject' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '4',
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_target_nodes',
    'label' => 'Target nodes',
    'required' => 1,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => '60',
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => '2',
    ),
  );

  // Exported field_instance: 'message_type-message_type-message_text'
  $field_instances['message_type-message_type-message_text'] = array(
    'bundle' => 'message_type',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => 'This is the text of all messages of this type.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'message_type',
    'field_name' => 'message_text',
    'label' => 'Message text',
    'required' => TRUE,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('Message text');
  t('Subject');
  t('Target nodes');
  t('This is the text of all messages of this type.');

  return $field_instances;
}
