<?php // $Id: template.custom-functions.inc,v 1.1.2.5 2009/12/24 01:47:01 jmburnz Exp $
// adaptivethemes.com

/**
 * @file template.custom-functions.inc
 */

/**
 * Clean a string of unwanted characters.
 *
 * @param $string
 *   The string
 * @return
 *   The converted string
 */
function safe_string($string) {
  $string = drupal_strtolower(preg_replace('/[^a-zA-Z0-9-]+/', '-', $string));
  return $string;
}

/**
 * Limit the length of a string.
 *
 * @param $string
 *   The string
 * @param $lenght
 *   The lenght of the trimmed string
 * @$ellipsis
 *
 * @return
 *   The converted string
 */
function wordlimit($string, $length = 50, $ellipsis = "...") {
  $words = explode(' ', strip_tags($string));
  if (count($words) > $length)
    return implode(' ', array_slice($words, 0, $length)) . $ellipsis;
  else
    return $string;
}

/**
 * Set a default color scheme and set a cookie.
 */
function get_at_colors() {
  $scheme = theme_get_setting('color_schemes');
  if (!$scheme) {
    $scheme = 'colors-default.css';
  }
  if (isset($_COOKIE["atcolors"])) {
    $scheme = $_COOKIE["atcolors"];
  }
  return $scheme;
}