<?php

/**
 * @file
 *   Allows users to attach videos with their FBSS status.
 */
define('FBSMP_VIDEO_CONVERSION_NONE', 0); 
define('FBSMP_VIDEO_CONVERSION_PENDING', 5);
define('FBSMP_VIDEO_CONVERSION_ACTIVE', 10);
define('FBSMP_VIDEO_CONVERSION_COMPLETE', 15);
define('FBSMP_VIDEO_CONVERSION_FAILED', 20);

fbsmp_include_library('ffmpeg.inc', 'ffmpeg');

/**
 * Implementation of hook_fbsmp_admin_settings_form().
 */
function fbsmp_video_fbsmp_admin_settings_form(&$form_state) {
  if (!module_exists('swftools')) {
    drupal_set_message(
      t('You must install <a href="!swftools">SWFTools</a> module to display the <i>FLV</i> or <i>F4V</i> videos.', array('!swftools' => 'http://drupal.org/project/swftools')),
      'error'
    );
  }
  $prev_settings = fbsmp_load_plugin_settings('video');
  
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
    '#description' => t('Extensions a user can upload to this field. Separate extensions with a space and do not include the leading dot. Leaving this blank will allow users to upload a file with any allowed video extension.'),
  );
  
  $form['general']['max_filesize'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum upload size per file'),
    '#default_value' => $prev_settings['max_filesize'],
    '#description' => t('Specify the size limit that applies to each file separately. Enter a value like "512" (bytes), "80K" (kilobytes) or "50M" (megabytes) in order to restrict the allowed file size. If you leave this this empty the file sizes will be limited only by PHP\'s maximum post and file upload sizes (current limit <strong>%limit</strong>).', array('%limit' => format_size(file_upload_max_size()))),
  );

  //@todo: Integrate it with filefield_paths module
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
    '#description' => t('Optional subdirectory within the "%directory" directory where video files will be stored. Do not include preceding or trailing slashes.', array('%directory' => variable_get('file_directory_path', 'files') . '/')),
    '#suffix' => theme('token_help', 'user'),
  );
  
  $form['ffmpeg'] = array(
    '#type' => 'fieldset',
    '#title' => t('FFMPEG settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['ffmpeg']['ffmpeg_path'] = array(
    '#type' => 'textfield',
    '#title' => t('FFMPEG path'),
    '#default_value' => $prev_settings['ffmpeg_path'],
    '#description' => t('Optional path to the ffmpeg binary. Defaults to %default_ffmpeg_path', array('%default_ffmpeg_path' => '/usr/bin/ffmpeg'))
  );
  
  $form['ffmpeg']['thumbnails'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video thumbnail options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['ffmpeg']['thumbnails']['enable_thumbnails'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically generate video thumbnails'),
    '#default_value' => $prev_settings['enable_thumbnails'],
    '#description' => t('Check this option to generate thumbnails for the uploaded video using %transcoder', array('%transcoder' => 'ffmpeg')),
  );
  
  $form['ffmpeg']['thumbnails']['thumbnails_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of thumbnails'),
    '#default_value' => $prev_settings['thumbnails_count'],
    '#description' => t('Enter the number of thumbnails to generate for the user to select.'),
  );
  
  $form['ffmpeg']['thumbnails']['thumbnails_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to Video Thumbnails'),
    '#description' => t('Path to save video thumbnails extracted from video'),
    '#default_value' => $prev_settings['thumbnails_path'],
  );
  
  $form['ffmpeg']['thumbnails']['thumbnails_command'] = array(
    '#type' => 'textarea',
    '#rows' => 5,
    '#title' => t('Options to generate thumbnails'),
    '#default_value' => $prev_settings['thumbnails_command'],
    '#description' => t('Provide the options for the thumbnailer (Leave empty to use the default options). Available argument values are: ') .'<ol><li>'. t('%videofile (the video file to thumbnail)') .'</li><li>'. t('%thumbfile (destination path of the thumbnail)') .'</li><li>'. t('%seek (Seek to given time position in seconds)') .'</li></ol>'. t('For example: !thumb_command', array('!thumb_command' => "<div>-i %videofile -an -y -f mjpeg -ss %seek -vframes 1 %thumbfile</div>")));
  
  $form['ffmpeg']['video'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video conversion options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['ffmpeg']['video']['enable_video'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically convert video format'),
    '#default_value' => $prev_settings['enable_video'],
    '#description' => t('Check this option for converting videos to other supported formats using %transcoder', array('%transcoder' => 'ffmpeg')),
  );
  
  $form['ffmpeg']['video']['show_original_video'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show original video if converted video is not available'),
    '#default_value' => $prev_settings['show_original_video'],
    '#description' => t('Checking this will display original video in the status, if converted video is not available.'),
  );
  
  $form['ffmpeg']['video']['ffmpeg_output_format'] = array(
    '#type' => 'textfield',
    '#title' => t('Output format'),
    '#default_value' => $prev_settings['ffmpeg_output_format'],
    '#description' => t('Output format of the converted video. Defaults to flv.'),
  );
  
  $form['ffmpeg']['video']['ffmpeg_output_ext'] = array(
    '#type' => 'textfield',
    '#title' => t('Output extension'),
    '#default_value' => $prev_settings['ffmpeg_output_ext'],
    '#description' => t('Output extension of the converted video. Defaults to %extension.', array('%extension' => '\'flv\'')),
  );
  
  $form['ffmpeg']['video']['ffmpeg_audio_ar'] = array(
    '#type' => 'textfield',
    '#title' => t('Audio sampling rate'),
    '#default_value' => $prev_settings['ffmpeg_audio_ar'],
    '#description' => t('The audio sampling rate in the output video. Defaults to 22050.'),
  );
  
  $form['ffmpeg']['video']['ffmpeg_audio_ab'] = array(
    '#type' => 'textfield',
    '#title' => t('Audio bit rate'),
    '#default_value' => $prev_settings['ffmpeg_audio_ab'],
    '#description' => t('The audio bit rate in the output video. Defaults to 64k.'),
  );
  
  $form['ffmpeg']['video']['ffmpeg_video_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Output video size'),
    '#default_value' => $prev_settings['ffmpeg_video_size'],
    '#description' => t('The resolution of the output video in WxH format. Defaults to the size of input video.'),
  );
  
  $form['ffmpeg']['video']['ffmpeg_video_br'] = array(
    '#type' => 'textfield',
    '#title' => t('Video sampling rate'),
    '#default_value' => $prev_settings['ffmpeg_video_br'],
    '#description' => t('The video sampling rate in the output video. Defaults to 200K.'),
  );
  
  $form['ffmpeg']['video']['ffmpeg_video_fps'] = array(
    '#type' => 'textfield',
    '#title' => t('Video frames per second'),
    '#default_value' => $prev_settings['ffmpeg_video_fps'],
    '#description' => t('The video frames per second in the output video. Defaults to 25.'),
  );
  
  $form['ffmpeg']['video']['ffmpeg_truncate_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration'),
    '#default_value' => $prev_settings['ffmpeg_truncate_time'],
    '#description' => t('Restrict the transcoded video to the duration specified in seconds. Leave empty if you do not want to truncate videos.'),
  );
  
  $form['ffmpeg']['video']['convert_command'] = array(
    '#type' => 'textarea',
    '#rows' => 5,
    '#title' => t('Options to convert videos'),
    '#default_value' => $prev_settings['convert_command'],
    '#description' => t('Provide the ffmpeg options to configure the video conversion (Leave empty to use the default options).  Available argument values are: ') .'<ol>'.
        '<li>'. t('%inputfile (the video file to convert)') .
        '</li><li>'. t('%outputfile (a newly created file to store the converted file)') .
        '</li></ol>'.
        t('For further informations refer to the !ffmpegdoc', array('!ffmpegdoc' => l(t('Official FFMpeg documentation.'), 'http://ffmpeg.mplayerhq.hu/ffmpeg-doc.html', array('fragment' => TRUE))))
  );
  
  $form['player'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video player options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['player']['player_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('Width of the video player. Defaults to 435.'),
    '#default_value' => $prev_settings['player_width'],
  );
  
  $form['player']['player_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('Height of the video player. Defaults to 350.'),
    '#default_value' => $prev_settings['player_height'],
  );
  
  $form['player']['autoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Autoplay video'),
    '#description' => t('Play the video automatically on page load.'),
    '#default_value' => $prev_settings['autoplay']
  );
  
  $form['cron'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cron options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['cron']['total_jobs'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of videos to process on cron run'),
    '#default_value' => $prev_settings['total_jobs']
  );
  
  $form['cron']['process_interval'] = array(
    '#type' => 'select',
    '#title' => t('Minimum interval between processing of videos'),
    '#options' => drupal_map_assoc(array(3600, 10800, 21600, 32400, 43200, 86400, 172800, 259200, 604800, 1209600, 2419200, 4838400, 9676800, 15724800, 31449600), 'format_interval'),
    '#default_value' => $prev_settings['process_interval']
  );
  
  
  return $form;
}

