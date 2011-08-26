<?php

/**
 * @file
 *   Integration of Link plugin with Emaudio.
 */

define('FBEMP_LINK_EMAUDIO_DEFAULT_AUDIO_WIDTH', 435);
define('FBSMP_LINK_EMAUDIO_DEFAULT_AUDIO_HEIGHT', 350);

/**
 * Matches the URL with HTTP/HTTPS and passes it to link checker.
 *
 * @param $url
 *  The shared URL.
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - emaudio_providers
 *       An array containing the allowed audio providers. Defaults to none.
 *   - emaudio_height
 *       An integer specifying the height of the embedded audio. Defaults to 435.
 *   - emaudio_width
 *       An integer specifying the height of the embedded audio. Defaults to 350.
 *   - emaudio_autoplay
 *       A boolean specifying whether to autoplay the embedded audio. Defaults to 0.
 *
 * @return
 *   An array containing the required emaudio data and thumbnails.
 */
function _fbsmp_link_emaudio_data($url, $settings = array()) {
  $settings += array(
    'emaudio_width' => 435,
    'emaudio_height' => 350,
    'emaudio_autoplay' => 0,
    'emaudio_providers' => array(),
  );

  $url = ' '. $url .' ';

  //Need to attach the variables to the callback after the regex.
  $callback = _fbsmp_link_emaudio_curry('_fbsmp_link_emaudio_parse_links', 2);

  // Match absolute URLs.
  $item = preg_replace_callback("`(<p>|<li>|<br\s*/?>|[ \n\r\t\(])((http://|https://)([a-zA-Z0-9@:%_+*~#?&=.,/;-]*[a-zA-Z0-9@:%_+*~#&=/;-]))([.,?!]*?)(?=(</p>|</li>|<br\s*/?>|[ \n\r\t\)]))`i", $callback($settings), $url);
  $item = unserialize($item);
  if (is_array($item)) {
    $item['image'] = emfield_include_invoke('emaudio', $item['provider'], 'thumbnail', '', $item, '', '', '', '');
  }
  return $item;
}

/**
 * Helper function which invokes the emaudio 'data' hook of the audio provider.
 */
