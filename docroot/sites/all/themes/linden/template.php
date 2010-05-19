<?php
/**
 * @file template.php
 */

// Don't include custom functions if the database is inactive.
if (db_is_active()) {
  // Include base theme custom functions.
  include_once(drupal_get_path('theme', 'adaptivetheme') .'/inc/template.custom-functions.inc');
}

/**
 * Add the color scheme stylesheet if color_enable_schemes is set to 'on'.
 * Note: you must have at minimum a color-default.css stylesheet in /css/theme/
 */
if (theme_get_setting('color_enable_schemes') == 'on') {
  drupal_add_css(drupal_get_path('theme', 'linden') .'/css/theme/'. get_at_colors(), 'theme');
}

/**
 * Override or insert variables into all templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered.
 */
/*
function linden_preprocess(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
*/

/**
 * Override or insert variables into the page templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered.
 */
/*
function linden_preprocess_page(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
*/

/**
 * Override or insert variables into the node templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered.
 */
/*
function linden_preprocess_node(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
*/

/**
 * Override or insert variables into the comment templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered.
 */
/*
function linden_preprocess_comment(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
*/

/**
 * Override or insert variables into the block templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered.
 */
/*
function linden_preprocess_block(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
*/

/*
 * Theme function for shoutbox posts.
 *
 * @param shout
 *   The shout to be themed.
 * @param links
 *   Links of possible actions that can be performed on this shout
 *   by the current user.
 * @param $alter_row_color
 *   Whether or not to alternate the row color for posts.  Should be set to
 *   FALSE for the page view.
 */
function linden_shoutbox_post($shout, $links = array(), $alter_row_color=TRUE) {
  global $user;  
  $tmp_user = user_load($shout->uid);
  if ($tmp_user->picture) {
    $user_pic = theme('imagecache', 'user_picture_meta', $tmp_user->picture, $alt, $title, $attributes);
  } else {
    $user_pic = theme('imagecache', 'user_picture_meta', 'default-user.png', $alt, $title, $attributes);
  }

  //Gather moderation links
  if ($links) {
    foreach ($links as $link) {
      $linkattributes = $link['linkattributes'];
      $link_html = '<img src="'. $link['img'] .'"  width="'. $link['img_width'] .'" height="'. $link['img_height'] .'" alt="'. $link['title'] .'" class="shoutbox-imglink">';
      $link_url = 'shoutbox/'. $shout->shout_id .'/'. $link['action'];
      $img_links = l($link_html, $link_url, array('html' => TRUE)) . $img_links;
    }
  }
  
  //Generate user name with link
  if ($shout->uid > 0) {
    $user_name = l($shout->nick, 'user/' . $shout->uid);
  }
  else {
    //Anonymous
    $user_name = $shout->nick;  
  }

  //Generate title attribute
  $title = t('Posted ' . format_date($shout->created, 'custom', 'm/d/y') . ' at ' . format_date($shout->created, 'custom', 'h:ia') . ' by ' . $shout->nick);
  
  $shout_classes = "shoutbox-msg ";
  if ($alter_row_color) {
    $shout_classes .= (($shout->color) ? ("shout-odd ") : ("shout-even "));
  }

  //Check for moderation
  if ($shout->moderate == 1) {
    $shout_classes .= "shoutbox-unpublished ";
    $shout->shout .= t("(This shout is waiting for approval by a moderator.)");
  }
  
  //Check for specific user class
  if ($shout->uid == $user->uid) {
    $user_class = ' shoutbox-current-user-name';
  }
  elseif ($shout->uid == 0) {
    $user_class = ' shoutbox-anonymous-user';  
  }
  
  return "<div class=\" $shout_classes \" title=\"$title\"><div class=\"shoutbox-admin-links\">$img_links</div>$user_pic<span class=\"shoutbox-user-name $user_class\">$user_name</span>: $shout->shout<span class=\"shoutbox-msg-time\">" . format_date($shout->created, 'custom', 'M jS g:ia') . "</span></div>\n";
  
}
