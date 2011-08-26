<?php

/**
 * @file
 *   This file provides a preprocess function for the author pane used by
 *   Advanced Forum and Advanced Profile Kit.
 */

/**
 * Implementation of hook_preprocess_author_pane().
 */
function facebook_status_preprocess_author_pane(&$variables) {
  $variables += array(
    'facebook_status' => '',
    'facebook_status_status' => '',
    'facebook_status_time' => '',
  );
  $status = _facebook_status_get_status_fast($variables['account']->uid);
  if (!facebook_status_user_access('view', $status)) {
    return;
  }
  //Show nothing if the status is blank.
  if (!empty($status->message)) {
    //The fully themed status, including the themed username (if settings permit) and the time.
    $variables['facebook_status'] = facebook_status_show($status);
    //Just the status, safe but with no filters run over it.
    $variables['facebook_status_status'] = check_plain($status->message);
    //The formatted time the status was submitted.
    $variables['facebook_status_time'] = theme('facebook_status_time', $status->created);
  }
}
