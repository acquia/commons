<?php

/**
 * @file
 *   Allows users to attach documents (such as ppt, docx, pdf, etc)
 *   via SlideShare with their FBSS status.
 */

define('FBSMP_SLIDESHARE_CONVERSION_PENDING', 0);
define('FBSMP_SLIDESHARE_CONVERSION_ACTIVE', 1);
define('FBSMP_SLIDESHARE_CONVERSION_COMPLETE', 2);
define('FBSMP_SLIDESHARE_CONVERSION_FAILED', 3);
define('FBSMP_SLIDESHARE_UPLOAD_PENDING', 4);
define('FBSMP_SLIDESHARE_UPLOAD_COMPLETE', 5);
define('FBSMP_SLIDESHARE_UPLOAD_FAILED', 6);

define('FBSMP_SLIDESHARE_OPERATION_DELETE', 'DELETE');
define('FBSMP_SLIDESHARE_OPERATION_UPLOAD', 'UPLOAD');
define('FBSMP_SLIDESHARE_OPERATION_EDIT', 'EDIT');
define('FBSMP_SLIDESHARE_OPERATION_SLIDESHOW', 'SLIDESHOW');

define('FBSMP_SLIDESHARE_UPLOAD_URL', "http://www.slideshare.net/api/2/upload_slideshow");
define('FBSMP_SLIDESHARE_SLIDESHOW_URL', "http://www.slideshare.net/api/2/get_slideshow");
define('FBSMP_SLIDESHARE_DELETE_URL', "http://www.slideshare.net/api/2/delete_slideshow");
define('FBSMP_SLIDESHARE_EDIT_URL', "http://www.slideshare.net/api/2/edit_slideshow");

define('FBSMP_SLIDESHARE_CACHE_KEY_PREFIX', "fbsmp_slideshare");

fbsmp_include_library('file.inc', 'file');
fbsmp_include_library('http_request.inc', 'http_request');

/**
 * Implementation of hook_fbsmp_admin_settings_form().
 */
function fbsmp_slideshare_fbsmp_admin_settings_form(&$form_state) {
  $prev_settings = fbsmp_load_plugin_settings('slideshare');
  
  $form = array();
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => FALSE,
  );
  $form['general']['file_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Permitted upload file extensions'),
    '#default_value' => $prev_settings['file_extensions'],
    '#size' => 64,
    '#description' => t('Extensions a user can upload to this field. Separate extensions with a space and do not include the leading dot. Leaving this blank will allow users to upload a file with any extension.'),
  );
  
  $form['general']['max_filesize'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum upload size per file'),
    '#default_value' => $prev_settings['max_filesize'],
    '#description' => t('Specify the size limit that applies to each file separately. Enter a value like "512" (bytes), "80K" (kilobytes) or "50M" (megabytes) in order to restrict the allowed file size. If you leave this this empty the file sizes will be limited only by PHP\'s maximum post and file upload sizes (current limit <strong>%limit</strong>).', array('%limit' => format_size(file_upload_max_size()))),
  );
  
  $form['general']['cache_duration'] = array(
    '#type' => 'select',
    '#title' => t('Cache duration'),
    '#options' => drupal_map_assoc(array(0, 3600, 10800, 21600, 32400, 43200, 86400, 172800, 259200, 604800, 1209600, 2419200, 4838400, 9676800, 15724800, 31449600), 'format_interval'),
    '#default_value' => $prev_settings['cache_duration'],
    '#description' => t('The slideshow retrieved from the SlideShare will be cached for the set time period to improve performance. Set Zero (0) to disable caching.'),
  );

  $form['path_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Path settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['path_settings']['file_path'] = array(
    '#type' => 'textfield',
    '#title' => t('File path'),
    '#default_value' => $prev_settings['file_path'],
    '#description' => t('Optional subdirectory within the "%directory" directory where document files will be stored. Do not include preceding or trailing slashes.', array('%directory' => variable_get('file_directory_path', 'files') . '/')),
    '#suffix' => theme('token_help', 'user'),
  );
  
  $form['slideshare_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('SlideShare settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['slideshare_settings']['slideshare_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => $prev_settings['slideshare_username'],
    '#required' => TRUE,
    '#description' => t('Username of the requesting user. <a href="!slideshare_signup">Signup</a> if not a member already.', array('!slideshare_signup' => url('http://www.slideshare.net/signup')))
  );
  $form['slideshare_settings']['slideshare_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#default_value' => $prev_settings['slideshare_password'],
    '#required' => TRUE,
    '#description' => t('Password of the requesting user.')
  );
  $form['slideshare_settings']['slideshare_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => $prev_settings['slideshare_api_key'],
    '#required' => TRUE,
    '#description' => t('Set this to the API Key that SlideShare has provided for you. <a href="!slideshare_apikey">Apply for API key</a>', array('!slideshare_apikey' => url('http://www.slideshare.net/developers/applyforapi')))
  );
  $form['slideshare_settings']['slideshare_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Shared secret'),
    '#default_value' => $prev_settings['slideshare_secret'],
    '#required' => TRUE,
    '#description' => t('Set this to the Secret Key that SlideShare has provided for you.')
  );
  return $form;
}

