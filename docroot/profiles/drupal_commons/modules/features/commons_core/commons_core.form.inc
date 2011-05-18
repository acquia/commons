<?php

/**
 * @file
 *   Form building and altering functions
 */
 
/**
 * Implementation of hook_form_FORM_ID_alter()
 * 
 * Alter the OG Features form
 */
function commons_core_form_og_features_feature_form_alter(&$form, &$form_state) {
  // Reorder the group features
  foreach ($form as $key => $item) {
    switch ($key) {
      case 'feature-commons_blog';
        $form[$key]['#weight'] = -100;
        break;
      case 'feature-commons_discussion';
        $form[$key]['#weight'] = -90;
        break;
      case 'feature-commons_wiki';
        $form[$key]['#weight'] = -80;
        break;
      case 'feature-commons_document';
        $form[$key]['#weight'] = -70;
        break;
      case 'feature-commons_poll';
        $form[$key]['#weight'] = -60;
        break;
      case 'feature-commons_event';
        $form[$key]['#weight'] = -50;
        break;
      case 'feature-commons_group_aggregator';
        $form[$key]['#weight'] = -40;
        break;
      case 'feature-commons_shoutbox';
        $form[$key]['#weight'] = -30;
        break;
    } 
  }
}

/**
 * Implementation of hook_form_FORM_ID_alter()
 * 
 * Optionally restrict voting only to members of the group
 */
function commons_core_form_poll_view_voting_alter(&$form, &$form_state) {
  // Check the settings
  if (variable_get('commons_group_prevent_open_voting', 0)) { 
    // Extract the poll node itself
    if ($poll = $form['#node']) {
      commons_core_group_restrict_form($poll, $form, t('vote'), array('vote'));
    }
  }
}

/**
 * Implementation of hook_form_FORM_ID_alter()
 * 
 * Optionally restrict commenting to only members of the group
 */
function commons_core_form_comment_form_alter(&$form, &$form_state) {
  // Check the settings
  if (variable_get('commons_group_prevent_open_commenting', 0)) { 
    // The node ID is either located at node/id or comment/reply/id
    $node = (arg(0) == 'node') ? node_load(arg(1)) : node_load(arg(2));  
      
    // Make sure the node loaded correctly
    if ($node) {
      commons_core_group_restrict_form($node, $form, t('comment'));
    }
  }
}

/**
 * Implementation of hook_form_FORM_ID_alter()
 * 
 * Alter the Views exposed form
 */
function commons_core_form_views_exposed_form_alter(&$form, &$form_state) {
  switch ($form['#id']) {
    // The "My unread" tab on the "My content" section
    case 'views-exposed-form-og-my-content-page-2':
    // The "All Content" tab on the "My content" section
    case 'views-exposed-form-og-my-content-page-1':
    // The "Recent group content" block found on group home pages
    case 'views-exposed-form-og-content-tracker-panel-pane-1':
      // The exposed filter for node type contains all nodes on the site
      // We want to limit it to group post types only
      if (isset($form['type'])) {
        foreach ($form['type']['#options'] as $type => $name) {
          if ($type != 'All' && !og_is_group_post_type($type)) {
            unset($form['type']['#options'][$type]);
          }
        }
      }
      break;
  }
}

/**
 * Implementation of hook_form_FORM_ID_alter()
 * 
 * Alter the Tagging admin settings form
 */
function commons_core_form_tagging_admin_settings_alter(&$form, &$form_state) {
  // Remove checkbox
  unset($form['tagging_show_suggestion_example']);
  
  // Add a field to supply static suggestions
  $form['commons_tag_suggestions'] = array(
    '#type' => 'textarea',
    '#title' => t('Static tag suggestions'),
    '#description' => t('Enter a comma-separated list of terms that will show up as tag suggestions when creating content items.'),
    '#weight' => -5,
    '#default_value' => variable_get('commons_tag_suggestions', ''),
  );
}

/**
 * Alter a node form
 */
function commons_core_node_form_alter(&$form, &$form_state) {
  // Extract the node
  $node = $form['#node'];
    
  // Remove default "Promoted to Front Page" option
  unset($form['options']['promote']);
  
  // Check if this is a group type
  if (module_exists('og')) {
    if (og_is_group_type($node->type)) {
      // Make user's aware of the max length
      $maxlength = $form['og_description']['#maxlength'];
      $form['og_description']['#description'] = $form['og_description']['#description'] . ' (' . t('!maxlength characters allowed', array('!maxlength' => $maxlength)) . ')'; 
      
      // Groups don't have titles, they have names
      $form['title']['#title'] = t('Name');
        
      // Add og options to a fieldset
      $form['og_options'] = array(
        '#type' => 'fieldset',
        '#title' => t('Group options'),
     );
        
      $form['og_options']['og_selective'] = $form['og_selective'];
      $form['og_options']['og_directory'] = $form['og_directory'];
      $form['og_options']['og_private'] = $form['og_private'];
      $form['og_options']['og_register'] = $form['og_register'];
      unset($form['og_selective']);
      unset($form['og_directory']);
      unset($form['og_register']);
      unset($form['og_private']);
    }
  }
}

/**
 * Alter a views bulk operations form
 */
function commons_core_views_bulk_operations_form_alter(&$form, &$form_state) {
  // Move operation controls above the content
  $form['submit']['#weight'] = -100; 
}

/**
 * Alter a form based on the current user's group membership status
 * 
 * If the current user is not a member of any of the given group(s)
 * associated with the $node, then remove $elements from the form
 * 
 * @param $node
 *   The group post node
 * @param $form
 *   The form to alter, passed in as reference
 * @param $action
 *   A string representing the action that is being prevented (Eg, comment)
 * @param $elements
 *   The form element identified to remove. If omitted, the entire form will be
 *   removed
 */
function commons_core_group_restrict_form($node, &$form, $action, $elements = array()) {
  // Make sure OG is enabled  
  if (!module_exists('og')) {
    return; 
  }
  
  // Determine which groups the poll belongs to
  $groups = og_get_node_groups($node);
        
  // Only act if this poll is part of a group
  if (count($groups)) {
    $access = FALSE;
          
    // Iterate through the groups, checking for membership
    foreach ($groups as $id => $name) {
      if (og_is_group_member($id)) {
        // Indicate that the user is a member of at least one group
        $access = TRUE;
        break; 
      }
    }
        
    // If the user isn't a member of any of the groups, they can't
    // vote on this poll
    if (!$access) {
      // Unset the specified elements
      if (empty($elements)) {
        // If non specified, remove the whole form
        $form = '';
      }
      else {
        foreach ($elements as $element) {
          unset($form[$element]);
        }
      }
      
      // Let user know why they can't act
      $form['denied_message'] = array(
        '#type' => 'item',
        '#value' => t('You must be a member of the group to !action', array('!action' => $action)),
      );
    } 
  }
}
