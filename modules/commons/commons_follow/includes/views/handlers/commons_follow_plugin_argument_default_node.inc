<?php

/**
 * @file
 * Holds the class defining the Views plugin that returns the node IDS that a
 * user has subscribed to.
 */

class commons_follow_plugin_argument_default_node extends views_plugin_argument_default {

  /**
   * Get the default argument.
   */
  function get_argument() {
    if (!$nids = commons_follow_get_nids()) {
      return FALSE;
    }

    return implode(',', $nids);
  }
}
