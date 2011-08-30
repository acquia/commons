<?php

/**
 * @file
 *   Interaction with ffmpeg to generate metadata, 
 *   thumbnails and convert videos to other file formats.
 */

fbsmp_include_library('file.inc', 'file');
 
/**
 * Get output from ffmpeg with given options.
 *
 * @param $command_options
 *   The options to run ffmpeg with. These options must
 *   be shell escpaed before calling this function.
 * @param $ffmeg_path
 *   The path to the ffmpeg executable. Defaults to '/usr/bin/ffmpeg'.
 * @param $ffmpeg_debug
 *   An array to store the debug information and the output.
 * @return
 *   The output of the command.
 */
function _fbsmp_ffmpeg_run_command($command_options, $ffmpeg_path = '', &$ffmpeg_debug = array()) {
  if (!$ffmpeg_path) {
    $ffmpeg_path = '/usr/bin/ffmpeg';
  }
  $ffmpeg_debug['cwd'] = getcwd();
  $ffmpeg_debug['command'] = $ffmpeg_path .' '. $command_options;
  $ffmpeg_debug['output'] = shell_exec($ffmpeg_debug['command'] .'  2>&1');
  
  return $ffmpeg_debug['output'];
}

/**
 * Get the duration of a video in seconds.
 *
 * @param $filepath
 *   The path to video file.
 * @param $settings
 * (optional) An array which can have one or more of following keys:
 *   - ffmpeg_path
 *       A string containing the path to the ffmpeg executable.
 * @param $ffmpeg_output
 *   A string containing output of ffmpeg if it has already been run.
 *
 * @return
 *   An integer containing the duration of the video in seconds.
 */
function _fbsmp_ffmpeg_get_playtime($filepath, $settings = array(), $ffmpeg_output = NULL) {
  if (!$output) {
    $filepath = escapeshellarg($filepath);
    $ffmpeg_output = _fbsmp_ffmpeg_run_command("-i $filepath", $settings['ffmpeg_path']);
  }
  //Parse the output looking for 'Duration: 00:02:12'
  $pattern = '/Duration: ([0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9])/';
  preg_match_all($pattern, $ffmpeg_output, $matches, PREG_PATTERN_ORDER);
  $playtime = $matches[1][0];
  $hmsmm = explode(":", $playtime);
  $tmp = explode(".", $hmsmm[2]);
  $seconds = $tmp[0];
  $hours = $hmsmm[0];
  $minutes = $hmsmm[1];
  return $seconds + ($hours * 3600) + ($minutes * 60);
}

/**
 * Generates the given number of thumbnails from a video file.
 *
 * @param $filepath
 *   The path to video file.
 * @param unique_id
 *   An optional string to append to the thumbnail file. Usually,
 *   the fid of the video file. Defaults to video filename.
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
 * @param $replace 
 *   Replace behavior when a thumbnail with the same name already
 *   exists in the destination directory.
 *   - FILE_EXISTS_REPLACE
 *       Replace the existing thumbnail
 *   - FILE_EXISTS_RENAME
 *       Append _{incrementing number} until the filename is unique
 *   - FILE_EXISTS_ERROR
 *       Do nothing but include the thumbnail in the returned file list.
 *
 * @return
 *   An array containing filepaths of the thumbnails or FALSE in case of error.
 */
function _fbsmp_ffmpeg_generate_thumbnails($filepath, $unique_id = '', $settings = array(), $replace = FILE_EXISTS_ERROR) {
  if (!file_exists($filepath)) {
    return FALSE;
  }

  if (!$settings['thumbnails_command']) {
    $settings['thumbnails_command'] = '-i !videofile -an -y -f mjpeg -ss !seek -vframes 1 !thumbfile';
  }
  
  if (!$settings['thumbnails_count']) {
    $settings['thumbnails_count'] = 5;
  }
  
  if (!$settings['ffmpeg_path']) {
    $settings['ffmpeg_path'] = '/usr/bin/ffmpeg';
  }
  
  $thumbnails_path = file_directory_temp();
  if (!$unique_id) {
    $unique_id = str_replace('.', '-', basename($filepath));
  }
  
  if (!_fbsmp_file_check_directory($thumbnails_path, FILE_CREATE_DIRECTORY)) {
    watchdog('fbsmp_ffmpeg', 'The thumbnails directory %directory could not be created or is not accessible. A newly generated thumbnail could not be saved in this directory as a consequence, and the process was cancelled.', array('%directory' => $thumbnails_path));
    return FALSE;
  }
  
  $playtime = _fbsmp_ffmpeg_get_playtime($filepath, $settings);
  
  $files = array();
  for ($i = 1; $i <= $settings['thumbnails_count']; $i++) {
    $seek = ($playtime/$settings['thumbnails_count']) * $i;
    $thumb_filename = "fbsmp-video-thumb-$unique_id-$i.jpg";
    $thumb_filepath = $thumbnails_path .'/'. $thumb_filename;
    if ($dest = _fbsmp_file_destination($thumb_filepath, $replace)) {
      $command_options = strtr($settings['thumbnails_command'], array('!videofile' => escapeshellarg($filepath), '!seek' => $seek, '!thumbfile' => escapeshellarg($dest)));
      //Generate the thumbnail from the video.
      $command_output = _fbsmp_ffmpeg_run_command($command_options, $settings['ffmpeg_path']);
      if (!file_exists($dest) || !filesize($dest)) {
        $error_params = array('!thumbfile' => $dest, '!videofile' => $filepath, '!cmd' => $command_options, '!output' => $command_output);
        $error_message = t("The thumbnail !thumbfile for video !videofile could not be generated. The command options !cmd were executed which produced the following output: !output", $error_params);
        //Log the error message.
        watchdog('fbsmp_ffmpeg', $error_message, array(), WATCHDOG_ERROR);
        continue;
      }
      $files[] = $dest;
    }
    else {
      $files[] = $thumb_filepath;
    }
  }
  return $files;
}

