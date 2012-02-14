<?php

/**
 * Implementation of hook_strongarm().
 */
function commons_profile_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_terms_vocabs';
  $strongarm->value = array(
    1 => '1',
  );
  $export['user_terms_vocabs'] = $strongarm;

  return $export;
}
