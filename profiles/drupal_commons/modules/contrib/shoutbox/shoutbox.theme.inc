<?php

/**
 * @file
 *   Theme callbacks for the shoutbox module.
 */

/**
 * Load external files (JS & CSS)
 */
function theme_shoutbox_external_files() {
  drupal_add_css(drupal_get_path('module', 'shoutbox') .'/shoutbox.css');
  drupal_add_js('misc/jquery.form.js');
  drupal_add_js(drupal_get_path('module', 'shoutbox') .'/shoutbox-form.js', 'module');  
}

/**
 * Theme function of shoutbox actions. Actions are edit, delete, promote
 * and demote. NOTE: Function does not return html but rather an array
 * with the actions as keys. See code.
 */
function theme_shoutbox_links() {
  $links['edit']['action'] = 'edit';
  $links['edit']['title'] = 'Edit Shout';
  $links['edit']['img'] = base_path() . drupal_get_path('module', 'shoutbox') .'/images/icon_edit.png';
  $links['edit']['img_width'] = 15;
  $links['edit']['img_height'] = 15;
  $links['delete']['action'] = 'delete';
  $links['delete']['title'] = 'Delete Shout';
  $links['delete']['img'] = base_path() . drupal_get_path('module', 'shoutbox') .'/images/icon_delete.png';
  $links['delete']['img_width'] = 15;
  $links['delete']['img_height'] = 15;
  $links['publish']['action'] = 'publish';
  $links['publish']['title'] = 'Publish';
  $links['publish']['img'] = base_path() . drupal_get_path('module', 'shoutbox') .'/images/thumb_up.png';
  $links['publish']['img_width'] = 15;
  $links['publish']['img_height'] = 15;
  $links['unpublish']['action'] = 'unpublish';
  $links['unpublish']['title'] = 'Unpublish';
  $links['unpublish']['img'] = base_path() . drupal_get_path('module', 'shoutbox') .'/images/thumb_down.png';
  $links['unpublish']['img_width'] = 15;
  $links['unpublish']['img_height'] = 15;

  return $links;
}

/**
 * Theme function for shoutbox posts.
 *
 * @param shout
 *   The shout to be themed.
 * @param links
 *   Links of possible actions that can be performed on this shout
 *   by the current user.
 */
function theme_shoutbox_post($shout, $links = array()) {
  global $user;
  
  // Gather moderation links
  if ($links) {
    foreach ($links as $link) {
      $linkattributes = $link['linkattributes'];
      $link_html = '<img src="'. $link['img'] .'"  width="'. $link['img_width'] .'" height="'. $link['img_height'] .'" alt="'. $link['title'] .'" class="shoutbox-imglink"/>';
      $link_url = 'shout/'. $shout->shout_id .'/'. $link['action'];
      $img_links = l($link_html, $link_url, array('html' => TRUE, 'query' => array('destination' => drupal_get_path_alias($_GET['q'])))) . $img_links;
    }
  }
  
  // Generate user name with link
  $user_name = shoutbox_get_user_link($shout);

  // Generate title attribute
  $title = t('Posted !date at !time by !name', array('!date' => format_date($shout->created, 'custom', 'm/d/y'), '!time' => format_date($shout->created, 'custom', 'h:ia'), '!name' => $shout->nick));

  // Add to the shout classes
  $shout_classes = array();
  $shout_classes[] = 'shoutbox-msg';

  // Check for moderation
  if ($shout->moderate == 1) {
    $shout_classes[] = 'shoutbox-unpublished';
    $approval_message = '&nbsp;(' . t('This shout is waiting for approval by a moderator.') . ')';
  }
  
  // Check for specific user class
  $user_classes = array();
  $user_classes[] = 'shoutbox-user-name';
  if ($shout->uid == $user->uid) {
    $user_classes[] = 'shoutbox-current-user-name';
  }
  else if ($shout->uid == 0) {
    $user_classes[] = 'shoutbox-anonymous-user';  
  }
  
  // Build the post
  $post = '';
  $post .= '<div class="' . implode(' ', $shout_classes) . '" title="' . $title . '">';
  $post .= '<div class="shoutbox-admin-links">' . $img_links . '</div>';
  $post .= '<span class="' . implode(' ', $user_classes) . '">' . $user_name . '</span>:&nbsp;';
  $post .= '<span class="shoutbox-shout">' . $shout->shout . $approval_message . '</span>';
  $post .= '<span class="shoutbox-msg-time">';
  $format = variable_get('shoutbox_time_format', 'ago');
  switch ($format) {
    case 'ago';
      $post .=  t('!interval ago', array('!interval' => format_interval(time() - $shout->created)));
      break;
    case 'small':
    case 'medium':
    case 'large':
      $post .= format_date($shout->created, $format);
      break;
  }
  $post .= '</span>';
  $post .= '</div>' . "\n";

  return $post;
}

/**
 * Theme function for displaying the shoutbox page.
 *
 * @param $output
 *   The shout output data. See shoutbox_display_posts() 
 * @return
 *   String containing HTML formatted page.
 */
function theme_shoutbox_page($output) {
  $shouts = $output['rows'];
  
  if (!empty($shouts)) {
    $shouts = theme('table', NULL, $shouts); 
  }
  else {
    $shouts = t('There are currently no shouts');
  } 
  
  return "<div id=\"shoutbox-body\">\n" . $shouts . "</div>\n";
}

/**
 * Theme function for displaying the access denied message.
 *
 * @return
 *   String containing HTML formatted access denied message.
 */
function theme_shoutbox_post_forbidden() {
  return '<div class="shoutbox-msg">' . t('You\'re not permitted to post shouts.') . '</div>';
}

/**
 * Theme the link on the bottom of the block pointing to the shout page
 * 
 * @param $page_path
 *     Path to the shout page
 */
function theme_shoutbox_block_page_link($page_path) {
  return '<div class="shoutbox-all-shouts">' . l(t('All shouts'), $page_path) . '</div>';
}

/**
 * Theme the block message regarding auto-update interval
 * 
 * @param $interval
 *     The number of seconds the shouts auto-refresh
 */
function theme_shoutbox_interval_message($interval) {
  // Check if autoupdate is enabled
  if ($interval) {
    return '<div class="shoutbox-interval-msg">' . t('Shouts automatically update every !interval seconds', array('!interval' => $interval)) . '</div>';  
  }  
}
