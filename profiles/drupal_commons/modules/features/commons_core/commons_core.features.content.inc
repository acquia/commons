<?php

/**
 * Implementation of hook_content_default_fields().
 */
function commons_core_content_default_fields() {
  $fields = array();

  // Exported field: field_featured_group
  $fields['group-field_featured_group'] = array(
    'field_name' => 'field_featured_group',
    'type_name' => 'group',
    'display_settings' => array(
      'weight' => '4',
      'parent' => 'group_promote_content',
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
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
      'label' => 'Featured group',
      'weight' => '4',
      'description' => 'Checking this option will make this a Featured group. Featured groups get special placement on the home page. This should only be used for groups with a special purpose.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_group_image
  $fields['group-field_group_image'] = array(
    'field_name' => 'field_group_image',
    'type_name' => 'group',
    'display_settings' => array(
      'weight' => '5',
      'parent' => 'group_attributes',
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
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
        'filepath' => 'sites/default/files/default-group.png',
        'filemime' => 'image/png',
        'source' => 'default_image_upload',
        'destination' => 'sites/default/files/default-group.png',
        'filesize' => 3968,
        'uid' => '1',
        'status' => 1,
        'timestamp' => 1274378352,
        'fid' => '1',
      ),
      'use_default_image' => 1,
      'insert' => NULL,
      'insert_styles' => NULL,
      'insert_default' => NULL,
      'insert_class' => NULL,
      'insert_width' => NULL,
      'label' => 'Image',
      'weight' => '5',
      'description' => 'Specify an image to act as the group icon or avatar.',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_grouplink
  $fields['group-field_grouplink'] = array(
    'field_name' => 'field_grouplink',
    'type_name' => 'group',
    'display_settings' => array(
      'weight' => '6',
      'parent' => 'group_attributes',
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
    'validate_url' => '',
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

  // Exported field: field_content_images
  $fields['notice-field_content_images'] = array(
    'field_name' => 'field_content_images',
    'type_name' => 'notice',
    'display_settings' => array(
      'weight' => '35',
      'parent' => 'group_images',
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'content_image_primary_linked',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'content_image_primary_default',
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
        'imagecache_Small' => 'imagecache_Small',
        'imagecache_Featured' => 'imagecache_Featured',
        'auto' => 0,
        'link' => 0,
        'imagecache_content_image_secondary' => 0,
        'imagecache_profile_pictures' => 0,
        'imagecache_member_list_image' => 0,
        'imagecache_content_image_primary' => 0,
        'imagecache_user_picture_meta' => 0,
        'imagecache_group_images' => 0,
        'imagecache_group_images_thumb' => 0,
      ),
      'insert_default' => 'imagecache_Featured',
      'insert_class' => '',
      'insert_width' => '',
      'label' => 'Add images',
      'weight' => '35',
      'description' => 'After uploading an image, click "Insert" to add the image to the content body.',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Add images');
  t('Featured group');
  t('Image');
  t('Links');

  return $fields;
}
