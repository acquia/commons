<?php

/**
 * @file
 *   Integration of Link plugin with Emvideo. Mostly from eminline.module.
 */
 
define('FBEMP_LINK_EMVIDEO_DEFAULT_VIDEO_WIDTH', 435);
define('FBSMP_LINK_EMVIDEO_DEFAULT_VIDEO_HEIGHT', 350);

/**
 * Matches the URL with HTTP/HTTPS and passes it to link checker.
 *
 * @param $url
 *  The shared URL.
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - emvideo_providers
 *       An array containing the allowed video providers. Defaults to none.
 *   - emvideo_height
 *       An integer specifying the height of the embedded video. Defaults to 435.
 *   - emvideo_width
 *       An integer specifying the height of the embedded video. Defaults to 350.
 *   - emvideo_autoplay
 *       A boolean specifying whether to autoplay the embedded video. Defaults to 0.
 *
 * @return
 *   An array containing the required emvideo data and thumbnails.
 */
function _fbsmp_link_emvideo_data($url, $settings = array()) {
  $settings += array(
    'emvideo_width' => FBEMP_LINK_EMVIDEO_DEFAULT_VIDEO_WIDTH,
    'emvideo_height' => FBSMP_LINK_EMVIDEO_DEFAULT_VIDEO_HEIGHT,
    'emvideo_autoplay' => 0,
    'emvideo_providers' => array(),
  );

  $url = ' '. $url .' ';

  //Need to attach the variables to the callback after the regex.
  $callback = _fbsmp_link_emvideo_curry('_fbsmp_link_emvideo_parse_links', 2);

  // Match absolute URLs.
  $item = preg_replace_callback("`(<p>|<li>|<br\s*/?>|[ \n\r\t\(])((http://|https://)([a-zA-Z0-9@:%_+*~#?&=.,/;-]*[a-zA-Z0-9@:%_+*~#&=/;-]))([.,?!]*?)(?=(</p>|</li>|<br\s*/?>|[ \n\r\t\)]))`i", $callback($settings), $url);
  $item = unserialize($item);
  if (is_array($item)) {
    $item['image'] = emfield_include_invoke('emvideo', $item['provider'], 'thumbnail', '', $item, '', '', '', '');
  }
  return $item;
}

/**
 * Helper function which invokes the emvideo 'data' hook of the video provider.
 */
function _fbsmp_link_emvideo_parse_links($settings, $match) {
  //Get just the URL.
  $match[2] = check_url(decode_entities($match[2]));
  $field = _fbsmp_link_emvideo_create_field($settings);

  //Build our embed item.
  $item = emfield_parse_embed($field, $match[2], 'emvideo');
  // Check to make sure the provider that was found is an allowed provider.
  if ($field['providers'][$item['provider']]) {
    $item['data'] = (array)emfield_include_invoke('emvideo', $item['provider'], 'data', $field, $item);
  }
  else {
    return '';
  }

  return serialize($item);
}

/**
 * Creates a fake field for emfield.
 *
 * @param $settings
 *   An array which contains the following keys:
 *   - emvideo_providers
 *       An array containing the allowed video providers. Defaults to none.
 *   - emvideo_height
 *       An integer specifying the height of the embedded video. Defaults to 435.
 *   - emvideo_width
 *       An integer specifying the height of the embedded video. Defaults to 350.
 *   - emvideo_autoplay
 *       A boolean specifying whether to autoplay the embedded video. Defaults to 0.
 *
 * @return
 *   An emvideo field.
 */
function _fbsmp_link_emvideo_create_field($settings) {
  //Build a fake field.
  $field = array(
    'field_name' => 'fbsmp_link_emvideo',
    'type' => 'emvideo',
    'video_width' => empty($settings['emvideo_width']) ? $settings['default_emvideo_width'] : $settings['emvideo_width'],
    'video_height' => empty($settings['emvideo_height']) ? $settings['default_emvideo_height'] : $settings['emvideo_height'],
    'video_autoplay' => $settings['emvideo_autoplay'],
    'providers' =>  $settings['emvideo_providers'],
  );

  return $field;
}

