<?php

/**
 * @file
 * The theme system, which controls the output of the messages.
 */

function mimemail_theme_theme() {
  $path = drupal_get_path('module', 'mimemail') .'/theme';

  return array(
    'mimemail_message' => array(
      'arguments' => array('subject' => NULL, 'body' => NULL, 'mailkey' => NULL, 'recipient' => NULL),
      'template' => 'mimemail-message',
      'pattern' => 'mimemail_message__',
      'file' => 'mimemail.theme.inc',
      'path' => $path,
    )
  );
}

/**
 * A preprocess function for theme('mimemail_message').
 *
 * The $variables array initially contains the following arguments:
 * - $subject: The message subject
 * - $body:  The message body
 * - $mailkey:  The mailkey associated with the message
 *
 * See includes/mimemail.tpl.php for additional variables
 */
function template_preprocess_mimemail_message(&$variables) {
  $theme = variable_get('theme_default', NULL);

  // Fetch the theme for the current domain.
  if (module_exists('domain_theme')) {
    // Assign the selected theme, based on the active domain.
    global $_domain;
    $domain_theme = domain_theme_lookup($_domain['domain_id']);
    // The above returns -1 on failure.
    if ($domain_theme != -1) {
      $theme = $domain_theme['theme'];
    }
  }

  $themepath = (function_exists('path_to_subtheme')) ? path_to_subtheme() : drupal_get_path('theme', $theme);

  $sitestyle = variable_get('mimemail_sitestyle', 1);
  $mailstyle = $themepath .'/mail.css';

  $css_all = drupal_add_css();
  $css_files_mail = $css_files_screen = array();
  foreach ($css_all as $media => $types) {
    foreach ($types as $type => $file) {
      // Gather and always include CSS files with 'email' media.
      if ($media == 'email') {
        $css_files_mail[$media][$type] = $file;
      }
      // Gather and include other site style sheets if enabled.
      elseif ($type == 'theme' && ($media == 'all' || $media == 'screen')) {
        $css_files_screen[$media][$type] = $file;
      }
    }
  }
  $styles = _mimemail_css_file_paths($css_files_mail);

  // Check for the existence of a mail.css file in the current theme folder.
  if (@file_exists($mailstyle)) {
    array_push($styles, $mailstyle);
  }
  // When no mail.css was found, include site style sheets if enabled.
  elseif ($sitestyle) {
    // Grab local.css if it exists (support for Fusion based themes).
    $local = $themepath . '/css/local.css';
    if (@file_exists($local)) {
      $css_files_screen['all']['theme'][$local] = TRUE;
    }
    $styles = array_merge($styles, _mimemail_css_file_paths($css_files_screen));
  }

  // Process each style sheet
  $css = '';
  foreach ($styles as $style) {
    if (!empty($style) && @file_exists($style)) {
      $css .= @file_get_contents($style);
    }
  }

  // Regexp to match comment blocks.
  $comment     = '/\*[^*]*\*+(?:[^/*][^*]*\*+)*/';
  // Regexp to match double quoted strings.
  $double_quot = '"[^"\\\\]*(?:\\\\.[^"\\\\]*)*"';
  // Regexp to match single quoted strings.
  $single_quot = "'[^'\\\\]*(?:\\\\.[^'\\\\]*)*'";

  // Perform some safe CSS optimizations. (derived from core CSS aggregation)
  $css = preg_replace_callback(
    "<$double_quot|$single_quot|$comment>Sus",  // Match all comment blocks along
    "_mimemail_process_comment",                // with double/single quoted strings
    $css);                                      // and feed them to _mimemail_process_comment().
  $css = preg_replace(
    '<\s*([@{}:;,]|\)\s|\s\()\s*[^\n\S]>S',  // Remove whitespace around separators,
    '\1',                                    // but keep space around parentheses
    $css);                                   // and new lines between definitions.

  // End the file with a new line.
  $css .= "\n";

  // Wordwrap to adhere to RFC821
  $css = wordwrap($css, 700);
  $variables['css'] = $css;

   // Process mailkey to be a proper CSS class.
  $variables['mailkey'] = 'mail-'. str_replace('_', '-', $variables['mailkey']);
}

/**
 * Process comment blocks. (derived from core CSS aggregation)
 *
 * This is the callback function for the preg_replace_callback()
 * used in drupal_load_stylesheet_content(). Support for comment
 * hacks is implemented here.
 */
function _mimemail_process_comment($matches) {
  static $keep_nextone = FALSE;
  // Quoted string, keep it.
  if ($matches[0][0] == "'" || $matches[0][0] == '"') {
    return $matches[0];
  }
  // End of IE-Mac hack, keep it.
  if ($keep_nextone) {
    $keep_nextone = FALSE;
    return $matches[0];
  }
  switch (strrpos($matches[0], '\\')) {
    case FALSE :
      // No backslash, strip it.
      return '';
    case drupal_strlen($matches[0])-3 :
      // Ends with \*/ so is a multi line IE-Mac hack, keep the next one also.
      $keep_nextone = TRUE;
      return '/*_\*/';
    default :
      // Single line IE-Mac hack.
      return '/*\_*/';
  }
}

/**
 * Convert an array of CSS files to an array of file paths.
 */
function _mimemail_css_file_paths($css) {
  return explode("\n", preg_replace('|<link.*href="'. base_path()
                        .'([^"?]*)[?"].*|', '\1', drupal_get_css($css)));
}
