<?php
// $Id: ur_relationship.inc,v 1.1.2.1 2009/10/25 21:12:37 alexk Exp $

/**
 * @file
 * Plugin to provide access control based on user relationship.
 */

/**
 * Implement specially named hook_ctools_access().
 */
function user_relationships_panels_visibility_ur_relationship_ctools_access() {
  $args['ur_relationship'] = array(
    'title' => t("User Relationship"),
    'description' => t('Control access based on relationship between two users'),
    'callback' => 'user_relationships_panels_visibility_ctools_access_check',
    'default' => array('ur_relationship' => array()),
    'settings form' => 'user_relationships_panels_visibility_ctools_access_settings',
    'summary' => 'user_relationships_panels_visibility_ctools_access_summary',
    'required context' => array(
      new ctools_context_required(t('First User'), 'user'),
      new ctools_context_required(t('Second User'), 'user')),
  );

  return $args;
}

/**
 * Settings form for the user relationships access plugin
 */
function user_relationships_panels_visibility_ctools_access_settings(&$form, &$form_state, $conf) {

  $relationships = user_relationships_types_load();
  $options = array();
  foreach ($relationships as $key => $relationship) {
    $options[$key] = $relationship->name;
  }

  $form['settings']['ur_relationship'] = array(
    '#type' => 'checkboxes',
    '#options' => $options,
    '#title' => t('Allow if relationship between users is'),
    '#default_value' => $conf['ur_relationship'],
  );
}

/**
 * Check for access based on relationship.
 */
function user_relationships_panels_visibility_ctools_access_check($conf, $context) {

  if (empty($context) || count($context) != 2 || empty($context[0]->data) || empty($context[1]->data)) {
    return FALSE;
  }
  $account1 = $context[0]->data;
  $account2 = $context[1]->data;

  $relationships = user_relationships_load(array("between" => array($account1->uid, $account2->uid)));
  foreach ($relationships as $relationship) {
    // If this relationship is in the conf file
    if (!empty($conf['ur_relationship'][$relationship->rtid])) {
      // If no approval required, or approval has been granted
      if ( !$relationship->requires_approval || ($relationship->requires_approval && $relationship->approved) ) {
        // If not a oneway, or else it is a oneway requested by this user
        if (!$relationship->is_oneway || ($relationship->requester_id == $account1->uid)) {
          return TRUE;
        }
      }
    }
  }
  return FALSE;

}


/**
 * Provide a summary description based upon the checked relationships.
 */
function user_relationships_panels_visibility_ctools_access_summary($conf, $context) {
  if (!isset($conf['ur_relationship'])) {
    return t('Error, unset permission');
  }
  $account1 = $context[0]->data;
  $account2 = $context[1]->data;

  $relationship_types = user_relationships_types_load();

  $names = array();
  foreach (array_filter($conf['ur_relationship']) as $rtid) {
    $names[] = check_plain($relationship_types[$rtid]->name);
  }

  if (empty($names)) {
    return t('@id1 can have any relationship to @id2', array('@id1' => $context[0]->identifier, '@id2' => $context[1]->identifier));
  }

  return format_plural(count($names), '@id1 must have relationship "@rtids" to @id2', '@id1 can have relationships:  "@rtids" to @id2', array('@rtids' => implode(', ', $names), '@id1' => $context[0]->identifier, '@id2' => $context[1]->identifier));
}


