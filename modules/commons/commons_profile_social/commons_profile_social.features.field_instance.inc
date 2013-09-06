<?php
/**
 * @file
 * commons_profile_social.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function commons_profile_social_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_facebook_url'
  $field_instances['user-user-field_facebook_url'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'title' => '',
        'url' => '',
      ),
    ),
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_facebook_url',
    'label' => 'Facebook URL',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => 'facebook-url',
        'configurable_title' => 0,
        'rel' => 'nofollow',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => '80',
      ),
      'enable_tokens' => 0,
      'title' => 'none',
      'title_maxlength' => '128',
      'title_value' => '',
      'url' => 0,
      'user_register_form' => 0,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => '6',
    ),
  );

  // Exported field_instance: 'user-user-field_linkedin_url'
  $field_instances['user-user-field_linkedin_url'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'url' => '',
      ),
    ),
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_linkedin_url',
    'label' => 'LinkedIn URL',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => 'linkedin-url',
        'configurable_title' => 0,
        'rel' => 'nofollow',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => '80',
      ),
      'enable_tokens' => 0,
      'title' => 'none',
      'title_maxlength' => '128',
      'title_value' => '',
      'url' => 0,
      'user_register_form' => 0,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => '7',
    ),
  );

  // Exported field_instance: 'user-user-field_twitter_url'
  $field_instances['user-user-field_twitter_url'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'title' => '',
        'url' => '',
      ),
    ),
    'deleted' => '0',
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_twitter_url',
    'label' => 'Twitter URL',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => 'twitter-url',
        'configurable_title' => 0,
        'rel' => 'nofollow',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => '80',
      ),
      'enable_tokens' => 1,
      'title' => 'none',
      'title_maxlength' => '128',
      'title_value' => '',
      'url' => 0,
      'user_register_form' => 0,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => '8',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Facebook URL');
  t('LinkedIn URL');
  t('Twitter URL');

  return $field_instances;
}
