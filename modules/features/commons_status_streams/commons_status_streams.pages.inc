<?php

/**
 * The page callback for the main stream page
 */
function commons_status_streams_stream_page($group_node = NULL) {
  // Set the title
  // We do this here because we want the tab title and page title
  // to be different.
  if (!empty($group_node->title)) {
    drupal_set_title($group_node->title);
  }
  else {
    drupal_set_title(t('Activity stream'));  
  }
  
  
  // If the user is anonymous, prompt them to login or register
  if (user_is_anonymous()) {
    $prompt = array();
    $prompt[] = t('Share your own status updates, and follow the updates & activities of others by !register.', array('!register' => l(t('creating your own account'), 'user/register')));
    $prompt[] = t('Or, remember to !login If you already have an account.', array('!login' => l(t('log in'), 'user/login')));
    return implode('<br/><br/>', $prompt);
  }
  // Check access to view/use activity messages
  else if (user_access('view all activity messages')) {
    return theme('facebook_status_form_display', NULL, NULL, 'activity_log_stream');
  }
  // Logged in, but without access
  else {
    drupal_access_denied();
  }
}
