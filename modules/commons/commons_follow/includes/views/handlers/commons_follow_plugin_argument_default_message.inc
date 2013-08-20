<?php

/**
 * @file
 * Holds the class defining the Views plugin that returns the message IDS that a
 * user has subscribed to.
 */

class commons_follow_plugin_argument_default_message extends views_plugin_argument_default {

  /**
   * Get the default argument.
   */
  function get_argument() {
    if (!$mids = commons_follow_get_followed_message_ids()) {
      return FALSE;
    }

    return implode(',', $mids);
  }
}
