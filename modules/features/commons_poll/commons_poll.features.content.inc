<?php

/**
 * Implementation of hook_content_default_fields().
 */
function commons_poll_content_default_fields() {
  $fields = array();

  // Exported field: field_content_images
  $fields['poll-field_content_images'] = array(
    'field_name' => 'field_content_images',
    'type_name' => 'poll',
    'display_settings' => array(
      'weight' => '11',
      'parent' => 'group_images',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'image_plain',
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
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
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
      'default_image' => NULL,
      'use_default_image' => 0,
      'insert' => 1,
      'insert_styles' => array(
        'image' => 'image',
        'imagecache_Featured' => 'imagecache_Featured',
        'imagecache_Small' => 'imagecache_Small',
        'auto' => 0,
        'link' => 0,
        'imagecache_group_images' => 0,
        'imagecache_group_images_featured' => 0,
        'imagecache_group_images_medium' => 0,
        'imagecache_group_images_showcase' => 0,
        'imagecache_group_images_thumb' => 0,
        'imagecache_member_list_image' => 0,
        'imagecache_profile_pictures' => 0,
        'imagecache_user_picture_meta' => 0,
      ),
      'insert_default' => 'imagecache_Featured',
      'insert_class' => '',
      'insert_width' => '',
      'label' => 'Add images',
      'weight' => '11',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_featured_content
  $fields['poll-field_featured_content'] = array(
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
      'label' => 'Featured content',
      'weight' => 0,
      'description' => 'Marking a content item of featured will show the content item in the main \'Featured content\' section.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_poll_body
  $fields['poll-field_poll_body'] = array(
    'field_name' => 'field_poll_body',
    'type_name' => 'poll',
    'display_settings' => array(
      'weight' => '-2',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
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
    'text_processing' => '1',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '5',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_poll_body][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Body',
      'weight' => '-2',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Add images');
  t('Body');
  t('Featured content');

  return $fields;
}