/**
 * Implementation of hook_fbsmp_admin_settings_form_validate().
 */
function fbsmp_video_fbsmp_admin_settings_form_validate(&$form, &$form_state) {
  // Check that only web images are specified in the callback.
  $form_values = $form_state['values'];
  $extensions = array_filter(explode(' ', $form_values['file_extensions']));
  $web_extensions = array_keys(fbsmp_video_web_video_extensions());
  if (count(array_diff($extensions, $web_extensions))) {
    form_set_error('file_extensions', t('Only web-standard videos are supported through the Video plugin.'));
  }
  //Check that set filesize is valid
  if (!empty($form_values['max_filesize']) && !is_numeric(parse_size($form_values['max_filesize']))) {
    form_set_error('max_filesize', t('The "Maximum upload size" option must contain a valid value. You can either leave the text field empty or enter a string like "512" (bytes), "80K" (kilobytes) or "50M" (megabytes).'));
  }

  //Check the validity of the file path.
  //Strip slashes from the beginning and end of $widget['file_path']
  $form_values['file_path'] = trim($form_values['file_path'], '\\/');
  $form_values['thumbnails_path'] = trim($form_values['thumbnails_path'], '\\/');
  
  //Do not allow the file path to be the same as the file_directory_path().
  //This causes all sorts of problems with things like file_create_url().
  foreach (array('file_path', 'thumbnails_path') as $var)
    if (strpos($form_values[$var], file_directory_path()) === 0) {
      form_set_error($var, t('The file path (@file_path) cannot start with the system files directory (@files_directory), as this may cause conflicts when building file URLs.', array('@file_path' => $form_values[$var], '@files_directory' => file_directory_path())));
    }
    
  $numeric_fields = array(
    'thumbnails_count' => 'Number of thumbnails' ,
    'ffmpeg_audio_ar' => 'Audio sampling rate',
    'ffmpeg_audio_ab' => 'Audio bit rate',
    'ffmpeg_video_br' => 'Video sampling rate',
    'ffmpeg_video_fps' => 'Video frames per second',
  );
  
  foreach ($numeric_fields as $field => $name) {
    if (!empty($form_values[$field]) && !is_numeric(parse_size($form_values[$field]))) {
      form_set_error($field, t('The "!field_name" option must contain a valid value. You can either leave the text field empty or enter a string like "512", "80K" or "50M".', array('!field_name' => $name)));
    }
  }
  
  if (!empty($form_values['ffmpeg_video_size']) && !preg_match('/^[0-9]+x[0-9]+$/', $form_values['ffmpeg_video_size'])) {
    form_set_error('ffmpeg_video_size', t('Please specify a resolution in the format WIDTHxHEIGHT (e.g. 640x480).'));
  }
  
  $fields = array(
    'ffmpeg_output_format' => 'Output format',
    'ffmpeg_output_ext' => 'Output extension'
  );
  foreach ($fields as $field => $name) {
    $form_values[$field] = trim($form_values[$field], '.');
    form_set_value($form['ffmpeg']['video'][$field], $form_values[$field], $form_state);
  }
  
  foreach (array('player_height', 'player_width') as $attr) {
    if (!empty($form_values[$attr]) && (!is_numeric($form_values[$attr]) || $form_values[$attr] != round($form_values[$attr]) || $form_values[$attr] < 0)) {
      form_set_error($attr, t('The @attribute must be a non-negative integer.', array('@attribute' => $attr)));
    }
  }
  
  if (!is_numeric($form_values['total_jobs']) || $form_values['total_jobs'] != round($form_values['total_jobs']) || $form_values['total_jobs'] <= 0) {
      form_set_error('total_jobs', t('The "Number of videos to process" must be a positive integer.'));
  }
}

