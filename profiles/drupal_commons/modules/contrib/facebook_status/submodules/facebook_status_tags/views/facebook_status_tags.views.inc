<?php

/**
 * @file
 * Provide views data and handlers for the Facebook-style Statuses Tags module.
 */

/**
 * Implementation of hook_views_data().
 */
function facebook_status_tags_views_data() {
  $data['facebook_status_tags']['table']['group']  = t('Facebook-style Statuses Tags');

  // Advertise this table as a possible base table.
  $data['facebook_status_tags']['table']['base'] = array(
    'field' => 'sid',
    'title' => t('Facebook-style Statuses Tags'),
    'help' => t('#hashtags and @mentions.'),
    'weight' => 10,
  );

  $data['facebook_status_tags']['sid'] = array(
    'title' => t('Status ID'),
    'help' => t('The ID of the status update.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['facebook_status_tags']['rid'] = array(
    'title' => t('Tag ID'),
    'help' => t('The Tag ID of the status - either a UID or Term ID depending on the reference type.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['facebook_status_tags']['type'] = array(
    'title' => t('Tag type'),
    'help' => t('The type of tag - User or Taxonomy Term.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'facebook_status_tags_views_handler_filter_string_type',
    ),
  );

  $data['facebook_status_tags']['name'] = array(
    'title' => t('Tag Name'),
    'help' => t('The name of the tag - a username or taxonomy term name.'),
    'field' => array(
      'handler' => 'facebook_status_tags_views_handler_field_name',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['facebook_status']['has-tags'] = array(
    'title' => t('Status has tags'),
    'help' => t('Only show statuses with tags.'),
    'filter' => array(
      'field' => 'sid',
      'handler' => 'facebook_status_tags_views_handler_filter_has_tag',
    ),
  );

  $data['facebook_status']['has-specific-tag'] = array(
    'title' => t('Status has specific tag'),
    'help' => t('Only show statuses with a specific tag.'),
    'filter' => array(
      'field' => 'sid',
      'handler' => 'facebook_status_tags_views_handler_filter_has_this_tag',
    ),
    'argument' => array(
      'field' => 'sid',
      'handler' => 'facebook_status_tags_views_handler_argument_has_this_tag',
    ),
  );

  $data['facebook_status']['has-specific-tag-id'] = array(
    'title' => t('Status has specific tag ID'),
    'help' => t('Only show statuses with a specific tag ID.'),
    'argument' => array(
      'field' => 'sid',
      'handler' => 'facebook_status_tags_views_handler_argument_has_this_tag_id',
    ),
  );

  $data['facebook_status']['tags-terms'] = array(
    'title' => t('All Tags'),
    'help' => t('Show all #hashtags and/or @mentions associated with the status'),
    'field' => array(
      'field' => 'sid',
      'handler' => 'facebook_status_tags_views_handler_field_all_terms',
      'click sortable' => FALSE,
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function facebook_status_tags_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'facebook_status_tags') .'/views',
    ),
    'handlers' => array(
      'facebook_status_tags_views_handler_argument_has_this_tag' => array(
        'parent' => 'views_handler_argument_string',
      ),
      'facebook_status_tags_views_handler_argument_has_this_tag_id' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'facebook_status_tags_views_handler_field_all_terms' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_tags_views_handler_field_message' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_tags_views_handler_field_name' => array(
        'parent' => 'views_handler_field',
      ),
      'facebook_status_tags_views_handler_filter_has_tag' => array(
        'parent' => 'views_handler_filter',
      ),
      'facebook_status_tags_views_handler_filter_has_this_tag' => array(
        'parent' => 'views_handler_filter_string',
      ),
      'facebook_status_tags_views_handler_filter_string_type' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
    ),
  );
}
