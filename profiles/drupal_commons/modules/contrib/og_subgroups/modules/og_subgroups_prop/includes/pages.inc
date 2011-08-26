<?php

/**
 * Menu callback function. Override OG's unsubscribe confirm form
 */
function og_subgroups_prop_confirm_unsubscribe($form_state, $group, $account) {
  global $user;
  og_subgroups_include('tree');
  $form = array();
  $groups = array();

  // Determine the unsubscribe propagation directions
  $directions = array_filter(variable_get('og_subgroups_propagate_members_unsubscribe', array()));

  // Add all the groups in the direction specified
  foreach ($directions as $direction) {
    if ($direction) {
      foreach (_og_subgroups_prop_groups_by_direction($group, $direction) as $member) {
        // Check that the user is a member of this group
        if (isset($account->og_groups[$member->nid])) {
          // Make sure the user can unsubscribe from this group
          if (og_subgroups_prop_can_unsubscribe($member, $account)) {
            $groups[$member->nid] = l($member->title, "node/{$member->nid}");
          }
        }
      }
    }
  }

  // If the user being unsubscribed is the current user, we need to
  // change the wording of the messages
  if ($account->uid == $user->uid) {
    if (!empty($groups)) {
      $sub_message = t('By leaving the group !title, you will also be removed from the following groups: !groups', array('!title' => l($group->title, "node/{$group->nid}"), '!groups' => theme_item_list($groups)));
    }
   
    $message = t('Are you sure you want to leave the group %title?', array('%title' => $group->title));
    
    $confirm_text = t('Leave');
  }
  else {
    if (!empty($groups)) {
      $sub_message = t('By removing !name from the group !title, !name will also be removed from !groups', array('!name' => theme('username', $account), '!title' => l($group->title, "node/{$group->nid}"), '!groups' => theme_item_list($groups)));
    }
      
    $message = t('Are you sure you want to remove !name from the group %title?', array('!name' => theme('username', $account), '%title' => $group->title));

    $confirm_text = t('Remove');
  }
  
  // Set the page title to the confirmation message
  drupal_set_title($message);

  $form['group'] = array('#type' => 'value', '#value' => $group);
  $form['groups'] = array('#type' => 'value', '#value' => $groups);
  $form['account'] = array('#type' => 'value', '#value' => $account);
  $form['sub_message'] = array(
    '#prefix' => '<div class="container-inline">',
    '#value' => $sub_message,
    '#suffix' => '</div>',
    '#type' => 'item',
    '#access' => !empty($groups),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $confirm_text,
  );

  $form['cancel'] = array(
    '#type' => 'markup',
    '#value' => l(t('Cancel'), "node/{$group->nid}"),
  );

  $form['#submit'] = array('og_subgroups_prop_confirm_unsubscribe_submit');

  return $form;
}

/**
 * Submit handler
 *
 * @see og_subgroups_prop_confirm_unsubscribe
 */
function og_subgroups_prop_confirm_unsubscribe_submit($form, &$form_state) {
  global $user;
  
  // Extract needed form elements
  $account = $form_state['values']['account'];
  $group = $form_state['values']['group'];
  $groups = $form_state['values']['groups'];

  // Unsubscribe the user from the primary group
  // The propagation functions will take care of the rest
  og_delete_subscription($group->nid, $account->uid);
  
  // Add the primary group to the list of groups
  $groups[$group->nid] = l($group->title, "node/{$group->nid}");

  // See if the user being removed is the current user
  if ($user->uid == $account->uid) {
    // Message varies depending on the amount of groups left
    if (count($groups) > 1) {
      drupal_set_message(t('You have left from the following groups: !groups', array('!groups' => theme_item_list($groups))));
    }
    else {
      drupal_set_message(t('You have left the group !group', array('!group' => $groups[$group->nid])));
    }
  }
  else {
    // Message varies depending on the amount of groups left
    if (count($groups) > 1) {
      drupal_set_message(t('!user has been removed from the following groups: !groups', array('!user' => theme('username', $account), '!groups' => theme_item_list($groups))));
    }
    else {
      drupal_set_message(t('!user has been removed from the group !group', array('!user' => theme('username', $account), '!group' => $groups[$group->nid])));
    }  
  }

  // Determine where to go next. GHP if accessible, or else site front page.
  $form_state['redirect'] = node_access('view', $group) ? "node/{$group->nid}" : '<front>';
}
