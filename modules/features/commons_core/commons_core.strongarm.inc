<?php

/**
 * Implementation of hook_strongarm().
 */
function commons_core_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_notice';
  $strongarm->value = '2';
  $export['comment_default_order_notice'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_group';
  $strongarm->value = '0';
  $export['comment_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_notice';
  $strongarm->value = '0';
  $export['comment_preview_notice'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_group';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-2',
    'revision_information' => '5',
    'author' => '9',
    'options' => '10',
    'comment_settings' => '7',
    'menu' => '6',
    'taxonomy' => '-3',
    'path' => '8',
    'og_description' => '-4',
    'og_selective' => '2',
    'og_register' => '-1',
    'og_directory' => '0',
    'og_private' => '1',
  );
  $export['content_extra_weights_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_notice';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-2',
    'revision_information' => '-1',
    'author' => '3',
    'options' => '4',
    'comment_settings' => '2',
    'menu' => '0',
    'taxonomy' => '-4',
    'path' => '1',
  );
  $export['content_extra_weights_notice'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_first_day';
  $strongarm->value = '1';
  $export['date_first_day'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_long';
  $strongarm->value = 'l, j F, Y - H:i';
  $export['date_format_long'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_medium';
  $strongarm->value = 'j F, Y - H:i';
  $export['date_format_medium'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_short';
  $strongarm->value = 'j M Y - H:i';
  $export['date_format_short'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_forum';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_forum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_group';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_notice';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_notice'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_page';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_audience_required';
  $strongarm->value = '1';
  $export['og_audience_required'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_group';
  $strongarm->value = 'group';
  $export['og_content_type_usage_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_notice';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_notice'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_page';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_home_page_view';
  $strongarm->value = '0';
  $export['og_home_page_view'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_private_groups';
  $strongarm->value = '3';
  $export['og_private_groups'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_statistics_include_unapproved_members';
  $strongarm->value = '0';
  $export['og_statistics_include_unapproved_members'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility';
  $strongarm->value = '2';
  $export['og_visibility'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'quant_height';
  $strongarm->value = '175';
  $export['quant_height'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'quant_width';
  $strongarm->value = '425';
  $export['quant_width'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'remove_markup_default_group';
  $strongarm->value = 1;
  $export['remove_markup_default_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'remove_markup_default_notice';
  $strongarm->value = 1;
  $export['remove_markup_default_notice'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'remove_markup_default_page';
  $strongarm->value = 1;
  $export['remove_markup_default_page'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagadelic_block_tags_1';
  $strongarm->value = '20';
  $export['tagadelic_block_tags_1'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tagadelic_sort_order';
  $strongarm->value = 'weight,desc';
  $export['tagadelic_sort_order'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_settings';
  $strongarm->value = array(
    'toggle_logo' => 1,
    'toggle_name' => 1,
    'toggle_slogan' => 1,
    'toggle_mission' => 1,
    'toggle_node_user_picture' => 1,
    'toggle_comment_user_picture' => 1,
    'toggle_search' => 1,
    'toggle_favicon' => 1,
    'toggle_primary_links' => 1,
    'toggle_secondary_links' => 1,
    'toggle_node_info_blog' => 1,
    'toggle_node_info_discussion' => 1,
    'toggle_node_info_document' => 1,
    'toggle_node_info_event' => 1,
    'toggle_node_info_group' => 1,
    'toggle_node_info_notice' => 0,
    'toggle_node_info_page' => 0,
    'toggle_node_info_poll' => 1,
    'toggle_node_info_wiki' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'favicon_upload' => '',
  );
  $export['theme_settings'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_pictures';
  $strongarm->value = '1';
  $export['user_pictures'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_dimensions';
  $strongarm->value = '';
  $export['user_picture_dimensions'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_comments';
  $strongarm->value = 'user_picture_meta';
  $export['user_picture_imagecache_comments'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles';
  $strongarm->value = 'profile_pictures';
  $export['user_picture_imagecache_profiles'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles_default';
  $strongarm->value = 'user_picture_meta';
  $export['user_picture_imagecache_profiles_default'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_path';
  $strongarm->value = 'pictures';
  $export['user_picture_path'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_relationships_notifications_disabled';
  $strongarm->value = 1;
  $export['user_relationships_notifications_disabled'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_group_terms';
  $strongarm->value = 0;
  $export['user_terms_group_terms'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_group_title';
  $strongarm->value = 'User terms';
  $export['user_terms_group_title'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_profile_path';
  $strongarm->value = 'account';
  $export['user_terms_profile_path'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'vertical_tabs_default';
  $strongarm->value = 1;
  $export['vertical_tabs_default'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'vertical_tabs_minimum';
  $strongarm->value = '1';
  $export['vertical_tabs_minimum'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'vertical_tabs_node_type_settings';
  $strongarm->value = 0;
  $export['vertical_tabs_node_type_settings'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_filter_styles_border-1_1';
  $strongarm->value = array(
    'border' => 'border',
    'border-top' => 'border-top',
    'border-right' => 'border-right',
    'border-bottom' => 'border-bottom',
    'border-left' => 'border-left',
    'border-width' => 'border-width',
    'border-top-width' => 'border-top-width',
    'border-right-width' => 'border-right-width',
    'border-bottom-width' => 'border-bottom-width',
    'border-left-width' => 'border-left-width',
  );
  $export['wysiwyg_filter_styles_border-1_1'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_filter_styles_border-2_1';
  $strongarm->value = array(
    'border-color' => 'border-color',
    'border-top-color' => 'border-top-color',
    'border-right-color' => 'border-right-color',
    'border-bottom-color' => 'border-bottom-color',
    'border-left-color' => 'border-left-color',
    'border-style' => 'border-style',
    'border-top-style' => 'border-top-style',
    'border-right-style' => 'border-right-style',
    'border-bottom-style' => 'border-bottom-style',
    'border-left-style' => 'border-left-style',
  );
  $export['wysiwyg_filter_styles_border-2_1'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_filter_styles_dimension_1';
  $strongarm->value = array(
    'height' => 'height',
    'width' => 'width',
    'line-height' => 0,
    'max-height' => 0,
    'max-width' => 0,
    'min-height' => 0,
    'min-width' => 0,
  );
  $export['wysiwyg_filter_styles_dimension_1'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_filter_styles_layout_1';
  $strongarm->value = array(
    'float' => 'float',
    'clear' => 0,
    'display' => 0,
    'position' => 0,
    'visibility' => 0,
  );
  $export['wysiwyg_filter_styles_layout_1'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_filter_styles_text_1';
  $strongarm->value = array(
    'text-align' => 'text-align',
    'text-decoration' => 0,
    'text-indent' => 0,
    'text-transform' => 0,
    'letter-spacing' => 0,
    'word-spacing' => 0,
    'white-space' => 0,
    'direction' => 0,
    'unicode-bidi' => 0,
  );
  $export['wysiwyg_filter_styles_text_1'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_filter_valid_elements_parsed_1';
  $strongarm->value = array(
    'a' => array(
      'href' => array(
        'required' => TRUE,
      ),
      'target' => array(
        'values' => array(
          0 => '_blank',
        ),
      ),
      'title' => array(),
      'style' => array(),
    ),
    'address' => array(
      'style' => array(),
    ),
    'blockquote' => array(
      'style' => array(),
    ),
    'br' => array(
      'style' => array(),
    ),
    'cite' => array(
      'style' => array(),
    ),
    'code' => array(
      'style' => array(),
    ),
    'dd' => array(
      'style' => array(),
    ),
    'dl' => array(
      'style' => array(),
    ),
    'dt' => array(
      'style' => array(),
    ),
    'em' => array(
      'style' => array(),
    ),
    'h2' => array(
      'style' => array(),
    ),
    'h3' => array(
      'style' => array(),
    ),
    'h4' => array(
      'style' => array(),
    ),
    'h5' => array(
      'style' => array(),
    ),
    'h6' => array(
      'style' => array(),
    ),
    'img' => array(
      'src' => array(
        'required' => TRUE,
      ),
      'alt' => array(),
      'title' => array(),
      'style' => array(),
    ),
    'li' => array(
      'style' => array(),
    ),
    'ol' => array(
      'style' => array(),
    ),
    'p' => array(
      'align' => array(
        'values' => array(
          0 => 'center',
          1 => 'justify',
          2 => 'left',
          3 => 'right',
        ),
      ),
      'style' => array(),
    ),
    'pre' => array(
      'style' => array(),
    ),
    'span' => array(
      'style' => array(),
    ),
    'strong' => array(
      'style' => array(),
    ),
    'sub' => array(
      'style' => array(),
    ),
    'sup' => array(
      'style' => array(),
    ),
    'u' => array(
      'style' => array(),
    ),
    'ul' => array(
      'style' => array(),
    ),
  );
  $export['wysiwyg_filter_valid_elements_parsed_1'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_filter_valid_elements_raw_1';
  $strongarm->value = '@[style],
a[!href|target<_blank|title],
p[align<center?justify?left?right],
img[!src|alt|title|style],
br, em, strong, cite, sub, sup, span, blockquote, code, ul, ol, li, dl, dt, dd, pre, address, h2, h3, h4, h5, h6, u';
  $export['wysiwyg_filter_valid_elements_raw_1'] = $strongarm;

  return $export;
}
