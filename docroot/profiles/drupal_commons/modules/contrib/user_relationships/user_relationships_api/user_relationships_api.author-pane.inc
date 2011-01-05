<?php
// $Id: user_relationships_api.author-pane.inc,v 1.1.2.2 2010/12/22 09:34:01 alexk Exp $

/**
 * @file integration with Author Pane
 * @author Alex Karshakevich http://drupal.org/user/183217
 **/

/**
* Implementation of hook_preprocess_author_pane().
*/
function user_relationships_api_preprocess_author_pane(&$variables) {
  // Check if this preprocess needs to be run given who's calling it.
  if (!author_pane_run_preprocess('user_relationships_api', $variables['caller'])) {
    return;
  }

  global $user;
  $account = $variables['account'];

  // Anonymous users and users viewing their own account won't get a link.
  if (!$user->uid || !$account->uid || $user->uid == $account->uid) {
    return;
  }

  $rtids = variable_get('user_relationships_api_author_pane_rtids', 0);
  if (!is_array($rtids)) {
    $rtids = array($rtids);//wrap into array for now, while selection is single
  }
  if (!count($rtids)) {
    $return;
  }
  // Get a list of selected relationship types
  $all_rtypes = user_relationships_types_load();
  $rtypes = array();
  foreach ($rtids as $rtid) {
    $rtypes[] = $all_rtypes[$rtid];
  }
  
  foreach ($rtypes as $rtype) {
    $relationships = user_relationships_load(array('requester_id' => $user->uid, 'requestee_id' => $account->uid, 'rtid' => $rtype->rtid));
  
    if (count($relationships)) {
      // Existing relationship; need remove icon/link. (Despite the foreach,
      // there should only be one.)
      foreach ($relationships as $rtid => $relationship) {
        $link_label = t('Remove @name from @rel_plural_name', array('@name' => $account->name, '@rel_plural_name' => $relationship->plural_name));
        $css_class = str_replace(' ', '-', $relationship->name) .' author-pane-link user_relationships_popup_link author-relationship-remove-icon';
        //link to remove
        if (!isset($variables['user_relationships_api'])) {
          $variables['user_relationships_api'] = '';
        }
        $variables['user_relationships_api'] .= '<div class="author-pane-ur-link-item">';
        $variables['user_relationships_api'] .=
          l('<span>' . t('Remove @rel_name', array('@name' => $account->name, '@rel_name' => ur_tt("user_relationships:rtid:$relationship->rtid:name", $relationship->name))) . '</span>',
          "user/{$user->uid}/relationships/{$relationship->rid}/remove",
          array(
                'query' => drupal_get_destination(),
                'html' => TRUE,
                'attributes'  => array('title' => $link_label, 'class' => $css_class),
          ));
        $variables['user_relationships_api'] .= '</div>';
      }
    }
    else {
      //No existing relationship; need an add icon/link.
      if (!user_relationships_api_can_request($user, $rtype) || !user_relationships_api_can_receive($account, $rtype)) {
        continue;
      }
      $relationships_count = user_relationships_load(array('between' => array($user->uid, $account->uid)), array('count' => TRUE));
      $link_label = t('Add @rel_name', array('@rel_name' => ur_tt("user_relationships:rtid:$rtype->rtid:name", $rtype->name)));
      $css_class = str_replace(' ', '-', $rtype->name) .' author-pane-link user_relationships_popup_link author-relationship-add-icon';
      //add link
      if (!isset($variables['user_relationships_api'])) {
        $variables['user_relationships_api'] = '';
      }
      $variables['user_relationships_api'] .= '<div class="author-pane-ur-link-item">';
      $variables['user_relationships_api'] .=
        l('<span>' . t('Add @rel_name', array('@name' => $account->name, '@rel_name' => ur_tt("user_relationships:rtid:$rtype->rtid:name", $rtype->name))) . '</span>',
          "relationship/{$account->uid}/request/{$rtype->rtid}",
          array(
            'query' => drupal_get_destination(),
            'html' => TRUE,
            'attributes'  => array(
              'title' => t('Become @name\'s @rel_name', array('@name' => $account->name, '@rel_name' => ur_tt("user_relationships:rtid:$rtype->rtid:name", $rtype->name))),
              'class' => $css_class
            ),
          )
        );
      $variables['user_relationships_api'] .= '</div>';
    }
  }
}

/**
* Implementation of hook_author_pane_allow_preprocess_disable().
*/
function user_relationships_api_author_pane_allow_preprocess_disable() {
  return array('user_relationships_api' => 'User Relationships');
}