/**
 * Implementation of hook_fbsmp_admin_settings_form_validate().
 */
function fbsmp_slideshare_fbsmp_admin_settings_form_validate(&$form, &$form_state) {
  
  // Check that only web images are specified in the callback.
  $form_values = $form_state['values'];
  $extensions = array_filter(explode(' ', $form_values['file_extensions']));
  $web_extensions = fbsmp_slideshare_allowed_extensions();
  if (count(array_diff($extensions, $web_extensions))) {
    form_set_error('file_extensions', t('Only documents with extensions (@extensions) are supported through the SlideShare plugin.', array('@extensions' => implode(', ', $web_extensions))));
  }
  //Check that set filesize is valid
  if (!empty($form_values['max_filesize']) && !is_numeric(parse_size($form_values['max_filesize']))) {
    form_set_error('max_filesize', t('The "Maximum upload size" option must contain a valid value. You can either leave the text field empty or enter a string like "512" (bytes), "80K" (kilobytes) or "50M" (megabytes).'));
  }
  
  //Check the validity of the file path.
  //Strip slashes from the beginning and end of $widget['file_path']
  $form_values['file_path'] = trim($form_values['file_path'], '\\/');

  //Do not allow the file path to be the same as the file_directory_path().
  //This causes all sorts of problems with things like file_create_url().
  if (strpos($form_values['file_path'], file_directory_path()) === 0) {
    form_set_error('file_path', t('The file path (@file_path) cannot start with the system files directory (@files_directory), as this may cause conflicts when building file URLs.', array('@file_path' => $form_values['file_path'], '@files_directory' => file_directory_path())));
  }
}

/**
 * Implementation of hook_fbsmp_admin_settings_form_submit().
 */
function fbsmp_slideshare_fbsmp_admin_settings_form_submit(&$form, &$form_state) {
  $form_values = $form_state['values'];
  $settings = array();
  $settings['file_extensions'] = $form_values['file_extensions'];
  $settings['max_filesize'] = $form_values['max_filesize'];
  $settings['file_path'] = $form_values['file_path'];
  $settings['cache_duration'] = $form_values['cache_duration'];
  $settings['slideshare_username'] = $form_values['slideshare_username'];
  $settings['slideshare_password'] = $form_values['slideshare_password'];
  $settings['slideshare_api_key'] = $form_values['slideshare_api_key'];
  $settings['slideshare_secret'] = $form_values['slideshare_secret'];
  
  fbsmp_save_plugin_settings($settings, 'slideshare');
}

/**
 * Implementation of hook_fbsmp_widget_form().
 */
function fbsmp_slideshare_fbsmp_widget_form(&$form_state) {

  $form = array();
  $settings = fbsmp_load_plugin_settings('slideshare');
  $settings['file_extensions'] = !empty($settings['file_extensions']) ? $settings['file_extensions'] : implode(' ', fbsmp_slideshare_allowed_extensions());
  
  $max_filesize = parse_size(file_upload_max_size());
  if (!empty($settings['max_filesize']) && parse_size($settings['max_filesize']) < $max_filesize) {
    $max_filesize = parse_size($settings['max_filesize']);
  }
  $desc[] = t('Allowed Extensions: @ext', array('@ext' => $settings['file_extensions']));
  $desc[] = t('Maximum Filesize: @size', array('@size' => format_size($max_filesize)));
  
  $form['fbsmp_slideshare_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title (Required)'),
    '#description' => t('The title of the slideshow.'),
    '#default_value' => $form_state['values']['fbsmp_slideshare_title'] ? $form_state['values']['fbsmp_slideshare_title']: '',
    '#size' => 22,
  );
  $form['fbsmp_slideshare_upload'] = array(
    '#type' => 'file',
    '#description' => implode('<br />', $desc),
    '#size' => 22,
    '#upload_validators' => fbsmp_slideshare_widget_upload_validators($settings),
    '#settings' => $settings,
  );
  return $form;
}

