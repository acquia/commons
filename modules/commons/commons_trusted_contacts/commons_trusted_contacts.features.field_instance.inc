<?php
/**
 * @file
 * commons_trusted_contacts.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_trusted_contacts_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'message-trusted_contact_request_approved-field_approving_user'
  $field_instances['message-trusted_contact_request_approved-field_approving_user'] = array(
    'bundle' => 'trusted_contact_request_approved',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
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
    'field_name' => 'field_approving_user',
    'label' => 'Approving user',
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
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'message-trusted_contact_request_pending-field_requesting_user'
  $field_instances['message-trusted_contact_request_pending-field_requesting_user'] = array(
    'bundle' => 'trusted_contact_request_pending',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
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
    'field_name' => 'field_requesting_user',
    'label' => 'Requesting User',
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
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'og_membership-trusted_contacts-field_confirmation'
  $field_instances['og_membership-trusted_contacts-field_confirmation'] = array(
    'bundle' => 'trusted_contacts',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'og_membership',
    'field_name' => 'field_confirmation',
    'label' => 'Confirmation',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'og_membership-trusted_contacts-field_membership_token'
  $field_instances['og_membership-trusted_contacts-field_membership_token'] = array(
    'bundle' => 'trusted_contacts',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'og_membership',
    'field_name' => 'field_membership_token',
    'label' => 'Membership Token',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'og_membership-trusted_contacts-field_my_request'
  $field_instances['og_membership-trusted_contacts-field_my_request'] = array(
    'bundle' => 'trusted_contacts',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'og_membership',
    'field_name' => 'field_my_request',
    'label' => 'My request',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'og_membership-trusted_contacts-field_original_og_membership'
  $field_instances['og_membership-trusted_contacts-field_original_og_membership'] = array(
    'bundle' => 'trusted_contacts',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'og_membership',
    'field_name' => 'field_original_og_membership',
    'label' => 'Original OG Membership',
    'required' => 0,
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
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'og_membership-trusted_contacts-field_response_date'
  $field_instances['og_membership-trusted_contacts-field_response_date'] = array(
    'bundle' => 'trusted_contacts',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'og_membership',
    'field_name' => 'field_response_date',
    'label' => 'Response date',
    'required' => 0,
    'settings' => array(
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'user-user-user_trusted_contacts'
  $field_instances['user-user-user_trusted_contacts'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'search_results' => array(
        'custom settings' => TRUE,
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 16,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'user_trusted_contacts',
    'label' => 'User Trusted Contacts',
    'required' => FALSE,
    'settings' => array(
      'behaviors' => array(
        'og_widget' => array(
          'admin' => array(
            'widget_type' => 'entityreference_autocomplete',
          ),
          'default' => array(
            'widget_type' => 'entityreference_autocomplete',
          ),
          'status' => TRUE,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'view modes' => array(
      'full' => array(
        'custom settings' => FALSE,
        'label' => 'hidden',
        'type' => 'hidden',
      ),
      'teaser' => array(
        'custom settings' => FALSE,
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
    'widget' => array(
      'module' => 'og',
      'settings' => array(),
      'type' => 'og_complex',
      'weight' => '2',
    ),
  );

  // Exported field_instance: 'user-user-group_group'
  $field_instances['user-user-group_group'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 1,
      ),
    ),
    'deleted' => '0',
    'description' => 'Determine if this is an OG group.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'commons_trusted_contacts',
        'settings' => array(
          'allowed_values' => array(
            0 => 'Not a group',
            1 => 'Group',
          ),
          'allowed_values_function' => '',
        ),
        'type' => 'trusted_contact',
        'weight' => '3',
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'display_label' => 1,
    'entity_type' => 'user',
    'field_name' => 'group_group',
    'label' => 'Group',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'view modes' => array(
      'full' => array(
        'custom settings' => FALSE,
        'label' => 'Full',
        'type' => 'og_group_subscribe',
      ),
      'teaser' => array(
        'custom settings' => FALSE,
        'label' => 'Teaser',
        'type' => 'og_group_subscribe',
      ),
    ),
    'widget' => array(
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
        'og_hide' => TRUE,
      ),
      'type' => 'options_onoff',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'user-user-group_access'
  $field_instances['user-user-group_access'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 13,
      ),
    ),
    'display_in_partial_form' => 0,
    'entity_type' => 'user',
    'field_name' => 'group_access',
    'label' => 'Group visibility',
    'required' => 1,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 13,
    ),
  );
  // Provide appropriate settings for our fields when users are
  // indexed by Solr. ApacheSolr_User uses the 'search_index' view mode
  // to render the user document for indexing. Since this view mode doesn't
  // exist in Commons, the 'default' view mode is used. We need to ensure
  // that this does not include the names of the user's trusted contacts, so
  // that a search for users named "Jane Smith" doesn't include a result for
  // each user who calls Jane a contact.
  if (module_exists('commons_search_solr_user')) {
    $field_instances['user-user-group_group']['view modes']['search_results'] = array(
      'label' => 'hidden',
      'module' => 'commons_trusted_contacts',
      'settings' => array(),
      'type' => 'trusted_contact',
    );
    $field_instances['user-user-group_group']['display']['search_results'] = array(
      'label' => 'hidden',
      'module' => 'commons_trusted_contacts',
      'settings' => array(
        'allowed_values' => array(
          0 => 'Not a group',
          1 => 'Group',
        ),
        'allowed_values_function' => '',
      ),
      'type' => 'trusted_contact',
      'weight' => 17,
    );
    $field_instances['user-user-user_trusted_contacts']['display']['search_results'] = array(
      'label' => 'hidden',
      'custom settings' => TRUE,
      'type' => 'hidden',
      'weight' => 16,
    );
  }

  if ($group_content_entity_types = commons_groups_get_group_content_entity_types(FALSE)) {
    foreach (array_keys($group_content_entity_types['node']) as $type) {
      commons_trusted_contacts_field_definition_group($field_instances, 'node', $type);
    }
  }

  // Translatables
  // Included for use with string extractors like potx.
  t('Approving user');
  t('Confirmation');
  t('Membership Token');
  t('My request');
  t('Original OG Membership');
  t('Requesting User');
  t('Response date');
  t('User Trusted Contacts');

  return $field_instances;
}

function commons_trusted_contacts_field_definition_group(&$field_instances, $entity_type, $bundle) {
  // Exported field_instance: 'node-post-og_user_group_ref'
  $field_instances["$entity_type-$bundle-og_user_group_ref"] = array(
    'bundle' => $bundle,
    'default_value' => NULL,
    'default_value_function' => 'commons_groups_entityreference_default_value',
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'og_ui',
        'settings' => array(),
        'type' => 'og_list_default',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => $entity_type,
    'field_name' => 'og_user_group_ref',
    'label' => 'Visible to trusted contacts of',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'og_widget' => array(
          'admin' => array(
            'widget_type' => 'entityreference_autocomplete_tags',
          ),
          'default' => array(
            'widget_type' => 'entityreference_autocomplete_tags',
          ),
          'status' => TRUE,
        ),
        'prepopulate' => array(
          'status' => 0,
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
      'active' => 0,
      'module' => 'og',
      'settings' => array(),
      'type' => 'og_complex',
      'weight' => 5,
    ),
  );

}
