<?php

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _commons_core_content_default_fields() {
  $fields = array();

  // Exported field: field_featured_content
  $fields[] = array(
    'field_name' => 'field_featured_content',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => '1',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Featured
Featured',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Featured',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Featured Content',
      'weight' => '1',
      'description' => 'Marking a content item of featured will show the content item in the main \'Featured Content\' section.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_group_sticky
  $fields[] = array(
    'field_name' => 'field_group_sticky',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => 0,
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Sticky
Sticky',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Sticky',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Group Sticky',
      'weight' => 0,
      'description' => 'If you\'re a <strong>group owner</strong> you have the option to check this to make the content item "Sticky". Sticky items remain at the top of content lists so users can see them more easily. If this post is not a group post, this will be ignored.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_featured_content
  $fields[] = array(
    'field_name' => 'field_featured_content',
    'type_name' => 'discussion',
    'display_settings' => array(
      'weight' => '6',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Featured
Featured',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Featured',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Featured Content',
      'weight' => '6',
      'description' => 'Marking a content item of featured will show the content item in the main \'Featured Content\' section.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_group_sticky
  $fields[] = array(
    'field_name' => 'field_group_sticky',
    'type_name' => 'discussion',
    'display_settings' => array(
      'weight' => '5',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Sticky
Sticky',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Sticky',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Group Sticky',
      'weight' => '5',
      'description' => 'If you\'re a <strong>group owner</strong> you have the option to check this to make the content item "Sticky". Sticky items remain at the top of content lists so users can see them more easily. If this post is not a group post, this will be ignored.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_featured_content
  $fields[] = array(
    'field_name' => 'field_featured_content',
    'type_name' => 'document',
    'display_settings' => array(
      'weight' => '7',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Featured
Featured',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Featured',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Featured Content',
      'weight' => '7',
      'description' => 'Marking a content item of featured will show the content item in the main \'Featured Content\' section.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_file
  $fields[] = array(
    'field_name' => 'field_file',
    'type_name' => 'document',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '1',
    'multiple' => '1',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '1',
    'list_default' => 1,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => '',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'label' => 'Files',
      'weight' => '-2',
      'description' => '',
      'type' => 'filefield_widget',
      'module' => 'filefield',
    ),
  );

  // Exported field: field_group_sticky
  $fields[] = array(
    'field_name' => 'field_group_sticky',
    'type_name' => 'document',
    'display_settings' => array(
      'weight' => '6',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Sticky
Sticky',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Sticky',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Group Sticky',
      'weight' => '6',
      'description' => 'If you\'re a <strong>group owner</strong> you have the option to check this to make the content item "Sticky". Sticky items remain at the top of content lists so users can see them more easily. If this post is not a group post, this will be ignored.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_date
  $fields[] = array(
    'field_name' => 'field_date',
    'type_name' => 'event',
    'display_settings' => array(
      'weight' => '-1',
      'parent' => 'group_event_details',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'date',
    'required' => '1',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
      'hour' => 'hour',
      'minute' => 'minute',
    ),
    'timezone_db' => 'UTC',
    'tz_handling' => 'user',
    'todate' => 'optional',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'long',
    'widget' => array(
      'default_value' => 'blank',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'l, F j, Y - g:ia',
      'input_format_custom' => '',
      'increment' => '1',
      'text_parts' => array(),
      'year_range' => '-3:+3',
      'label_position' => 'above',
      'label' => 'Date',
      'weight' => '-1',
      'description' => '',
      'type' => 'date_popup',
      'module' => 'date',
    ),
  );

  // Exported field: field_featured_content
  $fields[] = array(
    'field_name' => 'field_featured_content',
    'type_name' => 'event',
    'display_settings' => array(
      'weight' => '7',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Featured
Featured',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Featured',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Featured Content',
      'weight' => '7',
      'description' => 'Marking a content item of featured will show the content item in the main \'Featured Content\' section.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_group_sticky
  $fields[] = array(
    'field_name' => 'field_group_sticky',
    'type_name' => 'event',
    'display_settings' => array(
      'weight' => '6',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Sticky
Sticky',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Sticky',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Group Sticky',
      'weight' => '6',
      'description' => 'If you\'re a <strong>group owner</strong> you have the option to check this to make the content item "Sticky". Sticky items remain at the top of content lists so users can see them more easily. If this post is not a group post, this will be ignored.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_location
  $fields[] = array(
    'field_name' => 'field_location',
    'type_name' => 'event',
    'display_settings' => array(
      'weight' => 0,
      'parent' => 'group_event_details',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_location][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Location',
      'weight' => 0,
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_featured_group
  $fields[] = array(
    'field_name' => 'field_featured_group',
    'type_name' => 'group',
    'display_settings' => array(
      'weight' => '4',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'editable',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Featured
Featured',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Featured',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Featured Group',
      'weight' => '4',
      'description' => 'Checking this option will make this a Featured Group. Featured Group\'s get special placement on the home page. This should only be used for groups with a special purpose.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_group_image
  $fields[] = array(
    'field_name' => 'field_group_image',
    'type_name' => 'group',
    'display_settings' => array(
      'weight' => '5',
      'parent' => 'group_attributes',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'group_images_default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'group_images_default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => 'group_images',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '0',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => array(
        'filename' => 'default-group.png',
        'filepath' => 'sites/default/files/imagefield_default_images/default-group.png',
        'filemime' => 'image/png',
        'source' => 'default_image_upload',
        'destination' => 'sites/default/files/imagefield_default_images/default-group.png',
        'filesize' => 3968,
        'uid' => '1',
        'status' => 1,
        'timestamp' => 1271175525,
        'fid' => '1',
      ),
      'use_default_image' => 1,
      'label' => 'Image',
      'weight' => '5',
      'description' => 'Specify an image to act as the group icon or avatar.',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_grouplink
  $fields[] = array(
    'field_name' => 'field_grouplink',
    'type_name' => 'group',
    'display_settings' => array(
      'weight' => '4',
      'parent' => 'group_attributes',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'link',
    'required' => '0',
    'multiple' => '1',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => '_blank',
      'rel' => '',
      'class' => '',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'optional',
    'title_value' => '',
    'enable_tokens' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'title' => '',
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Links',
      'weight' => '6',
      'description' => '',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Exported field: field_featured_content
  $fields[] = array(
    'field_name' => 'field_featured_content',
    'type_name' => 'poll',
    'display_settings' => array(
      'weight' => 0,
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'editable',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Featured
Featured',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Featured',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Featured Content',
      'weight' => 0,
      'description' => 'Marking a content item of featured will show the content item in the main \'Featured Content\' section.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_featured_content
  $fields[] = array(
    'field_name' => 'field_featured_content',
    'type_name' => 'wiki',
    'display_settings' => array(
      'weight' => '6',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Featured
Featured',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Featured',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Featured Content',
      'weight' => '6',
      'description' => 'Marking a content item of featured will show the content item in the main \'Featured Content\' section.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_group_sticky
  $fields[] = array(
    'field_name' => 'field_group_sticky',
    'type_name' => 'wiki',
    'display_settings' => array(
      'weight' => '5',
      'parent' => 'group_promote_content',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'editable',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Not Sticky
Sticky',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'Not Sticky',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Group Sticky',
      'weight' => '5',
      'description' => 'If you\'re a <strong>group owner</strong> you have the option to check this to make the content item "Sticky". Sticky items remain at the top of content lists so users can see them more easily. If this post is not a group post, this will be ignored.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Translatables
  array(
    t('Date'),
    t('Featured Content'),
    t('Featured Group'),
    t('Files'),
    t('Group Sticky'),
    t('Image'),
    t('Links'),
    t('Location'),
  );

  return $fields;
}

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _commons_core_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'context_ui',
    'attribute' => 'content',
    'value' => 'global_content',
    'description' => 'Site-wide content pages',
    'path' => array(
      'content/*' => 'content/*',
    ),
    'block' => array(
      'views_tag_cloud-block_1' => array(
        'module' => 'views',
        'delta' => 'tag_cloud-block_1',
        'weight' => 42,
        'region' => 'right',
        'status' => '0',
        'label' => 'Popular Tags',
        'type' => 'context_ui',
      ),
      'views_most_active_users-block_1' => array(
        'module' => 'views',
        'delta' => 'most_active_users-block_1',
        'weight' => 43,
        'region' => 'right',
        'status' => '0',
        'label' => 'Most Active Users',
        'type' => 'context_ui',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'context_ui',
    'attribute' => 'dashboard',
    'value' => 'dashboard',
    'description' => 'User Dashboard',
    'path' => array(
      'dashboard' => 'dashboard',
    ),
    'block' => array(
      'views_og_dashboard_groups-block_1' => array(
        'module' => 'views',
        'delta' => 'og_dashboard_groups-block_1',
        'weight' => -45,
        'region' => 'left',
        'status' => '0',
        'label' => 'My Groups (custom)',
        'type' => 'context_ui',
      ),
      'views_my_recent_items-block_1' => array(
        'module' => 'views',
        'delta' => 'my_recent_items-block_1',
        'weight' => -44,
        'region' => 'left',
        'status' => '0',
        'label' => 'My Recent Items',
        'type' => 'context_ui',
      ),
      'views_og_dashboard_groups-block_2' => array(
        'module' => 'views',
        'delta' => 'og_dashboard_groups-block_2',
        'weight' => -43,
        'region' => 'left',
        'status' => '0',
        'label' => 'New Groups (custom)',
        'type' => 'context_ui',
      ),
      'user_relationship_blocks_user-1' => array(
        'module' => 'user_relationship_blocks',
        'delta' => 'user-1',
        'weight' => -42,
        'region' => 'left',
        'status' => '0',
        'label' => 'User Relationships: Friends ',
        'type' => 'context_ui',
      ),
      'views_most_active_users-block_1' => array(
        'module' => 'views',
        'delta' => 'most_active_users-block_1',
        'weight' => -41,
        'region' => 'left',
        'status' => '0',
        'label' => 'Most Active Users',
        'type' => 'context_ui',
      ),
      'views_recent_notices-block_1' => array(
        'module' => 'views',
        'delta' => 'recent_notices-block_1',
        'weight' => -44,
        'region' => 'right',
        'status' => '0',
        'label' => 'Recent Notices',
        'type' => 'context_ui',
      ),
      'views_upcoming_events-block_1' => array(
        'module' => 'views',
        'delta' => 'upcoming_events-block_1',
        'weight' => -43,
        'region' => 'right',
        'status' => '0',
        'label' => 'Upcoming Events (Global)',
        'type' => 'context_ui',
      ),
      'views_og_featured-block_1' => array(
        'module' => 'views',
        'delta' => 'og_featured-block_1',
        'weight' => -42,
        'region' => 'right',
        'status' => '0',
        'label' => 'Featured Groups',
        'type' => 'context_ui',
      ),
      'views_recent_featured-block_1' => array(
        'module' => 'views',
        'delta' => 'recent_featured-block_1',
        'weight' => -41,
        'region' => 'right',
        'status' => '0',
        'label' => 'Recent Featured Content',
        'type' => 'context_ui',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'context_ui',
    'attribute' => 'global',
    'value' => 'global',
    'description' => 'Show on every page',
    'sitewide' => '1',
    'block' => array(
      'views_user_meta-block_1' => array(
        'module' => 'views',
        'delta' => 'user_meta-block_1',
        'weight' => 40,
        'region' => 'header',
        'status' => '0',
        'label' => 'User Meta Info',
        'type' => 'context_ui',
      ),
      'user_1' => array(
        'module' => 'user',
        'delta' => '1',
        'weight' => 60,
        'region' => 'right',
        'status' => '0',
        'label' => 'Navigation',
        'type' => 'context_ui',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'context_ui',
    'attribute' => 'group',
    'value' => 'group',
    'description' => 'Show on group context',
    'og' => array(
      '0' => 1,
    ),
    'block' => array(
      'og_views_0' => array(
        'module' => 'og_views',
        'delta' => '0',
        'weight' => 43,
        'region' => 'right',
        'status' => '0',
        'label' => 'Group search',
        'type' => 'context_ui',
      ),
      'og_0' => array(
        'module' => 'og',
        'delta' => '0',
        'weight' => 44,
        'region' => 'right',
        'status' => '0',
        'label' => 'Group details',
        'type' => 'context_ui',
      ),
      'views_og_upcoming_events-block_1' => array(
        'module' => 'views',
        'delta' => 'og_upcoming_events-block_1',
        'weight' => 45,
        'region' => 'right',
        'status' => '0',
        'label' => 'Upcoming Events (Group)',
        'type' => 'context_ui',
      ),
      'views_og_members_custom_block-block_1' => array(
        'module' => 'views',
        'delta' => 'og_members_custom_block-block_1',
        'weight' => 46,
        'region' => 'right',
        'status' => '0',
        'label' => 'Group members',
        'type' => 'context_ui',
      ),
      'views_og_members_custom_block-block' => array(
        'module' => 'views',
        'delta' => 'og_members_custom_block-block',
        'weight' => 47,
        'region' => 'right',
        'status' => '0',
        'label' => 'Group admins',
        'type' => 'context_ui',
      ),
      'og_aggregator_0' => array(
        'module' => 'og_aggregator',
        'delta' => '0',
        'weight' => 48,
        'region' => 'right',
        'status' => '0',
        'label' => 'Group aggregator',
        'type' => 'context_ui',
      ),
      'views_og_recent_poll-block_1' => array(
        'module' => 'views',
        'delta' => 'og_recent_poll-block_1',
        'weight' => 49,
        'region' => 'right',
        'status' => '0',
        'label' => 'Latest Group Poll',
        'type' => 'context_ui',
      ),
      'views_og_tag_cloud-block_1' => array(
        'module' => 'views',
        'delta' => 'og_tag_cloud-block_1',
        'weight' => 50,
        'region' => 'right',
        'status' => '0',
        'label' => 'Group Content Tag Cloud',
        'type' => 'context_ui',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'context_ui',
    'attribute' => 'profile',
    'value' => 'profile',
    'description' => 'User Profile',
    'user' => array(
      '0' => 2,
    ),
    'block' => array(
      'user_relationship_blocks_actions' => array(
        'module' => 'user_relationship_blocks',
        'delta' => 'actions',
        'weight' => -43,
        'region' => 'right',
        'status' => '0',
        'label' => 'User Relationships: Actions',
        'type' => 'context_ui',
      ),
      'views_og_profile_user_groups-block_1' => array(
        'module' => 'views',
        'delta' => 'og_profile_user_groups-block_1',
        'weight' => -42,
        'region' => 'right',
        'status' => '0',
        'label' => 'User Being Viewed\'s Groups',
        'type' => 'context_ui',
      ),
      'user_relationship_blocks_user-1' => array(
        'module' => 'user_relationship_blocks',
        'delta' => 'user-1',
        'weight' => -41,
        'region' => 'right',
        'status' => '0',
        'label' => 'User Relationships: Friends ',
        'type' => 'context_ui',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'context_ui',
    'attribute' => 'users',
    'value' => 'user_browser',
    'description' => 'User Browser',
    'views' => array(
      '0' => 'user_directory',
    ),
    'block' => array(
      'commons_0' => array(
        'module' => 'commons',
        'delta' => '0',
        'weight' => -45,
        'region' => 'right',
        'status' => '0',
        'label' => 'User Statistics',
        'type' => 'context_ui',
      ),
      'user_3' => array(
        'module' => 'user',
        'delta' => '3',
        'weight' => -44,
        'region' => 'right',
        'status' => '0',
        'label' => 'Who\'s online',
        'type' => 'context_ui',
      ),
      'views_most_active_users-block_1' => array(
        'module' => 'views',
        'delta' => 'most_active_users-block_1',
        'weight' => -43,
        'region' => 'right',
        'status' => '0',
        'label' => 'Most Active Users',
        'type' => 'context_ui',
      ),
      'views_newest_users-block_1' => array(
        'module' => 'views',
        'delta' => 'newest_users-block_1',
        'weight' => -42,
        'region' => 'right',
        'status' => '0',
        'label' => 'Newest Users',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _commons_core_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => 1);
  }
  else if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => 1);
  }
  else if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_fieldgroup_default_groups().
 */
function _commons_core_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_promote_content
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'blog',
    'group_name' => 'group_promote_content',
    'label' => 'Promote Content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '0',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset_collapsed',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '0',
    'fields' => array(
      '0' => 'field_group_sticky',
      '1' => 'field_featured_content',
    ),
  );

  // Exported group: group_promote_content
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'discussion',
    'group_name' => 'group_promote_content',
    'label' => 'Promote Content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '0',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset_collapsed',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '0',
    'fields' => array(
      '0' => 'field_group_sticky',
      '1' => 'field_featured_content',
    ),
  );

  // Exported group: group_promote_content
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'document',
    'group_name' => 'group_promote_content',
    'label' => 'Promote Content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '1',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset_collapsed',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '1',
    'fields' => array(
      '0' => 'field_group_sticky',
      '1' => 'field_featured_content',
    ),
  );

  // Exported group: group_event_details
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'event',
    'group_name' => 'group_event_details',
    'label' => 'Event Details',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '-2',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '-2',
    'fields' => array(
      '0' => 'field_date',
      '1' => 'field_location',
    ),
  );

  // Exported group: group_promote_content
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'event',
    'group_name' => 'group_promote_content',
    'label' => 'Promote Content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '1',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset_collapsed',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '1',
    'fields' => array(
      '0' => 'field_group_sticky',
      '1' => 'field_featured_content',
    ),
  );

  // Exported group: group_attributes
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'group',
    'group_name' => 'group_attributes',
    'label' => 'Group Attributes',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '-2',
        'label' => 'hidden',
        'teaser' => array(
          'format' => 'simple',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'simple',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '-2',
    'fields' => array(
      '0' => 'field_group_image',
      '1' => 'field_grouplink',
    ),
  );

  // Exported group: group_promote_content
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'group',
    'group_name' => 'group_promote_content',
    'label' => 'Promote Group',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '3',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset_collapsed',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset_collapsed',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '3',
    'fields' => array(
      '0' => 'field_featured_group',
    ),
  );

  // Exported group: group_promote_content
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'poll',
    'group_name' => 'group_promote_content',
    'label' => 'Promote Content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '-1',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset_collapsed',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset_collapsed',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '-1',
    'fields' => array(
      '0' => 'field_featured_content',
    ),
  );

  // Exported group: group_promote_content
  $groups[] = array(
    'group_type' => 'standard',
    'type_name' => 'wiki',
    'group_name' => 'group_promote_content',
    'label' => 'Promote Content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '0',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset_collapsed',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '0',
    'fields' => array(
      '0' => 'field_group_sticky',
      '1' => 'field_featured_content',
    ),
  );

  // Translatables
  array(
    t('Event Details'),
    t('Group Attributes'),
    t('Promote Content'),
    t('Promote Group'),
  );

  return $groups;
}

/**
 * Helper to implementation of hook_imagecache_default_presets().
 */
function _commons_core_imagecache_default_presets() {
  $items = array(
    'group_images' => array(
      'presetname' => 'group_images',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '75',
            'height' => '75',
          ),
        ),
      ),
    ),
    'group_images_thumb' => array(
      'presetname' => 'group_images_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '24',
            'height' => '24',
          ),
        ),
      ),
    ),
    'profile_pictures' => array(
      'presetname' => 'profile_pictures',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '150',
            'height' => '150',
          ),
        ),
      ),
    ),
    'user_picture_meta' => array(
      'presetname' => 'user_picture_meta',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '24',
            'height' => '24',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_default_page_manager_handlers().
 */
function _commons_core_default_page_manager_handlers() {
  $export = array();
  $handler = new stdClass;
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Group Homepage',
    'no_blocks' => FALSE,
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        '0' => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'group' => 'group',
            ),
          ),
          'context' => 'argument_nid_1',
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display;
  $display->layout = 'twocol_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array();
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass;
    $pane->pid = 'new-1';
    $pane->panel = 'bottom';
    $pane->type = 'block';
    $pane->subtype = 'heartbeat-ogheartbeat';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Recent Group Activity',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-1'] = $pane;
    $display->panels['bottom'][0] = 'new-1';
    $pane = new stdClass;
    $pane->pid = 'new-2';
    $pane->panel = 'bottom';
    $pane->type = 'views';
    $pane->subtype = 'og_content_tracker';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '10',
      'pager_id' => '',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $display->content['new-2'] = $pane;
    $display->panels['bottom'][1] = 'new-2';
    $pane = new stdClass;
    $pane->pid = 'new-3';
    $pane->panel = 'left';
    $pane->type = 'node_content';
    $pane->subtype = 'node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'links' => 0,
      'page' => 1,
      'no_extras' => 0,
      'override_title' => 1,
      'override_title_text' => '',
      'teaser' => 0,
      'identifier' => '',
      'link' => 0,
      'leave_node_title' => 0,
      'context' => 'argument_nid_1',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-3'] = $pane;
    $display->panels['left'][0] = 'new-3';
    $pane = new stdClass;
    $pane->pid = 'new-4';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'shoutbox-0';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'style' => 'block',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-4'] = $pane;
    $display->panels['right'][0] = 'new-4';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;

  $export['node_view_panel_context'] = $handler;
  $handler = new stdClass;
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view_panel_context';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'User Profile',
    'no_blocks' => FALSE,
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display;
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array();
  $display->cache = array();
  $display->title = '%user:user\'s Profile';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass;
    $pane->pid = 'new-1';
    $pane->panel = 'middle';
    $pane->type = 'user_profile';
    $pane->subtype = 'user_profile';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_uid_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-1'] = $pane;
    $display->panels['middle'][0] = 'new-1';
    $pane = new stdClass;
    $pane->pid = 'new-2';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'heartbeat-privateheartbeat';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Recent Activity',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $display->content['new-2'] = $pane;
    $display->panels['middle'][1] = 'new-2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-1';
  $handler->conf['display'] = $display;

  $export['user_view_panel_context'] = $handler;
  return $export;
}

/**
 * Helper to implementation of hook_default_page_manager_pages().
 */
function _commons_core_default_page_manager_pages() {
  $page = new stdClass;
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'homepage';
  $page->task = 'page';
  $page->admin_title = 'Homepage';
  $page->admin_description = 'A 2-variant panel page that acts as a homepage for both anonymous and authenticated users.';
  $page->path = 'home';
  $page->access = array(
    'plugins' => array(),
    'logic' => 'and',
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Home',
    'name' => 'primary-links',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array();
  $page->default_handlers = array();
  $handler = new stdClass;
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_homepage_panel_context_2';
  $handler->task = 'page';
  $handler->subtask = 'homepage';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Home',
    'no_blocks' => 1,
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
  );
  $display = new panels_display;
  $display->layout = 'threecol_33_34_33_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array();
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass;
    $pane->pid = 'new-1';
    $pane->panel = 'bottom';
    $pane->type = 'views_panes';
    $pane->subtype = 'home_featured_blogs-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-1'] = $pane;
    $display->panels['bottom'][0] = 'new-1';
    $pane = new stdClass;
    $pane->pid = 'new-2';
    $pane->panel = 'bottom';
    $pane->type = 'views';
    $pane->subtype = 'tag_cloud';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $display->content['new-2'] = $pane;
    $display->panels['bottom'][1] = 'new-2';
    $pane = new stdClass;
    $pane->pid = 'new-3';
    $pane->panel = 'left';
    $pane->type = 'block';
    $pane->subtype = 'shoutbox-0';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'homepage-middle',
    );
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-3'] = $pane;
    $display->panels['left'][0] = 'new-3';
    $pane = new stdClass;
    $pane->pid = 'new-4';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'home_newest_users';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'homepage-middle',
    );
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-4'] = $pane;
    $display->panels['middle'][0] = 'new-4';
    $pane = new stdClass;
    $pane->pid = 'new-5';
    $pane->panel = 'right';
    $pane->type = 'views';
    $pane->subtype = 'og_dashboard_groups';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_2',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'homepage-middle',
    );
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-5'] = $pane;
    $display->panels['right'][0] = 'new-5';
    $pane = new stdClass;
    $pane->pid = 'new-6';
    $pane->panel = 'top';
    $pane->type = 'views_panes';
    $pane->subtype = 'home_featured_event-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-6'] = $pane;
    $display->panels['top'][0] = 'new-6';
    $pane = new stdClass;
    $pane->pid = 'new-7';
    $pane->panel = 'top';
    $pane->type = 'views_panes';
    $pane->subtype = 'home_recent_notice-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $display->content['new-7'] = $pane;
    $display->panels['top'][1] = 'new-7';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-5';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['homepage'] = $page;

  $page = new stdClass;
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'user_dashboard';
  $page->task = 'page';
  $page->admin_title = 'User Dashboard';
  $page->admin_description = '';
  $page->path = 'dashboard';
  $page->access = array();
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Dashboard',
    'name' => 'primary-links',
    'weight' => '1',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array();
  $page->default_handlers = array();
  $handler = new stdClass;
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_user_dashboard_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'user_dashboard';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display;
  $display->layout = 'onecol';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          '0' => 1,
          '1' => 'main',
          '2' => 2,
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => '100',
        'width_type' => '%',
        'children' => array(
          '0' => 'main-row',
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          '0' => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      '1' => array(
        'type' => 'column',
        'width' => '240',
        'width_type' => 'px',
        'parent' => 'canvas',
        'children' => array(),
      ),
      '2' => array(
        'type' => 'column',
        'width' => '240',
        'width_type' => 'px',
        'parent' => 'canvas',
        'children' => array(),
      ),
    ),
  );
  $display->panel_settings = array();
  $display->cache = array();
  $display->title = 'Dashboard';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass;
    $pane->pid = 'new-1';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'recent_content_all';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '10',
      'pager_id' => '',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'style' => 'block',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-1'] = $pane;
    $display->panels['middle'][0] = 'new-1';
    $pane = new stdClass;
    $pane->pid = 'new-2';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'heartbeat-connectedheartbeat';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Recent Activity',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $display->content['new-2'] = $pane;
    $display->panels['middle'][1] = 'new-2';
    $pane = new stdClass;
    $pane->pid = 'new-3';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'blog_stream';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '10',
      'pager_id' => '',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array();
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $display->content['new-3'] = $pane;
    $display->panels['middle'][2] = 'new-3';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['user_dashboard'] = $page;

 return $pages;

}

/**
 * Helper to implementation of hook_rules_defaults().
 */
function _commons_core_rules_defaults() {
  return array(
    'rules' => array(
      'commons_core_1' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Heartbeat: when user adds a page, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_published',
            '#info' => array(
              'label' => 'page is published',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[author:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_add_node',
              'variables_param' => '@username=|=[author:user-name-url]-|-@node_type=|=[node:type]-|-@node_title=|=[node:title-link]-|-@types=|=pages-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'node',
                    '1' => 'author',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs activity for single users adding a page',
              'label callback' => FALSE,
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_2' => array(
        '#type' => 'rule',
        '#set' => 'event_og_become_co_admin',
        '#categories' => array(
          '0' => 'og_activity',
          '1' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#label' => 'User becomes co-admin of a group',
        '#active' => 1,
        '#weight' => '0',
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 1,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'og_become_co_admin',
              'variables_param' => '@user=|=[user:user-name-url]-|-@group=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'node',
                    '1' => 'user',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_3' => array(
        '#type' => 'rule',
        '#set' => 'event_user_insert',
        '#label' => 'Heartbeat: when user account is created, save activity',
        '#active' => 0,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '[account:uid]',
              'nid_param' => '',
              'nid_target_param' => '',
              'message_id_param' => 'heartbeat_create_user',
              'variables_param' => '@user_name=|=[account:account-url]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_4' => array(
        '#type' => 'rule',
        '#set' => 'event_user_delete',
        '#label' => 'Heartbeat: when user account is deleted, save activity',
        '#active' => 0,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '[account:uid]',
              'nid_param' => '',
              'nid_target_param' => '',
              'message_id_param' => 'heartbeat_delete_user',
              'variables_param' => '@user_name=|=[account:user]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_5' => array(
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'Heartbeat: when user deletes content, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '[author:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_delete_content',
              'variables_param' => '@user_name=|=[user:user-name-url]-|-@type=|=[node:type]-|-@node_title=|=[node:title]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'uid_target_param' => array(
                    '0' => 'author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'node',
                    '1' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_6' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_delete',
        '#label' => 'Heartbeat: when deletes adds a comment, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Commented content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '[comment_author:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_delete_comment',
              'variables_param' => '@username=|=[user:user-name-url]-|-@comment_title=|=[comment:comment-title]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'uid_target_param' => array(
                    '0' => 'comment_author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'comment',
                    '1' => 'node',
                    '2' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_7' => array(
        '#type' => 'rule',
        '#set' => 'event_user_relationships_approve',
        '#label' => 'Heartbeat: user A and user B are now friends',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[requester:uid]',
              'uid_target_param' => '[requestee:uid]',
              'nid_param' => 0,
              'nid_target_param' => 0,
              'message_id_param' => 'heartbeat_become_friends',
              'variables_param' => '@user1=|=[requester::user-name-url]-|-@relation_type=|=[relationship:relationship-name]s-|-@user2=|=[requestee:user-name-url]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'requester',
                  ),
                  'uid_target_param' => array(
                    '0' => 'requestee',
                  ),
                  'variables_param' => array(
                    '0' => 'requester',
                    '1' => 'requestee',
                    '2' => 'relationship',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_users_action',
            '#info' => array(
              'label' => 'Logs default user activity between users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'message_id_param',
                '3' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_8' => array(
        '#type' => 'rule',
        '#set' => 'event_user_relationships_remove',
        '#label' => 'Heartbeat: user A and user B are no longer friends',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[requester:uid]',
              'uid_target_param' => '[requestee:uid]',
              'nid_param' => 0,
              'nid_target_param' => 0,
              'message_id_param' => 'heartbeat_friend_removed',
              'variables_param' => '@userA=|=[requester:user-name-url]-|-@userB=|=[requestee:user-name-url]-|-@relationship_type=|=[relationship-name]s-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'requester',
                  ),
                  'uid_target_param' => array(
                    '0' => 'requestee',
                  ),
                  'variables_param' => array(
                    '0' => 'requester',
                    '1' => 'requestee',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_users_action',
            '#info' => array(
              'label' => 'Logs default user activity between users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'message_id_param',
                '3' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_9' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Heartbeat: when user edits a group, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'page is published',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
          '1' => array(
            '#info' => array(
              'label' => 'Content is a group',
              'arguments' => array(
                'group' => array(
                  'type' => 'node',
                  'label' => 'Group',
                ),
              ),
              'module' => 'Organic groups',
            ),
            '#name' => 'og_rules_condition_content_is_group',
            '#settings' => array(
              '#argument map' => array(
                'group' => 'node',
              ),
            ),
            '#type' => 'condition',
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs activity for single users adding a page',
              'label callback' => FALSE,
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:nid]',
              'message_id_param' => 'heartbeat_edit_node',
              'variables_param' => '@username=|=[user:user-name-url]-|-@node_type=|=[node:type]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'node',
                    '1' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_10' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Heartbeat: when user edits a page, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'page is published',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
          '1' => array(
            '#negate' => 1,
            '#weight' => 0,
            '#info' => array(
              'label' => 'Content is a group',
              'arguments' => array(
                'group' => array(
                  'type' => 'node',
                  'label' => 'Group',
                ),
              ),
              'module' => 'Organic groups',
            ),
            '#name' => 'og_rules_condition_content_is_group',
            '#settings' => array(
              '#argument map' => array(
                'group' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#info' => array(
              'label' => 'Logs activity for single users adding a page',
              'label callback' => FALSE,
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_edit_node',
              'variables_param' => '@username=|=[user:user-name-url]-|-@node_type=|=[node:type]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'node',
                    '1' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_11' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_insert',
        '#label' => 'Heartbeat: when user adds a comment, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Commented content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[comment_author:uid]',
              'uid_target_param' => '[node_author:user]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_add_comment',
              'variables_param' => '@username=|=[comment_author:user-name-url]-|-@title=|=[node:title-link]-|-@comment=|=[comment:comment-title]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'comment_author',
                  ),
                  'uid_target_param' => array(
                    '0' => 'node_author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'comment',
                    '1' => 'comment_author',
                    '2' => 'node',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_12' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_update',
        '#label' => 'Heartbeat: when user edits a comment, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Commented content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[user:uid]',
              'uid_target_param' => '[node_author:user]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '[node:og-id]',
              'message_id_param' => 'heartbeat_edit_comment',
              'variables_param' => '@username=|=[user:user-name-url]-|-@comment_title=|=[comment:comment-title]-|-@title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'user',
                  ),
                  'uid_target_param' => array(
                    '0' => 'node_author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'comment',
                    '1' => 'node',
                    '2' => 'user',
                  ),
                  'nid_target_param' => array(
                    '0' => 'node',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_13' => array(
        '#type' => 'rule',
        '#set' => 'event_user_update',
        '#label' => 'Heartbeat: when user edits a profile, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '',
              'nid_param' => '',
              'nid_target_param' => '',
              'message_id_param' => 'heartbeat_edit_account',
              'variables_param' => '@username=|=[account:user-name-url]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_14' => array(
        '#type' => 'rule',
        '#set' => 'event_og_user_insert',
        '#label' => 'Heartbeat: when user joins a group, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[group:nid]',
              'nid_target_param' => '[group:nid]',
              'message_id_param' => 'heartbeat_join_group',
              'variables_param' => '@username=|=[account:user-name-url]-|-@group_title=|=[group:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'nid_param' => array(
                    '0' => 'group',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                    '1' => 'group',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'nid_target_param' => array(
                    '0' => 'group',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_15' => array(
        '#type' => 'rule',
        '#set' => 'event_og_user_delete',
        '#label' => 'Heartbeat: when user leaves a group, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'uid_param' => '[account:uid]',
              'uid_target_param' => '0',
              'nid_param' => '[group:nid]',
              'nid_target_param' => '[group:nid]',
              'message_id_param' => 'heartbeat_leave_group',
              'variables_param' => '@username=|=[account:user-name-url]-|-@group_name=|=[group:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'account',
                  ),
                  'nid_param' => array(
                    '0' => 'group',
                  ),
                  'variables_param' => array(
                    '0' => 'account',
                    '1' => 'group',
                  ),
                  'uid_target_param' => array(
                    '0' => 'account',
                  ),
                  'nid_target_param' => array(
                    '0' => 'group',
                  ),
                ),
              ),
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_16' => array(
        '#type' => 'rule',
        '#set' => 'event_flag_flagged_bookmarks',
        '#label' => 'Heartbeat: when user flags a page, log user activity',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_published',
            '#info' => array(
              'label' => 'Flagged content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[flagging_user:uid]',
              'uid_target_param' => '[flagging_user:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '',
              'message_id_param' => 'heartbeat_flag_content',
              'variables_param' => '@username=|=[flagging_user:user-name-url]-|-@type=|=[node:type]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'flagging_user',
                  ),
                  'uid_target_param' => array(
                    '0' => 'flagging_user',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'flagging_user',
                    '1' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'commons_core_17' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_publish',
        '#label' => 'Heartbeat: When a user adds a comment',
        '#active' => 0,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'heartbeat',
          'commons_core' => 'commons_core',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Logs user activity for single users',
              'eval input' => array(
                '0' => 'uid_param',
                '1' => 'uid_target_param',
                '2' => 'nid_param',
                '3' => 'nid_target_param',
                '4' => 'message_id_param',
                '5' => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'heartbeat_rules_default_action',
            '#settings' => array(
              'uid_param' => '[comment_author:uid]',
              'uid_target_param' => '[node_author:uid]',
              'nid_param' => '[node:nid]',
              'nid_target_param' => '0',
              'message_id_param' => 'heartbeat_add_comment',
              'variables_param' => '@username=|=[comment_author:user-name-url]-|-@title=|=[node:title-link]-|-@comment=|=[comment:comment-body-raw]-|-',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'uid_param' => array(
                    '0' => 'comment_author',
                  ),
                  'uid_target_param' => array(
                    '0' => 'node_author',
                  ),
                  'nid_param' => array(
                    '0' => 'node',
                  ),
                  'variables_param' => array(
                    '0' => 'comment',
                    '1' => 'comment_author',
                    '2' => 'node',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _commons_core_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_discussion';
  $strongarm->value = '0';

  $export['comment_controls_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_blog';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-2',
    'revision_information' => '2',
    'comment_settings' => '3',
    'menu' => '-4',
    'taxonomy' => '-3',
    'flag' => '1',
    'og_nodeapi' => '-1',
  );

  $export['content_extra_weights_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_discussion';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-2',
    'revision_information' => '2',
    'comment_settings' => '3',
    'menu' => '-4',
    'taxonomy' => '-3',
    'flag' => '1',
    'og_nodeapi' => '-1',
  );

  $export['content_extra_weights_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_document';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-1',
    'revision_information' => '3',
    'comment_settings' => '4',
    'menu' => '-4',
    'taxonomy' => '-3',
    'flag' => '2',
    'og_nodeapi' => '0',
  );

  $export['content_extra_weights_document'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_event';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-1',
    'revision_information' => '3',
    'comment_settings' => '4',
    'menu' => '-4',
    'taxonomy' => '-3',
    'flag' => '2',
    'og_nodeapi' => '0',
  );

  $export['content_extra_weights_event'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_group';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-1',
    'revision_information' => '7',
    'comment_settings' => '8',
    'menu' => '6',
    'taxonomy' => '-3',
    'path' => '9',
    'og_description' => '-4',
    'og_selective' => '5',
    'og_register' => '0',
    'og_directory' => '1',
    'og_private' => '2',
  );

  $export['content_extra_weights_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_poll';
  $strongarm->value = array(
    'title' => '-5',
    'revision_information' => '4',
    'comment_settings' => '5',
    'menu' => '3',
    'taxonomy' => '-2',
    'path' => '6',
    'choice_wrapper' => '-4',
    'settings' => '-3',
    'flag' => '2',
    'og_nodeapi' => '1',
  );

  $export['content_extra_weights_poll'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_wiki';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-2',
    'revision_information' => '2',
    'comment_settings' => '3',
    'menu' => '-4',
    'taxonomy' => '-3',
    'flag' => '1',
    'og_nodeapi' => '-1',
  );

  $export['content_extra_weights_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_camelcase';
  $strongarm->value = 0;

  $export['freelinking_camelcase'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_nodetype';
  $strongarm->value = 'wiki';

  $export['freelinking_nodetype'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_notfound';
  $strongarm->value = 'no access search';

  $export['freelinking_notfound'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_onceonly';
  $strongarm->value = 0;

  $export['freelinking_onceonly'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'freelinking_restriction';
  $strongarm->value = array(
    'wiki' => 'wiki',
  );

  $export['freelinking_restriction'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'heartbeat_access_types';
  $strongarm->value = array(
    'privateheartbeat' => array(
      'name' => 'Personal Heartbeat',
      'class' => 'PrivateHeartbeat',
      'path' => 'includes/privateheartbeat.inc',
      'module' => 'heartbeat',
      'access' => 'user_is_logged_in',
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'publicheartbeat' => array(
      'name' => 'Public Heartbeat',
      'class' => 'PublicHeartbeat',
      'path' => 'includes/publicheartbeat.inc',
      'module' => 'heartbeat',
      'access' => TRUE,
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'connectedheartbeat' => array(
      'name' => 'Heartbeat relational activity',
      'class' => 'ConnectedHeartbeat',
      'path' => 'connectedheartbeat.inc',
      'module' => 'friendlist_activity',
      'access' => 'user_is_logged_in',
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'ogheartbeat' => array(
      'name' => 'Organic group activity',
      'class' => 'OgHeartbeat',
      'path' => 'ogheartbeat.inc',
      'module' => 'og_activity',
      'access' => NULL,
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'groupsactivity' => array(
      'name' => 'Organic groups activity',
      'class' => 'GroupsActivity',
      'path' => 'groupsactivity.inc',
      'module' => 'og_activity',
      'access' => NULL,
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
    'singleheartbeat' => array(
      'name' => 'Single activity',
      'class' => 'SingleHeartbeat',
      'path' => 'includes/singleheartbeat.inc',
      'module' => 'heartbeat',
      'access' => TRUE,
      'status' => 'default',
      'messages_denied' => array(),
      'display_filters' => 0,
      'display_block_filters' => 0,
      'filters' => array(),
      'filters_cumul' => 0,
      'settings' => array(
        'block_items_max' => 10,
        'block_show_pager' => 2,
        'page_items_max' => 15,
        'page_show_pager' => 1,
        'page_pager_ajax' => 1,
        'num_load_max' => 30,
      ),
      'poll_messages' => 0,
    ),
  );

  $export['heartbeat_access_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'heartbeat_relations_api';
  $strongarm->value = 'user_relationships_api';

  $export['heartbeat_relations_api'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_blog';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
  );

  $export['node_options_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_discussion';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
  );

  $export['node_options_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_document';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
  );

  $export['node_options_document'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_event';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
  );

  $export['node_options_event'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_forum';
  $strongarm->value = array(
    '0' => 'status',
  );

  $export['node_options_forum'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_group';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
  );

  $export['node_options_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_notice';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
  );

  $export['node_options_notice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_page';
  $strongarm->value = array(
    '0' => 'status',
  );

  $export['node_options_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_poll';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
  );

  $export['node_options_poll'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_wiki';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
    '2' => 'revision',
  );

  $export['node_options_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_audience_required';
  $strongarm->value = '1';

  $export['og_audience_required'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_blog';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_blog'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_discussion';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_document';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_document'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_event';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_event'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_group';
  $strongarm->value = 'group';

  $export['og_content_type_usage_group'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_notice';
  $strongarm->value = 'omitted';

  $export['og_content_type_usage_notice'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_page';
  $strongarm->value = 'omitted';

  $export['og_content_type_usage_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_poll';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_poll'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_wiki';
  $strongarm->value = 'group_post_wiki';

  $export['og_content_type_usage_wiki'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_home_page_view';
  $strongarm->value = '0';

  $export['og_home_page_view'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_private_groups';
  $strongarm->value = '3';

  $export['og_private_groups'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility';
  $strongarm->value = '2';

  $export['og_visibility'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_blog_pattern';
  $strongarm->value = 'blog/[title-raw]';

  $export['pathauto_node_blog_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_discussion_pattern';
  $strongarm->value = 'discussion/[title-raw]';

  $export['pathauto_node_discussion_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_document_pattern';
  $strongarm->value = 'document/[title-raw]';

  $export['pathauto_node_document_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_event_pattern';
  $strongarm->value = 'event/[title-raw]';

  $export['pathauto_node_event_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_group_pattern';
  $strongarm->value = 'groups/[title-raw]';

  $export['pathauto_node_group_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_notice_pattern';
  $strongarm->value = 'notice/[title-raw]';

  $export['pathauto_node_notice_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_poll_pattern';
  $strongarm->value = 'poll/[title-raw]';

  $export['pathauto_node_poll_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_wiki_pattern';
  $strongarm->value = 'wiki/[title-raw]';

  $export['pathauto_node_wiki_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_tracker_pattern';
  $strongarm->value = 'users/[user-raw]/track';

  $export['pathauto_tracker_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_user_pattern';
  $strongarm->value = 'users/[user-raw]';

  $export['pathauto_user_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagadelic_block_tags_2';
  $strongarm->value = '20';

  $export['tagadelic_block_tags_2'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagadelic_sort_order';
  $strongarm->value = 'weight,desc';

  $export['tagadelic_sort_order'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagging_inject_2';
  $strongarm->value = 1;

  $export['tagging_inject_2'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagging_show_suggestion_example';
  $strongarm->value = 0;

  $export['tagging_show_suggestion_example'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_adaptivetheme_settings';
  $strongarm->value = array(
    'skip_navigation_display' => 'hide',
    'breadcrumb_display' => 'yes',
    'breadcrumb_separator' => ' &#187; ',
    'breadcrumb_home' => '0',
    'breadcrumb_trailing' => '0',
    'breadcrumb_title' => '0',
    'display_search_form_label' => '1',
    'search_snippet' => '1',
    'search_info_type' => '1',
    'search_info_user' => '1',
    'search_info_date' => '1',
    'search_info_comment' => '1',
    'search_info_upload' => '1',
    'search_info_separator' => ' - ',
    'primary_links_tree' => '0',
    'secondary_links_tree' => '0',
    'mission_statement_pages' => 'home',
    'taxonomy_settings_enabled' => '0',
    'taxonomy_display_default' => 'only',
    'taxonomy_format_default' => 'vocab',
    'taxonomy_delimiter_default' => ', ',
    'taxonomy_enable_content_type' => '0',
    'submitted_by_settings_enabled' => '0',
    'submitted_by_author_default' => '1',
    'submitted_by_date_default' => '1',
    'submitted_by_enable_content_type' => '0',
    'display_links_settings_enabled' => '0',
    'display_links_default' => 'all',
    'display_links_enable_content_type' => '0',
    'rebuild_registry' => '0',
    'show_theme_info' => '0',
    'cleanup_classes_section' => '0',
    'cleanup_classes_front' => '0',
    'cleanup_classes_user_status' => '0',
    'cleanup_classes_normal_path' => '0',
    'cleanup_classes_node_type' => '0',
    'cleanup_classes_add_edit_delete' => '0',
    'cleanup_classes_language' => '0',
    'cleanup_article_id' => '0',
    'cleanup_article_classes_promote' => '0',
    'cleanup_article_classes_sticky' => '0',
    'cleanup_article_classes_teaser' => '0',
    'cleanup_article_classes_preview' => '0',
    'cleanup_article_classes_type' => '0',
    'cleanup_article_classes_language' => '0',
    'cleanup_comment_anonymous' => '0',
    'cleanup_comment_article_author' => '0',
    'cleanup_comment_by_viewer' => '0',
    'cleanup_comment_new' => '0',
    'cleanup_comment_zebra' => '0',
    'cleanup_comment_wrapper_type' => '0',
    'cleanup_block_block_module_delta' => '0',
    'cleanup_block_classes_module' => '0',
    'cleanup_block_classes_zebra' => '0',
    'cleanup_block_classes_region' => '0',
    'cleanup_block_classes_count' => '0',
    'cleanup_menu_menu_class' => '1',
    'cleanup_menu_leaf_class' => '1',
    'cleanup_menu_first_last_classes' => '0',
    'cleanup_menu_active_classes' => '0',
    'cleanup_menu_title_class' => '0',
    'cleanup_links_type_class' => '1',
    'cleanup_links_active_classes' => '0',
    'cleanup_links_first_last_classes' => '0',
    'cleanup_item_list_zebra' => '0',
    'cleanup_item_list_first_last' => '0',
    'cleanup_views_css_name' => '0',
    'cleanup_views_view_name' => '0',
    'cleanup_views_display_id' => '0',
    'cleanup_views_dom_id' => '0',
    'cleanup_views_unformatted' => '0',
    'cleanup_views_item_list' => '0',
    'cleanup_fields_type' => '0',
    'cleanup_fields_name' => '0',
    'cleanup_fields_zebra' => '0',
    'cleanup_headings_title_class' => '0',
    'cleanup_headings_namespaced_class' => '0',
    'links_add_span_elements' => '0',
    'at_user_menu' => '0',
    'block_edit_links' => '1',
    'at_admin_hide_help' => '0',
    'layout_method' => '0',
    'layout_width' => '960px',
    'layout_sidebar_first_width' => '240',
    'layout_sidebar_last_width' => '240',
    'layout_enable_settings' => 'on',
    'layout_enable_width' => 'on',
    'layout_enable_sidebars' => 'on',
    'layout_enable_method' => 'on',
    'layout_enable_frontpage' => 'on',
    'equal_heights_sidebars' => '0',
    'equal_heights_blocks' => '0',
    'equal_heights_gpanels' => '0',
    'horizontal_login_block' => '0',
    'horizontal_login_block_overlabel' => '0',
    'horizontal_login_block_enable' => 'on',
    'color_schemes' => 'colors-default.css',
    'color_enable_schemes' => 'off',
    'mission' => '',
    'default_logo' => 1,
    'logo_path' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'primary_links' => 1,
    'secondary_links' => 1,
    'toggle_logo' => 1,
    'toggle_favicon' => 1,
    'toggle_name' => 1,
    'toggle_search' => 1,
    'toggle_slogan' => 0,
    'toggle_mission' => 1,
    'toggle_node_user_picture' => 0,
    'toggle_comment_user_picture' => 0,
    'toggle_primary_links' => 1,
    'toggle_secondary_links' => 1,
  );

  $export['theme_adaptivetheme_settings'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_linden_settings';
  $strongarm->value = array(
    'skip_navigation_display' => 'hide',
    'breadcrumb_display' => 'yes',
    'breadcrumb_separator' => ' &#62; ',
    'breadcrumb_home' => 1,
    'breadcrumb_trailing' => 0,
    'breadcrumb_title' => 1,
    'display_search_form_label' => 1,
    'search_snippet' => 1,
    'search_info_type' => 1,
    'search_info_user' => 1,
    'search_info_date' => 1,
    'search_info_comment' => 1,
    'search_info_upload' => 1,
    'search_info_separator' => ' - ',
    'primary_links_tree' => 1,
    'secondary_links_tree' => 0,
    'mission_statement_pages' => 'home',
    'taxonomy_settings_enabled' => 0,
    'taxonomy_display_default' => 'only',
    'taxonomy_format_default' => 'vocab',
    'taxonomy_delimiter_default' => ', ',
    'taxonomy_enable_content_type' => '0',
    'submitted_by_settings_enabled' => 0,
    'submitted_by_author_default' => '1',
    'submitted_by_date_default' => '1',
    'submitted_by_enable_content_type' => '0',
    'display_links_settings_enabled' => 0,
    'display_links_default' => 'all',
    'display_links_enable_content_type' => '0',
    'rebuild_registry' => 0,
    'show_theme_info' => '0',
    'cleanup_classes_section' => 0,
    'cleanup_classes_front' => 0,
    'cleanup_classes_user_status' => 0,
    'cleanup_classes_normal_path' => 0,
    'cleanup_classes_node_type' => 0,
    'cleanup_classes_add_edit_delete' => 0,
    'cleanup_classes_language' => '0',
    'cleanup_article_id' => 0,
    'cleanup_article_classes_promote' => 0,
    'cleanup_article_classes_sticky' => 0,
    'cleanup_article_classes_teaser' => 0,
    'cleanup_article_classes_preview' => 0,
    'cleanup_article_classes_type' => 0,
    'cleanup_article_classes_language' => '0',
    'cleanup_comment_anonymous' => 0,
    'cleanup_comment_article_author' => 0,
    'cleanup_comment_by_viewer' => 0,
    'cleanup_comment_new' => 0,
    'cleanup_comment_zebra' => 0,
    'cleanup_comment_wrapper_type' => 0,
    'cleanup_block_block_module_delta' => 0,
    'cleanup_block_classes_module' => 0,
    'cleanup_block_classes_zebra' => 0,
    'cleanup_block_classes_region' => 0,
    'cleanup_block_classes_count' => 0,
    'cleanup_menu_menu_class' => 1,
    'cleanup_menu_leaf_class' => 1,
    'cleanup_menu_first_last_classes' => 1,
    'cleanup_menu_active_classes' => 0,
    'cleanup_menu_title_class' => 0,
    'cleanup_links_type_class' => 1,
    'cleanup_links_active_classes' => 0,
    'cleanup_links_first_last_classes' => 1,
    'cleanup_item_list_zebra' => 0,
    'cleanup_item_list_first_last' => 0,
    'cleanup_views_css_name' => 1,
    'cleanup_views_view_name' => 1,
    'cleanup_views_display_id' => 1,
    'cleanup_views_dom_id' => 1,
    'cleanup_views_unformatted' => 1,
    'cleanup_views_item_list' => 1,
    'cleanup_fields_type' => 0,
    'cleanup_fields_name' => 0,
    'cleanup_fields_zebra' => 0,
    'cleanup_headings_title_class' => 0,
    'cleanup_headings_namespaced_class' => 0,
    'links_add_span_elements' => 0,
    'at_user_menu' => 0,
    'block_edit_links' => 0,
    'at_admin_hide_help' => 0,
    'layout_method' => '0',
    'layout_width' => '960px',
    'layout_sidebar_first_width' => '240',
    'layout_sidebar_last_width' => '240',
    'layout_enable_settings' => 'on',
    'layout_enable_width' => 'on',
    'layout_enable_sidebars' => 'on',
    'layout_enable_method' => 'on',
    'layout_enable_frontpage' => 'on',
    'equal_heights_sidebars' => 0,
    'equal_heights_blocks' => '0',
    'equal_heights_gpanels' => 0,
    'horizontal_login_block' => 0,
    'horizontal_login_block_overlabel' => 0,
    'horizontal_login_block_enable' => 'on',
    'color_schemes' => 'colors-default.css',
    'color_enable_schemes' => 'off',
    'mission' => '',
    'default_logo' => 1,
    'logo_path' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'primary_links' => 1,
    'secondary_links' => 1,
    'toggle_logo' => 1,
    'toggle_favicon' => 1,
    'toggle_name' => 1,
    'toggle_search' => 1,
    'toggle_slogan' => 0,
    'toggle_mission' => 1,
    'toggle_node_user_picture' => 0,
    'toggle_comment_user_picture' => 0,
    'toggle_primary_links' => 1,
    'toggle_secondary_links' => 1,
    'logo_upload' => '',
    'favicon_upload' => '',
    'equalize_leaderboard' => 0,
    'equalize_header' => 0,
    'equalize_secondary-content' => 0,
    'equalize_content-top' => 0,
    'equalize_content-bottom' => 0,
    'equalize_tertiary-content' => 0,
    'equalize_footer' => 0,
    'exported_settings' => 'settings[skip_navigation_display]="hide"
    settings[breadcrumb_display]="yes"
    settings[breadcrumb_separator]=" &#62; "
    settings[breadcrumb_home]="1"
    settings[breadcrumb_trailing]="0"
    settings[breadcrumb_title]="1"
    settings[display_search_form_label]="1"
    settings[search_snippet]="1"
    settings[search_info_type]="1"
    settings[search_info_user]="1"
    settings[search_info_date]="1"
    settings[search_info_comment]="1"
    settings[search_info_upload]="1"
    settings[search_info_separator]=" - "
    settings[primary_links_tree]="1"
    settings[secondary_links_tree]="0"
    settings[mission_statement_pages]="home"
    settings[taxonomy_settings_enabled]="0"
    settings[taxonomy_display_default]="only"
    settings[taxonomy_format_default]="vocab"
    settings[taxonomy_delimiter_default]=", "
    settings[taxonomy_enable_content_type]="0"
    settings[submitted_by_settings_enabled]="0"
    settings[submitted_by_author_default]="1"
    settings[submitted_by_date_default]="1"
    settings[submitted_by_enable_content_type]="0"
    settings[display_links_settings_enabled]="0"
    settings[display_links_default]="all"
    settings[display_links_enable_content_type]="0"
    settings[rebuild_registry]="0"
    settings[show_theme_info]="0"
    settings[cleanup_classes_section]="0"
    settings[cleanup_classes_front]="0"
    settings[cleanup_classes_user_status]="0"
    settings[cleanup_classes_normal_path]="0"
    settings[cleanup_classes_node_type]="0"
    settings[cleanup_classes_add_edit_delete]="0"
    settings[cleanup_classes_language]="0"
    settings[cleanup_article_id]="0"
    settings[cleanup_article_classes_promote]="0"
    settings[cleanup_article_classes_sticky]="0"
    settings[cleanup_article_classes_teaser]="0"
    settings[cleanup_article_classes_preview]="0"
    settings[cleanup_article_classes_type]="0"
    settings[cleanup_article_classes_language]="0"
    settings[cleanup_comment_anonymous]="0"
    settings[cleanup_comment_article_author]="0"
    settings[cleanup_comment_by_viewer]="0"
    settings[cleanup_comment_new]="0"
    settings[cleanup_comment_zebra]="0"
    settings[cleanup_comment_wrapper_type]="0"
    settings[cleanup_block_block_module_delta]="0"
    settings[cleanup_block_classes_module]="0"
    settings[cleanup_block_classes_zebra]="0"
    settings[cleanup_block_classes_region]="0"
    settings[cleanup_block_classes_count]="0"
    settings[cleanup_menu_menu_class]="1"
    settings[cleanup_menu_leaf_class]="1"
    settings[cleanup_menu_first_last_classes]="1"
    settings[cleanup_menu_active_classes]="0"
    settings[cleanup_menu_title_class]="0"
    settings[cleanup_links_type_class]="1"
    settings[cleanup_links_active_classes]="0"
    settings[cleanup_links_first_last_classes]="1"
    settings[cleanup_item_list_zebra]="0"
    settings[cleanup_item_list_first_last]="0"
    settings[cleanup_views_css_name]="0"
    settings[cleanup_views_view_name]="0"
    settings[cleanup_views_display_id]="0"
    settings[cleanup_views_dom_id]="0"
    settings[cleanup_views_unformatted]="0"
    settings[cleanup_views_item_list]="0"
    settings[cleanup_fields_type]="0"
    settings[cleanup_fields_name]="0"
    settings[cleanup_fields_zebra]="0"
    settings[cleanup_headings_title_class]="0"
    settings[cleanup_headings_namespaced_class]="0"
    settings[links_add_span_elements]="0"
    settings[at_user_menu]="0"
    settings[block_edit_links]="0"
    settings[at_admin_hide_help]="0"
    settings[layout_method]="0"
    settings[layout_width]="960px"
    settings[layout_sidebar_first_width]="240"
    settings[layout_sidebar_last_width]="240"
    settings[layout_enable_settings]="on"
    settings[layout_enable_width]="on"
    settings[layout_enable_sidebars]="on"
    settings[layout_enable_method]="on"
    settings[layout_enable_frontpage]="on"
    settings[equal_heights_sidebars]="0"
    settings[equal_heights_blocks]="0"
    settings[equal_heights_gpanels]="0"
    settings[horizontal_login_block]="0"
    settings[horizontal_login_block_overlabel]="0"
    settings[horizontal_login_block_enable]="on"
    settings[color_schemes]="colors-default.css"
    settings[color_enable_schemes]="off"
    ',
  );

  $export['theme_linden_settings'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_comments';
  $strongarm->value = 'user_picture_meta';

  $export['user_picture_imagecache_comments'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles';
  $strongarm->value = 'profile_pictures';

  $export['user_picture_imagecache_profiles'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles_default';
  $strongarm->value = 'user_picture_meta';

  $export['user_picture_imagecache_profiles_default'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_path';
  $strongarm->value = 'pictures';

  $export['user_picture_path'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_pictures';
  $strongarm->value = '1';

  $export['user_pictures'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_group_terms';
  $strongarm->value = 0;

  $export['user_terms_group_terms'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_group_title';
  $strongarm->value = 'User terms';

  $export['user_terms_group_title'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_profile_path';
  $strongarm->value = 'account';

  $export['user_terms_profile_path'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_vocabs';
  $strongarm->value = array(
    '2' => '2',
  );

  $export['user_terms_vocabs'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_404_type';
  $strongarm->value = array(
    'Link to creation' => 'Link to creation',
    'Link to search' => 0,
    'Creation form' => 0,
  );

  $export['wikitools_404_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_disallowed_characters';
  $strongarm->value = '[]{}|';

  $export['wikitools_disallowed_characters'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_main_page_title';
  $strongarm->value = 'Main Page';

  $export['wikitools_main_page_title'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_node_types';
  $strongarm->value = array(
    'wiki' => 'wiki',
    'blog' => 0,
    'discussion' => 0,
    'document' => 0,
    'event' => 0,
    'group' => 0,
    'page' => 0,
    'poll' => 0,
    'story' => 0,
  );

  $export['wikitools_node_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_options';
  $strongarm->value = array(
    'node creation' => 'node creation',
    'node search' => 'node search',
    'unique titles' => 'unique titles',
    'underscore as space' => 'underscore as space',
    'auto redirect' => 0,
    'move protection' => 0,
    'dash as space' => 0,
  );

  $export['wikitools_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_path';
  $strongarm->value = 'wiki';

  $export['wikitools_path'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_subpages';
  $strongarm->value = 'edit, delete, view, revisions';

  $export['wikitools_subpages'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wikitools_subpages_handling';
  $strongarm->value = 'disabled';

  $export['wikitools_subpages_handling'] = $strongarm;
  return $export;
}
