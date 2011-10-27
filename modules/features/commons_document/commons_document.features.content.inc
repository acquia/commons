<?php

/**
 * Implementation of hook_content_default_fields().
 */
function commons_document_content_default_fields() {
  $fields = array();

  // Exported field: field_featured_content
  $fields['document-field_featured_content'] = array(
    'field_name' => 'field_featured_content',
    'type_name' => 'document',
    'display_settings' => array(
      'weight' => '7',
      'parent' => 'group_promote_content',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
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
      'label' => 'Featured content',
      'weight' => '7',
      'description' => 'Marking a content item of featured will show the content item in the main \'Featured content\' section.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_file
  $fields['document-field_file'] = array(
    'field_name' => 'field_file',
    'type_name' => 'document',
    'display_settings' => array(
      'weight' => '-1',
      'parent' => 'group_upload',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
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
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '1',
    'list_default' => 1,
    'description_field' => '1',
    'widget' => array(
      'file_extensions' => 'jpg jpeg gif png doc docx txt xls xlsx pdf ppt pps odt ods odp tar gz tgz zip',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'insert' => 0,
      'insert_styles' => array(
        'auto' => 0,
        'link' => 0,
        'image' => 0,
        'imagecache_profile_pictures' => 0,
        'imagecache_content_image_secondary' => 0,
        'imagecache_group_images' => 0,
        'imagecache_user_picture_meta' => 0,
        'imagecache_group_images_thumb' => 0,
        'imagecache_content_image_primary' => 0,
        'imagecache_member_list_image' => 0,
      ),
      'insert_default' => 'auto',
      'insert_class' => '',
      'insert_width' => '',
      'label' => 'Files',
      'weight' => '-1',
      'description' => '',
      'type' => 'filefield_widget',
      'module' => 'filefield',
    ),
  );

  // Exported field: field_group_sticky
  $fields['document-field_group_sticky'] = array(
    'field_name' => 'field_group_sticky',
    'type_name' => 'document',
    'display_settings' => array(
      'weight' => '6',
      'parent' => 'group_promote_content',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
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
      'label' => 'Group sticky',
      'weight' => '6',
      'description' => 'If you\'re a <strong>group owner</strong> you have the option to check this to make the content item "Sticky". Sticky items remain at the top of content lists so users can see them more easily. If this post is not a group post, this will be ignored.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Featured content');
  t('Files');
  t('Group sticky');

  return $fields;
}