/**
 * Implementation of hook_fbsmp_admin_settings_form_submit().
 */
function fbsmp_video_fbsmp_admin_settings_form_submit(&$form, &$form_state) {
  $form_values = $form_state['values'];
  $settings = array();
  $settings['file_extensions'] = $form_values['file_extensions'];
  $settings['max_filesize'] = $form_values['max_filesize'];
  $settings['file_path'] = $form_values['file_path'];
  $settings['convert_video_path'] = $form_values['file_path'];
  $settings['thumbnails_path'] = $form_values['thumbnails_path'];
  $settings['ffmpeg_path'] = $form_values['ffmpeg_path'];
  $settings['enable_thumbnails'] = $form_values['enable_thumbnails'];
  $settings['thumbnails_count'] = $form_values['thumbnails_count'];
  $settings['thumbnails_command'] = $form_values['thumbnails_command'];
  $settings['enable_video'] = $form_values['enable_video'];
  $settings['show_original_video'] = $form_values['show_original_video'];
  $settings['ffmpeg_output_format'] = $form_values['ffmpeg_output_format'];
  $settings['ffmpeg_output_ext'] = $form_values['ffmpeg_output_ext'];
  $settings['ffmpeg_audio_ar'] = $form_values['ffmpeg_audio_ar'];
  $settings['ffmpeg_audio_ab'] = $form_values['ffmpeg_audio_ab'];
  $settings['ffmpeg_video_size'] = $form_values['ffmpeg_video_size'];
  $settings['ffmpeg_video_br'] = $form_values['ffmpeg_video_br'];
  $settings['ffmpeg_video_fps'] = $form_values['ffmpeg_video_fps'];
  $settings['ffmpeg_truncate_time'] = $form_values['ffmpeg_truncate_time'];
  $settings['convert_command'] = $form_values['convert_command'];
  $settings['player_width'] = $form_values['player_width'];
  $settings['player_height'] = $form_values['player_height'];
  $settings['autoplay'] = $form_values['autoplay'];
  $settings['total_jobs'] = $form_values['total_jobs'];
  $settings['process_interval'] = $form_values['process_interval'];
  
  fbsmp_save_plugin_settings($settings, 'video');
}



/**
 * Implementation of hook_fbsmp_widget_form().
 */
