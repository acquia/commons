<?php
// $Id: views_slideshow.theme.inc,v 1.1.2.2.2.6 2010/04/13 06:21:51 redndahead Exp $

/**
 * The current element of the slideshow.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_main_section($id, $hidden_elements, $plugin) {
  $attributes['id'] = "${plugin}_main_${id}";
  $attributes['class'] = "${plugin}_main views_slideshow_main";
  $attributes = drupal_attributes($attributes);

  return "<div$attributes>$hidden_elements</div>";
}
