<?php
/**
 * @file
 * commons_media.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_media_field_default_field_instances() {
  $field_instances = array();

  $commons_groups_entity_types = commons_entity_integration_info();
  foreach ($commons_groups_entity_types as $entity_type => $bundles) {
    foreach ($bundles as $bundle => $integrations) {
      if (isset($integrations['media']) && $integrations['media'] == TRUE
        && isset($integrations['is_group_content']) && $integrations['is_group_content'] == TRUE) {
        commons_media_field_definition($field_instances, $entity_type, $bundle);
      }
    }
  }

  return $field_instances;
}

function commons_media_field_definition(&$field_instances, $entity_type, $bundle) {
  // Exported field_instance: 'entity-bundle-field_media'
  $field_instances["$entity_type-$bundle-field_media"] = array(
    'bundle' => $bundle,
    'deleted' => 0,
    'description' => 'Attach an image or video.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'file_entity',
        'settings' => array(
          'file_view_mode' => 'default',
        ),
        'type' => 'file_rendered',
        'weight' => -48,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'file_entity',
        'settings' => array(
          'file_view_mode' => 'teaser',
        ),
        'type' => 'file_rendered',
        'weight' => -48,
      ),
    ),
    'display_in_partial_form' => 1,
    'entity_type' => 'node',
    'field_name' => 'field_media',
    'label' => 'Media',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'media',
      'file_extensions' => 'jpg jpeg gif png oembed mov mp4 m4v mpeg avi ogv webp webm',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'oembed' => 'oembed',
          'public' => 'public',
        ),
        'allowed_types' => array(
          'audio' => 0,
          'document' => 0,
          'image' => 'image',
          'video' => 'video',
        ),
        'browser_plugins' => array(
          'media_default--media_browser_1' => 0,
          'media_default--media_browser_my_files' => 0,
          'media_internet' => 'media_internet',
          'upload' => 'upload',
        ),
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => -48,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Attach an image or video.');
  t('Media');

  return $field_instances;
}
