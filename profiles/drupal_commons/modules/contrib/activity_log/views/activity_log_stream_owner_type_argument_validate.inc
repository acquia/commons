<?php
  
/**
 * @file
 *   Adds an option to validate arguments as stream owner types.
 */

/**
 * Validate whether an argument is a valid stream owner type.
 */
class activity_log_stream_owner_type_argument_validate extends views_plugin_argument_validate {
  var $option_name = 'validate_argument_activity_log_stream_owner_type';
  function validate_argument($argument) {
    return in_array($argument, array_keys(activity_log_get_rules_data_types()));
  }
}