function fbsmp_video_fbsmp_widget_form(&$form_state) {
  $form = array();
  $settings = fbsmp_load_plugin_settings('video');
  if (isset($form_state['fbsmp_video']['step']) && $form_state['fbsmp_video']['step'] == 2) {
    $data = $form_state['fbsmp_video']['data'];
    if (isset($data['thumbnails']) && is_array($data['thumbnails']) && count($data['thumbnails']) > 0) {
      $delta = 0;
      foreach ($data['thumbnails'] as $image_url => $size) {
        $delta++;
        $form['fbsmp_video_thumbnail_'. $delta] = array(
          '#type' => 'hidden',
          '#access' => TRUE,
          '#attributes' => array('class' => 'fbsmp-video-thumbnail-'. $delta),
          '#value' => $image_url,
        );
      }
      $form['fbsmp_video_thumbnail_count'] = array(
        '#type' => 'hidden',
        '#access' => TRUE,
        '#value' => $delta,
      );
      $current_thumbnail = isset($form_state['fbsmp_video']['current_thumbnail']) ? $form_state['fbsmp_video']['current_thumbnail'] : 1;
      $form['fbsmp_video_current_thumbnail'] = array(
        '#type' => 'hidden',
        '#access' => TRUE,
        '#default_value' => $current_thumbnail,
      );
      $form['fbsmp_video_thumbnail_select'] = array(
        '#value' => fbsmp_video_render_thumbnail_select($form['fbsmp_video_thumbnail_'. $current_thumbnail]['#value'], $current_thumbnail, $delta, $settings),
      );
    }
    $form['fbsmp_video_title'] = array(
      '#title' => t('Title'),
      '#type' => 'textfield',
      '#maxlength' => $settings['max_title_length'],
      '#default_value' => '',
    );
    $form['fbsmp_video_description'] = array(
      '#title' => t('Description'),
      '#type' => 'textarea',
      '#maxlength' => $settings['max_description_length'],
      '#default_value' => '',
      '#resizable' => FALSE,
    );    
    $form['fbsmp_video_data'] = array(
      '#type' => 'value',
      '#value' => $form_state['fbsmp_video'],
    );
  }
  else {
    $max_filesize = parse_size(file_upload_max_size());
    if (!empty($settings['max_filesize']) && parse_size($settings['max_filesize']) < $max_filesize) {
      $max_filesize = parse_size($settings['max_filesize']);
    }
    
    $settings['file_extensions'] = !empty($settings['file_extensions']) ? $settings['file_extensions'] : implode(' ', array_keys(fbsmp_video_web_video_extensions()));
    
    $desc[] = t('Maximum Filesize: @size', array('@size' => format_size($max_filesize)));
    
    $form['fbsmp_video_upload'] = array(
      '#type' => 'file',
      '#size' => 22,
      '#description' => implode('<br />', $desc),
      '#upload_validators' => fbsmp_video_widget_upload_validators($settings),
      '#settings' => $settings,
    );
  }
  return $form;
}

/**
 * Implementation of hook_fbsmp_widget_form_validate().
 */
function fbsmp_video_fbsmp_widget_form_validate(&$form, &$form_state) {
  $settings = $form['fbsmp']['fbsmp_video_upload']['#settings'];
  $upload_name = 'fbsmp_video_upload';
  $dest = _fbsmp_file_create_path($settings['file_path']);
  if (!_fbsmp_file_check_directory($dest, FILE_CREATE_DIRECTORY)) {
    watchdog('fbsmp', 'The upload directory %directory could not be created or is not accessible. A newly uploaded video could not be saved in this directory as a consequence, and the upload was canceled.', array('%directory' => $dest));
    form_set_error($upload_name, t('The video could not be uploaded.'));
    return 0;
  }
  if ($file = _fbsmp_file_save_upload($upload_name, $form['fbsmp'][$upload_name]['#upload_validators'], $dest)) {
    $form_state['values'][$upload_name] = $file->fid;
  }
  else {
    form_set_error($upload_name, t('The video could not be uploaded.')); 
  }
}


/**
 * Implementation of hook_fbsmp_widget_form_save().
 */
function fbsmp_video_fbsmp_widget_form_save($form, $form_state) {
  $record = array();
  $fid = $form_state['values']['fbsmp_video_upload'];
  $settings = $form['fbsmp']['fbsmp_video_upload']['#settings'];
  $record['fid'] = $fid;
  if ($fid) {
    file_set_status(_fbsmp_file_load($fid), FILE_STATUS_PERMANENT);
    $video = array(
      'fid' => $fid,
      'sid' => 0,
      'status' => !empty($settings['enable_video']) ? FBSMP_VIDEO_CONVERSION_PENDING : FBSMP_VIDEO_CONVERSION_NONE,
      'cid' => 0,
    );
    drupal_write_record('fbsmp_videos', $video);
    $thumbnails = array();
    if ($settings['enable_thumbnails'])  {
      $thumbnails = fbsmp_video_generate_thumbnails($fid, $settings);
    }
    if (empty($thumbnails)) {
      $record['thumbnails'] = array();
      $record['current_thumbnail'] = NULL;
    }
    else {
      $record['thumbnails'] = $thumbnails;
      $record['current_thumbnail'] = $thumbnails[rand(0, count($thumbnails) - 1)];
    }
  }
  return $record;
}

/**
 * Returns the themed form element for thumbnail selection.
 */
function fbsmp_video_render_thumbnail_select($image_url, $current, $images_count, $settings = array()) {
  $output = '';
  $output .= '<div class="fbsmp-video-thumbnails">';
  
  $attributes = array();
  $prefix = 'preview_thumbnail_';
  foreach (array('height', 'width') as $attr) {
    if (isset($settings[$prefix . $attr]) && $settings[$prefix . $attr]) {
      $attributes[$attr] = $settings[$prefix . $attr];
    }
  }
  
  $attributes['class'] = "fbsmp-video-thumbnail-select";
  $output .= theme('image', $image_url, '', '', $attributes, FALSE);  
  $images_path = _fbsmp_get_image_dir() .'/plugins/images';
  
  $output .= theme('image', $images_path .'/previous.png', t('Previous'), '', array('class' => 'fbsmp-video-previous-button'), FALSE);
  $output .= theme('image', $images_path .'/next.png', t('Next'), '', array('class' => 'fbsmp-video-next-button'), FALSE);
  
  $output .= '<span class="fbsmp-video-chars">'. t('%current of %max', array('%current' => $current, '%max' => $images_count)) .'</span>';
  $output .= '</div>';
  return $output;
}

/**
 * Break out for fbsmp_fbsmp_delete().
 */
