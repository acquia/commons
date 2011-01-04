<?php
// $Id: realname_content_profile.inc,v 1.1.2.8 2010/05/26 20:34:45 nancyw Exp $
/**
 * @file
 * Realname module support for Content Profile module.
 */

/**
 * Implementation of hook_profile_load();
 */
function content_profile_load_profile(&$account, $type = NULL) {
  $profile = content_profile_load($type, $account->uid);
  if (!$profile) {
    return;
  }
  $fields = content_fields(NULL, $type);
  
  foreach ($fields as $field_name => $field_attributes) {
    if (isset($profile->$field_name)) {
      $values = array();
      $contents = $profile->$field_name;
      foreach ($contents as $content) {
        if (isset($content['value'])) {
          $values[] = $content['value'];
        }
        else {
          $values[] = content_format($field_name, $content);
        }
      }
      if (empty($account->{$field_name})) {
        switch (count($values)) {
          case 0:
            $account->{$field_name} = NULL;
            break;
          case 1:
            $account->{$field_name} = $values[0];
            break;
          default:
            $account->{$field_name} = $values;
        }
      }
    }
  }
  
//  $account->title = $profile->title; // http://drupal.org/node/606364
}

function realname_content_profile_get_types() {
  return content_profile_get_types('names');
}

function realname_content_profile_get_fields($current, $type) {
  $fields = $links = array();
  $all_fields = content_fields(NULL, $type);
  if ($all_fields) {
    foreach ($all_fields as $field_name => $field_attributes) {
      // If it's not they type we are looking for, then skip the field.
      if ($field_attributes['type_name'] != $type) {
        continue;
      }
      switch ($field_attributes['type']) {
        case 'text':
          if ($field_attributes['multiple']) {
            drupal_set_message(t('The RealName module does not currently support fields with multiple values, such as @fld.', array('@fld' => $field_name)), 'warning');
          }
          else {
            $selected = array_key_exists($field_name, $current);
            $fields[$field_name] = array(
              'title' => $field_attributes['widget']['label'],
              'weight' => $selected ? $current[$field_name] : 0,
              'selected' => $selected,
              );
          }
          break;

        case 'link':
          $links[$field_name] = $field_attributes['widget']['label'];
      }
    }
  }
  else {
    drupal_set_message(t('The !type content type has no fields to use.', array('!type' => $type)), 'error');
  }

  if (variable_get('realname_use_title', FALSE)) {
    $fields['title'] = array(
      'title' => t('Node title'),
      'weight' => isset($current['title']) ? $current['title']['weight'] : 0,
      'selected' => array_key_exists('title', $current),
      );
  }

  return array('fields' => $fields, 'links' => $links);
}

