<?php // $Id: template.preprocess-comment-wrapper.inc,v 1.1.2.4 2009/12/05 21:03:01 jmburnz Exp $
// adaptivethemes.com

/**
 * @file template.preprocess-comment-wrapper.inc
 */

global $theme;

$classes = array();

// Add support for Skinr module classes http://drupal.org/project/skinr
if (function_exists('node_skinr_data') && !empty($vars['skinr'])) {
  $classes[] = $vars['skinr'];
}
 
// Class for content types: "forum-comments", "blog-comments", etc.
if (theme_get_setting('cleanup_comment_wrapper_type')) {
  $classes[] = $vars['node']->type .'-comments';
}

/**
 * $classes is the variable that holds the comment-wrapper 
 * classes and is printed in comment-wrapper.tpl.php
 */
$vars['classes'] = implode(' ', $classes);