/**
 * Converts a video into another format such as flv.
 *
 * @param $filepath
 *   The path to video file.
 * @param unique_id
 *   An optional string to append to the converted video file. Usually,
 *   the size of the output video file.
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
 * @param $replace 
 *   Replace behavior when a video with the same name already
 *   exists in the destination directory.
 *   - FILE_EXISTS_REPLACE
 *       Replace the existing thumbnail
 *   - FILE_EXISTS_RENAME
 *       Append _{incrementing number} until the filename is unique
 *   - FILE_EXISTS_ERROR
 *       Do nothing but include the thumbnail in the returned file list.
 *
 * @return
 *   The path to the converted output video file or FALSE in case of error.
 */
function _fbsmp_ffmpeg_convert_video($filepath, $unique_id = '', $settings = array(), $replace = FILE_EXISTS_ERROR) {
  if (!file_exists($filepath)) {
    return FALSE;
  }
  
  //Merge the defaults.
  $settings += array(
    'ffmpeg_audio_ar' => '22050',
    'ffmpeg_audio_ab' => '64000',
    'ffmpeg_video_br' => '200000',
    'ffmpeg_video_fps' => '25',
  );
  
  if (!$settings['ffmpeg_output_format']) {
    $settings['ffmpeg_output_format'] = 'flv';
  }
  
  if (!$settings['ffmpeg_path']) {
    $settings['ffmpeg_path'] = '/usr/bin/ffmpeg';
  }
  
  if (!$settings['convert_command']) {
    $options = array();
    //Input file and Overrite output file.
    $options[] = '-y -i !inputfile';
    //Output video format.
    $options[] =  '-f '. $settings['ffmpeg_output_format'];
    //Output audio sampling rate.
    $options[] = '-ar '. $settings['ffmpeg_audio_ar'];
    //Ouput audio bit rate.
    $options[] = '-ab '. $settings['ffmpeg_audio_ab'];
    //Ouput video bit rate.
    $options[] = '-b '. $settings['ffmpeg_video_br'];
    //Output video frame rate in Hz.
    $options[] = '-r '. $settings['ffmpeg_video_fps'];
    
    //Output video size.
    if ($settings['ffmpeg_video_size']) {
      $options[] = '-s '. $settings['ffmpeg_video_size'];
    }
    //Truncate time?
    if ($settings['ffmpeg_truncate_time']) {
      $options[] = '-t '. $settings['ffmpeg_truncate_time'];
    }
    //Add the output file.
    $options[] = '!outputfile';
    
    $settings['convert_command'] = implode(" ", $options);
  }
  
  $output_path = file_directory_temp();
  if (!_fbsmp_file_check_directory($output_path, FILE_CREATE_DIRECTORY)) {
    watchdog('fbsmp_ffmpeg', 'The directory %directory could not be created or is not accessible. A newly converted video could not be saved in this directory as a consequence, and the process was cancelled.', array('%directory' => $output_path));
    return FALSE;
  }
  
  $dest = $output_path .'/'. basename($filepath) ."-$unique_id.". $settings['ffmpeg_output_ext'];
  $outfile = _fbsmp_file_destination($dest, $replace);
  if (!$outfile) {
    return $dest;
  }
  
  //Replace the placeholders.
  $command_options = strtr($settings['convert_command'], array('!inputfile' => escapeshellarg($filepath), '!outputfile' => escapeshellarg($outfile)));
  $command_output = _fbsmp_ffmpeg_run_command($command_options, $settings['ffmpeg_path']);
  if (!file_exists($outfile) || !filesize($outfile)) {
    $error_params = array('!outfile' => $outfile, '!videofile' => $filepath, '!cmd' => $command_options, '!output' => $command_output);
    $error_message = t("The converted video !outfile for video !videofile could not be generated. The command options !cmd were executed which produced the following output: !output", $error_params);
    //Log the error message.
    watchdog('fbsmp_ffmpeg', $error_message, array(), WATCHDOG_ERROR);
    return FALSE;
  }
  return $outfile;
}