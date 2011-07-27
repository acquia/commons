<?php

/**
 * Implementation of hook_og_features_registry()
 *
 * Register your feature(s) with og_features so it can be toggled within
 * a given group
 * 
 * @return
 *   An array of information used to register your feature with 
 *   og_features
 */
function hook_og_features_registry() {
  $registry = array();
  
  // Feature: my_feature
  $feature = new stdClass;
  // The feature id
  $feature->id = 'my_feature';
  // The name that will show up on the feature toggle form
  $feature->name = t('Blog');
  // The description that will show up on the feature toggle form
  $feature->description = t('Provide a simple blog for your group');
  // The components of the feature that will be enabled/disabled
  $feature->components = array(
    'views' => array(
      'og_tab_blogs',
    ),
    'node' => array(
      'blog',
    ),
    'context' => array(
      'group_blogs',
    ),
    'path' => array(
      'node/%node/aggregator',
    ),
    'pane' => array(
      'og_content_tracker-panel_pane_1',
    ),
    'og link' => array(
      'og_invite',  // The key of the link in the group details block
    ),
  );
  // It's recommended that you key the feature with the name of the 
  // module/feature that is supplying this, so that any custom page
  // callbacks provided by this module/feature become disabled within
  // the group
  $registry[$feature->id] = $feature;
  
  // Feature: my_second_feature
  $feature = new stdClass;
  // You can continue to add as many as you'd like
  
  return $registry;
}

/**
 * Implementation of hook_og_features_registry_alter()
 * 
 * Alter the registry which contains information from hook_og_features()
 * before it's cached to the database
 * 
 * @param &$registry
 *   The og features registry
 */
function hook_og_features_registry_alter(&$registry) {
  // Change the name of the my_feature feature
  $registry['my_feature']->name = t('Fun feature');
}

/**
 * Implementation of hook_og_features_toggle()
 * 
 * Invoked whenever features are enabled/disabled inside a group
 * 
 * @param $group
 *   The group that toggled features
 * @param $features
 *   An array, keyed by feature name, with a value of their status
 *   inside the group
 */
function hook_og_features_toggle($group, $features) {
  if (!$features['my_feature']) {
    db_query("DELETE FROM {og_things} WHERE nid = %d", $group->nid);
  }
}

/**
 * Implementation of hook_og_features_disabled_alter()
 * 
 * Alter the list of disabled features for a given node upon
 * loading them
 * 
 * @param &$disabled
 *   The array of features disabled for the given group
 * @param $group
 *   The group being loaded
 */
function hook_og_features_disabled_alter(&$disabled, $group) {
  // Force-disable a feature for all but a given group
  if ($group->nid != variable_get('special_group_nid', 0)) {
    $disabled['special_feature'] = 'special_feature';
  }
}

/**
 * USEFUL FUNCTIONS ===========================================
 * 
 * @see
 *   og_features_feature_is_disabled($feature, $group = NULL)
 *     Determine if a feature is disabled for a given group, or the 
 *     current group if group is omitted.
 * 
 *   og_features_component_is_disabled($type, $name, $group = NULL)
 *     Determine if a certain feature component is disabled
 * 
 *   og_features_in_feature($feature, $type, $name)
 *     Determine if a feature component is part of a certain feature 
 *     (applies only to what is supplied in hook_og_features())
 */
 

