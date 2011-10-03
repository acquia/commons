<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function commons_document_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_promote_content
  $groups['document-group_promote_content'] = array(
    'group_type' => 'standard',
    'type_name' => 'document',
    'group_name' => 'group_promote_content',
    'label' => 'Promote content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '-1',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
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
      '0' => 'field_group_sticky',
      '1' => 'field_featured_content',
    ),
  );

  // Exported group: group_upload
  $groups['document-group_upload'] = array(
    'group_type' => 'standard',
    'type_name' => 'document',
    'group_name' => 'group_upload',
    'label' => 'Upload',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '-2',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
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
    'weight' => '-2',
    'fields' => array(
      '0' => 'field_file',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Promote content');
  t('Upload');

  return $groups;
}
