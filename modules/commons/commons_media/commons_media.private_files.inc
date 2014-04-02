<?php

/**
 * @file
 * Functions related to ensuring that the private file system is used when embedding files in private group content.
 */

/**
 * Implements hook_field_attach_insert().
 */
function commons_media_field_attach_insert($entity_type, $entity) {
  _commons_media_filter_add_file_usage_from_fields($entity_type, $entity);
}

/**
 * Implements hook_field_attach_update().
 */
function commons_media_field_attach_update($entity_type, $entity) {
  _commons_media_filter_add_file_usage_from_fields($entity_type, $entity);
}

/**
 * Ensure that the private file system is used when embedding files in private group content.
 */
function _commons_media_filter_add_file_usage_from_fields($entity_type, $entity) {
  // Only proceed if the Media: WYSIWYG module is enabled.
  if (!module_exists('media_wysiwyg')) {
    return;
  }

  // Only proceed if the private file system has been configured.
  if (!variable_get('file_private_path', FALSE)) {
    return;
  }

  // Track the total usage for files from all fields combined.
  $entity_files = commons_media_entity_field_count_files($entity_type, $entity);

  list($entity_id, $entity_vid, $entity_bundle) = entity_extract_ids($entity_type, $entity);

  // Only proceed if the entity has been configured as group content.
  if (!og_is_group_content_type($entity_type, $entity_bundle)) {
    return;
  }

  // Ensure that the private file system is used when attaching files to private
  // group content.
  foreach ($entity_files as $fid => $entity_count) {
    // Move files to the private file system if the content is private.
    if ($entity->group_content_access[LANGUAGE_NONE][0]['value'] == 2) {
      if ($source_file = file_load($fid)) {

        // Only move public files.
        if (file_uri_scheme($source_file->uri) == 'public') {
          $usage = file_usage_list($source_file);

          // Only move files that aren't currently in use.
          if (empty($usage)) {
            $scheme = 'private://';
            $uri = file_stream_wrapper_uri_normalize($scheme . $source_file->filename);
            file_move($source_file, $uri, FILE_EXISTS_RENAME);
          }
        }
      }
    }
  }
}

/**
 * Utility function to get the file count in this entity
 *
 * @param type $entity
 * @param type $entity_type
 * @return int
 */
function commons_media_entity_field_count_files($entity_type, $entity) {
  $entity_files = array();

  foreach (commons_media_filter_parse_from_fields($entity_type, $entity) as $file_reference) {
    if (empty($entity_files[$file_reference['fid']])) {
      $entity_files[$file_reference['fid']] = 1;
    }
    else {
      $entity_files[$file_reference['fid']]++;
    }
  }

  return $entity_files;
}

/**
 * Parse file references from an entity's text fields and return them as an array.
 */
function commons_media_filter_parse_from_fields($entity_type, $entity) {
  $file_references = array();

  foreach (media_wysiwyg_filter_fields_with_text_filtering($entity_type, $entity) as $field_name) {
    if ($field_items = field_get_items($entity_type, $entity, $field_name)) {
      foreach ($field_items as $field_item) {
        preg_match_all(MEDIA_WYSIWYG_TOKEN_REGEX, $field_item['value'], $matches);

        foreach ($matches[0] as $tag) {
          $tag = str_replace(array('[[', ']]'), '', $tag);
          $tag_info = drupal_json_decode($tag);

          if (isset($tag_info['fid']) && $tag_info['type'] == 'media') {
            $file_references[] = $tag_info;
          }
        }

        preg_match_all(MEDIA_WYSIWYG_TOKEN_REGEX, $field_item['value'], $matches_alt);

        foreach ($matches_alt[0] as $tag) {
          $tag = urldecode($tag);
          $tag_info = drupal_json_decode($tag);

          if (isset($tag_info['fid']) && $tag_info['type'] == 'media') {
            $file_references[] = $tag_info;
          }
        }
      }
    }
  }

  return $file_references;
}