function _fbsmp_link_emvideo_curry($func, $arity) {
  return create_function('', "
    \$args = func_get_args();
    if(count(\$args) >= $arity)
        return call_user_func_array('$func', \$args);
    \$args = var_export(\$args, 1);
    return create_function('','
        \$a = func_get_args();
        \$z = ' . \$args . ';
        \$a = array_merge(\$z,\$a);
        return call_user_func_array(\'$func\', \$a);
    ');
  ");
}

/**
 * Generates the embedded code for the shared video.
 *
 * @param $attachment
 *   The attachment object. It contains an array containing the raw data, 
 *   provider and the data version. ($attachment->data['emfield_data'])
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - emvideo_providers
 *       An array containing the allowed video providers. Defaults to none.
 *   - emvideo_height
 *       An integer specifying the height of the embedded video. Defaults to 435.
 *   - emvideo_width
 *       An integer specifying the height of the embedded video. Defaults to 350.
 *   - emvideo_autoplay
 *       A boolean specifying whether to autoplay the embedded video. Defaults to 0.
 *
 * @return
 *   A string containing the embedded code.
 */
function theme_fbsmp_link_emvideo($attachment, $settings = array()) {
  $settings += array(
    'emvideo_width' => FBEMP_LINK_EMVIDEO_DEFAULT_VIDEO_WIDTH,
    'emvideo_height' => FBSMP_LINK_EMVIDEO_DEFAULT_VIDEO_HEIGHT,
    'emvideo_autoplay' => 0,
    'emvideo_providers' => array(),
  );

  $field = _fbsmp_link_emvideo_create_field($settings);
  $options = array(
    'width' => $field['video_width'],
    'height' => $field['video_height'],
    'autoplay' => $field['video_autoplay'],
  );
  $display_format = "video_video";
  
  $emfield_item = $attachment->data['emfield_data'];
  $emfield_item['embed'] = TRUE;
  
  $content = emfield_emfield_field_formatter($field, $emfield_item, $display_format, NULL, 'emvideo', $options);
  $output = '';
  $output .= '<div class="fbsmp-link-emvideo">';
  $output .= $content;
  $output .= '</div>';
  return $output;
}

/**
 * Settings form for Link-Emvideo integration.
 */
function _fbsmp_link_emvideo_settings_form(&$form_state, $settings = array()) {
  $form = array();

  $module = 'emvideo';
  $providers = emfield_system_list($module);
  foreach ($providers as $provider) {
    if (variable_get('emfield_'. $module .'_allow_'. $provider->name, TRUE)) {
      $info = emfield_include_invoke($module, $provider->name, 'info');
      $options[$provider->name] = $info['name'];
    }
  }
  $form['provider_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Providers Supported'),
    '#description' => t('Select which third party providers you wish to allow from the list below. When a user submits new content, the URL they enter will be matched to the provider, assuming that provider is allowed here.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['provider_list']['emvideo_providers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Providers'),
    '#default_value' => empty($settings['emvideo_providers']) ? array() : $settings['emvideo_providers'],
    '#options' => $options,
  );

  $form['video'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video Display Settings'),
    '#description' => t('These settings control how this video is displayed in its full size'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['video']['emvideo_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Video display width'),
    '#default_value' => empty($settings['emvideo_width']) ? $settings['default_emvideo_width'] : $settings['emvideo_width'],
    '#required' => TRUE,
    '#description' => t('The width of the embedded video. It defaults to @width.', array('@width' => $settings['default_emvideo_width'])),
  );
  $form['video']['emvideo_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Video display height'),
    '#default_value' => empty($settings['emvideo_height']) ? $settings['default_emvideo_height'] : $settings['emvideo_height'],
    '#required' => TRUE,
    '#description' => t('The height of the video. It defaults to @height.', array('@height' => $settings['default_emvideo_height'])),
  );
  $form['video']['emvideo_autoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Autoplay'),
    '#default_value' => empty($settings['emvideo_autoplay']) ? '' : $settings['emvideo_autoplay'],
    '#description' => t('If supported by the provider, checking this box will cause the video to automatically begin after the video loads.'),
  );
  $form['video']['emvideo_inline_video_replacement'] = array(
    '#type' => 'checkbox',
    '#title' => t('Video inline replacement'),
    '#default_value' => empty($settings['emvideo_inline_video_replacement']) ? '' : $settings['emvideo_inline_video_replacement'],
    '#description' => t('Checking this box will cause the video to be delay loaded, only when the user clicks on the thumbnail.'),
  );
  return $form;
}

/**
 * Validation for the settings form
 */
function _fbsmp_link_emvideo_settings_form_validate(&$form, &$form_state) {
  $form_values = $form_state['values'];
  foreach (array('emvideo_height' => 'video height', 'emvideo_width' => 'video width') as $attr => $desc) {
    if (!empty($form_values[$attr]) && (!is_numeric($form_values[$attr]) || $form_values[$attr] != round($form_values[$attr]) || $form_values[$attr] < 0)) {
      form_set_error($attr, t('The @attribute must be a non-negative integer.', array('@attribute' => $desc)));
    }
  }
}

/**
 * Submit function for the settings form.
 */
function _fbsmp_link_emvideo_settings_form_submit(&$form, &$form_state) {
  $settings = array();
  $settings['emvideo_providers'] = $form_state['values']['emvideo_providers'];
  $settings['emvideo_width'] = $form_state['values']['emvideo_width'];
  $settings['emvideo_height'] = $form_state['values']['emvideo_height'];
  $settings['emvideo_autoplay'] = $form_state['values']['emvideo_autoplay'];
  $settings['emvideo_inline_video_replacement'] = $form_state['values']['emvideo_inline_video_replacement'];

  return $settings;
}

/**
 * Menu callback for inline video replacement.
 */
function fbsmp_link_emvideo_video_replace($sid) {
  $attachment = fbsmp_load($sid);
  $settings = fbsmp_load_plugin_settings('link');
  
  print theme('fbsmp_link_emvideo', $attachment, $settings);
}