/**
 * Implementation of hook_fbsmp_widget_form_validate().
 */
function fbsmp_slideshare_fbsmp_widget_form_validate(&$form, &$form_state) {
  $title = trim($form_state['values']['fbsmp_slideshare_title']);
  if (!$title) {
    form_set_error('fbsmp_slideshare_title', t('The title of the slideshow is required.'));
    return 0;
  }
  
  $settings = $form['fbsmp']['fbsmp_slideshare_upload']['#settings'];
  $upload_name = 'fbsmp_slideshare_upload';
  $dest = _fbsmp_file_create_path($settings['file_path']);
  if (!_fbsmp_file_check_directory($dest, FILE_CREATE_DIRECTORY)) {
    watchdog('fbsmp', 'The upload directory %directory could not be created or is not accessible. A newly uploaded slideshare document could not be saved in this directory as a consequence, and the upload was canceled.', array('%directory' => $dest));
    form_set_error($upload_name, t('The document could not be uploaded.'));
    return 0;
  }
  if ($file = _fbsmp_file_save_upload($upload_name, $form['fbsmp'][$upload_name]['#upload_validators'], $dest)) {
    $form_state['values']['fbsmp_slideshare_upload'] = $file->fid;
  }
  else {
    form_set_error($upload_name, t('The document could not be uploaded.')); 
  }
}

/**
 * Implementation of hook_fbsmp_widget_form_save().
 */
function fbsmp_slideshare_fbsmp_widget_form_save($form, $form_state) {
  $fid = $form_state['values']['fbsmp_slideshare_upload'];
  $title = $form_state['values']['fbsmp_slideshare_title'];
  $file = _fbsmp_file_load($fid);
  file_set_status($file, FILE_STATUS_PERMANENT);  //Cache the file.
  
  $settings = fbsmp_load_plugin_settings('slideshare');
  $slideshare_id = 0;
  if ($id = fbsmp_slideshare_upload_file_slideshare($file->filepath, $settings, $title)) {
    $slideshare_id = $id;
  }
  
  $record = array(
    'fid' => $fid,
    'title' => $title,
    'slideshare_id' => $slideshare_id
  );
  return $record;
}

/**
 * Break out for fbsmp_fbsmp_delete().
 */
function fbsmp_slideshare_fbsmp_delete($status) {
  $attachment_data = $status->attachment->data;
  _fbsmp_file_delete(_fbsmp_file_load($attachment_data['fid']));
  $settings = fbsmp_load_plugin_settings('slideshare');
  fbsmp_slideshare_delete_file_slideshare($attachment_data['slideshare_id'], $settings);
}

/**
 * Implementation of hook_fbsmp_subtheme().
 */
function fbsmp_slideshare_fbsmp_subtheme() {
  return array(
    'fbsmp_slideshare_attachment'  => array(
      'arguments' => array('attachment' => NULL, 'settings' => NULL),
      'file' => 'plugins/slideshare.inc',
    )
  );
}

/**
 * Implementation of hook_fbsmp_themed_attachment().
 */
function fbsmp_slideshare_fbsmp_themed_attachment($attachment) {
  $settings = fbsmp_load_plugin_settings('slideshare');
  return theme('fbsmp_slideshare_attachment', $attachment, $settings);
}

/**
 * Themes a document or presentation.
 *
 * @param $attachment
 *   The attacment object.
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - slideshare_api_key
 *       API key provided by SlideShare.
 *   - slideshare_secret
 *       Secret key provided by SlideShare.
 *   - cache_duration
 *       Set this to the time period after which the slideshow cache entry 
 *       should expire (in seconds). Default is 9676800 seconds (16 weeks)
 *
 * @return
 *   Return the HTML code to embed for the slideshow.
 */
function theme_fbsmp_slideshare_attachment($attachment, $settings = array()) {
  $slideshow = fbsmp_slideshare_get_slideshow($attachment->data['slideshare_id'], $settings);
  if ($slideshow && $slideshow['status'] == FBSMP_SLIDESHARE_CONVERSION_COMPLETE && $slideshow['embed']) {
    return $slideshow['embed'];
  }
  return '';
}

/**
 * Implementation of hook_fbsmp_token_list().
 */
