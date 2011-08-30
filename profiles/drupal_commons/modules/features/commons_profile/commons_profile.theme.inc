<?php

/**
 * @file
 *   Theme callbacks for commons_profile
 */

/**
 * Render the content for the profile image and action links block
 * 
 * @param $picture
 *   The user picture
 * @param $links
 *   An array of action links
 * @param $account
 *   The user being viewed
 */
function theme_commons_profile_image_action_links_block($picture, $links, $account) {
  $content = '';
  
  // Add the picture
  $content .= $picture;
  
  // Add the links
  $content .= theme('links', $links);
  
  return $content;
}

/**
 * Render the autocomplete options on the "find a friend" form
 */
function theme_commons_profile_friend_autocomplete_item($name, $picture) {
  $content = '';
  
  // Determine the picture to user
  $picture = $picture ? $picture : variable_get('user_picture_default', '');
  
  // Add the picture
  $content .= '<span class="friend-autocomplete-picture">';
  $content .= $picture ? theme('imagecache', 'user_picture_meta', $picture): '';
  $content .= '</span>';
  
  // Add the name
  $content .= '<span class="friend-autocomplete-name">';
  $content .= $name;
  $content .= '</span>';
  
  return $content;
}
