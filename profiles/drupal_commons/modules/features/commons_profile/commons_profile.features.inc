<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function commons_profile_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_views_api().
 */
function commons_profile_views_api() {
  return array(
    'api' => '2',
  );
}

/**
 * Implementation of hook_strongarm_alter().
 */
function commons_profile_strongarm_alter(&$items) {
  // Ensure that the user_terms vocabularies variable refers to
  // the correct vid.
  if (isset($items['user_terms_vocabs'])) {
    $commons_tags_vid = variable_get('commons_tags_vid', 1);
    $items['user_terms_vocabs']->value = array($commons_tags_vid => $commons_tags_vid);
  }
}