function fbsmp_video_fbsmp_delete($status) {
  $attachment_data = $status->attachment->data;
  _fbsmp_file_delete(_fbsmp_file_load($attachment_data['fid']));
  
  $video = db_fetch_object(db_query("SELECT fv.* FROM {fbsmp_videos} fv WHERE fid = %d", $attachment_data['fid']));
  if ($video) {
    _fbsmp_file_delete(_fbsmp_file_load($video->cid));
  }
  db_query("DELETE FROM {fbsmp_videos} WHERE fid = %d", $attachment_data['fid']);
  
  $thumbnails = $attachment_data['thumbnails'];
  if ($thumbnails) {
    foreach ($thumbnails as $thumbnail_fid) {
      _fbsmp_file_delete(_fbsmp_file_load($thumbnail_fid));
    }
  }
}

function fbsmp_video_process_queue($total_jobs, $settings = array()) {
  $result = db_query_range('SELECT fv.fid, fv.sid FROM {fbsmp_videos} fv LEFT JOIN {files} f ON fv.fid = f.fid WHERE fv.status = %d AND f.status = %d ORDER BY f.timestamp', FBSMP_VIDEO_CONVERSION_PENDING, FILE_STATUS_PERMANENT, 0, $total_jobs);
  while ($video = db_fetch_object($result)) {
    fbsmp_video_convert_video($video->fid, $video->sid, $settings);
  }
}

/**
 * Generates the given number of thumbnails from a video file.
 *
 * @param $fid
 *   The fid of the video file or the file object.
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - ffmpeg_path
 *       A string containing the path to the ffmpeg executable.
 *   - thumbnails_command
 *       A string overriding the default command options for 
 *       generating thumbnails using ffmpeg.
 *   - thumbnails_count
 *       An integer containing the number of thumbnails to generate. Defaults
 *       to 5.
 *
 * @return
 *   An array containing file objects of the thumbnails or FALSE in case of error.
 */
function fbsmp_video_generate_thumbnails($fid, $settings = array()) {
  if (is_object($fid)) {
    $fid = $fid->fid;
  }
  $video = _fbsmp_file_load($fid);
  if (!$video) {
    watchdog('fbsmp_video', 'The video file with fid %fid was not found in {files} table. The thumbnails generation for the video was cancelled as a consequence.', array('%fid' => $fid), ERROR);
    return FALSE;
  }
  
  $thumbnails = _fbsmp_ffmpeg_generate_thumbnails($video->filepath, $video->fid, $settings);
  
  if ($thumbnails !== FALSE && count($thumbnails) > 0) {
    $dest = _fbsmp_file_create_path($settings['thumbnails_path']);
    $files = array();
    foreach ($thumbnails as $temp_path) {
      $saved_file = _fbsmp_file_save_file($temp_path, array(), $dest);
      if ($saved_file) {
        $files[] = $saved_file->fid;
      }
    }
    return $files;
  }
  else {
    //fbsmp_ffmpeg library has already documented the reasons for failure, do nothing.
    return FALSE;
  }
}

/**
 * Converts a video into another format such as flv.
 *
 * @param $fid
 *   The fid of the video file or the file object.
 * @param $sid
 *   The ID of the status to which video is attached.
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - ffmpeg_path
 *       A string containing the path to the ffmpeg executable. Defaults
 *       to /usr/bin/ffmpeg
 *   - convert_command
 *       A string overriding the default command options for 
 *       converting video using ffmpeg. It can contain two placeholders
 *       '!inputfile' and '!outputfile' which will be replaced by input filepath
 *       and output filepath respectively.
 *   - ffmpeg_output_format
 *       A string containing the output format. Defaults to 'flv'.
 *   - ffmpeg_audio_ar
 *       The output audio sampling rate. Defaults to 22050.
 *   - ffmpeg_audio_ab
 *       The output audio bit rate. Defaults to 64k.
 *   - ffmpeg_video_size
 *       The output video size in WxH format. Defaults to the size 
 *       of input video file.
 *   - ffmpeg_video_br
 *       The output video bit rate. Defaults to 200k.
 *   - ffmpeg_video_fps
 *       The output video frames per second. Defaults to 25 Hz.
 *   - ffmpeg_truncate_time
 *       The time period of the output video.
 *   - ffmpeg_output_ext
 *       The extension of the converted output video.
 *   - convert_video_path
 *       The destination path for the converted video files.
 * @param $account
 *   The user account object that should associated with the converted file.
 *
 * @return
 *   The converted video file object or FALSE in case of error.
 */
function fbsmp_video_convert_video($fid, $sid = 0, $settings = array(), $account = NULL) {
  if (is_object($fid)) {
    $fid = $fid->fid;
  }
  $video = fbsmp_video_file_load($fid);
  if (!$video) {
    watchdog('fbsmp_video', 'The video file with fid %fid was not found in either {files} or {fbsmp_videos} table. The video conversion was cancelled as a consequence.', array('%fid' => $fid), ERROR);
    return FALSE;
  }
  
  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }
  fbsmp_video_set_status($video, FBSMP_VIDEO_CONVERSION_ACTIVE);
  
  $unique_id = !empty($settings['ffmpeg_video_size']) ? $settings['ffmpeg_video_size'] : 'fbsmp-video';
  $temp_file = _fbsmp_ffmpeg_convert_video($video->filepath, $unique_id, $settings);
  $dest = _fbsmp_file_create_path($settings['convert_video_path']);
  if ($temp_file && $converted = _fbsmp_file_save_file($temp_file, array(), $dest, FILE_EXISTS_RENAME, $account)) {
    file_set_status($converted, FILE_STATUS_PERMANENT);
    fbsmp_video_set_status($video, FBSMP_VIDEO_CONVERSION_COMPLETE);
    db_query('UPDATE {fbsmp_videos} SET cid = %d WHERE fid = %d', $converted->fid, $video->fid);
    if (is_numeric($sid) && $sid > 0) {
      module_invoke_all('fbsmp_video', 'conversion_complete', $sid, $video, $converted);
    }
    return $converted;
  }
  else {
    fbsmp_video_set_status($video, FBSMP_VIDEO_CONVERSION_FAILED);
    if (is_numeric($sid) && $sid > 0) {
      module_invoke_all('fbsmp_video', 'conversion_failed', $sid, $video);
    }
    //ffmpeg library has already logged the reason for this failure, so do nothing.
    return FALSE;
  }
}

