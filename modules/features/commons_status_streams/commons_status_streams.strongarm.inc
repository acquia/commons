<?php

/**
 * Implementation of hook_strongarm().
 */
function commons_status_streams_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_block_view';
  $strongarm->value = 1;
  $export['facebook_status_block_view'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_default_text';
  $strongarm->value = 'What\'s on your mind?';
  $export['facebook_status_default_text'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_default_text_other';
  $strongarm->value = 'Write something...';
  $export['facebook_status_default_text_other'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_filter';
  $strongarm->value = '5';
  $export['facebook_status_filter'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_hide_length';
  $strongarm->value = '500';
  $export['facebook_status_hide_length'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_imagecache_preset';
  $strongarm->value = 'user_picture_meta';
  $export['facebook_status_imagecache_preset'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_length';
  $strongarm->value = '0';
  $export['facebook_status_length'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_nl2br';
  $strongarm->value = 1;
  $export['facebook_status_nl2br'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_profile';
  $strongarm->value = 0;
  $export['facebook_status_profile'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_reply_type';
  $strongarm->value = 'convo';
  $export['facebook_status_reply_type'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_share_view';
  $strongarm->value = 'activity_log_stream';
  $export['facebook_status_share_view'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_userpoints_other';
  $strongarm->value = '4';
  $export['facebook_status_userpoints_other'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_userpoints_own';
  $strongarm->value = '3';
  $export['facebook_status_userpoints_own'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'facebook_status_user_other_view';
  $strongarm->value = 'activity_log_stream';
  $export['facebook_status_user_other_view'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fbsmp_disabled_plugins';
  $strongarm->value = array(
    0 => 'video',
    1 => 'slideshare',
  );
  $export['fbsmp_disabled_plugins'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fbsmp_ignore_sdefault';
  $strongarm->value = 1;
  $export['fbsmp_ignore_sdefault'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fbsmp_plugin_photo';
  $strongarm->value = array(
    'file_extensions' => 'png gif jpg jpeg',
    'max_filesize' => '',
    'min_resolution' => '0',
    'max_resolution' => '0',
    'imagecache_preset' => 'Status_picture:imagelink',
    'file_path' => '',
    'width' => '0',
    'height' => '0',
    'alt' => '',
    'class' => '',
  );
  $export['fbsmp_plugin_photo'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fbss_comments_userpoints';
  $strongarm->value = '2';
  $export['fbss_comments_userpoints'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fbss_comments_user_pictures';
  $strongarm->value = 'user_picture_meta';
  $export['fbss_comments_user_pictures'] = $strongarm;

  return $export;
}
