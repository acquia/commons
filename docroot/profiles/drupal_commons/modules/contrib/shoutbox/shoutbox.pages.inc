<?php
// $Id: shoutbox.pages.inc,v 1.2.2.2 2010/08/10 02:29:35 mikestefff Exp $

/**
 * @file
 * Page callbacks for the shoutbox module.
 */

/**
 *  Shout Deletion callbacks
 */

/**
 * Function to handle deleting of shouts.
 *
 * @param shout_id
 *   The shout id to be deleted.
 * @return
 *   HTML asking the user to confirm.
 */
function theme_shoutbox_delete_form($shout) {
  _shoutbox_sanitize_shout($shout);
  $output = '';
  $output .= theme('shoutbox_post', $shout);
  $output .= drupal_get_form('shoutbox_delete_form', $shout);
  return $output;
}

/**
 * Display a confirmation page for publsihing
 * a moderated shout.
 *
 * @param shout_id
 *   The id of the shoutto be published.
 *
 * @return
 *   HTML asking the user to confirm.
 */
function theme_shoutbox_publish_form($shout) {
  _shoutbox_sanitize_shout($shout);
  $output = '';
  $output .= theme('shoutbox_post', $shout);
  $output .= drupal_get_form('shoutbox_publish_form', $shout);
  return $output;
}

/**
 * Function to handle moderation of shouts.
 *
 * @param shout_id
 *   The shout id to be unpublished.
 * @return
 *   HTML asking the user to confirm.
 */
function theme_shoutbox_unpublish_form($shout) {
  _shoutbox_sanitize_shout($shout);
  $output = '';
  $output .= theme('shoutbox_post', $shout);
  $output .= drupal_get_form('shoutbox_unpublish_form', $shout);
  return $output;
}