/**
 * Set the status of a fbsmp video file.
 *
 * @param $video 
 *   A Drupal file object.
 * @param $status
 *   A status value to set the video file to.
 *
 * @return
 *   FALSE on failure and TRUE on success
 */
function fbsmp_video_set_status($video, $status) {
  if (db_query('UPDATE {fbsmp_videos} SET status = %d WHERE fid = %d', $status, $video->fid)) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Load a file from the database
 *
 * @param $fid
 *   A numeric file id or string containing the file path.
 *
 * @return
 *   A file object if the file is also present in the {fbsmp_videos} table,
 *   otherwise FALSE.
 */
function fbsmp_video_file_load($fid) {
  if (empty($fid)) {
    return FALSE;
  }
  $query = "SELECT f.* FROM {fbsmp_videos} fv JOIN {files} f ON fv.fid = f.fid WHERE f.fid=fv.fid AND f.fid = %d";
  if (!is_numeric($fid)) {
    $query = "SELECT f.* FROM {fbsmp_videos} fv JOIN {files} f ON fv.fid = f.fid WHERE f.fid=fv.fid AND f.filepath = '%s'";
  }
  
  return db_fetch_object(db_query($query, $fid));
}

/**
 * Get the upload validators for a video upload field.
 *
 * @param $settings
 *   The settings array for the plugin.
 * @return
 *   An array suitable for passing to file_save_upload() or the file field
 *   element's '#upload_validators' property.
 */
function fbsmp_video_widget_upload_validators($settings) {
  $max_filesize = parse_size(file_upload_max_size());
  if (!empty($settings['max_filesize']) && parse_size($settings['max_filesize']) < $max_filesize) {
    $max_filesize = parse_size($settings['max_filesize']);
  }

  $validators = array(
    '_fbsmp_file_validate_size' => array($max_filesize),
    '_fbsmp_file_validate_extensions' => array($settings['file_extensions'])
  );
  
  return $validators;
}

/*
 * Returns the list of supported extensions along with their player.
 */
function fbsmp_video_web_video_extensions() {
  $extensions = array(
    'divx'  => 'fbsmp_video_play_divx',
    'mov'   => 'fbsmp_video_play_quicktime',
    '3gp'   => 'fbsmp_video_play_quicktime',
    '3g2'   => 'fbsmp_video_play_quicktime',
    'mp4'   => 'fbsmp_video_play_quicktime',
    'rm'    => 'fbsmp_video_play_realmedia',
    'f4v'   => 'fbsmp_video_play_flv',
    'flv'   => 'fbsmp_video_play_flv',
    'swf'   => 'fbsmp_video_play_flash',
    'dir'   => 'fbsmp_video_play_dcr',
    'dcr'   => 'fbsmp_video_play_dcr',
    'asf'   => 'fbsmp_video_play_windowsmedia',
    'wmv'   => 'fbsmp_video_play_windowsmedia',
    'avi'   => 'fbsmp_video_play_windowsmedia',
    'mpg'   => 'fbsmp_video_play_windowsmedia',
    'mpeg'  => 'fbsmp_video_play_windowsmedia',
    'ogg'   => 'fbsmp_video_play_theora',
    'ogv'   => 'fbsmp_video_play_theora',
  );
  return $extensions;
}

/**
 * Implementation of hook_fbsmp_themed_attachment().
 */
function fbsmp_video_fbsmp_themed_attachment($attachment) {
  $settings = fbsmp_load_plugin_settings('video');
  
  $file = fbsmp_video_load_displayed_video($attachment, $settings);
  $thumbnail_url = '';
  if ($file) {
    if ($attachment->data['current_thumbnail']) {
      $thumbnail_file = (array)_fbsmp_file_load($attachment->data['current_thumbnail']);
      if ($thumbnail_file) {
        $thumbnail_url = file_create_url($thumbnail_file['filepath']);
      }
    }
    return theme('fbsmp_video_attachment', $file, $thumbnail_url, $attachment_data['title'], $attachment_data['description'], $settings);
  }
  return '';
}

/**
 * Loads the original video or converted video based on the settings.
 *
 * @param $attachment
 *   The attachment object.
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - show_original_video
 *       Whether to show original video, in case converted video is not available.
 *
 * @return
 *   An array containing the file information including the video download url.
 */
function fbsmp_video_load_displayed_video($attachment, $settings = array()) {
  $query = "SELECT fv.* from {fbsmp_videos} as fv WHERE fid = %d";
  $fv_object = db_fetch_object(db_query($query, $attachment->data['fid']));
  if ($fv_object) {
    $cid = ($fv_object->status == FBSMP_VIDEO_CONVERSION_NONE || ($fv_object->status != FBSMP_VIDEO_CONVERSION_COMPLETE && $settings['show_original_video'])) ? $fv_object->fid : ($fv_object->status == FBSMP_VIDEO_CONVERSION_COMPLETE ? $fv_object->cid : 0);

    $file = (array)_fbsmp_file_load($cid);
    if (is_file($file['filepath'])) {
      $file['url'] = file_create_url($file['filepath']);
    }
    else {
      $file = array();
    }
  }
  
  return $file;
}

/**
 * Themes a given video file to embed in the status.
 * 
 * @param $file
 *   The video file object.
 * @param $thumbnail_url
 *   The URL of the selected video thumbnail.
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - player_width
 *       The width of the video player
 *   - player_height
 *       The height of the video player
 *   - autoplay
 *       A boolean representing whether to play video on page load.
 *
 * @return
 *   HTML code which can be embedded into the status.
 */
function theme_fbsmp_video_attachment($file, $thumbnail_url = '', $title = '', $description = '', $settings = array()) {
  $output = '';
  if (!empty($file)) {
    $video_extension = pathinfo($file['filename'], PATHINFO_EXTENSION);
    $extensions = fbsmp_video_web_video_extensions();
    if (key_exists($video_extension, $extensions)) {
      $settings['player_width'] = !empty($settings['player_width']) ? $settings['player_width'] : 435;
      $settings['player_height'] = !empty($settings['player_height']) ? $settings['player_height'] : 350;
      $output .= theme($extensions[$video_extension], $file['url'], $thumbnail_url, $settings);
    }
  }

  return $output;
}

/**
 * Implementation of hook_fbsmp_token_list().
 */
function fbsmp_video_fbsmp_token_list() {
  return array(
    'video-id' => t('The fid of the saved video.'),
    'video-url' => t('The URL that can be used to download the video.'),
    'video-thumbnail-url' => t('The URL to the thumbnail image of the video.') 
  );
}

/**
 * Implementation of hook_fbsmp_token_values().
 */
function fbsmp_video_fbsmp_token_values($attachment) {
  $attachment_data = $attachment->data;
  $settings = fbsmp_load_plugin_settings('video');
  
  $file = fbsmp_video_load_displayed_video($attachment, $settings);
  $video_url = '';
  $thumbnail_url = '';
  if (!empty($file['url'])) {
    $video_url = $file['url'];
  }
  if (is_file($attachment_data['current_thumbnail'])) {
    $thumbnail_url = file_create_url($attachment_data['current_thumbnail']);
  }
  return array(
    'video-id' => $attachment_data['fid'],
    'video-url' => $video_url,
    'video-thumbnail-url' => $thumbnail_url
  );  
}

/**
 * Implementation of hook_fbsmp_subtheme().
 */
function fbsmp_video_fbsmp_subtheme() {
  $themes = array();
  $extensions = fbsmp_video_web_video_extensions();
  
  foreach ($extensions as $ext => $player) {
    $themes[$player] = array(
      'arguments' => array('video_url' => NULL, 'thumbnail_url' => NULL, 'settings' => NULL),
      'file' => 'plugins/video.inc',
    );
  }
  
  $themes['fbsmp_video_attachment'] = array(
    'arguments' => array('file' => NULL, 'thumbnail_url' => NULL, 'title' => NULL, 'description' => NULL, 'settings' => NULL),
    'file' => 'plugins/video.inc',
  );
  return $themes;
}

function theme_fbsmp_video_play_quicktime($video_url, $thumbnail_url = '', $settings = array()) {
  $autoplay = $settings['autoplay'] ? 'true' : 'false';
  
  $output  = '';
  $output .= '<object classid="clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B" codebase="http://www.apple.com/qtactivex/qtplugin.cab#version=7,3,0,0"  width="' . $settings['player_width'] .'" height="'. $settings['player_height'] .'">';
  $output .= '<param name="src" value="'. $video_url .'" />';
  $output .= '<param name="controller" value="true" />';
  $output .= '<param name="scale" value="tofit" />';
  $output .= '<param name="autoplay" value="' . $autoplay .'" />';
  $output .= '<param name="pluginurl" value="http://www.apple.com/quicktime/download/" />';
  $output .= '<embed src="'. $video_url .'"
  	type="video/quicktime"
    pluginspage="http://www.apple.com/quicktime/download/" 
    width="'. $settings['player_width'] .'" 
    height="'. $settings['player_height'] .'" 
    autostart="'. $autoplay .'" 
    controller="true" >
  </embed>';
  $output .= '</object>';

  return $output;
}

function theme_fbsmp_video_play_divx($video_url, $thumbnail_url = '', $settings = array()) {
  $output  = '';
  $output .= '<object classid="clsid:67DABFBF-D0AB-41fa-9C46-CC0F21721616" width="' . $settings['player_width'] .'" height="'. $settings['player_height'] .'" codebase="http://go.divx.com/plugin/DivXBrowserPlugin.cab">';
  $output .= '<param name="pluginspage" value="http://go.divx.com/plugin/download/" />';
  $output .= '<param name="mode" value="zero" />';
  $output .= '<object class="video-object" type="video/divx" data="'. $video_url .'" width="'. $settings['player_width'] .'" height="'. $settings['player_height'] .'" mode="zero">';
  $output .= t('No video?  Get the DivX Web Player !plugin', array('!plugin' => l(t('Plugin'), 'http://go.divx.com/plugin/download/')));
  $output .= '</object>';
  $output .= '</object>';
  
  return $output;
}

function theme_fbsmp_video_play_dcr($video_url, $thumbnail_url = '', $settings = array()) {
  $output  = '';
  $output .= '<object classid="clsid:166B1BCA-3F9C-11CF-8075-444553540000" type="application/x-director" width="' . $settings['player_width'] .'" height="'. $settings['player_height'] .'" codebase="http://download.macromedia.com/pub/shockwave/cabs/director/sw.cab#version=10,0,0,0">';
  $output .= '<param name="src" value="'. $video_url .'" />';
  $output .= '<object class="video-object" type="application/x-director" data="'. $video_url .'" width="'. $settings['player_width'] .'" height="'. $settings['player_height'] .'" mode="zero">';
  $output .= t('No video?  Get the Director !plugin', array('!plugin' => l(t('Plugin'), 'http://www.macromedia.com/shockwave/download/')));
  $output .= '</object>';
  $output .= '</object>';
  
  return $output;
}

function theme_fbsmp_video_play_flv($video_url, $thumbnail_url = '', $settings = array()) {
  $output = '';
  $othervars = array();
  if (!empty($thumbnail_url)) {
    $othervars = array(
      'image' => $thumbnail_url,
    );
  }

  if (module_exists(swftools)) {
    $options = array(
      'params' => array(
        'width' => $settings['player_width'],
        'height' => $settings['player_height'],
        'allowfullscreen' => TRUE,
        'wmode' => 'transparent'
      ),
      'othervars' => $othervars,
    );
    $output = swf($video_url, $options);
  }

  return $output;
}

function theme_fbsmp_video_play_flash($video_url, $thumbnail_url = '', $settings = array()) {
  $output = '';
  $output .= '<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="'. $settings['player_width'] .'" height="'. $settings['player_height'] .'" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,40,0">';
  $output .= '<param name="movie" value="' . $video_url .'" />';
  $output .= '<param name="autoplay" value="' . $settings['autoplay'] .'" />';
  $output .= '<param name="wmode" value="transparent" />';
  $output .= '<object class="video-object" type="application/x-shockwave-flash" data="'. $video_url .'" width="'. $settings['player_width'] .'" height="'. $settings['player_height'] .'">';
  $output .= t('No video?  Get the Adobe Flash !plugin', array('!plugin' => l(t('Plugin'), 'http://get.adobe.com/flashplayer/')));
  $output .= '</object>';
  $output .= '</object>';
  
  return $output;
}

function theme_fbsmp_video_play_windowsmedia($video_url, $thumbnail_url = '', $settings = array()) {
  $output = '';
  $output .= '<object type="video/x-ms-wmv" data="'. $video_url .'" width="'. $settings['player_width'] .'" height="'. $settings['player_height'] .'">';
  $output .= '<param name="src" value="'. $video_url .'" valuetype="ref" type="'. $video_url .'">';
  $output .= '<param name="animationatStart" value="true">';
  $output .= '<param name="transparentatStart" value="true">';
  $output .= '<param name="autostart" value="'. $settings['autoplay'] .'">';
  $output .= '<param name="controller" value="1">';
  $output .= t('No video?  Get the Windows Media !plugin', array('!plugin' => l(t('Plugin'), 'http://www.microsoft.com/windows/windowsmedia/player/download/')));
  $output .= '</object>';
  
  return $output;
}

function theme_fbsmp_video_play_theora($video_url, $thumbnail_url = '', $settings = array()) {
  $output = '';
  $output .= '<applet=code="com.fluendo.player.Cortado.class" archive="'. $settigs['theora_player'] .'" width="'. $settings['player_width'] .'" height="'. $settings['player_height'] .'">';
  $output .= '<param name="url" value="'. $video_url .'" />';
  $output .= '<param name="local" value="false" />';
  $output .= '<param name="mode" value="zero" />';
  $output .= '<param name="keepaspect" value="true" />';
  $output .= '<param name="video" value="true" />';
  $output .= '<param name="audio" value="true" />';
  $output .= '<param name="seekable" value="true" />';
  $output .= '<param name="bufferSize" value="200" />';
  $output .= t('No video?  Get the Latest Cortado !plugin', array('!plugin' => l(t('Plugin'), 'http://www.theora.org/cortado/')));
  $output .= '</applet>';
  
  return $output;
}

function theme_fbsmp_video_play_realmedia($video_url, $thumbnail_url = '', $settings = array()) {
  $output  = '';
  $output .= '<object classid="clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA" width="'. $settings['player_width'] .'" height="'. $settings['player_height'] .'">';
  $output .= '<param name="src" value="'. $video_url .'" />';
  $output .= '<param name="autostart" value="'. $settings['autoplay'] .'" />';
  $output .= '<param name="controls" value="imagewindow" />';
  $output .= '<param name="console" value="video" />';
  $output .= '<param name="loop" value="false" />';
  $output .= '<object class="video-object" type="audio/x-pn-realaudio-plugin" data="'. $video_url .'" width="'. $settings['player_width'] .'" height="'. $settings['player_height'] .'">';
  $output .= t('No video?  Get the Real Media !plugin', array('!plugin' => l(t('Plugin'), 'http://www.real.com/realplayer')));
  $output .= '</object>';
  $output .= '</object>';
  
  return $output;
}