<?php

/**
 * @file
 *   CTools plugins declarations.
 */

/**
 * Break out for fbsmp_fbsmp_plugins().
 */
function _fbsmp_fbsmp_plugins() {
  $path = drupal_get_path('module', 'fbsmp') .'/plugins';
  $image_path = _fbsmp_get_image_dir() .'/plugins';
  $info = array();
  $info['link'] = array(
    'name' => t('Link'),
    'file' => 'link.inc',
    'path' => $path,
    'icon' => $image_path .'/images/link.png',
    'description' => t('Lets users publish links with their statuses.'),
    'admin_settings_form' => 'fbsmp_link_fbsmp_admin_settings_form',
    'admin_settings_form_validate' => 'fbsmp_link_fbsmp_admin_settings_form_validate',
    'admin_settings_form_submit' => 'fbsmp_link_fbsmp_admin_settings_form_submit',
    'widget_form' => 'fbsmp_link_fbsmp_widget_form',
    'widget_form_validate' => 'fbsmp_link_fbsmp_widget_form_validate',
    'widget_form_save' => 'fbsmp_link_fbsmp_widget_form_save',
    'subtheme' => 'fbsmp_link_fbsmp_subtheme',
    'themed attachment' => 'fbsmp_link_fbsmp_themed_attachment',
    'token list' => 'fbsmp_link_fbsmp_token_list',
    'token values' => 'fbsmp_link_fbsmp_token_values',
    'repost_form' => 'fbsmp_link_fbsmp_repost_form',
    'repost_form_validate' => 'fbsmp_link_fbsmp_widget_form_validate',
    'repost_form_submit' => 'fbsmp_link_fbsmp_widget_form_save',
    'edit_form' => 'fbsmp_link_fbsmp_edit_form',
    'edit_form_submit' => 'fbsmp_link_fbsmp_edit_form_submit',
    'supported_url_params' => 'fbsmp_link_fbsmp_supported_url_params',
    'url_param_form' => 'fbsmp_link_fbsmp_url_param_form',
    'url_param_form_validate' => 'fbsmp_link_fbsmp_widget_form_validate',
    'url_param_form_submit' => 'fbsmp_link_fbsmp_widget_form_save',
  );
  $info['photo'] = array(
    'name' => t('Photo'),
    'file' => 'photo.inc',
    'path' => $path,
    'icon' => $image_path .'/images/photo.png',
    'widget_form' => 'fbsmp_photo_fbsmp_widget_form',
    'widget_form_validate' => 'fbsmp_photo_fbsmp_widget_form_validate',
    'admin_settings_form' => 'fbsmp_photo_fbsmp_admin_settings_form',
    'admin_settings_form_validate' => 'fbsmp_photo_fbsmp_admin_settings_form_validate',
    'admin_settings_form_submit' => 'fbsmp_photo_fbsmp_admin_settings_form_submit',
    'description' => t('Lets users publish images with their statuses.'),
    'subtheme' => 'fbsmp_photo_fbsmp_subtheme',
    'themed attachment' => 'fbsmp_photo_fbsmp_themed_attachment',
    'widget_form_save' => 'fbsmp_photo_fbsmp_widget_form_save',
    'token list' => 'fbsmp_photo_fbsmp_token_list',
    'token values' => 'fbsmp_photo_fbsmp_token_values',
    'repost_form' => 'fbsmp_photo_fbsmp_repost_form',
    'repost_form_validate' => 'fbsmp_photo_fbsmp_repost_form_validate',
    'repost_form_submit' => 'fbsmp_photo_fbsmp_repost_form_save',
  );
  $info['video'] = array(
    'name' => t('Video'),
    'file' => 'video.inc',
    'path' => $path,
    'icon' => $image_path .'/images/video.png',
    'widget_form' => 'fbsmp_video_fbsmp_widget_form',
    'widget_form_validate' => 'fbsmp_video_fbsmp_widget_form_validate',
    'admin_settings_form' => 'fbsmp_video_fbsmp_admin_settings_form',
    'admin_settings_form_validate' => 'fbsmp_video_fbsmp_admin_settings_form_validate',
    'admin_settings_form_submit' => 'fbsmp_video_fbsmp_admin_settings_form_submit',
    'description' => t('Lets users publish videos with their statuses.'),
    'subtheme' => 'fbsmp_video_fbsmp_subtheme',
    'themed attachment' => 'fbsmp_video_fbsmp_themed_attachment',
    'widget_form_save' => 'fbsmp_video_fbsmp_widget_form_save',
    'token list' => 'fbsmp_video_fbsmp_token_list',
    'token values' => 'fbsmp_video_fbsmp_token_values',
  );
  $info['slideshare'] = array(
    'name' => t('Document'),
    'file' => 'slideshare.inc',
    'path' => $path,
    'icon' => $image_path .'/images/document.png',
    'widget_form' => 'fbsmp_slideshare_fbsmp_widget_form',
    'widget_form_validate' => 'fbsmp_slideshare_fbsmp_widget_form_validate',
    'admin_settings_form' => 'fbsmp_slideshare_fbsmp_admin_settings_form',
    'admin_settings_form_validate' => 'fbsmp_slideshare_fbsmp_admin_settings_form_validate',
    'admin_settings_form_submit' => 'fbsmp_slideshare_fbsmp_admin_settings_form_submit',
    'description' => t('Lets users publish documents (ppt, doc, etc) with their statuses via SlideShare.'),
    'subtheme' => 'fbsmp_slideshare_fbsmp_subtheme',
    'themed attachment' => 'fbsmp_slideshare_fbsmp_themed_attachment',
    'widget_form_save' => 'fbsmp_slideshare_fbsmp_widget_form_save',
    'token list' => 'fbsmp_slideshare_fbsmp_token_list',
    'token values' => 'fbsmp_slideshare_fbsmp_token_values',
  );
  return $info;
}