function fbsmp_slideshare_fbsmp_token_list() {
  return array(
    'slideshare-document-title' => t('The title of the shared document.'),
    'slideshare-document-url' => t('The web permalink for the document on SlideShare'),
    'slideshare-document-thumbnail' => t('The URL of the thumbnail of the document.'),
    'slideshare-document-download-url' => t('The download URL of the document, if available'),
    'slideshare-document-status' => t('0 if queued for conversion, 1 if converting, 2 if converted successfully, 3 if conversion failed'),
    'slideshare-document-embed-code' => t('The embed code to insert the document slideshow if converted successfully'),
    'slideshare-document-slideshow-type' => t('The type of the slideshow (presentation, document, portfolio or video).')
  );
}

/**
 * Implementation of hook_fbsmp_token_values().
 */
function fbsmp_slideshare_fbsmp_token_values($attachment) {
  $settings = fbsmp_load_plugin_settings('slideshare');
  $slideshow = fbsmp_slideshare_get_slideshow($attachment->data['slideshare_id'], $settings);
  
  if (!$slideshow) {
    $slideshow = array();
  }
  
  $document_map = array(
    '0' => 'presentaion',
    '1' => 'document',
    '2' => 'portfolio',
    '3' => 'video'
  );
  
  return array(
    'slideshare-document-title' => check_plain($slideshow['title']),
    'slideshare-document-url' => check_url($slideshow['url']),
    'slideshare-document-thumbnail' => check_url($slideshow['thumbnail_url']),
    'slideshare-document-download-url' => check_url($slideshow['download_url']),
    'slideshare-document-status' => $slideshow['status'],
    'slideshare-document-embed-code' => $slideshow['embed'],
    'slideshare-document-slideshow-type' => $document_map[$slideshow['slideshow_type']]
  );
}

/**
 * Get the upload validators for a slideshare document upload field.
 *
 * @param $settings
 *   The settings array for the plugin.
 * @return
 *   An array suitable for passing to file_save_upload() or the file field
 *   element's '#upload_validators' property.
 */
function fbsmp_slideshare_widget_upload_validators($settings) {
  $max_filesize = parse_size(file_upload_max_size());
  if (!empty($settings['max_filesize']) && parse_size($settings['max_filesize']) < $max_filesize) {
    $max_filesize = parse_size($settings['max_filesize']);
  }

  $validators = array(
    '_fbsmp_file_validate_size' => array($max_filesize),
    '_fbsmp_file_validate_extensions' => array($settings['file_extensions']),
  );
  
  return $validators;
}

/**
 * Returns the file extensions supported by SlideShare
 */
function fbsmp_slideshare_allowed_extensions() {
  return array(
    'ppt', 'pps', 'pptx', 'ppsx', 'pot', 'potx',
    'odp',
    'pdf',
    'doc', 'docx', 'rtf', 'xls',
    'odt', 'ods'
  );
}

function fbsmp_slideshare_upload_file_slideshare($filepath, $settings, $title) {
  if (!is_file($filepath) || !$settings['slideshare_username'] || !$settings['slideshare_password'] || !$settings['slideshare_secret'] || !$settings['slideshare_api_key'] || !check_plain($title)) {
    return FALSE;
  }
  $file_url = file_create_url($filepath);
  $timestamp  = time();
  
  $params     = array('api_key'               => $settings['slideshare_api_key'],
                      'ts'                    => $timestamp,
                      'hash'                  => sha1($settings['slideshare_secret'] . $timestamp),
                      'username'              => $settings['slideshare_username'],
                      'password'              => $settings['slideshare_password'],
                      'slideshow_title'       => check_plain($title),
                      'upload_url'            => $file_url
                    );
  
  $request_url = url(FBSMP_SLIDESHARE_UPLOAD_URL, array('query' => $params, 'external' => TRUE));
  $result = fbsmp_http_request($request_url);
  if ($result->code != 200) {
    return FALSE;
  }
  return fbsmp_slideshare_parse_xml($result->data);
}

function fbsmp_slideshare_delete_file_slideshare($slideshare_id, $settings) {
  if (!$settings['slideshare_username'] || !$settings['slideshare_password'] || !$settings['slideshare_secret'] || !$settings['slideshare_api_key'] || !$slideshare_id) {
    return FALSE;
  }
  $timestamp  = time();
  $params     = array('api_key'               => $settings['slideshare_api_key'],
                      'ts'                    => $timestamp,
                      'hash'                  => sha1($settings['slideshare_secret'] . $timestamp),
                      'username'              => $settings['slideshare_username'],
                      'password'              => $settings['slideshare_password'],
                      'slideshow_id'          => $slideshare_id
                    );
  
  $request_url = url(FBSMP_SLIDESHARE_DELETE_URL, array('query' => $params, 'external' => TRUE));
  $result = fbsmp_http_request($request_url);
  
  if ($result->code != 200) {
    return FALSE;
  }
  return fbsmp_slideshare_parse_xml($result->data);
}

