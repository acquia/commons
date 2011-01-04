<?php
// $Id: realname_plugin_argument_validate_user.inc

/**
 * Override of style plugin. Replaces username with realname
 *
 */
class realname_plugin_argument_validate_user extends views_plugin_argument_validate_user {
  
  function validate_argument($argument) {
    $result = parent::validate_argument($argument);
    $this->argument->validated_title = realname_make_name($account);
    return TRUE;
  }
}