function _fbsmp_link_emaudio_parse_links($settings, $match) {
  //Get just the URL.
  $match[2] = check_url(decode_entities($match[2]));
  $field = _fbsmp_link_emaudio_create_field($settings);

  //Build our embed item.
  $item = emfield_parse_embed($field, $match[2], 'emaudio');
  // Check to make sure the provider that was found is an allowed provider.
  if ($field['providers'][$item['provider']]) {
    $item['data'] = (array)emfield_include_invoke('emaudio', $item['provider'], 'data', $field, $item);
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
 *   - emaudio_providers
 *       An array containing the allowed audio providers. Defaults to none.
 *   - emaudio_height
 *       An integer specifying the height of the embedded audio. Defaults to 435.
 *   - emaudio_width
 *       An integer specifying the height of the embedded audio. Defaults to 350.
 *   - emaudio_autoplay
 *       A boolean specifying whether to autoplay the embedded audio. Defaults to 0.
 *
 * @return
 *   An emaudio field.
 */
function _fbsmp_link_emaudio_create_field($settings) {
  //Build a fake field.
  $field = array(
    'field_name' => 'fbsmp_link_emaudio',
    'type' => 'emaudio',
    'audio_width' => empty($settings['emaudio_width']) ? $settings['default_emaudio_width'] : $settings['emaudio_width'],
    'audio_height' => empty($settings['emaudio_height']) ? $settings['default_emaudio_height'] : $settings['emaudio_height'],
    'audio_autoplay' => $settings['emaudio_autoplay'],
    'providers' =>  $settings['emaudio_providers'],
  );

  return $field;
}

function _fbsmp_link_emaudio_curry($func, $arity) {
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
 * Generates the embedded code for the shared audio.
 *
 * @param $attachment
 *   The attachment object. It contains an array containing the raw data, 
 *   provider and the data version. ($attachment->data['emfield_data'])
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - emaudio_providers
 *       An array containing the allowed audio providers. Defaults to none.
 *   - emaudio_height
 *       An integer specifying the height of the embedded audio. Defaults to 435.
 *   - emaudio_width
 *       An integer specifying the height of the embedded audio. Defaults to 350.
 *   - emaudio_autoplay
 *       A boolean specifying whether to autoplay the embedded audio. Defaults to 0.
 *
 * @return
 *   A string containing the embedded code.
 */
function theme_fbsmp_link_emaudio($attachment, $settings = array()) {
  $settings += array(
    'emaudio_width' => 435,
    'emaudio_height' => 350,
    'emaudio_autoplay' => 0,
    'emaudio_providers' => array(),
  );

  $field = _fbsmp_link_emaudio_create_field($settings);
  $options = array(
    'width' => $field['audio_width'],
    'height' => $field['audio_height'],
    'autoplay' => $field['audio_autoplay'],
  );
  $display_format = "audio_audio";
  $content = emfield_emfield_field_formatter($field, $attachment->data['emfield_data'], $display_format, NULL, 'emaudio', $options);
  $output = '';
  $output .= '<div class="fbsmp-link-emaudio">';
  $output .= $content;
  $output .= '</div>';
  return $output;
}

/**
 * Settings form for Link-emaudio integration.
 */
function _fbsmp_link_emaudio_settings_form(&$form_state, $settings = array()) {
  $form = array();

  $module = 'emaudio';
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
  $form['provider_list']['emaudio_providers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Providers'),
    '#default_value' => empty($settings['emaudio_providers']) ? array() : $settings['emaudio_providers'],
    '#options' => $options,
  );

  $form['audio'] = array(
    '#type' => 'fieldset',
    '#title' => t('Audio Display Settings'),
    '#description' => t('These settings control how this audio is displayed in its full size'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['audio']['emaudio_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Audio display width'),
    '#default_value' => empty($settings['emaudio_width']) ? $settings['default_emaudio_width'] : $settings['emaudio_width'],
    '#required' => TRUE,
    '#description' => t('The width of the embedded audio. It defaults to @width.', array('@width' => $settings['default_emaudio_width'])),
  );
  $form['audio']['emaudio_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Audio display height'),
    '#default_value' => empty($settings['emaudio_height']) ? $settings['default_emaudio_height'] : $settings['emaudio_height'],
    '#required' => TRUE,
    '#description' => t('The height of the audio. It defaults to @height.', array('@height' => $settings['default_emaudio_height'])),
  );
  $form['audio']['emaudio_autoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Autoplay'),
    '#default_value' => empty($settings['emaudio_autoplay']) ? '' : $settings['emaudio_autoplay'],
    '#description' => t('If supported by the provider, checking this box will cause the audio to automatically begin after the audio loads.'),
  );
  
  return $form;
}

/**
 * Validation for the settings form
 */
function _fbsmp_link_emaudio_settings_form_validate(&$form, &$form_state) {
  $form_values = $form_state['values'];
  foreach (array('emaudio_height' => 'audio height', 'emaudio_width' => 'audio width') as $attr => $desc) {
    if (!empty($form_values[$attr]) && (!is_numeric($form_values[$attr]) || $form_values[$attr] != round($form_values[$attr]) || $form_values[$attr] < 0)) {
      form_set_error($attr, t('The @attribute must be a non-negative integer.', array('@attribute' => $desc)));
    }
  }
}

/**
 * Submit function for the settings form.
 */
function _fbsmp_link_emaudio_settings_form_submit(&$form, &$form_state) {
  $settings = array();
  $settings['emaudio_providers'] = $form_state['values']['emaudio_providers'];
  $settings['emaudio_width'] = $form_state['values']['emaudio_width'];
  $settings['emaudio_height'] = $form_state['values']['emaudio_height'];
  $settings['emaudio_autoplay'] = $form_state['values']['emaudio_autoplay'];

  return $settings;
}