function fbsmp_slideshare_get_slideshow($slideshare_id, $settings) {
  //Merge the default settings.
  $settings += array(
    'cache_duration' => 9676800,
  );
  
  //Create the cid for the cache table.
  $cache_key = FBSMP_SLIDESHARE_CACHE_KEY_PREFIX .":". $slideshare_id;
  if ($settings['cache_duration'] && $cache = cache_get($cache_key, 'cache')) {
    return $cache->data;
  }

  if (!$settings['slideshare_secret'] || !$settings['slideshare_api_key'] || !$slideshare_id) {
    return FALSE;
  }
  $timestamp  = time();
  $params     = array('api_key'               => $settings['slideshare_api_key'],
                      'ts'                    => $timestamp,
                      'hash'                  => sha1($settings['slideshare_secret'] . $timestamp),
                      'slideshow_id'          => $slideshare_id
                    );
  
  $request_url = url(FBSMP_SLIDESHARE_SLIDESHOW_URL, array('query' => $params, 'external' => TRUE));
  $result = fbsmp_http_request($request_url);
  
  if ($result->code != 200) {
    return FALSE;
  }
  $slideshow = fbsmp_slideshare_parse_xml($result->data);
  if ($slideshow && $slideshow['status'] == FBSMP_SLIDESHARE_CONVERSION_COMPLETE && $settings['cache_duration']) {
    cache_set($cache_key, $slideshow, 'cache', time() + $settings['cache_duration']);
  }
  
  return $slideshow;
}

function fbsmp_slideshare_parse_xml($string) {
  if (!defined('LIBXML_VERSION') || (version_compare(phpversion(), '5.1.0', '<'))) {
    @ $xml = simplexml_load_string($string, NULL);
  }
  else {
    @ $xml = simplexml_load_string($string, NULL, LIBXML_NOERROR | LIBXML_NOWARNING | LIBXML_NOCDATA);
  }
  
  //Got a malformed XML.
  if ($xml === FALSE || is_null($xml)) {
    return FALSE;
  }
  
  $operation_type = _fbsmp_slideshare_operation_detect($xml);
  
  switch ($operation_type) {
    case FBSMP_SLIDESHARE_OPERATION_DELETE:
    case FBSMP_SLIDESHARE_OPERATION_UPLOAD:
    case FBSMP_SLIDESHARE_OPERATION_EDIT:
      return (string)$xml->SlideShowID;
    case FBSMP_SLIDESHARE_OPERATION_SLIDESHOW:
      $node = array();
      $node['id']           = (string)$xml->ID;
      $node['title']        = (string)$xml->Title;
      $node['description']  = (string)$xml->Description;
      $node['embed']        = html_entity_decode((string)$xml->Embed);
      $node['status']       = (string)$xml->Status;
      $node['url']          = (string)$xml->URL;
      $node['download']     = (string)$xml->Download;
      $node['download_url'] = (string)$xml->DownloadUrl;
      $node['thumbnail_url'] = (string)$xml->ThumbnailURL;
      $node['slideshow_type'] = (string)$xml->SlideshowType;
      return $node;
    default:
      return FALSE;
  }
}

/**
 * Determine the slideshare operation of a SimpleXML parsed object structure.
 *
 * @param $xml
 *  SimpleXML-preprocessed XML.
 * @return
 *  The operation type (one of upload, slideshow, delete, edit) or FALSE if not compatible.
 */
function _fbsmp_slideshare_operation_detect($xml) {
  if (!is_object($xml)) {
    return FALSE;
  }
  $type = strtolower($xml->getName());
  
  if ($type == "slideshowuploaded") {
    return FBSMP_SLIDESHARE_OPERATION_UPLOAD;
  }
  elseif ($type == "slideshowdeleted") {
    return FBSMP_SLIDESHARE_OPERATION_DELETE;
  }
  elseif ($type == "slideshowedited") {
    return FBSMP_SLIDESHARE_OPERATION_EDIT;
  }
  elseif ($type == "slideshow") {
    return FBSMP_SLIDESHARE_OPERATION_SLIDESHOW;
  }
  else {
    return FALSE;
  }
}
