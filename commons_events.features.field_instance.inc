<?php
/**
 * @file
 * commons_events.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_events_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-event-body'
  $field_instances['node-event-body'] = array(
    'bundle' => 'event',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => '5',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => '3',
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Description',
    'required' => 1,
    'settings' => array(
      'display_summary' => FALSE,
      'text_processing' => '1',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => '20',
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => '1',
    ),
  );

  // Exported field_instance: 'node-event-field_address'
  $field_instances['node-event-field_address'] = array(
    'bundle' => 'event',
    'default_value' => array(
      0 => array(
        'element_key' => 'node|event|field_address|und|0',
        'thoroughfare' => '',
        'premise' => '',
        'locality' => '',
        'administrative_area' => '',
        'postal_code' => '',
        'country' => 'US',
      ),
    ),
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => '2',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address'
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => '2',
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_address',
    'label' => 'Address',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield',
      'settings' => array(
        'available_countries' => array(),
        'format_handlers' => array(
          'address' => 'address',
          'address-hide-country' => 0,
          'organisation' => 0,
          'name-full' => 0,
          'name-oneline' => 0,
        ),
      ),
      'type' => 'addressfield_standard',
      'weight' => '8',
    ),
  );

  // Exported field_instance: 'node-event-field_date'
  $field_instances['node-event-field_date'] = array(
    'bundle' => 'event',
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'event_datetime',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
        'weight' => '1',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'event_datetime',
          'fromto' => 'both',
        ),
        'type' => 'date_default',
        'weight' => '1',
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_date',
    'label' => 'Date',
    'required' => 1,
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
        'input_format_custom' => 'd M Y - h:i:s a',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => '5',
    ),
  );

  // Exported field_instance: 'node-event-field_location'
  $field_instances['node-event-field_location'] = array(
    'bundle' => 'event',
    'default_value' => array(
      0 => array(
        'value' => 'online_physical',
      ),
    ),
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '9',
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '0',
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_location',
    'label' => 'Location',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => '7',
    ),
  );

  // Exported field_instance: 'node-event-field_logo'
  $field_instances['node-event-field_logo'] = array(
    'bundle' => 'event',
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '50x50',
        ),
        'type' => 'image',
        'weight' => '0',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_style' => '50x50',
        ),
        'type' => 'image',
        'weight' => '0',
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_logo',
    'label' => 'Event logo',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '2 MB',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => '50x50',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => '9',
    ),
  );

  // Exported field_instance: 'node-event-field_number_of_attendees'
  $field_instances['node-event-field_number_of_attendees'] = array(
    'bundle' => 'event',
    'default_value' => array(
      0 => array(
        'value' => '0',
      ),
    ),
    'deleted' => '0',
    'description' => 'Enter 0 for unlimited',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '8',
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_number_of_attendees',
    'label' => 'Maximum number of attendees',
    'required' => 1,
    'settings' => array(
      'max' => '',
      'min' => '0',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => '12',
    ),
  );

  // Exported field_instance: 'node-event-field_offsite_url'
  $field_instances['node-event-field_offsite_url'] = array(
    'bundle' => 'event',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => '4',
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_offsite_url',
    'label' => 'URL',
    'required' => 0,
    'settings' => array(
      'text_processing' => '0',
      'user_register_form' => FALSE,
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

  // Exported field_instance: 'node-event-field_organizers'
  $field_instances['node-event-field_organizers'] = array(
    'bundle' => 'event',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'hidden',
        'weight' => 12,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_organizers',
    'label' => 'Organizers',
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
      'type' => 'entityreference_autocomplete_tags',
      'weight' => '2',
    ),
  );

  // Exported field_instance: 'node-event-field_registration'
  $field_instances['node-event-field_registration'] = array(
    'bundle' => 'event',
    'default_value' => array(
      0 => array(
        'registration_type' => 'event',
      ),
    ),
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '10',
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_registration',
    'label' => 'Registration',
    'required' => 0,
    'settings' => array(
      'default_registration_settings' => array(
        'capacity' => '0',
        'reminder' => array(
          'reminder_settings' => array(
            'reminder_date' => '',
            'reminder_template' => '',
          ),
          'send_reminder' => 0,
        ),
        'scheduling' => array(
          'close' => '',
          'open' => '',
        ),
        'settings' => array(
          'from_address' => 'admin@example.com',
          'multiple_registrations' => 0,
        ),
        'status' => 1,
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'registration',
      'settings' => array(),
      'type' => 'registration_select',
      'weight' => '10',
    ),
  );

  // Exported field_instance: 'node-event-field_registration_type'
  $field_instances['node-event-field_registration_type'] = array(
    'bundle' => 'event',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '11',
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_registration_type',
    'label' => 'Registration type',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => '11',
    ),
  );

  // Exported field_instance: 'node-event-field_topics'
  $field_instances['node-event-field_topics'] = array(
    'bundle' => 'event',
    'default_value' => NULL,
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => '6',
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_topics',
    'label' => 'Topics',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => '13',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Address');
  t('Date');
  t('Description');
  t('Enter 0 for unlimited');
  t('Event logo');
  t('Location');
  t('Maximum number of attendees');
  t('Organizers');
  t('Registration');
  t('Registration type');
  t('URL');

  return $field_instances;
}
